#include "bluedevice.h"
#include <QDebug>
#include <QTimer>
BlueDevice::BlueDevice()
{
    dbgr.name = "蓝牙设备";
    dbgr.dbg("启动");
    dbgr.Debug = DebugUseTcpON;
}

void BlueDevice::DiscoveryDevice(QString pattern_str, QString SvcUUID, FYBTDevice name)
{
    pattern_strA = pattern_str;
    SvcUUIDA = SvcUUID;
    Name = name;
    connect(Sendmsg_delayTimer, &QTimer::timeout, this, &BlueDevice::delayTimer_timeout);
    m_deviceDiscoveryAgent = new QBluetoothDeviceDiscoveryAgent(this);
    m_deviceDiscoveryAgent->setLowEnergyDiscoveryTimeout(30000);                                                  //设置连接超时时间
    connect(m_deviceDiscoveryAgent, &QBluetoothDeviceDiscoveryAgent::deviceDiscovered,
            this, &BlueDevice::m_deviceDiscoveryAgent_deviceDiscovered);
    connect(m_deviceDiscoveryAgent, &QBluetoothDeviceDiscoveryAgent::finished, this, [this]()
    {
        dbgr.dbg("蓝牙搜索器：搜索结束");                                                                            //蓝牙设备搜索完成后，筛选出目标设备进行连接，并进行相关信号与槽函数的绑定
        if(connectState == QLowEnergyController::DiscoveredState)
        {
            dbgr.dbg("蓝牙搜索器：蓝牙控制器连接完成");
        }
        else
        {
            dbgr.dbg("蓝牙搜索器：蓝牙控制器没有连接设备，继续新一轮搜索");
            m_deviceDiscoveryAgent->start();
        }
    });

    m_deviceDiscoveryAgent->start();
    dbgr.dbg("蓝牙搜索器：开始搜索蓝牙设备... 目标设备：" + pattern_strA + " 目标设备服务: " + SvcUUIDA);
    qWarning() << "蓝牙搜索器：开始搜索蓝牙设备... 目标设备：" + pattern_strA + " 目标设备服务: " + SvcUUIDA;                                                                    // 开始外围设备搜索
}

void BlueDevice::m_deviceDiscoveryAgent_deviceDiscovered()
{
    QList<QBluetoothDeviceInfo> device_list;                                                                      //存放搜索到到蓝牙设备列表
    device_list = m_deviceDiscoveryAgent->discoveredDevices();                                                    //遍历显示设备详情

    QList<QBluetoothDeviceInfo>::iterator it;
#ifndef DebugBtDeviceList
    dbgr.dbg("蓝牙搜索器：设备列表开始<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<");
#endif
    for (int i = 0; i < device_list.size(); ++i)
    {
        tmp_device = device_list[i];
        QString device_name = tmp_device.name();
#ifdef DebugBtDeviceList
        bool le = tmp_device.coreConfigurations() & QBluetoothDeviceInfo::LowEnergyCoreConfiguration;             //打印搜索出来的全部低功耗蓝牙
        if(le)
        {
            QString dbgStr = QString(le ? "*低功耗" : "") + "蓝牙名称:" + device_name
                    + " 地址:" + tmp_device.address().toString();
            dbgr.dbg(dbgStr);
        }
        //qDebug() << dbgStr;
#endif
        QRegExp rx(pattern_strA);
        if(rx.exactMatch(device_name) || tmp_device.address().toString() == pattern_strA)
        {
            m_deviceDiscoveryAgent->stop();
            if(connectState ==  QLowEnergyController::ConnectedState ||
                    connectState ==  QLowEnergyController::ConnectingState)
            {
                return;
            }
            dbgr.dbg("蓝牙搜索器：在设备列表里找到目标设备：");
            dbgr.dbg("蓝牙搜索器：停止蓝牙设备搜索");
            dbgr.dbg("蓝牙搜索器：------>目标设备名称:" + device_name + " ------>目标设备地址:" + getAddress(tmp_device));

            m_controler = QLowEnergyController::createCentral(tmp_device, this);                                  //创建匹配的蓝牙客户端
            connect(m_controler, &QLowEnergyController::connected, this, &BlueDevice::DeviceConnected);
            connect(m_controler, &QLowEnergyController::serviceDiscovered, this, &BlueDevice::serviceDiscovered);
            connect(m_controler, &QLowEnergyController::discoveryFinished, this, &BlueDevice::discoveryFinished);
            connect(m_controler, &QLowEnergyController::stateChanged, this, [this](QLowEnergyController::ControllerState state)
            {
                qDebug() << "蓝牙控制器：状态变化:" << state;
                dbgr.dbg("蓝牙控制器：状态变化:" + QString::number(state));
                connectState = state;
               if(state == QLowEnergyController::ClosingState)
               {
                   emit DeviceIsConnected(Name);
               }
            });
            connect(m_controler, &QLowEnergyController::connectionUpdated, this, [this](const QLowEnergyConnectionParameters &parameters)
            {
                dbgr.dbg("蓝牙控制器：连接状态变化:" + QString::number(parameters.latency()));
            });

            m_controler ->setRemoteAddressType(QLowEnergyController::PublicAddress);
            m_controler->connectToDevice();

            dbgr.dbg("蓝牙控制器：打开目标设备中...");
        }
    }
#ifdef DebugBtDeviceList
    dbgr.dbg("设备列表结束>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\r\n");
#endif
}

void BlueDevice:: DeviceConnected()
{
    dbgr.dbg("蓝牙控制器：目标设备打开!");

    m_controler->discoverServices();                                                                              //搜索服务
    dbgr.dbg("蓝牙控制器：查找目标设备中的服务...");
}

void BlueDevice::serviceDiscovered(QBluetoothUuid serviceUuid)
{
    dbgr.dbg("----蓝牙控制器：在目标设备中找到服务之一: " + serviceUuid.toString());

    if(serviceUuid == QBluetoothUuid(SvcUUIDA))
    {
        dbgr.dbg("----蓝牙控制器：找到目标服务--> " + SvcUUIDA);
        m_service = m_controler->createServiceObject(QBluetoothUuid(SvcUUIDA), this);
        dbgr.dbg("----蓝牙控制器：创建目标服务--> " + SvcUUIDA);
        if(m_service)
        {
            dbgr.dbg("----蓝牙服务器：创建目标服务成功，目标服务状态:" + QString::number(m_service->state()));
            connect(m_service, &QLowEnergyService::stateChanged, this, &BlueDevice::stateChanged);
            connect(m_service, &QLowEnergyService::characteristicChanged, this, &BlueDevice::m_service_characteristicChanged); // 通过监听特征对象的变化，不断获得数据。
            //connect(m_service, &QLowEnergyService::characteristicRead , this , &BlueDevice::m_service_characteristicRead);

            if(m_service->state() == QLowEnergyService::DiscoveryRequired)
            {
                dbgr.dbg("----蓝牙服务器：无记录，搜索特征中...");
                m_service->discoverDetails();
            }
            else
            {
                dbgr.dbg("----蓝牙服务器：有记录，不需要搜索特征");
                searchCharacteristic();
            }
        }
    }
}

void BlueDevice::stateChanged(QLowEnergyService::ServiceState state)
{                                                                                                  // 服务对象创建成功后，监听服务状态变化，如果状态变成已发现，则进行后续服务下特征对象获取
    dbgr.dbg( "----蓝牙服务器：目标服务状态有变化 " + QString::number(state));
    if(state == QLowEnergyService::ServiceDiscovered)                                              //发现服务, 建立characteristic对象实例
    {
        dbgr.dbg( "----蓝牙服务器：目标服务的特征搜索完成 " + QString::number(state));
        QList<QLowEnergyCharacteristic> Characteristics = m_service->characteristics();

        for (int i = 0; i < Characteristics.size(); ++i)                                           //列出子服务
        {
            Characteristic = Characteristics[i];
            dbgr.dbg("--------特征列表[" + QString::number(i) + "]： " + Characteristic.uuid().toString());
            m_notificationDesc = Characteristic.descriptor(QBluetoothUuid::ClientCharacteristicConfiguration);
            if (m_notificationDesc.isValid())
            {
                m_service->writeDescriptor(m_notificationDesc, QByteArray::fromHex("0100"));
                dbgr.dbg("--------蓝牙服务器：写入'0100'到特征列表[" + QString::number(i) + "]的客户端特征配置描述符" + m_notificationDesc.uuid().toString() + "中");
            }
        }

        if(Characteristics.size())
        {
            Characteristic = m_service->characteristic(Characteristics[0].uuid());

            dbgr.dbg("--------蓝牙服务器：根据特征列表[0]创建特征 : " + Characteristic.uuid().toString());
            QLowEnergyCharacteristic::PropertyTypes PropertyType = Characteristic.properties();
            dbgr.dbg("--------特征：属性类型: " + QString::number(PropertyType));

            if(SvcUUIDA == "53480001-534d-4152-542d-455343414c45")                                  //如果是身高体重仪
            {
                dbgr.dbg("********SH身高体重仪：" + Characteristic.uuid().toString());
                emit DeviceIsConnected(Name);
                return;
            }
            if(SvcUUIDA == "0000fff0-0000-1000-8000-00805f9b34fb")
            {
                dbgr.dbg("********智能眼镜：" + Characteristic.uuid().toString());
                if (Characteristic.properties() & QLowEnergyCharacteristic::Read)
                {
                    m_service->readCharacteristic(Characteristic);
                }
                emit DeviceIsConnected(Name);
                Sendmsg("3");                                                                      //如果是智能眼镜就全开
            }
            if(SvcUUIDA == "46590001-0000-1000-8000-00805f9b34fb")
            {
                dbgr.dbg("********智能视力表：" + Characteristic.uuid().toString());
                emit DeviceIsConnected(Name);
            }

        }

        QList<QLowEnergyDescriptor> descriptors = Characteristic.descriptors();
        for (int i = 0; i < descriptors.size(); ++i)
        {
            dbgr.dbg("----------------目标特征的描述符[" + QString::number(i) + "]: " + descriptors[i].name() + " UUID: "
                     + descriptors[i].uuid().toString() + " 值:"
                     + descriptors[i].value());
        }

        if(descriptors.size())Descriptor = descriptors[0];
        if(!Descriptor.isValid())
        {
            dbgr.dbg("----------------目标特征的描述符[0]无效");
        }
        else
        {
            m_service->readDescriptor(Descriptor);
            dbgr.dbg("----------------目标特征的描述符[0]类型: " + QString::number(Descriptor.type(), 16));
        }
    }
    if(state == QLowEnergyService::InvalidService)
    {
        dbgr.dbg("----目标服务无效");
        Power = 0 ;
    }
}

void BlueDevice::sendmsg(QString msg)
{
    if (Characteristic.properties() & QLowEnergyCharacteristic::WriteNoResponse ||
            Characteristic.properties() & QLowEnergyCharacteristic::Write)
    {
        m_service->writeCharacteristic(Characteristic, msg.toUtf8()   /*.toLatin1()*/);
    }
    dbgr.dbg("*发送字符 '" + msg + "' 到特征" + Characteristic.uuid().toString());
    Sendmsg_delayTimer->stop();
}

void BlueDevice::Sendmsg(QString msg ,int delay_ms)
{

    if(connectState == QLowEnergyController::DiscoveredState)
    {
        if(delay_ms)
        {
            MSG = msg ;
            Sendmsg_delayTimer->start(delay_ms);
        }
        else
        {
            sendmsg(msg) ;
        }
        return;
    }
}

void BlueDevice::m_service_characteristicChanged(QLowEnergyCharacteristic c, QByteArray value)
{
#if 0
    dbgr.dbg(QString("characteristicChanged state change: ") + c.uuid().toString() +
             QString(" value length: " ) + QString::number(value.length()) +
             QString(" value: " ) + QString(value.toHex()));
#endif
    C = c;
    if(c.uuid() != QUuid("0000fff4-0000-1000-8000-00805f9b34fb"))                                   //过滤眼镜心跳
    {
        dbgr.dbg("特征" + c.uuid().toByteArray() + "改变，值：" + value + "，Hex:" + value.toHex());
    }
}

//void BlueDevice::m_service_characteristicRead(QLowEnergyCharacteristic c, QByteArray value)
//{
//    Value = value;
//    Power = value.toHex().toInt();
//    C = c;
//    dbgr.dbg("读取" + c.uuid().toByteArray() + "特征，值：" + value + "，Hex:" + value.toHex());;
//}


void BlueDevice::searchCharacteristic(){
    if(m_service)
    {
        foreach (QLowEnergyCharacteristic c, m_service->characteristics())
        {
            if(c.isValid())
            {
                if (c.properties() & QLowEnergyCharacteristic::WriteNoResponse ||
                        c.properties() & QLowEnergyCharacteristic::Write)
                {
                    Characteristic = c;

                    qWarning() << "特征:" << c.uuid().toString() << "连接成功";
                    dbgr.dbg("特征:" + c.uuid().toString() + "连接成功");
                    if(c.properties() & QLowEnergyCharacteristic::WriteNoResponse)
                    {
                        m_writeMode = QLowEnergyService::WriteWithoutResponse;
                        qWarning() << "----------------特征:写入方式：无回复写";
                        dbgr.dbg("----------------特征:写入方式：无回复写");
                    }

                    else
                    {
                        m_writeMode = QLowEnergyService::WriteWithResponse;
                        qWarning() << "----------------特征:写入方式：有回复写";
                        dbgr.dbg("----------------特征:写入方式：有回复写");
                    }

                }
                if (c.properties() & QLowEnergyCharacteristic::Read)
                {
                    Characteristic = c;
                    qWarning() << "----------------特征:可读";
                    dbgr.dbg("----------------特征:可读");

                }
                m_notificationDesc = c.descriptor(QBluetoothUuid::ClientCharacteristicConfiguration);
                if (m_notificationDesc.isValid())
                {
                    m_service->writeDescriptor(m_notificationDesc, QByteArray::fromHex("0100"));
                    qWarning() << "----------------描述符客户端特征配置:有效，写入16进制'0100'激活";
                    dbgr.dbg("----------------描述符客户端特征配置:有效，写入16进制'0100'激活");
                }
            }
        }
    }
}


void BlueDevice::discoveryFinished()
{
    dbgr.dbg("蓝牙控制器：搜索设备服务完毕");
}

void BlueDevice::delayTimer_timeout()
{
    sendmsg(MSG);
}

QString BlueDevice::getAddress(QBluetoothDeviceInfo device) const                                  // mac和其他系统上address获取有少许差异，参见官方文档
{
#ifdef Q_OS_MAC
    // On OS X and iOS we do not have addresses,
    // only unique UUIDs generated by Core Bluetooth.
    return device.deviceUuid().toString();
#else
    return device.address().toString();
#endif
}

void BlueDevice::startAdvertisting()
{                                                                                               //https://stackoverflow.com/questions/52988257/qt-bluetooth-peripheral-segmentation-fault
    qWarning() << "初始化蓝牙控制器和蓝牙服务器并开始广播";

    Controller = QLowEnergyController::createPeripheral(this);                                              // 创建外围角色
    QLowEnergyServiceData ServiceData;
    {
        ServiceData.setType(QLowEnergyServiceData::ServiceTypePrimary);
        QBluetoothUuid ServiceUuid = QBluetoothUuid(quint32(0x46590001));
        ServiceData.setUuid(ServiceUuid);

        QLowEnergyCharacteristicData CharacteristicData;
        {
            QBluetoothUuid DescriptorUuid = QBluetoothUuid(quint32(0x46590003));
            QLowEnergyDescriptorData DescriptorData(DescriptorUuid, "FY-SVC-TV-BLE-DATA");
            {
                DescriptorData.setWritePermissions(true);
                DescriptorData.setReadPermissions(true);
            }
            CharacteristicData.addDescriptor(DescriptorData);
            QBluetoothUuid CharacteristicUuid = QBluetoothUuid(quint32(0x46590002));
            CharacteristicData.setUuid(CharacteristicUuid);
            CharacteristicData.setValue("FY-SVC-TV-010.2023");
            CharacteristicData.setProperties(QLowEnergyCharacteristic::Write |
                                             QLowEnergyCharacteristic::Read);
        }
        ServiceData.addCharacteristic(CharacteristicData);                                            //添加002
        QLowEnergyCharacteristicData CharacteristicData2;
        {
            QBluetoothUuid DescriptorUuid = QBluetoothUuid(QBluetoothUuid::ClientCharacteristicConfiguration);
            QLowEnergyDescriptorData DescriptorData(DescriptorUuid, "FY-SVC-TV-BLE-DATA");

            CharacteristicData2.addDescriptor(DescriptorData);
            QBluetoothUuid CharacteristicUuid = QBluetoothUuid(quint32(0x46590005));
            CharacteristicData2.setUuid(CharacteristicUuid);
            CharacteristicData2.setValue("FY-SVC-TV-010.2023");
            CharacteristicData2.setProperties(QLowEnergyCharacteristic::Notify);
        }
        ServiceData.addCharacteristic(CharacteristicData2);                                            //添加005
    }

    Service = Controller->addService(ServiceData);

    QLowEnergyAdvertisingParameters parameters;
    QLowEnergyAdvertisingData advertisingData;
    {
        advertisingData.setLocalName("fyairo001");                                                   //这步是必须的 即使不管用
        QList<QBluetoothUuid> QBluetoothUuidList;
        {
            QBluetoothUuid AdvertisingUuid = QBluetoothUuid(quint32(0x46590000));
            QBluetoothUuidList << AdvertisingUuid;
        }
        advertisingData.setServices(QBluetoothUuidList);
    }
    QLowEnergyAdvertisingData scanResponseData;

    Controller->startAdvertising(parameters, advertisingData, scanResponseData);
}

void BlueDevice::ServerServiceConnections()
{
    connect(Controller, &QLowEnergyController::connected, this, []()
    {
        qWarning() << "蓝牙控制器：客户端已经连接";
    });
    connect(Controller, &QLowEnergyController::disconnected, this, []()
    {
        qDebug() << "蓝牙控制器：客户端连接已经断开";
    });
    connect(Controller, &QLowEnergyController::stateChanged, this, [](QLowEnergyController::ControllerState state)
    {
        switch (state)
        {
        case QLowEnergyController::UnconnectedState:
            qDebug() << "蓝牙控制器：客户端未连接";
            break;
        case QLowEnergyController::ConnectingState:
            qDebug() << "蓝牙控制器：客户端正连接";
            break;
        case QLowEnergyController::ConnectedState:
            qDebug() << "蓝牙控制器：客户端已连接";
            break;
        case QLowEnergyController::DiscoveringState:
            qDebug() << "蓝牙控制器：正在搜索";
            break;
        case QLowEnergyController::DiscoveredState:
            qDebug() << "蓝牙控制器：搜索完毕";
            break;
        case QLowEnergyController::ClosingState:
            qDebug() << "蓝牙控制器：连接正在关闭";
            break;
        case QLowEnergyController::AdvertisingState:
            qDebug() << "蓝牙控制器：正在广播";
            break;
        }
    });
    connect(Controller, &QLowEnergyController::connectionUpdated, this, [](const QLowEnergyConnectionParameters &parameters)
    {
        qDebug() << "蓝牙控制器：客户端已更新" << parameters.latency();
    });

    connect(Service, &QLowEnergyService::stateChanged, this, [this](QLowEnergyService::ServiceState ServiceState)
    {
        if(ServiceState == QLowEnergyService::ServiceDiscovered)
        {
            QList<QLowEnergyCharacteristic> Characteristics = Service->characteristics();
            for (int i = 0; i < Characteristics.size(); ++i)
            {
                qDebug() << "蓝牙服务器：找到特征：<<<<<<<<<<<" << Characteristics[i].name() << Characteristics[i].uuid();

            }
            if(Characteristics.size())
            {
                Characteristic = Characteristics[0];
                Descriptor = Characteristic.descriptor(QBluetoothUuid::ClientCharacteristicConfiguration);                  //子服务.子项  这个动作是必须的
                if (Descriptor.isValid())
                {
                    Service->writeDescriptor(Descriptor, QByteArray::fromHex("0100"));                                      //身高体重仪和眼镜都要先写一下
                    qDebug()<<("蓝牙服务器：写入'0100'到服务:" + QString::number(0) + "的" + Characteristic.uuid().toString());
                }
                Characteristic = Service->characteristic(Characteristics[0].uuid());                                        //绑定子服务进行操作
            }
        }
    });
    if(Service->state() == QLowEnergyService::DiscoveryRequired)
    {
        Service->discoverDetails();
    }
    connect(Service, &QLowEnergyService::characteristicChanged, this, [this](QLowEnergyCharacteristic c, QByteArray value)
    {
        qDebug().noquote() << "蓝牙服务器：特征改变:" + c.uuid().toByteArray() + " 值：" + value + " 值的二进制" + value.toHex() + "   ";
        emit ValueArrive(c.uuid().toString(), value);
    });
    connect(Service, &QLowEnergyService::characteristicRead , this , [](QLowEnergyCharacteristic c, QByteArray value)
    {
        qDebug().noquote() << "蓝牙服务器：特征读取:" + c.uuid().toByteArray() + " " + value + "   " + value.toHex() + "   ";
    });
    connect(Service, &QLowEnergyService::descriptorRead, this, [](QLowEnergyDescriptor c, QByteArray value)
    {
        qDebug().noquote() << "蓝牙服务器：描述符:" + c.uuid().toByteArray() + " " + value + "   " + value.toHex() + "   ";
    });

    qWarning() << "使蓝牙控制器和蓝牙服务器响应信号..";
}

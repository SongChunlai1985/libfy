#ifndef BLUEDEVICE_H
#define BLUEDEVICE_H
#include <QObject>
#include<QBluetoothDeviceDiscoveryAgent>
#include<QBluetoothDeviceInfo>
#include<QBluetoothUuid>
#include<QBluetoothServiceInfo>
#include<QLowEnergyController>
#include<QLowEnergyService>
#include<QLowEnergyDescriptor>
#include<QLowEnergyAdvertisingParameters>
#include<QLowEnergyAdvertisingData>
#include<QLowEnergyCharacteristicData>
#include<QLowEnergyServiceData>
#include<QLowEnergyDescriptorData>
#include<QLowEnergyController>
#include<QLowEnergyConnectionParameters>
#include<QTimer>

#include<network/tcpwork.h>


enum FYBLEODER
{
    ONull,
    OStepStr,
    OSymbolImage,
    OResult,
    ORecord,

    Odistance,
    OCheckStart,
    Ocontinue,
    OCheckfunction,
    OStudentInfo1,

    OStudentInfo2,
    OStudentInfo3,
    OGlass_State,
    OGlass_Pow,
    OSymbolImageList1,

    OSymbolImageList2,
    OSymbolImageList3,
    OSymbolImageList4,
    OSymbolImageList5,
    OSymbolImageList6,

    OSymbolImageList7,
    OSymbolImageList8,
    OQuestion,
    OQrImage1,
    OQrImage2,

    OQrImage3
};

enum FYBTDevice
{
    FYBTDevice_UnKnow,
    FYBTDevice_TV,
    FYBTDevice_Glass,
    FYBTDevice_HightChecker
};

class BlueDevice: public QObject{
    Q_OBJECT

public:
    BlueDevice();
    void searchCharacteristic();
    void DiscoveryDevice(QString pattern_str = "Fy-Glass.*",
                         QString SvcUUID = "0000fff0-0000-1000-8000-00805f9b34fb" /*"53480001-534d-4152-542d-455343414c45"*/, FYBTDevice name = FYBTDevice_UnKnow);
    QString getAddress(QBluetoothDeviceInfo device) const;
    void stateChanged(QLowEnergyService::ServiceState state);
    void sendmsg(QString msg);
    void Sendmsg(QString msg, int delay_ms = 0);
    int Power = 0;
    tcpwork dbgr;
    QLowEnergyCharacteristic Characteristic;
    QLowEnergyService::WriteMode m_writeMode;
    QLowEnergyDescriptor m_notificationDesc;
    QLowEnergyDescriptor Descriptor;
    QByteArray Value;
    QLowEnergyCharacteristic C;                                         //避免未使用提示
    QLowEnergyController::ControllerState connectState = QLowEnergyController::UnconnectedState;
    FYBTDevice Name;

    QBluetoothDeviceInfo tmp_device;
    void serviceDiscovered(QBluetoothUuid serviceUuid);
    void discoveryFinished();
    void DeviceConnected();
    void delayTimer_timeout();
    void PowerReadTimer_timeout();
    void m_deviceDiscoveryAgent_deviceDiscovered();

    void m_service_characteristicChanged(QLowEnergyCharacteristic c, QByteArray value);
    //void m_service_characteristicRead(QLowEnergyCharacteristic c, QByteArray value);

    void startAdvertisting();
    void ServerServiceConnections();
    QLowEnergyService* Service;
    QLowEnergyController *Controller;
    QLowEnergyService *m_service;                            //服务对象实例

    QLowEnergyController *m_controler;                       //单个蓝牙设备控制器

    QLowEnergyAdvertisingParameters parameters;
    QLowEnergyAdvertisingData advertisingData;
    QLowEnergyAdvertisingData scanResponseData;

signals:
    void ValueArrive(QString c, QByteArray value);
    void DeviceIsConnected(FYBTDevice d);

private:

    QBluetoothDeviceDiscoveryAgent *m_deviceDiscoveryAgent;  //设备搜索对象

    QLowEnergyAdvertisingParameters m_parameters = QLowEnergyAdvertisingParameters();
    QLowEnergyAdvertisingData m_Data;

    QTimer *Sendmsg_delayTimer = new QTimer(this);
    QString MSG ;
    QString pattern_strA;
    QString SvcUUIDA;

};
#endif // BLUEDEVICE_H

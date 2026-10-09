FyVisionCheck Qt/C++ 多模块工具库
基于 Qt 的多模块 C++ 工具集合，覆盖 CSV/Excel、JSON、Base64、TCP/UDP/HTTP/HTTPS、BLE 蓝牙、摄像头二维码、音频采集与播放、OpenCV 图像处理、SQL 数据库封装、HTTP 服务器等场景。

1. 简介
本仓库是一组偏工程化的 Qt/C++ 源文件集合，主要面向视觉检测、蓝牙设备接入、音视频采集、网络通信、数据库记录、文件导入导出等应用。各模块之间耦合较低，可按需拷贝到 Qt 工程中使用。

典型能力包括：

CSV 文件读写，支持 GBK 编码转换、生成 JSON、自动生成列键。

XLSX 文件读取、工作表列表、写入。

JSON / QByteArray / QString 互转，快捷构造 JSON。

Base64 编码与解码。

TCP / UDP / HTTP / HTTPS 请求与简易 HTTP 服务器。

IoT 平台 Action 签名请求。

BLE 蓝牙中心设备与外围设备，支持扫描、连接、服务发现、特征读写、通知。

摄像头视频帧过滤，基于 OpenCV + ZBar 识别二维码。

音频播放、录音、DFT 频谱数据生成。

OpenCV 图像处理，绘制 E 字视标、生成二维码、Mat/QImage 转换。

SQL 语句生成、数据库连接、执行、查询结果转 JSON / Map。

学生与视力记录数据库控制器。

QAbstractTableModel 简易表格模型，支持 QJsonArray 数据加载。

2. 环境与依赖
Qt 模块
建议使用 Qt 5.x。部分代码使用 QTextCodec、QAudioInput、QAudioOutput、QtAndroid、QLowEnergyController 等 Qt 5 风格 API，迁移到 Qt 6 时需要调整。

常见需要：

qmake
QT += core gui network sql multimedia bluetooth qml quick
android {
    QT += androidextras
}
第三方库
OpenCV：opencv_core、opencv_imgproc、opencv_imgcodecs 等。

ZBar：二维码识别。

libqrencode：二维码生成。

xlsxio：XLSX 读写，提供 xlsxioread_* / xlsxiowrite_*。

Qt SQL 对应数据库驱动：SQLite、MySQL、ODBC、PostgreSQL 等。

C++ 标准
至少 C++11。

base64.cpp 中部分接口在 C++17 下提供 std::string_view 重载。

平台
代码中包含：

WIN32

Q_OS_ANDROID

Q_OS_MAC

因此可在 Windows、Android、Linux/macOS 上按条件编译，但部分路径和权限需要自行调整。

3. 构建配置示例
以下仅为 .pro 示例，实际库名和路径按本机环境调整：

qmake
QT += core gui network sql multimedia bluetooth qml quick

CONFIG += c++11

DEFINES += FyTcpDebug
# DEFINES += FyTcpDebugGBK
# DEFINES += DebugBtDeviceList

INCLUDEPATH += /usr/include/opencv4

LIBS += \
    -lopencv_core \
    -lopencv_imgproc \
    -lopencv_imgcodecs \
    -lzbar \
    -lqrencode \
    -lxlsxio_read \
    -lxlsxio_write
Android 权限示例：

xml
<uses-permission android:name="android.permission.RECORD_AUDIO"/>
<uses-permission android:name="android.permission.BLUETOOTH"/>
<uses-permission android:name="android.permission.BLUETOOTH_ADMIN"/>
<uses-permission android:name="android.permission.ACCESS_FINE_LOCATION"/>
<uses-permission android:name="android.permission.INTERNET"/>
<uses-permission android:name="android.permission.ACCESS_NETWORK_STATE"/>
4. 模块与文件说明
文件	主要类/函数	功能	主要依赖
base.cpp	in、rnd、Tan、fyDiv、int2byte、byte2int、getMyIp、getScreenDPI、checkPermission、GetCurrentTime、getCurrentMSecsSinceEpoch、toQDateTime	通用工具函数，时间解析、字节转换、权限检查、屏幕 DPI、本机 IP	Qt Core/Gui/Network，Android
base64.cpp	base64_encode、base64_decode、base64_encode_pem、base64_encode_mime	Base64 编解码，支持 URL-safe、PEM/MIME 换行	无
fjson.cpp	JsonObject2ByteArray、ByteArray2JsonObject、String2JsonObject、JsonObject2String、mkjson、mkjsonJ、shortJson	JSON 与字节/字符串互转，快捷构造 JSON	Qt Core
csvfile.cpp	csvfile	CSV 读取、写入、GBK 编解码、转 JSON、自动列键	Qt Core
msxlsx.cpp	msxlsx	XLSX 读取、工作表列表、写入	xlsxio
iotsdk.cpp	iotSDK	IoT 平台 Action 请求，SHA1 签名，HTTPS POST	Qt Network
httpwork.cpp	httpwork	HTTP 登录取 token，GET/POST/PUT 请求	Qt Network
httpserver.cpp	httpserver	简易 HTTP 服务器，静态文件响应，JSON 转 HTML 表格	Qt Network
tcpwork.cpp	tcpwork	TCP 调试客户端/服务端，连接状态与调试输出	Qt Network
udpwork.cpp	udpwork	UDP 发送与调试输出	Qt Network
mw.cpp	mw	UDP 接收示例，绑定端口并打印数据报	Qt Network
bluedevice.cpp	BlueDevice	BLE 中心/外围设备，扫描、连接、服务、特征、通知、写入	Qt Bluetooth
camerafilter.cpp	CameraFilter、CameraFilterRunnable	QVideoFrame 过滤，OpenCV 灰度化，ZBar 二维码识别	Qt Multimedia、OpenCV、ZBar
audioplayer.cpp	audioplayer	简单音频输入/输出初始化	Qt Multimedia
audiorecorder.cpp	AudioRecorder	音频采集、DFT、频谱数据生成并发送信号	Qt Multimedia、OpenCV
fcv.cpp	fcv	OpenCV 图像处理，E 字视标绘制，二维码生成，Mat 转 data URL	OpenCV、libqrencode
sqlOderMaker.cpp	SqlOderMaker、Variant2String	生成建表、插入、更新、查询、删除 SQL	Qt SQL
DataBaseCommander.cpp	DataBaseCommander	数据库连接，执行 SQL，结果转 JSON / Map	Qt SQL
DatabaseController.cpp	DatabaseController	业务数据库控制器，学生表、视力记录表	Qt SQL
easytablemodel.cpp	EasyTableModel	QAbstractTableModel 子类，QJsonArray 加载表格数据	Qt Core/QML
fysvcinterface.cpp	fySvcInterface	登录、登出、上传记录接口	Qt Network
gps.cpp	无	当前仅包含头文件，占位模块	-
main.cpp	main	示例入口，启动 mw	Qt Core
5. 主要 API 与用法
5.1 CSV 读写
cpp
csvfile csv;
csv.init("data.csv");

int rows = csv.readcsv();
QStringList keys = csv.autoKeys(10);
QJsonObject tableJson = csv.getJson(keys);

csv.maketable("学校", "schoolId", "schoolUid", classList, studentList);
csv.writecsv("标题", colNames);
说明：

init 默认使用 GBK 编解码。

readcsv 按逗号分割，适合简单 CSV。

getJson 可将表格行按 keys 转成 JSON。

autoKey 生成类似 k__0000_A 的列键。

5.2 XLSX 读写
cpp
msxlsx xlsx;
QList<QVariantList> table = xlsx.read("data.xlsx");
QVariantList sheets = xlsx.sheetList("data.xlsx");
xlsx.write("out.xlsx", table);
5.3 JSON 与 Base64
cpp
QJsonObject obj;
obj.insert("name", "test");

QByteArray bytes = JsonObject2ByteArray(obj);
QJsonObject obj2 = ByteArray2JsonObject(bytes);
QString json = JsonObject2String(obj2);

std::string encoded = base64_encode("hello", false);
std::string decoded = base64_decode(encoded, false);
5.4 TCP / UDP / HTTP
cpp
httpwork http;
QString token = http.getkey();

QString message;
QString result;
http.SendAndGetText("http://example.com/api", POST, "{\"a\":1}", message, result, token);
cpp
udpwork udp;
udp.send("hello", QHostAddress("192.168.1.10"), 12345);
udp.dbg("调试信息");
cpp
tcpwork tcp;
tcp.name = "Debug";
tcp.dbg("hello");
5.5 简易 HTTP 服务器
cpp
httpserver server;
server.httpport = 8080;
server.init();
支持：

监听端口。

处理 GET 请求。

返回 assets: 静态文件。

将查询参数解析为 JSON。

通过 httpquerry 信号交给业务处理。

5.6 IoT SDK
cpp
iotSDK sdk;
sdk.init(deviceSN, productSN, projectId, publicKey, region, key, url);

QByteArray reply = sdk.Action(
    "property/set",
    "{}",
    "{}",
    "/topic",
    "",
    ""
);
签名拼接顺序为：

text
Action + action +
DeviceSN + DeviceSN +
MessageContent + MessageContent +
ProductSN + ProductSN +
ProjectId + ProjectId +
Property + Property +
PublicKey + PublicKey +
Region + Region +
TopicFullName + TopicFullName +
Key
其中空字段不会加入。实际对接时必须与平台规则保持一致。

5.7 BLE 蓝牙
cpp
BlueDevice device;
device.DiscoveryDevice("目标设备名", "服务UUID", FYBTDevice);
connect(&device, &BlueDevice::DeviceIsConnected, [](FYBTDevice dev) {
    // 设备连接完成
});
device.Sendmsg("3");
支持：

低功耗蓝牙扫描。

按名称或地址匹配。

连接目标设备。

发现服务与特征。

写入描述符激活通知。

发送字符串到特征。

接收 characteristicChanged 并输出。

代码中针对以下服务 UUID 有专门处理：

53480001-534d-4152-542d-455343414c45：身高体重仪。

0000fff0-0000-1000-8000-00805f9b34fb：智能眼镜。

46590001-0000-1000-8000-00805f9b34fb：智能视力表。

也包含 BLE 外围设备广播示例 startAdvertisting()。

5.8 摄像头二维码识别
cpp
CameraFilter *filter = new CameraFilter;
QVideoFilterRunnable *runnable = filter->createFilterRunnable();

connect(filter, &CameraFilter::qrcode, [](QString code, QString extra) {
    qDebug() << code;
});
处理流程：

映射 QVideoFrame。

转为 OpenCV Mat。

转灰度。

裁剪中间区域。

缩放到 QrImgWidth。

翻转。

用 ZBar 扫描 Y800 图像。

发出 qrcode 信号。

5.9 音频
音频播放/采集初始化：

cpp
audioplayer player;
录音并输出频谱：

cpp
AudioRecorder recorder;
connect(&recorder, &AudioRecorder::soundArrive, [](cv::Mat data) {
    // 处理频谱数据
});
recorder.start();
// ...
recorder.stop();
5.10 OpenCV 图像与二维码
cpp
fcv vision;
vision.init();

int np = 0;
QString eImg = vision.drawE1(10.0, np);

QString qrImg;
vision.makeqr("https://example.com", qrImg);
支持：

Loadimage 加载 QImage。

cvMat2dataimage 将 Mat 编码为 data URL。

drawE0、drawE2、drawE1 绘制不同方向 E 字视标。

makeqr 使用 libqrencode 生成二维码。

5.11 SQL 与数据库封装
cpp
DatabaseInfo info;
info.DatabaseType = "QSQLITE";
info.DatabaseName = "data.db";

DataBaseCommander db;
db.ConnectDatabase(info);

QJsonObject result = db.ExecuteSqlOder2JsonObject("SELECT * FROM student");
QList<QMap<QString, QVariant>> rows = db.ExecuteSqlOder2MapList("SELECT * FROM student");
业务控制器：

cpp
DatabaseController controller;
controller.Init("user", "password");

controller.Students_tblstudent_Insert(studentInfo);
QJsonObject visionRows = controller.Students_tblvisionrecord_QuerryJ("*", "", "LIMIT 10");
controller.Students_tblvisionrecord_Insert(values);
5.12 EasyTableModel
适用于 QML/Qt Widgets 表格：

cpp
EasyTableModel model;
model.setHorHeader({"姓名", "性别", "班级"});
model.setInitData(jsonArray);
角色名：

value：显示值。

edit：编辑值。

6. 平台与权限注意事项
Android
录音需要 RECORD_AUDIO。

BLE 扫描需要蓝牙与定位权限。

checkPermission() 内部使用 QtAndroid::checkPermission 和 requestPermissionsSync。

资源路径使用 assets:/...。

Windows
fcv::init() 中硬编码了：

cpp
C:/code/fyvisioncheck/android/assets/0.png
如果工程路径不同，需要修改这些资源路径。

Linux/macOS
蓝牙地址获取方式在 macOS 下使用 device.deviceUuid()。

部分音频/摄像头设备索引依赖系统默认设备。

getMyIp() 会枚举所有 IPv4 地址。

7. 注意事项与已知限制
csvfile::readcsv() 使用简单逗号分割，不处理 CSV 引号、转义、换行字段。复杂 CSV 建议改用成熟解析器。

csvfile::readcsv() 在空表时提前 return 0，此时文件可能未关闭，建议调整顺序。

csvfile::writecsv() 中 ColNames 的索引从 1 开始参与写入，ColNames[0] 可能未被使用，调用时需确认标题与列名参数含义。

audioplayer 构造函数中直接启动输入与输出，且父对象为 nullptr，生命周期需要调用方管理。

camerafilter 中 QVideoFrame::map() 后未见 unmap()，实际使用中应补充。

iotSDK::Action() 签名参数顺序敏感，空字段拼接规则必须与云端一致。

DataBaseCommander::InsertNewRow() 返回的是 error 字段，语义上可能反直觉，调用方应确认。

toQDateTime() 尝试大量日期格式，仍可能无法覆盖所有输入，建议业务层明确格式。

httpserver 是简化实现，不支持完整 HTTP 方法、POST Body、HTTPS、路由、并发保护。

BlueDevice 中包含大量 qDebug() 和 dbgr.dbg() 输出，生产环境可关闭相关宏。

多数网络、数据库、蓝牙类未做线程安全封装，跨线程使用需自行加锁或转到对象所属线程。

部分 new 对象未显式释放，依赖 Qt 父子对象机制；若父对象为空，需注意内存泄漏。

gps.cpp 当前只有 #include "gps.h"，属于占位模块。

源码中未声明开源许可证，正式发布前请补充 LICENSE。

8. 快速示例：最小 Qt 控制台程序
cpp
#include <QCoreApplication>
#include "mw.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    mw mwt;
    return a.exec();
}
该示例启动 UDP 接收模块，绑定 12346 端口并打印收到的数据报。

9. 建议的工程目录
text
project/
├── src/
│   ├── base.cpp
│   ├── base64.cpp
│   ├── fjson.cpp
│   ├── csvfile.cpp
│   ├── msxlsx.cpp
│   ├── ...
│   └── main.cpp
├── include/
│   ├── base.h
│   ├── base64.h
│   ├── fjson.h
│   └── ...
├── assets/
│   ├── 0.png
│   ├── 1.png
│   └── t0.png
├── README.md
└── project.pro
10. 许可证
源码中未包含许可证声明。若要对外发布或商用，请根据实际项目补充 MIT、Apache-2.0、GPL 或其他许可证，并保留第三方库的许可证声明。
捐赠 BTC: 13SongiriQuWoFhoimsVS21CyaTxozKBVA

/*
 * DatabaseController类是视力检测系列的一部分,由视力检测APP的多个分支调用
 * */
#ifndef MYDATABASE_H
#define MYDATABASE_H

#include <QObject>

#include <sqlite/DataBaseCommander.h>
#include <csvfile.h>

enum VisionDataBase
{
    DB_users,
    DB_student
};

enum Users
{
    tbluser,
    tblstudentmaster
};

enum Student
{
    tblstudent,
    tblvisionrecord
};


class DatabaseController: public QObject{
    Q_OBJECT
public:
    DatabaseController();

    DatabaseInfo users
    {
        "QSQLITE",
        "users",
        "127.0.0.1",
        "song",
        "test",
        {
            {
                "tbluser",
                "id",
                {
                    "createby",
                    "createtime",
                    "email",
                    "id",
                    "password",
                    "updateby",
                    "updatetime",
                    "username"
                },
                {
                    "INT NOT NULL",
                    "DATETIME NULL",
                    "VARCHAR(45) NULL",
                    "INT NOT NULL",
                    "VARCHAR(45) NULL",
                    "INT NOT NULL",
                    "DATETIME NULL",
                    "VARCHAR(45) NULL"
                }
            },
            {
                "tblstudentmaster",
                "id",
                {
                    "createby",
                    "createtime",
                    "database",
                    "id",
                    "startyear",
                    "updateby",
                    "updatetime"
                },
                {
                    "INT NOT NULL",
                    "DATETIME NULL",
                    "VARCHAR(45) NULL",
                    "INT NOT NULL",
                    "VARCHAR(45) NULL",
                    "INT NOT NULL",
                    "DATETIME NULL",
                    "VARCHAR(45) NULL"
                }
            }
        }
    };

    DatabaseInfo student
    {
        "QSQLITE",
        "student",
        "127.0.0.1",
        "song",
        "test",
        {
            {
                "tblstudent",
                "k01_studentid",
                {
                    "k01_studentid",
                    "k02_studentName",
                    "k03_grade",
                    "k04_className",
                    "k05_schoolName",

                    "k06_checkstate",
                    "k07_classid",
                    "k08_classuid",
                    "k09_schoolid",
                    "k10_schooluid",

                    "k11_studentuid",

                    "k12_f1",                                                          //出生年月
                    "k13_f2",                                                          //性别
                    "k14_f3",                                                          //批号
                    "k15_f4",
                    "k16_f5",
                    "k17_f6",
                    "k18_f7"
                },
                {
                    "VARCHAR(20) NULL",
                    "VARCHAR(80) NULL",
                    "VARCHAR(40) NULL",
                    "VARCHAR(45) NULL",
                    "VARCHAR(160) NULL",

                    "VARCHAR(10) NULL",
                    "INT NULL",
                    "VARCHAR(45) NULL",
                    "INT NULL",
                    "VARCHAR(45) NULL",

                    "VARCHAR(45) NULL",

                    "VARCHAR(30) NULL",
                    "VARCHAR(2) NULL",
                    "INT NULL",
                    "VARCHAR(8) NULL",
                    "VARCHAR(8) NULL",
                    "VARCHAR(8) NULL",
                    "VARCHAR(8) NULL"
                }
            },
            {
                "tblvisionrecord",
                "k00_PrimaryKey",
                {},                                                                    //需要计算
                {
                    "VARCHAR(10) NULL",                                         //   主键

                    "VARCHAR(150) NULL",                                        //   *所属区
                    "VARCHAR(150) NULL",                                        //   *所属学校
                    "VARCHAR(18) NULL",                                         //   *学校机构代码
                    "VARCHAR(80) NULL",                                         //   *姓名
                    "VARCHAR(19) NULL",                                         //   *学籍号

                    "VARCHAR(28) NULL",                                         //   *证件类型（身份证/护照/其他）
                    "VARCHAR(30) NULL",                                         //   *证件号码
                    "VARCHAR(2) NULL",                                          //   *性别
                    "INT NULL",                                                 //   *机构单位层次
                    "INT NULL",                                                 //   *学校性质                                //10



                    "INT NULL",                                                 //   *学年
                    "VARCHAR(45) NULL",                                         //   *年级
                    "VARCHAR(45) NULL",                                         //   *班级
                    "VARCHAR(6) NULL",                                          //   *身高（cm）
                    "VARCHAR(6) NULL",                                          //   *体重（kg）

                    "VARCHAR(45) NULL",                                         //   一般检查医师
                    "VARCHAR(4) NULL",                                         //   *裸眼视力左（对数表）
                    "VARCHAR(4) NULL",                                         //   *裸眼视力右（对数表）
                    "VARCHAR(45) NULL",                                         //   视力检查医师
                    "VARCHAR(45) NULL",                                         //   血压收缩压（mmHg）                                        //20



                    "VARCHAR(8) NULL",                                         //   血压舒张压（mmHg）
                    "VARCHAR(8) NULL",                                         //   *脉搏（次数/分钟）
                    "VARCHAR(8) NULL",                                         //   血压脉搏检查医师
                    "VARCHAR(8) NULL",                                         //   *心脏（正常/异常/未体检）
                    "VARCHAR(8) NULL",                                         //   心脏备注

                    "VARCHAR(8) NULL",                                         //   *肺（正常/异常/未体检）
                    "VARCHAR(8) NULL",                                         //   肺备注
                    "VARCHAR(8) NULL",                                         //   *肝脾（正常/异常/未体检）
                    "VARCHAR(8) NULL",                                         //   肝脾备注
                    "VARCHAR(8) NULL",                                         //   心肺脾检查医师                                       //30



                    "VARCHAR(8) NULL",                                         //   *眼科（常规）（外眼（斜视等）、内眼（沙眼等））（正常/异常/未体检）
                    "VARCHAR(8) NULL",                                         //   眼科（常规）备注
                    "VARCHAR(8) NULL",                                         //   眼科（可选）（色觉、矫正视力等）（正常/异常/未体检）
                    "VARCHAR(8) NULL",                                         //   眼科（可选）备注
                    "VARCHAR(8) NULL",                                         //   *口腔（牙齿、牙周等）（正常/异常/未体检）

                    "VARCHAR(8) NULL",                                         //   口腔备注
                    "VARCHAR(8) NULL",                                         //   *耳鼻咽喉科（常规）（外耳、内耳、鼻腔、咽喉部、扁桃体等）（正常/异常/未体检）
                    "VARCHAR(8) NULL",                                         //   耳鼻咽喉（常规）备注
                    "VARCHAR(8) NULL",                                         //   耳鼻咽喉科（可选）（嗅觉、听力）（正常/异常/未体检）
                    "VARCHAR(8) NULL",                                         //   耳鼻咽喉（可选）备注                     //40



                    "VARCHAR(8) NULL",                                         //   *残缺畸形（正常/异常/未体检）
                    "VARCHAR(8) NULL",                                         //   畸形备注
                    "VARCHAR(8) NULL",                                         //   *外科（常规）（头部、颈部、胸部、脊柱、腹部、四肢、皮肤、淋巴结等）（正常/异常/未体检）
                    "VARCHAR(8) NULL",                                         //   外科（常规）备注
                    "VARCHAR(8) NULL",                                         //   外科（可选）（隐睾、疝气、包皮过长、精索静脉曲张等）（正常/异常/未体检）

                    "VARCHAR(8) NULL",                                         //   外科（可选）备注
                    "VARCHAR(8) NULL",                                         //   外科检查医师
                    "VARCHAR(8) NULL",                                         //   血常规检查（正常/异常/未体检）
                    "VARCHAR(8) NULL",                                         //   血常规备注
                    "VARCHAR(8) NULL",                                         //   血清丙氨酸氨基转移酶（U/L）（正常/异常/未体检）                                                //50



                    "VARCHAR(8) NULL",                                         //   血清丙氨酸氨基转移酶备注
                    "VARCHAR(8) NULL",                                         //   血常规检查医师
                    "VARCHAR(8) NULL",                                         //   肛门（正常/异常/未体检）
                    "VARCHAR(8) NULL",                                         //   肛门备注
                    "VARCHAR(8) NULL",                                         //   足底（正常/异常/未体检）

                    "VARCHAR(8) NULL",                                         //   足底备注
                    "VARCHAR(8) NULL",                                         //   月经史（有/无/未体检）
                    "VARCHAR(8) NULL",                                         //   尿常规（正常/异常/未体检）
                    "VARCHAR(8) NULL",                                         //   尿常规备注
                    "VARCHAR(8) NULL",                                         //   蛔虫卵（μm）（有/无/未体检）                       //60



                    "VARCHAR(8) NULL",                                         //   检查医师
                    "VARCHAR(8) NULL",                                         //   即往病史（有就填写真实情况/无/未体检）
                    "VARCHAR(8) NULL",                                         //   现病史（有就填写真实情况/无/未体检）
                    "VARCHAR(8) NULL",                                         //   体检结论
                    "VARCHAR(8) NULL",                                         //   健康指导

                    "VARCHAR(160) NULL",                                         //   *体检机构
                    "VARCHAR(26) NULL",                                        //   *检查日期
                    "VARCHAR(8) NULL",                                         //   体检备注
                    "VARCHAR(8) NULL",                                         //   完成状态
                    "VARCHAR(26) NULL",                                         //   计划检测时间                                   //70



                    "VARCHAR(26) NULL",                                         //   导入时间
                    "VARCHAR(10) NULL",                                         //   导入人员
                    "VARCHAR(10) NULL",                                         //   学校ID
                    "VARCHAR(10) NULL",                                         //   学校UID
                    "VARCHAR(10) NULL",                                         //   班级ID

                    "VARCHAR(20) NULL",                                         //   班级UID
                    "VARCHAR(20) NULL",                                         //   学生ID
                    "VARCHAR(20) NULL",                                         //   学生UID
                    "VARCHAR(512) NULL",                                        //   SHA256
                    "VARCHAR(20) NULL",                                         //   SN                                           //80



                    "VARCHAR(14) NULL",                                         //   学生生日
                    "VARCHAR(8) NULL",                                         //
                    "VARCHAR(8) NULL",                                         //
                    "VARCHAR(8) NULL",                                         //
                    "VARCHAR(8) NULL",                                         //

                    "VARCHAR(8) NULL",                                         //
                    "VARCHAR(8) NULL",                                         //
                    "VARCHAR(8) NULL",                                         //
                    "VARCHAR(8) NULL",                                         //
                    "VARCHAR(8) NULL",                                         //                                                   //90



                    "VARCHAR(8) NULL",                                         //
                    "VARCHAR(8) NULL",                                         //
                    "VARCHAR(8) NULL",                                         //
                    "VARCHAR(8) NULL",                                         //
                    "VARCHAR(8) NULL",                                         //

                    "VARCHAR(8) NULL",                                         //
                    "VARCHAR(8) NULL",                                         //
                    "VARCHAR(8) NULL",                                         //
                    "VARCHAR(8) NULL",                                         //
                    "VARCHAR(8) NULL",                                         //                                                   //100


                    "VARCHAR(8) NULL",                                         //
                }                                                                     //需要填充
            }
        }
    };

    QStringList tblvisionrecord_table_model_horHeader = QStringList
    {
            "条目", "*所属区", "*所属学校", "*学校机构代码", "*姓名", "*学籍号",
            "*证件类型（身份证/护照/其他）", "*证件号码", "*性别", "*机构单位层次",
            "*学校性质", "*学年", "*年级", "*班级", "*身高（cm）", "*体重（kg）",
            "一般检查医师", "*裸眼视力左（对数表）", "*裸眼视力右（对数表）", "视力检查医师",
            "血压收缩压（mmHg）", "血压舒张压（mmHg）", "*脉搏（次数/分钟）",
            "血压脉搏检查医师", "*心脏（正常/异常/未体检）", "心脏备注", "*肺（正常/异常/未体检）",
            "肺备注", "*肝脾（正常/异常/未体检）", "肝脾备注", "心肺脾检查医师",
            "*眼科（常规）（外眼（斜视等）、内眼（沙眼等））（正常/异常/未体检）",
            "眼科（常规）备注", "眼科（可选）（色觉、矫正视力等）（正常/异常/未体检）",
            "眼科（可选）备注", "*口腔（牙齿、牙周等）（正常/异常/未体检）", "口腔备注",
            "*耳鼻咽喉科（常规）（外耳、内耳、鼻腔、咽喉部、扁桃体等）（正常/异常/未体检）",
            "耳鼻咽喉（常规）备注", "耳鼻咽喉科（可选）（嗅觉、听力）（正常/异常/未体检）",
            "耳鼻咽喉（可选）备注", "*残缺畸形（正常/异常/未体检）", "畸形备注",
            "*外科（常规）（头部、颈部、胸部、脊柱、腹部、四肢、皮肤、淋巴结等）（正常/异常/未体检）",
            "外科（常规）备注", "外科（可选）（隐睾、疝气、包皮过长、精索静脉曲张等）（正常/异常/未体检）",
            "外科（可选）备注", "外科检查医师", "血常规检查（正常/异常/未体检）", "血常规备注",
            "血清丙氨酸氨基转移酶（U/L）（正常/异常/未体检）", "血清丙氨酸氨基转移酶备注", "血常规检查医师",
            "肛门（正常/异常/未体检）", "肛门备注", "足底（正常/异常/未体检）", "足底备注",
            "月经史（有/无/未体检）", "尿常规（正常/异常/未体检）", "尿常规备注",
            "蛔虫卵（μm）（有/无/未体检）", "检查医师", "即往病史（有就填写真实情况/无/未体检）",
            "现病史（有就填写真实情况/无/未体检）", "体检结论", "健康指导", "*体检机构", "*检查日期", "体检备注",
            "完成状态", "计划检测时间", "导入时间", "导入人员",
            "学校ID", "学校UID", "班级ID", "班级UID", "学生ID", "学生UID",

            "SHA256", "SN",
            "预留1", "预留2", "预留3", "预留4", "预留5", "预留6", "预留7", "预留8", "预留9", "预留10",
            "预留11", "预留12", "预留13", "预留14", "预留15", "预留16", "预留17", "预留18", "预留19",
            "预留20"
};

    csvfile Csv;
    DataBaseCommander dataBaseCommander[2];

    QString student_tblvisionrecord_k00_PrimaryKey_Value = "";

    void Init(QString UserName, QString PassWord);

    void Students_tblstudent_Insert(QVariantList studentL);
    void Students_tblvisionrecord_Insert(QVariantList values);
//    QList<QMap<QString, QVariant> > Students_tblvisionrecord_Querry(QString Columns = "*",
//                                                                    QString Conditions = "",
//                                                                    QString LIMIT = "");

    QMap<QString, QVariant> Students_tblvisionrecord_GetRowValues();
    QJsonObject Students_tblvisionrecord_Update(QVariantList values);

    int Students_tblvisionrecord_TotalColumns;

    QJsonObject Students_tblstudent_QuerryJ(QString Columns = "*",
                                            QString Conditions = "",
                                            QString LIMIT = "");

    QJsonObject Students_tblvisionrecord_QuerryJ(QString Columns = "*",
                                                 QString Conditions = "",
                                                 QString LIMIT = "");

    void Disconnection();
    int ConnectToHosts(DatabaseInfo databaseInfo);

};

#endif // MYDATABASE_H

#ifndef EASYTABLEMODEL_H
#define EASYTABLEMODEL_H

#include <QAbstractTableModel>
#include <QQmlParserStatus>
#include <QHash>
#include <QList>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonValue>

class EasyTableModel : public QAbstractTableModel, public QQmlParserStatus
{
    Q_OBJECT
    Q_INTERFACES(QQmlParserStatus)
    Q_PROPERTY(QStringList horHeader READ getHorHeader WRITE setHorHeader NOTIFY horHeaderChanged)
    Q_PROPERTY(QJsonArray initData READ getInitData WRITE setInitData NOTIFY initDataChanged)

public:
    explicit EasyTableModel(QObject *parent = nullptr);
    QStringList getHorHeader() const;
    void setHorHeader(const QStringList &header);
    QJsonArray getInitData() const;
    void setInitData(const QJsonArray &jsonArr);

    void classBegin() override;                                                                               // QQmlParserStatus：构造前
    void componentComplete() override;                                                                        // QQmlParserStatus：构造后
    QHash<int,QByteArray> roleNames() const override;                                                         // 自定义role

    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override; // 表头
    bool setHeaderData(int section, Qt::Orientation orientation, const QVariant &value, int role = Qt::EditRole) override;

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;                                   // 数据，这三个必须实现
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    bool setData(const QModelIndex &index, const QVariant &value,                                             // 编辑
                 int role = Qt::EditRole) override;
    Qt::ItemFlags flags(const QModelIndex& index) const override;

private:
    void loadData(const QJsonArray &data);
    QJsonArray initData;

signals:
    void horHeaderChanged();
    void initDataChanged();
private:
    bool completed=false;                                                                                    // 组件是否初始化完成
                                                                                                             // 加载的数据
    QVector<QVector<QVariant>> modelData;                                                                    // 数据，一般纯展示，用vector就行了
    QList<QString> HeaderList;                                                                               // 横项表头
};

#endif // EASYTABLEMODEL_H

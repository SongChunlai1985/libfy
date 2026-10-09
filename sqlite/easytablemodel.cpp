#include "easytablemodel.h"

#include <QDebug>

EasyTableModel::EasyTableModel(QObject *parent) : QAbstractTableModel(parent)
{
}

QStringList EasyTableModel::getHorHeader() const
{
    return HeaderList;
}

void EasyTableModel::setHorHeader(const QStringList &header)
{
    HeaderList=header;
    emit horHeaderChanged();
}

QJsonArray EasyTableModel::getInitData() const
{
    return initData;
}

void EasyTableModel::setInitData(const QJsonArray &jsonArr)
{
    initData=jsonArr;
    if(completed){
        loadData(initData);
    }
    emit initDataChanged();
}

void EasyTableModel::classBegin()
{
    qDebug()<<"EasyTableModel::classBegin()";
}

void EasyTableModel::componentComplete()
{
    qDebug()<<"EasyTableModel::componentComplete()";
    completed=true;
    if(!initData.isEmpty()){
        loadData(initData);
    }
}

QHash<int, QByteArray> EasyTableModel::roleNames() const                                            //value表示取值，edit表示编辑
{
    return QHash<int,QByteArray>{
        { Qt::DisplayRole,"value" },
        { Qt::EditRole,"edit" }
    };
}

QVariant EasyTableModel::headerData(int section, Qt::Orientation orientation, int role) const      //返回表头数据，无效的返回None
{
    if(role==Qt::DisplayRole){
        if(orientation==Qt::Horizontal){
            return HeaderList.value(section,QString::number(section));
        }else if(orientation==Qt::Vertical){
            return QString::number(section);
        }
    }
    return QVariant();
}

bool EasyTableModel::setHeaderData(int section, Qt::Orientation orientation, const QVariant &value, int role)
{
    if (value != headerData(section, orientation, role) && orientation==Qt::Horizontal && role==Qt::EditRole) {
        HeaderList[section]=value.toString();
        emit headerDataChanged(orientation, section, section);
        return true;
    }
    return false;
}

int EasyTableModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid()) return 0;
    return modelData.count();
}

int EasyTableModel::columnCount(const QModelIndex &parent) const
{
    if (parent.isValid()) return 0;
    return HeaderList.count();
}

QVariant EasyTableModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid()) return QVariant();
    switch (role) {
    case Qt::DisplayRole:
    case Qt::EditRole:
        int row = index.row();
        int col = index.column();
        //qDebug()<<__FUNCTION__<<"row ="<<row<<"col ="<<col;
        int maxcol = modelData[0].size();
        if(col > maxcol)return modelData.at(row).at(col);
        return modelData.at(row).at(col);
    }
    return QVariant();
}

bool EasyTableModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (value.isValid() && index.isValid() && (data(index, role) != value ) && Qt::EditRole==role) {
        modelData[index.row()][index.column()]=value;
        emit dataChanged(index, index, QVector<int>() << role);
        return true;
    }
    return false;
}

Qt::ItemFlags EasyTableModel::flags(const QModelIndex &index) const
{
    if (!index.isValid()) return Qt::NoItemFlags;
    return Qt::ItemIsEnabled|Qt::ItemIsSelectable|Qt::ItemIsEditable;
}

void EasyTableModel::loadData(const QJsonArray &data)
{
    QStringList keys=data.first().toObject().keys();

    QVector<QVector<QVariant>> vectorData;
    foreach (QJsonValue row, data) {
        QVector<QVariant> vectorRow;
        foreach (QString key, keys) {
            vectorRow.append(row[key]);
        }
        vectorData.push_back(vectorRow);
    }

    emit beginResetModel();
    modelData=vectorData;
    emit endResetModel();
}

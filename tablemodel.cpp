#include "tablemodel.h"

QVariant Tablemodel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if(role != Qt::DisplayRole){
        return QVariant();
    }

    if(orientation == Qt::Vertical){
        return section;
    }

    switch (section) {
        case 0:
            return "Путь до файла";

        case 1:
            return "Разжатый размер";

        case 2:
            return "Сжатый размер";
    }

    return QVariant();
}

void Tablemodel::appendData(const QString &path, const QString &compSize, const QString &uncompSize)
{
    fullPath.push_back(path);
    compressSize.push_back(compSize);
    uncompressSize.push_back(uncompSize);

    beginInsertRows(QModelIndex(), countRows, countRows);
    endInsertRows();

    ++countRows;
}

bool Tablemodel::removeRows()
{
    if(countRows > 0){
        for(int i = 0; i < countRows; ++i){
            beginRemoveRows(QModelIndex(), 0, 0);
            fullPath.removeAt(0);
            compressSize.removeAt(0);
            uncompressSize.removeAt(0);
            endRemoveRows();
        }
    countRows = 0;
    }else{
        return false;
    }

    return true;
}

int Tablemodel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);

    return fullPath.count();
}

int Tablemodel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);

    return countColumn;
}

QVariant Tablemodel::data(const QModelIndex &index, int role) const
{
    QVariant value;

    if(!index.isValid() || role != Qt::DisplayRole || fullPath.count() <= index.row())
         return QVariant();

     switch (index.column()) {
        case 0:
            value = fullPath.at(index.row());
        break;

        case 1:
            value = uncompressSize.at(index.row());
        break;

        case 2:
            value = compressSize.at(index.row());
        break;
     }

    return value;
}

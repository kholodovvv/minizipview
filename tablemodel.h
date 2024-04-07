#ifndef TABLEMODEL_H
#define TABLEMODEL_H

#include <QAbstractTableModel>
#include <QStringList>

class Tablemodel: public QAbstractTableModel
{
    Q_OBJECT
public:
    Tablemodel(QObject* parent = 0){};
    ~Tablemodel(){};
    virtual int rowCount(const QModelIndex &parent) const override;
    virtual int columnCount(const QModelIndex &parent) const override;
    virtual QVariant data(const QModelIndex &index, int role) const  override;
    virtual QVariant headerData(int section, Qt::Orientation orientation, int role) const override;
    void appendData(const QString &path, const QString &compSize, const QString &uncompSize);
    bool removeRows();

private:
    QStringList fullPath;
    QStringList compressSize;
    QStringList uncompressSize;
    int countRows = 0;
    const int countColumn = 3;
};

#endif // TABLEMODEL_H

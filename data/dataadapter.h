#ifndef DATA_ADAPTER_H
#define DATA_ADAPTER_H
#define ROW_HEIGHT 80

#include <QAbstractTableModel>
#include <QSize>
#include "student.h"
#include "../ui/mainwindow.h"

class DataModel: public QAbstractTableModel{

    Q_OBJECT

public:
    DataModel(QObject* parent);
    int rowCount(const QModelIndex &parent = QModelIndex()) const override ;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

};

#endif // DATA_ADAPTER_H

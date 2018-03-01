#ifndef DATA_ADAPTER_H
#define DATA_ADAPTER_H
#define ROW_HEIGHT 80

#include <QAbstractTableModel>
#include <QSize>
#include "student.h"
#include "../ui/mainwindow.h"

class DataAdapter: public QAbstractTableModel{

    Q_OBJECT

public:
    DataAdapter(QObject* parent);
    int rowCount(const QModelIndex &parent = QModelIndex()) const override ;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;
    void update();
    static DataAdapter* getInstance();

private:
    static DataAdapter* instance;

};

#endif // DATA_ADAPTER_H

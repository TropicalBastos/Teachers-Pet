#ifndef DATA_ADAPTER_H
#define DATA_ADAPTER_H
#define ROW_HEIGHT 80
#define COLUMN_COUNT 4
#define ID_COLUMN 0
#define NAME_COLUMN 1
#define PAID_COLUMN 2
#define REMOVE_COLUMN 3
#define DANGER 255, 56, 56

#include <QAbstractTableModel>
#include <QSize>
#include "student.h"
#include "../ui/mainwindow.h"
#include <QPushButton>
#include <QBrush>
#include <QMessageBox>
#include "resetter.h"

/* Global table */
namespace maintable {
    extern QTableView* tableView;
}

class DataAdapter: public QAbstractTableModel{

    Q_OBJECT

public:
    DataAdapter(QObject* parent);
    int rowCount(const QModelIndex &parent = QModelIndex()) const override ;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;
    void add();
    void remove(int id);
    bool confirmDelete(QString name);
    void handleCheckbox(int row, int id, bool isChecked);
    void resetPaidCells();
    void loadData(char* path);
    void update();
    static DataAdapter* getInstance();

public slots:
    void onCellClicked(const QModelIndex& index);

private:
    static DataAdapter* instance;

};

#endif // DATA_ADAPTER_H

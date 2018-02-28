#include "ui/mainwindow.h"
#include <QApplication>
#include <QTableView>
#include "data/datamodel.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    QTableView tableView(&w);
    DataModel dm(0);
    tableView.setModel(&dm);
    tableView.show();
    tableView.setFixedSize(w.width(), w.height() / 2);
    tableView.move(tableView.x(), tableView.y() + 50);
    return a.exec();
}

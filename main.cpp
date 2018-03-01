#include "ui/mainwindow.h"
#include <QApplication>
#include <QTableView>
#include <QHeaderView>
#include "data/dataadapter.h"

int main(int argc, char *argv[])
{
    /* Set up main window */
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    /* Set up main table */
    QTableView tableView(&w);
    DataAdapter da(0);
    tableView.setModel(&da);
    tableView.show();
    tableView.setFixedSize(w.width(), w.height() * 0.7);
    tableView.move(tableView.x(), tableView.y() + 24);
    QHeaderView* header = tableView.horizontalHeader();
    header->setSectionResizeMode(QHeaderView::Stretch);
    /* End setup */

    /* Execute event loop */
    return a.exec();
}

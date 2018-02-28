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
    DataModel dm(0);
    tableView.setModel(&dm);
    tableView.show();
    tableView.setFixedSize(w.width(), w.height() / 2);
    tableView.move(tableView.x(), tableView.y() + 50);
    QHeaderView* header = tableView.horizontalHeader();
    header->setSectionResizeMode(QHeaderView::Stretch);
    /* End setup */

    /* Execute event loop */
    return a.exec();
}

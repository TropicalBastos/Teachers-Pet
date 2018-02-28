#include "dataadapter.h"

DataModel::DataModel(QObject *parent): QAbstractTableModel(parent){

}

int DataModel::rowCount(const QModelIndex &parent) const{
    return appstate::getStudentCount();
}

int DataModel::columnCount(const QModelIndex &parent) const{
    return STUDENT_MEMBERS;
}

QVariant DataModel::data(const QModelIndex &index, int role) const{
    using namespace appstate;

    int row = index.row();
    int col = index.column();

    switch(role){
    case Qt::DisplayRole:
        if(col == 0) return studentList.at(row)->id;
        if(col == 1) return studentList.at(row)->name;
        break;

    case Qt::TextAlignmentRole:
        return Qt::AlignVCenter;
        break;

    case Qt::SizeHintRole: {
        QSize size(MainWindow::getInstance()->width(), ROW_HEIGHT);
        return size;
        break;
    }

    case Qt::CheckStateRole:

        if (col == (STUDENT_MEMBERS - 1)) //add a checkbox to cell(1,0)
        {
            if(studentList.at(row)->paid){
                return Qt::Checked;
            }else{
                return Qt::Unchecked;
            }
        }
    }

    return QVariant();
}

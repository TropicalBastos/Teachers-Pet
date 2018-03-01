#include "dataadapter.h"

DataAdapter* DataAdapter::instance;

DataAdapter::DataAdapter(QObject *parent): QAbstractTableModel(parent){
    DataAdapter::instance = this;
}

int DataAdapter::rowCount(const QModelIndex &parent) const{
    return appstate::getStudentCount();
}

int DataAdapter::columnCount(const QModelIndex &parent) const{
    return STUDENT_MEMBERS;
}

QVariant DataAdapter::data(const QModelIndex &index, int role) const{
    using namespace appstate;

    int row = index.row();
    int col = index.column();

    switch(role){
    case Qt::DisplayRole:
        if(col == 0) return studentList.at(row)->id;
        if(col == 1){
            const char* name = studentList.at(row)->name;
            QString str;
            str.sprintf("%s", name);
            //qDebug() << str;
            return str;
        }
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

QVariant DataAdapter::headerData(int section, Qt::Orientation orientation, int role) const{
    switch(role){
        case Qt::DisplayRole:
        if(orientation == Qt::Horizontal){
            if(section == 0) return "Student ID";
            if(section == 1) return "Name";
            if(section == 2) return "Paid";
        }
    }
    return QVariant();
}


/*
 * We need a global instance so our parent ui
 * can signal events to change data
*/
DataAdapter* DataAdapter::getInstance(){
    return DataAdapter::instance;
}

void DataAdapter::update(){
    beginInsertRows(QModelIndex(), appstate::studentList.size(), appstate::studentList.size());
    endInsertRows();

    QModelIndex top = createIndex(appstate::studentList.size() - 1, 0, Q_NULLPTR);
    QModelIndex bottom = createIndex(appstate::studentList.size() - 1, 3, Q_NULLPTR);

    emit dataChanged(top, bottom);
}

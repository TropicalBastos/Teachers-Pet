#include "dataadapter.h"

DataAdapter* DataAdapter::instance;

DataAdapter::DataAdapter(QObject *parent): QAbstractTableModel(parent){
    using namespace maintable;
    connect(tableView, SIGNAL(clicked(const QModelIndex&)), this, SLOT(onCellClicked(const QModelIndex&)));
    DataAdapter::instance = this;
}

int DataAdapter::rowCount(const QModelIndex &parent) const{
    return appstate::getStudentCount();
}

int DataAdapter::columnCount(const QModelIndex &parent) const{
    return COLUMN_COUNT;
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
        if(col == 3) return "Delete";
        break;

    case Qt::TextAlignmentRole:
        return Qt::AlignCenter;
        break;

    case Qt::SizeHintRole: {
        QSize size(MainWindow::getInstance()->width(), ROW_HEIGHT);
        return size;
        break;
    }

    case Qt::BackgroundRole: {
        QBrush brush(QColor(DANGER));
        if(col == 3) return brush;
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
            if(section == 3) return "Remove";
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

void DataAdapter::add(){
    beginInsertRows(QModelIndex(), appstate::studentList.size(), appstate::studentList.size());
    endInsertRows();

    QModelIndex top = createIndex(appstate::studentList.size() - 1, 0, Q_NULLPTR);
    QModelIndex bottom = createIndex(appstate::studentList.size() - 1, COLUMN_COUNT, Q_NULLPTR);

    emit dataChanged(top, bottom);
}

void DataAdapter::remove(int id){
    QModelIndexList matches = this->match(this->index(0, 0), Qt::DisplayRole, id);
    QModelIndex matchedRow = matches.first();

    beginRemoveRows(QModelIndex(), matchedRow.row(), matchedRow.row());
    int rowRemoved = appstate::removeStudent(id);
    endRemoveRows();

    QModelIndex top = createIndex(rowRemoved, 0, Q_NULLPTR);
    QModelIndex bottom = createIndex(rowRemoved, COLUMN_COUNT, Q_NULLPTR);

    emit dataChanged(top, bottom);
}

void DataAdapter::onCellClicked(const QModelIndex& index){
    int row = index.row();
    int column = index.column();

    QAbstractTableModel* model = (QAbstractTableModel*) index.model();
    int id = model->data(model->index(row, 0), Qt::DisplayRole).toInt();
    QString name = model->data(model->index(row, NAME_COLUMN), Qt::DisplayRole).toString();
    bool isChecked = (bool) model->data(model->index(row, PAID_COLUMN), Qt::CheckStateRole).toBool();

    qDebug() << "Cell Clicked!";
    switch(column){
        case PAID_COLUMN:
        qDebug() << "Paid cell clicked!";
        handleCheckbox(row, id, isChecked);
        break;

        case REMOVE_COLUMN:
        bool confirm = confirmDelete(name);
        if(!confirm)
            break;
        remove(id);
        break;
    }
}

bool DataAdapter::confirmDelete(QString name){
    QString text("Are you sure you want to delete ");
    text.append(name);
    int reply;
    reply = QMessageBox::question(MainWindow::getInstance(),
                                  "Caution",  text, QMessageBox::Yes, QMessageBox::No);
    return (reply == QMessageBox::Yes);
}

void DataAdapter::handleCheckbox(int row, int id, bool isChecked){
    appstate::toggleCheckedState(id, isChecked);
    QModelIndex top = createIndex(row, 0, Q_NULLPTR);
    QModelIndex bottom = createIndex(row, COLUMN_COUNT, Q_NULLPTR);
    emit dataChanged(top, bottom);
}

void DataAdapter::resetPaidCells(){
    Resetter::reset();
    update();
}

void DataAdapter::update(int size){
    QModelIndex top = this->index(0, 0);
    QModelIndex bottom = this->index(size, COLUMN_COUNT);
    emit dataChanged(top, bottom);
}

void DataAdapter::loadData(char *path){
    newData();
    BinarySerializer bs;
    bs.read(path);
    beginInsertRows(QModelIndex(), 0, appstate::studentList.size() - 1);
    endInsertRows();
    update();
}

void DataAdapter::newData(){
    int prevSize = appstate::studentList.size();
    appstate::studentList = std::vector<appstate::STUDENT*>();
    beginRemoveRows(QModelIndex(), 0, prevSize - 1);
    endRemoveRows();
    update(prevSize);
}

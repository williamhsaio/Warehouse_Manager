#include "tablemodel.h"
#include <algorithm>
#include <iostream>
#include <iterator>

using namespace std;

TableModel::TableModel(QObject *parent) : QAbstractTableModel(parent){}

TableModel::~TableModel(){
    while(!m_table.empty()){
        Product *p = m_table.back();
        delete(p);
        m_table.pop_back();
    }
}
QVariant TableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role == Qt::DisplayRole)
    {
        if (orientation == Qt::Horizontal) {
            switch (section)
            {
            case PRODUCT_NAME:
                return tr("Product Name");
            case LOCATION:
                return tr("Location");
            case STOCK:
                return tr("Stock");
            case SOLD:
                return tr("Sold");
            default:
                return QString();
            }
        }
    }
    return QVariant();
}

TableModel::Errors TableModel::updateStock(const string &name, int stock){
    if(stock <= 0 || stock % 1 < 0){
        cout<<"Amount sold cannot be negative or zero and must be a whole number."<<endl;
        return Errors::INVALD_VAL;
    }
    const auto it = find_if(m_table.begin(), m_table.end(), [name](const auto *p) {
        return p->getName() == name;
    });
    if(it != m_table.end()){
        int currStock = (*it)->getStock();
        (*it)->setStock(currStock + stock);
        return Errors::SUCCESS;
    }
    else{
        cout<<"Could not find product to update."<<endl;
        return Errors::FAIL_TO_UPDATE;
    }
}

TableModel::Errors TableModel::updateSold(const string &name, int sold){
    if(sold <= 0 || sold % 1 < 0){
        cout<<"Amount sold cannot be negative or zero and must be a whole number."<<endl;
        return Errors::INVALD_VAL;
    }
    const auto it = find_if(m_table.begin(), m_table.end(), [name](const auto *p) {
        return p->getName() == name;
    });
    if(it != m_table.end()){
        int currStock = (*it)->getStock();
        if(sold > currStock){
            cout<<"Amount sold cannot exceed current stock."<<endl;
            return Errors::INVALD_VAL;
        }
        (*it)->setStock(currStock - sold);

        int currSold = (*it)->getSold();
        (*it)->setSold(currSold + sold);
        return Errors::SUCCESS;
    }
    else{
        cout<<"Could not find product to update."<<endl;
        return Errors::FAIL_TO_UPDATE;
    }
}

TableModel::Errors TableModel::addProduct(const string &name, const string &location, int stock, int sold){
    const auto it = find_if(m_table.begin(), m_table.end(), [name](const auto *p) {
        return p->getName() == name;
    });
    if(it != m_table.end()){
        cout<<"Product already exists."<<endl;
        return Errors::FAIL_TO_ADD;
    }
    else{
        beginInsertColumns(QModelIndex(), rowCount(), rowCount());
        Product *p = new Product(name, location, stock, sold);
        if(p->getSold() < p->getStock()){
            m_table.push_back(p);
        }
        else{
            cout<<"Sold amount must be less than current stock."<<endl;
            delete(p);
            return Errors::INVALD_VAL;
        }

        endInsertRows();
        return Errors::SUCCESS;
    }
}
TableModel::Errors TableModel::removeProduct(const string &name){
    const auto it = find_if(m_table.begin(), m_table.end(), [name](const auto *p) {
        return p->getName() == name;
    });
    if(it != m_table.end()){
        cout<<"Product "<< (*it)->getName() << " found."<<endl;
        auto index = it-m_table.begin();
        cout<<"Iter index is: "<< index <<endl;
        beginRemoveRows(QModelIndex(), index, index);
        cout<<"Start remove." <<endl;
        delete(*it);
        m_table.erase(it);
        cout<<"Erasing."<<endl;
        endRemoveRows();
        cout<<"Finished remove."<<endl;

        cout<<"Deleted pointers."<<endl;
        return Errors::SUCCESS;
    }
    else{
        cout<<"Could not find the product."<<endl;
        return Errors::FAIL_TO_DELETE;
    }
}

Product* TableModel::getProduct(const string& name) const{
    const auto it = find_if(m_table.begin(), m_table.end(), [name](const auto *p) {
        return p->getName() == name;
    });
    if(it != m_table.end()){
        return *it;
    }
    else{
        return nullptr;
    }
}

// QHash<int, QByteArray> TableModel::roleNames() const{
//     return {(Roles::PRODUCT_NAME_ROLE, "Name"), (Roles::LOCATION_ROLE, "Location"),
//             (Roles::STOCK_ROLE, "Stock"), (Roles::SOLD_ROLE, "Sold")};
// }

int TableModel::rowCount(const QModelIndex &parent) const{
    return m_table.size();
}
int TableModel::columnCount(const QModelIndex &parent) const{
    return 4;
}
QVariant TableModel::data(const QModelIndex &index, int role) const{
    int row = index.row(), col = index.column();
    if(row < m_table.size() && col < 4){
        if(role == Qt::DisplayRole) {
            const auto *p = m_table[row];
            switch(col){
            case Columns::PRODUCT_NAME:
                return QString::fromStdString(p->getName());
            case Columns::LOCATION:
                return QString::fromStdString(p->getLoc());
            case Columns::STOCK:
                return p->getStock();
            case Columns::SOLD:
                return p->getSold();
            default:
                break;
            }
        }
    }

    return QVariant{};
}


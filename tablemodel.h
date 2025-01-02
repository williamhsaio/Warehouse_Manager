#ifndef TABLEMODEL_H
#define TABLEMODEL_H

#include "product.h"
#include <vector>
#include <QAbstractTableModel>

class TableModel: public QAbstractTableModel
{
    Q_OBJECT
public:
    enum class Errors{
        SUCCESS,
        FAIL_TO_ADD,
        FAIL_TO_DELETE,
        FAIL_TO_UPDATE,
        INVALD_VAL,
        NOT_FOUND
    };

    enum Columns{
        PRODUCT_NAME,
        LOCATION,
        STOCK,
        SOLD
    };

    explicit TableModel(QObject *parent = nullptr);
    ~TableModel();

    QVariant headerData(int section, Qt::Orientation orientation, int role) const override;

    //Editing Data
    Errors updateStock(const string &name, int stock);
    Errors updateSold(const string &name, int sold);
    Errors addProduct(const string &name, const string &location, int stock, int sold);
    Errors removeProduct(const string &name);

    //Table View
    //QHash<int, QByteArray> roleNames() const override;
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    //Getters & Setters
    vector<Product*> getTable() const{
        return m_table;
    }
    Product* getProduct(const string& name) const;

private:
    vector<Product*> m_table;
};

#endif // TABLEMODEL_H

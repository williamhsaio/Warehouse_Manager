#ifndef PRODUCT_H
#define PRODUCT_H

#include <string>

using namespace std;

class Product
{
public:
    Product(const string& name, const string& location, int stock, int sold);

    //Getters & Setters
    string getName() const{
        return m_name;
    }
    string getLoc() const{
        return m_location;
    }
    int getStock() const{
        return m_stock;
    }
    int getSold() const{
        return m_sold;
    }
    void setName(const string &name){
        m_name = name;
    }
    void setLoc(const string &loc){
        m_location = loc;
    }
    void setStock(int stock){
        m_stock = stock;
    }
    void setSold(int sold){
        m_sold = sold;
    }

private:
    string m_name;
    string m_location;
    int m_stock;
    int m_sold;
};

#endif // PRODUCT_H

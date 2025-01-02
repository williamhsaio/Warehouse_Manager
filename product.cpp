// #include <QObject>
#include "product.h"

using namespace std;

Product::Product(const string& name, const string& location, int stock, int sold):
    m_name(name), m_location(location), m_stock(stock), m_sold(sold){}


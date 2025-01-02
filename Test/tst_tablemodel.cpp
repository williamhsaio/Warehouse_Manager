#include <gmock/gmock-matchers.h>
#include <gtest/gtest.h>
#include "../tablemodel.h"

using namespace testing;

TEST(TableModel, get_Add_Table)
{
    TableModel table;
    table.addProduct("Frog", "A1", 200, 23);
    EXPECT_EQ(table.getTable().size(), 1);

    Product *p = table.getTable().back();
    EXPECT_EQ(p->getName(), "Frog");
}

TEST(TableModel, updateSold)
{
    TableModel table;
    table.addProduct("Frog", "A1", 200, 0);

    TableModel::Errors e = table.updateSold("Frog", -1);
    EXPECT_EQ(e, TableModel::Errors::INVALD_VAL);

    e = table.updateSold("Dog", 23);
    EXPECT_EQ(e, TableModel::Errors::FAIL_TO_UPDATE);

    table.updateSold("Frog", 23);
    Product *p = table.getTable().back();
    EXPECT_EQ(p->getSold(), 23);
    EXPECT_EQ(p->getStock(), 177);
}
TEST(TableModel, data)
{
    TableModel table;
    table.addProduct("Frog", "A1", 200, 0);
    table.addProduct("Fog", "A2", 20, 180);
    table.addProduct("Frg", "A3", 22, 178);
    table.addProduct("Fg", "A4", 2, 198);

    QVariant name = table.data(table.index(0,0));
    QVariant loc = table.data(table.index(1,1));
    QVariant stock = table.data(table.index(2,2));
    QVariant sold = table.data(table.index(3,3));

    EXPECT_EQ(name, "Frog");
    EXPECT_EQ(loc, "A2");
    EXPECT_EQ(stock, 22);
    EXPECT_EQ(sold, 198);
}
/*TEST(TableModel, updateStock)
{
    TableModel table;
    table.addProduct("Frog", "A1", 200, 23);

    table.updateStock("N/A", 200)
    EXPECT_EQ(table.getTable().size(), 1);

    Product *p = table.getTable().back();
    EXPECT_EQ(p->getName(), "Frog");
}

TEST(TableModel, removeProduct)
{
    TableModel table;
    table.addProduct("Frog", "A1", 200, 23);
    table.removeProduct("Frog");
    EXPECT_EQ(table.getTable().empty(), true);
}
*/

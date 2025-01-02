#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTableView>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QPushButton>

#include "tablemodel.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void createTableView();
    QVBoxLayout* createAddLayout();
    QVBoxLayout* createRemoveLayout();
    QVBoxLayout* createUpStockLayout();
    QVBoxLayout* createUpSoldLayout();

private slots:
    void handleAddButtonClicked();
    void handleRemoveButtonClicked();
    void handleUpStockButtonClicked();
    void handleUpSoldButtonClicked();

private:
    Ui::MainWindow *ui;
    QTableView *tableView;
    TableModel *tableModel;

    QLineEdit *nameLineEdit;
    QLineEdit *nameRemoveEdit;
    QLineEdit *locLineEdit;
    QLineEdit *stockLineEdit;
    QLineEdit *soldLineEdit;
    QLineEdit *nameUpStockEdit;
    QLineEdit *stockUpStockEdit;
    QLineEdit *nameUpSoldEdit;
    QLineEdit *soldUpSoldEdit;

    QPushButton *addButton;
    QPushButton *removeButton;
    QPushButton *upStockButton;
    QPushButton *upSoldButton;

};
#endif // MAINWINDOW_H

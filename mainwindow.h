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

private slots:
    void handleAddButtonClicked();
    void handleRemoveButtonClicked();
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
    QlineEdit *nameUpSoldEdit;
    QPushButton *addButton;
    QPushButton *removeButton;

};
#endif // MAINWINDOW_H

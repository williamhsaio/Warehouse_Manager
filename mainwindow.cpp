#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <QMainWindow>
#include <QTableView>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFormLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //Display Warehouse Table
    createTableView();

    QHBoxLayout *m_layout = new QHBoxLayout;
    m_layout->addWidget(tableView);

    setWindowTitle(QObject::tr("Warehouse Manager"));

    QVBoxLayout *text_layout = new QVBoxLayout;

    QVBoxLayout *add_form = createAddLayout();
    text_layout->addLayout(add_form);

    QVBoxLayout *remove_form = createRemoveLayout();
    text_layout->addLayout(remove_form);

    m_layout->addLayout(text_layout);

    ui->centralwidget->setLayout(m_layout);

    connect(addButton, &QPushButton::clicked, this, &MainWindow::handleAddButtonClicked);
    connect(removeButton, &QPushButton::clicked, this, &MainWindow::handleRemoveButtonClicked);
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::handleAddButtonClicked(){
    const auto name = nameLineEdit->text().toStdString();
    const auto location = locLineEdit->text().toStdString();
    const auto stock = stockLineEdit->text().toInt();
    const auto sold = soldLineEdit->text().toInt();
    tableModel->addProduct(name, location, stock, sold);
}

void MainWindow::handleRemoveButtonClicked(){
    const auto name = nameRemoveEdit->text().toStdString();
    tableModel->removeProduct(name);
}

void MainWindow::createTableView(){
    tableView = new QTableView(this);
    tableModel = new TableModel(this);
    tableModel->addProduct("Shovel", "A1", 200, 34);
    tableModel->addProduct("spade", "B1", 133, 34);
    tableModel->addProduct("axe", "C2", 300, 34);
    tableView->setModel(tableModel);
}

QVBoxLayout* MainWindow::createAddLayout(){
    QVBoxLayout* add_form_layout = new QVBoxLayout;
    add_form_layout->addWidget(new QLabel("Add Product", this));
    QFormLayout *formLayout = new QFormLayout(this);

    nameLineEdit = new QLineEdit(this);
    locLineEdit = new QLineEdit(this);
    stockLineEdit = new QLineEdit(this);
    soldLineEdit = new QLineEdit(this);

    formLayout->addRow(tr("&Name:"), nameLineEdit);
    formLayout->addRow(tr("&Location:"), locLineEdit);
    formLayout->addRow(tr("&Stock:"), stockLineEdit);
    formLayout->addRow(tr("&Sold:"), soldLineEdit);

    add_form_layout->addLayout(formLayout);
    addButton = new QPushButton("Add", this);
    add_form_layout->addWidget(addButton);

    return add_form_layout;
}

QVBoxLayout* MainWindow::createRemoveLayout(){
    QVBoxLayout* remove_form_layout = new QVBoxLayout;
    remove_form_layout->addWidget(new QLabel("Remove Product", this));
    QFormLayout *formLayout = new QFormLayout(this);

    nameRemoveEdit = new QLineEdit(this);

    formLayout->addRow(tr("&Name:"), nameRemoveEdit);

    remove_form_layout->addLayout(formLayout);
    removeButton = new QPushButton("Remove", this);
    remove_form_layout->addWidget(removeButton);

    return remove_form_layout;
}

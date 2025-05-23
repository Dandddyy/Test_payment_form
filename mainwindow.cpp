#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "cashemulation.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->tableWidget->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Stretch);
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(1, QHeaderView::ResizeToContents);
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(2, QHeaderView::ResizeToContents);

    ui->labelThank->hide();

    CashEmulation *cashWindow = new CashEmulation(this);
    cashWindow->setAttribute(Qt::WA_DeleteOnClose);
    connect(cashWindow, &CashEmulation::moneyInserted, this, &MainWindow::onMoneyInserted);
    cashWindow->show();

    // Заповнюємо вхідні дані
    products.push_back({"Бритва", 24.30, 1});
    products.push_back({"Зубна щітка", 37.80, 2});
    products.push_back({"Шампунь", 21.55, 1});

    fillTable();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::fillTable()
{
    ui->tableWidget->setRowCount(products.size());
    for (int i = 0; i < products.size(); ++i) {
        const Product &p = products[i];

        QTableWidgetItem *nameItem = new QTableWidgetItem(p.name);
        QTableWidgetItem *qtyItem = new QTableWidgetItem(QString::number(p.quantity));
        QTableWidgetItem *priceItem = new QTableWidgetItem(QString::number(p.total(), 'f', 2) + " грн");

        ui->tableWidget->setItem(i, 0, nameItem);
        ui->tableWidget->setItem(i, 1, qtyItem);
        ui->tableWidget->setItem(i, 2, priceItem);

        totalPrice += p.total();
    }

    toPay = totalPrice;

    ui->labelTotal->setText("Загальна сума: " + QString::number(totalPrice, 'f', 2) + " грн");
    ui->labelToPay->setText("До сплати: " + QString::number(toPay, 'f', 2) + " грн");
}

void MainWindow::onMoneyInserted(float amount)
{
    if (isPaid)
        return;

    payed += amount;
    toPay -= amount;

    ui->labelPayed->setText("Сплачено: " + QString::number(payed, 'f', 2) + " грн");
    if(toPay <= 0.0){
        change = payed - totalPrice;
        float roundedChange = std::floor(change * 10) / 10.0;
        ui->labelChange->setText("Решта: " + QString::number(roundedChange, 'f', 2) + " грн");
        ui->labelToPay->setText("До сплати: 0.0 грн");
        ui->labelThank->show();
        isPaid = true;
    }
    else{
        ui->labelToPay->setText("До сплати: " + QString::number(toPay, 'f', 2) + " грн");
        ui->labelChange->setText("Решта: 0.00 грн");
    }
}

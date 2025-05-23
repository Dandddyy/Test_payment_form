#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "Product.h"

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

public slots:
    void onMoneyInserted(float amount);

private:
    Ui::MainWindow *ui;

    QVector<Product> products;
    float totalPrice = 0.0;
    float toPay = 0.0;
    float payed = 0.0;
    float change = 0.0;
    bool isPaid = false;

    void fillTable();
};
#endif // MAINWINDOW_H

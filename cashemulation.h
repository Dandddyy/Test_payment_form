#ifndef CASHEMULATION_H
#define CASHEMULATION_H

#include <QDialog>

namespace Ui {
class CashEmulation;
}

class CashEmulation : public QDialog
{
    Q_OBJECT

public:
    explicit CashEmulation(QWidget *parent = nullptr);
    ~CashEmulation();

signals:
    void moneyInserted(float amount);

public slots:
    void handleCashButton(QString value);

private:
    Ui::CashEmulation *ui;
};

#endif // CASHEMULATION_H

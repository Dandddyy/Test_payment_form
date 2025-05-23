#include "cashemulation.h"
#include "ui_cashemulation.h"

CashEmulation::CashEmulation(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::CashEmulation)
{    
    ui->setupUi(this);

    QList<QPushButton*> buttons = this->findChildren<QPushButton*>();

    for (QPushButton *btn : buttons) {
        QString text = btn->text();
        connect(btn, &QPushButton::clicked, this, [this, text]() {
            this->handleCashButton(text);
        });
    }
}

CashEmulation::~CashEmulation()
{
    delete ui;
}

void CashEmulation::handleCashButton(QString text)
{
    float amount = 0.0;

    if (text.endsWith("грн")) {
        text.replace(" грн", "");
        amount = text.toFloat();
    } else if (text.endsWith("коп")) {
        text.replace(" коп", "");
        amount = text.toFloat() / 100.0;
    }

    emit moneyInserted(amount);
}

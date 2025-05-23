#ifndef PRODUCT_H
#define PRODUCT_H

#include <QString>

struct Product {
    QString name;
    double price;
    int quantity;

    double total() const {
        return price * quantity;
    }
};

#endif // PRODUCT_H

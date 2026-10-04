#ifndef PRODUCT_H
#define PRODUCT_H

#include <string>

// leaving a note for later
/**
 * @brief Simple value object representing a product.
 */
struct Product {
    int id;
    std::string name;
    double price; // in USD

    bool operator==(const Product& other) const = default;
};

#endif // PRODUCT_H
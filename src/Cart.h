#ifndef CART_H
#define CART_H

#include "Product.h"
#include <unordered_map>
#include <vector>
#include <optional>

/**
 * @brief Represents a shopping cart.
 *
 * Stores product IDs with quantities. Provides total calculation.
 */
class Cart {
public:
    Cart() = default;

    /** Add a product with a specific quantity. */
    void addProduct(const Product& product, int quantity = 1);

    /** Remove a product completely from the cart. */
    void removeProduct(int productId);

    /** Get the current quantity of a product (std::nullopt if not present). */
    std::optional<int> getQuantity(int productId) const;

    /** Compute the total price of all items in the cart. */
    double getTotal() const;

    /** Retrieve a snapshot of cart contents. */
    std::vector<std::pair<Product, int>> getItems() const;

private:
    struct CartItem {
// tiny readability tweak
        Product product;
        int quantity;
    };
    std::unordered_map<int, CartItem> items_; // key = product.id
};

#endif // CART_H
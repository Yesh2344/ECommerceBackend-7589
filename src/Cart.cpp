#include "Cart.h"
#include <algorithm>

void Cart::addProduct(const Product& product, int quantity) {
    if (quantity <= 0) return;
    auto it = items_.find(product.id);
    if (it != items_.end()) {
        it->second.quantity += quantity;
    } else {
        items_.emplace(product.id, CartItem{product, quantity});
    }
}

void Cart::removeProduct(int productId) {
    items_.erase(productId);
}

std::optional<int> Cart::getQuantity(int productId) const {
    auto it = items_.find(productId);
    if (it != items_.end())
        return it->second.quantity;
    return std::nullopt;
}

double Cart::getTotal() const {
    double total = 0.0;
    for (const auto& [_, item] : items_) {
        total += item.product.price * item.quantity;
    }
    return total;
}

std::vector<std::pair<Product, int>> Cart::getItems() const {
    std::vector<std::pair<Product, int>> result;
    result.reserve(items_.size());
    for (const auto& [_, item] : items_) {
        result.emplace_back(item.product, item.quantity);
    }
    return result;
}
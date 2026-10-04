#include "Logger.h"
#include "Config.h"
#include "Cart.h"
#include "Product.h"
#include "PaymentProcessor.h"

#include <memory>
#include <iostream>

int main() {
    Logger::instance().log(Logger::Level::INFO, "ECommerceBackend starting...");

    // Sample products
    Product laptop{1, "Laptop", 1499.99};
    Product mouse{2, "Wireless Mouse", 29.99};
    Product keyboard{3, "Mechanical Keyboard", 89.99};

    // Build a cart
    Cart cart;
    cart.addProduct(laptop, 1);
    cart.addProduct(mouse, 2);
    cart.addProduct(keyboard, 1);

    Logger::instance().log(Logger::Level::INFO,
        "Cart total: $" + std::to_string(cart.getTotal()));

    // Choose payment method based on configuration
    auto paymentMethodOpt = Config::instance().get<std::string>("PAYMENT_METHOD");
    if (!paymentMethodOpt) {
        Logger::instance().log(Logger::Level::ERROR, "PAYMENT_METHOD not set in .env");
        return EXIT_FAILURE;
    }

    std::unique_ptr<PaymentProcessor> processor;
    std::string method = *paymentMethodOpt;
    if (method == "credit_card") {
        processor = std::make_unique<CreditCardProcessor>();
    } else if (method == "paypal") {
        processor = std::make_unique<PayPalProcessor>();
    } else {
        Logger::instance().log(Logger::Level::ERROR, "Unsupported PAYMENT_METHOD: " + method);
        return EXIT_FAILURE;
    }

    bool success = processor->process(cart.getTotal());
    if (success) {
        Logger::instance().log(Logger::Level::INFO, "Order completed successfully!");
    } else {
        Logger::instance().log(Logger::Level::ERROR, "Order failed during payment.");
    }

    Logger::instance().log(Logger::Level::INFO, "ECommerceBackend shutting down.");
    return success ? EXIT_SUCCESS : EXIT_FAILURE;
}
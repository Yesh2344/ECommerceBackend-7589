#include "PaymentProcessor.h"
#include "Config.h"
#include "Logger.h"
#include <random>
#include <chrono>

class PayPalProcessor : public PaymentProcessor {
public:
    PayPalProcessor() {
        auto cfg = Config::instance();
        clientId_ = cfg.get<std::string>("PAYPAL_CLIENT_ID").value_or("UNKNOWN");
        secret_   = cfg.get<std::string>("PAYPAL_SECRET").value_or("UNKNOWN");
    }

    bool process(double amount) override {
        Logger::instance().log(Logger::Level::INFO,
            "Processing PayPal payment of $" + std::to_string(amount));
        std::this_thread::sleep_for(std::chrono::milliseconds(700));

        bool approved = randomBool();
        if (approved) {
            Logger::instance().log(Logger::Level::INFO,
                "PayPal payment successful.");
        } else {
            Logger::instance().log(Logger::Level::WARN,
                "PayPal payment failed.");
        }
        return approved;
    }

private:
    std::string clientId_;
    std::string secret_;

    bool randomBool() {
        static std::mt19937 rng{ std::random_device{}() };
        std::uniform_int_distribution<int> dist(0, 1);
        return dist(rng) == 1;
    }
};

extern "C" PaymentProcessor* create() {
    return new PayPalProcessor();
}
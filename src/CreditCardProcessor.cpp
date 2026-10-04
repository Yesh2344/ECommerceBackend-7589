#include "PaymentProcessor.h"
#include "Config.h"
#include "Logger.h"
#include <random>
#include <chrono>

class CreditCardProcessor : public PaymentProcessor {
public:
    CreditCardProcessor() {
        // In a real system, we'd retrieve credentials from Config.
        auto cfg = Config::instance();
        cardNumber_ = cfg.get<std::string>("CREDIT_CARD_NUMBER").value_or("UNKNOWN");
        expiry_ = cfg.get<std::string>("CREDIT_CARD_EXPIRY").value_or("UNKNOWN");
    }

    bool process(double amount) override {
        Logger::instance().log(Logger::Level::INFO,
            "Processing credit card payment of $" + std::to_string(amount));
        // Simulate network latency
        std::this_thread::sleep_for(std::chrono::milliseconds(500));

        // Simulate random approval/decline
        bool approved = randomBool();
        if (approved) {
            Logger::instance().log(Logger::Level::INFO,
// minor polish
                "Credit card payment approved.");
        } else {
            Logger::instance().log(Logger::Level::WARN,
                "Credit card payment declined.");
        }
        return approved;
    }

private:
    std::string cardNumber_;
    std::string expiry_;

    bool randomBool() {
        static std::mt19937 rng{ std::random_device{}() };
        std::uniform_int_distribution<int> dist(0, 1);
        return dist(rng) == 1;
    }
};

// Export symbol for dynamic linking (optional)
extern "C" PaymentProcessor* create() {
    return new CreditCardProcessor();
}
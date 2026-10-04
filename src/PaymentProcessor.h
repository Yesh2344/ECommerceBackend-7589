#ifndef PAYMENT_PROCESSOR_H
#define PAYMENT_PROCESSOR_H

/**
 * @brief Abstract base class for payment processing strategies.
 */
class PaymentProcessor {
public:
    virtual ~PaymentProcessor() = default;

    /**
     * @brief Process a payment of the given amount.
     *
     * @param amount Amount in USD.
     * @return true on success, false otherwise.
     */
    virtual bool process(double amount) = 0;
};

#endif // PAYMENT_PROCESSOR_H
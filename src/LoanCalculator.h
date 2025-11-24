#ifndef LOANCALCULATOR_H_INCLUDED
#define LOANCALCULATOR_H_INCLUDED

#include <string>
#include <stdexcept>

/**
 * @class LoanCalculator
 * @brief Provides functionality for loan-related financial calculations.
 *
 * This class stores loan parameters such as amount, interest rate,
 * monthly payment, periods, and opening fees, and provides functions
 * for calculating balance, monthly payments, number of payments, etc.
 */
class LoanCalculator
{
public:

    /**
     * @brief Constructs an empty calculator with default values.
     */
    LoanCalculator();

    ~LoanCalculator() {}

    //
    // --- Setters / Getters ---
    //

    /**
     * @brief Sets the total loan principal amount.
     * @param A Total loan amount.
     * @throws std::invalid_argument If A <= 0.
     */
    inline void setAmount(float A) {
        if(A <= 0)
            throw std::invalid_argument("Loan amount must be > 0");
        amount_ = A;
        amountSet_ = true;
    }

    /**
     * @brief Returns the loan amount.
     * @return Loan amount.
     */
    inline float getAmount() const { return amount_; }

    /**
     * @brief Sets the initial down-payment.
     * @param v Initial payment value.
     */
    inline void setInitialPayment(float v) { initialPayment_ = v; }

    /**
     * @brief Returns the initial payment.
     * @return Initial payment.
     */
    inline float getInitialPayment() const { return initialPayment_; }

    /**
     * @brief Sets the annual interest rate (percentage).
     *
     * Also calculates periodic (monthly) rate internally.
     *
     * @param i Interest rate in percent.
     * @throws std::invalid_argument If i <= 0.
     */
    inline void setInterest(float i) {
        if(i <= 0)
            throw std::invalid_argument("Interest must be > 0");
        interest_ = i;
        interestPeriodic_ = i/100.0f/12.0f;
        interestSet_ = true;
    }

    /**
     * @brief Returns the annual interest rate.
     * @return Annual interest percent.
     */
    inline float getInterest() const { return interest_; }

    /**
     * @brief Returns the monthly periodic interest rate.
     * @return Monthly interest factor.
     */
    inline float getPeriodicInterest() const { return interestPeriodic_; }

    /**
     * @brief Sets the monthly payment amount.
     * @param P Monthly payment.
     */
    inline void setPayment(float P) {
        payment_ = P;
        paymentSet_ = true;
    }

    /**
     * @brief Returns monthly payment.
     * @return Monthly payment.
     */
    inline float getPayment() const { return payment_; }

    /**
     * @brief Sets total number of payments.
     * @param N Number of payments.
     * @throws std::invalid_argument If N <= 0.
     */
    inline void setPeriodTotal(int N) {
        if(N <= 0)
            throw std::invalid_argument("Total period must be > 0");
        periodTotal_ = N;
        periodTotalSet_ = true;
    }

    /**
     * @brief Returns total number of payments.
     * @return Period count.
     */
    inline int getPeriodTotal() const { return periodTotal_; }

    /**
     * @brief Sets number of elapsed payments.
     * @param n Number elapsed.
     */
    inline void setPeriodElapsed(int n) {
        periodElapsed_ = n;
        periodElapsedSet_ = true;
    }

    /**
     * @brief Returns number of elapsed payments.
     * @return Number elapsed.
     */
    inline int getPeriodElapsed() const { return periodElapsed_; }

    /**
     * @brief Sets opening fee value.
     * @param fee Opening fee amount.
     */
    inline void setOpeningFee(float fee) { openingFee_ = fee; }

    /**
     * @brief Returns opening fee amount.
     * @return Opening fee.
     */
    inline float getOpeningFee() const { return openingFee_; }

    /**
     * @brief Sets opening fee percentage.
     * @param percent Opening percent.
     */
    inline void setOpeningPercent(float percent) { openingPercent_ = percent; }

    /**
     * @brief Returns opening percent.
     * @return Opening percent.
     */
    inline float getOpeningPercent() const { return openingPercent_; }

    /**
     * @brief Resets the calculator and clears all values.
     */
    inline void reset() {
        amount_ = initialPayment_ = interest_ = interestPeriodic_ = payment_ = openingFee_ = openingPercent_ = 0.0f;
        periodTotal_ = periodElapsed_ = 0;
        amountSet_ = false;
        interestSet_ = false;
        paymentSet_ = false;
        periodTotalSet_ = false;
        periodElapsedSet_ = false;
    }

    //
    // Calculation functions
    //

    /**
     * @brief Computes remaining loan balance.
     * @return Remaining balance.
     */
    float calculateLoanBalance();

    /**
     * @brief Computes monthly payment amount.
     * @return Payment amount.
     */
    float calculatePayment();

    /**
     * @brief Computes number of required payments.
     * @return Count of payments.
     */
    float calculateNumberPayments();

    /**
     * @brief Computes principal loan amount.
     * @return Loan amount.
     */
    float calculateLoanAmount();

    /**
     * @brief Computes the annual interest rate based on values.
     * @return Interest rate.
     */
    float calculateInterestRate();

    /**
     * @brief Computes effective annual interest rate including fees.
     * @return Effective interest %.
     */
    float calculateEffectiveInterestRate();

    /**
     * @brief Converts current loan data into string format.
     * @return A formatted string.
     */
    std::string toString();

private:
    float amount_ = 0.0f;
    bool  amountSet_ = false;

    float initialPayment_ = 0.0f;

    float interest_ = 0.0f;
    float interestPeriodic_ = 0.0f;
    bool  interestSet_ = false;

    float payment_ = 0.0f;
    bool  paymentSet_ = false;

    int   periodTotal_ = 0;
    bool  periodTotalSet_ = false;

    int   periodElapsed_ = 0;
    bool  periodElapsedSet_ = false;

    float openingFee_ = 0.0f;
    float openingPercent_ = 0.0f;
};

#endif // LOANCALCULATOR_H_INCLUDED

#ifndef LOANCALCULATOR_H_INCLUDED
#define LOANCALCULATOR_H_INCLUDED

#include <string>
#include <stdexcept>

class LoanCalculator
{
public:
    LoanCalculator();
    ~LoanCalculator() {}

    //
    // --- Setters / Getters ---
    //

    inline void setAmount(float A) {
        if(A <= 0)
            throw std::invalid_argument("Loan amount must be > 0");
        amount_ = A;
        amountSet_ = true;
    }
    inline float getAmount() const { return amount_; }

    inline void setInitialPayment(float v) { initialPayment_ = v; }
    inline float getInitialPayment() const { return initialPayment_; }

    inline void setInterest(float i) {
        if(i <= 0)
            throw std::invalid_argument("Interest must be > 0");
        interest_ = i;
        interestPeriodic_ = i/100.0f/12.0f;
        interestSet_ = true;
    }
    inline float getInterest() const         { return interest_; }
    inline float getPeriodicInterest() const { return interestPeriodic_; }

    inline void setPayment(float P) {
        payment_ = P;
        paymentSet_ = true;
    }
    inline float getPayment() const { return payment_; }

    inline void setPeriodTotal(int N) {
        if(N <= 0)
            throw std::invalid_argument("Total period must be > 0");
        periodTotal_ = N;
        periodTotalSet_ = true;
    }
    inline int getPeriodTotal() const { return periodTotal_; }

    inline void setPeriodElapsed(int n) {
        periodElapsed_ = n;
        periodElapsedSet_ = true;
    }
    inline int getPeriodElapsed() const { return periodElapsed_; }

    inline void setOpeningFee(float fee) { openingFee_ = fee; }
    inline float getOpeningFee() const   { return openingFee_; }

    inline void setOpeningPercent(float percent) { openingPercent_ = percent; }
    inline float getOpeningPercent() const       { return openingPercent_; }

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
    // Calculations
    //

    float calculateLoanBalance();
    float calculatePayment();
    float calculateNumberPayments();
    float calculateLoanAmount();
    float calculateInterestRate();
    float calculateEffectiveInterestRate();

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

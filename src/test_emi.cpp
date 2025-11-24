#include <gtest/gtest.h>
#include <cmath>
#include "LoanCalculator.h"

static bool isFiniteFloat(float v) { return std::isfinite((double)v); }

// Test 1: Normal EMI calculation (compare to independent formula)
TEST(LoanCalculatorTest, NormalEmiCalculation) {
    LoanCalculator calc;
    calc.setAmount(200000.0f);     // principal
    calc.setInterest(6.5f);       // yearly percent
    calc.setPeriodTotal(360);     // 30 years * 12

    // Independent calculation using long double for reference
    long double A = 200000.0L;
    long double i = (6.5L/100.0L)/12.0L;
    int N = 360;
    long double expected = (i * A) / (1.0L - powl(1.0L + i, - (long double)N));

    float payment = calc.calculatePayment();
    EXPECT_TRUE(isFiniteFloat(payment));
    EXPECT_NEAR((double)payment, (double)expected, 1e-3);
}

// Test 2: Invalid input handling (negative amount or zero interest)
TEST(LoanCalculatorTest, InvalidInputHandling) {
    LoanCalculator calc;

    // negative amount should throw
    EXPECT_THROW(calc.setAmount(-1000.0f), std::invalid_argument);

    // zero or negative interest should throw
    EXPECT_THROW(calc.setInterest(0.0f), std::invalid_argument);
    EXPECT_THROW(calc.setInterest(-5.0f), std::invalid_argument);

    // If we set amount and set a too-small payment, calculating number payments should throw.
    calc.setAmount(10000.0f);
    calc.setInterest(5.0f);
    calc.setPayment(1.0f); // absurdly small payment
    EXPECT_THROW(calc.calculateNumberPayments(), std::invalid_argument);
}

// Test 3: Large tenure calculations without overflow
TEST(LoanCalculatorTest, LargeTenureNoOverflow) {
    LoanCalculator calc;
    calc.setAmount(10000.0f);
    calc.setInterest(5.0f);
    // Very large number of months (stress test). Should not overflow or return NaN/Inf.
    calc.setPeriodTotal(100000); // 100k months
    float payment = calc.calculatePayment();
    EXPECT_TRUE(isFiniteFloat(payment));
    EXPECT_GT(payment, 0.0f);
}

#include <gtest/gtest.h>
#include <cmath>
#include "../LoanCalculator.h"
using namespace std;

static bool isFiniteFloat(float v) { return std::isfinite((double)v); }

// Normal EMI calculation (compare to independent formula)
TEST(LoanCalculatorTest, NormalEmiCalculation) {
    LoanCalculator calc;
    calc.setAmount(200000.0f);     
    calc.setInterest(6.5f);      
    calc.setPeriodTotal(360);     

    long double A = 200000.0L;
    long double i = (6.5L/100.0L)/12.0L;
    int N = 360;
    long double expected = (i * A) / (1.0L - powl(1.0L + i, - (long double)N));

    float payment = calc.calculatePayment();
    EXPECT_TRUE(isFiniteFloat(payment));
    EXPECT_NEAR((double)payment, (double)expected, 1e-3);
}

// Invalid input handling (negative amount or zero interest)
TEST(LoanCalculatorTest, InvalidInputHandling) {
    LoanCalculator calc;

   
    EXPECT_THROW(calc.setAmount(-1000.0f), invalid_argument);

    
    EXPECT_THROW(calc.setInterest(0.0f), invalid_argument);
    EXPECT_THROW(calc.setInterest(-5.0f), invalid_argument);

    calc.setAmount(10000.0f);
    calc.setInterest(5.0f);
    calc.setPayment(1.0f); 
    EXPECT_THROW(calc.calculateNumberPayments(), invalid_argument);
}

// Large tenure calculations without overflow
TEST(LoanCalculatorTest, LargeTenureNoOverflow) {
    LoanCalculator calc;
    calc.setAmount(10000.0f);
    calc.setInterest(5.0f);
    calc.setPeriodTotal(100000); // 100k months
    float payment = calc.calculatePayment();
    EXPECT_TRUE(isFiniteFloat(payment));
    EXPECT_GT(payment, 0.0f);
}

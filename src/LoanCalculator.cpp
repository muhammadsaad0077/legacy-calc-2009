#include <iostream>
#include <cmath>
#include <stdexcept>
#include <sstream>
#include <string>

#include "LoanCalculator.h"
using namespace std;

LoanCalculator::LoanCalculator()
  : amountSet_(false),
    initialPayment_(0.0f),
    interestSet_(false),
    paymentSet_(false),
    periodTotalSet_(false),
    periodElapsedSet_(false),
    openingFee_(0.0f),
    openingPercent_(0.0f)
{
}

float LoanCalculator::calculateLoanBalance()
{
  if(!amountSet_ || !interestSet_ || !periodElapsedSet_ || !paymentSet_)
    throw invalid_argument("Must set loan amount, interest, and elapsed period for this calculation");

  const float base = 1.0f + interestPeriodic_;
  const float powBaseN = pow(base, periodElapsed_);

  return (amount_ * powBaseN)
       - (payment_ / interestPeriodic_) * (powBaseN - 1.0f);
}

float LoanCalculator::calculatePayment()
{
  long double i = interestPeriodic_;
  long double totalAmount = amount_ - initialPayment_;
  totalAmount += openingFee_ + (totalAmount * (openingPercent_/100.0));

  long double denom = (1.0L - pow(1.0L + i, - (long double)periodTotal_));
  long double result = (i * totalAmount) / denom;

  return (float)result;
}

float LoanCalculator::calculateNumberPayments()
{
  if(!amountSet_ || !interestSet_ || !paymentSet_)
    throw invalid_argument("Must set loan amount, interest, and payment for this calculation");

  long double i = interestPeriodic_;
  long double arg = 1.0L - (i * amount_ / payment_);

  if(!(arg > 0.0L))
    throw invalid_argument("Payment too small relative to interest, loan will never be repaid.");

  long double numerator = -log10l(arg);
  long double denominator = log10l(1.0L + i);

  if(!(denominator > 0.0L))
    throw invalid_argument("Invalid periodic interest value");

  return (float)(numerator / denominator);
}

float LoanCalculator::calculateLoanAmount()
{
  if(!paymentSet_ || !interestSet_ || !periodTotalSet_)
    throw invalid_argument("Must set payment, interest, and total period");

  const float base = 1.0f + interestPeriodic_;

  return (payment_/interestPeriodic_) *
         (1.0f - pow(base, -periodTotal_));
}

float LoanCalculator::calculateInterestRate()
{
  if(!amountSet_ || !paymentSet_ || !periodTotalSet_)
    throw invalid_argument("Must set amount, payment, and total period");

  float q = log10(1.0 + 1.0/periodTotal_) / log10(2.0);

  float monthlyInterest =
    pow(pow(1.0 + payment_/amount_, 1.0/q) -1.0, q) -1.0;

  return monthlyInterest * 12.0f * 100.0f;
}

float LoanCalculator::calculateEffectiveInterestRate()
{
  if(!amountSet_ || !periodTotalSet_)
    throw invalid_argument("Must set amount and total period");

  float payment = calculatePayment();
  float totalAmount = amount_ - initialPayment_;

  float q = log10(1.0 + 1.0/periodTotal_) / log10(2.0);

  float monthlyInterest =
    pow(pow(1.0 + payment/totalAmount, 1.0/q) -1.0, q) -1.0;

  return monthlyInterest * 12.0f * 100.0f;
}

string LoanCalculator::toString()
{
  stringstream ss;

  if(amountSet_)           ss << "Initial Amount:      " << amount_ << "\n";
  if(initialPayment_ != 0) ss << "Initial Payment:     " << initialPayment_ << "\n";
  if(initialPayment_ != 0) ss << "Actual Loan Amount:  " << (amount_ - initialPayment_) << "\n";
  if(interestSet_)         ss << "Yearly Interest:     " << interest_ << "%\n";
  if(paymentSet_)          ss << "Monthly payment:     " << payment_ << "\n";
  if(periodTotalSet_)      ss << "Loan Period:         " << periodTotal_ << " months\n";
  if(periodElapsedSet_)    ss << "Elapsed Period:      " << periodElapsed_ << " months\n";
  if(openingFee_ != 0.0f)  ss << "Opening Fee:         " << openingFee_ << "\n";
  if(openingPercent_ != 0) ss << "Opening Fee %:       " << openingPercent_ << "% = "
                                << (openingPercent_/100)*(amount_ - initialPayment_) << "\n";

  return ss.str();
}

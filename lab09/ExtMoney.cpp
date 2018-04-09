#include "ExtMoney.h"
#include <iostream>
using namespace std;


ExtMoneyType::ExtMoneyType(long newDollars, long newCents, const string name):
MoneyType(newDollars, newCents)
//constructor
{
	currency = name;
}

ExtMoneyType::ExtMoneyType():MoneyType()            
//default constructor  
{
	currency = "\0";
}

string ExtMoneyType::CurrencyIs() const
// Post: Class member currency is returned.
{
	return currency;
}


void ExtMoneyType::Initialize(long newDollars, long newCents, string name)
// Post: dollars is set to newDollars; cents is set to newCents.
{
	MoneyType::Initialize(newDollars, newCents);
	currency = name;
}

void ExtMoneyType::Print() const
// Post: print the member dollars and cents.
{
  cout << MoneyType::DollarsAre() << " " << MoneyType::CentsAre() << " " << currency << " ";
}


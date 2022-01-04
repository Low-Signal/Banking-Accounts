/*
Name: Daimeun Praytor
FSUID: Dcp18z
Section: 7
*/

#include "Account.h"

Account::Account()
{
    cout << "Please enter the first name of the account.>: ";
    cin >> firstName;

    cout << "Please enter the first name of the account.: ";
    cin >> lastName;
}

Account::Account(const string ln, const string fn, const string type)
{
    firstName = fn;
    lastName = ln;
    accType = type;
}

Account::~Account()
{
}

string Account::getFirstName() const
{
    return firstName;
}

string Account::getLastName() const
{
    return lastName;
}

string Account::getAccType() const
{
    return accType;
}

Savings::Savings(const string fn, const string ln, const string type, 
double currentBal, double interestRate):
        Account(ln, fn, type)
{
    this->currentBal = currentBal;
    this->interestRate = interestRate;
}

double Savings::ProjectedBalance() const
{   
    // Formula for savings projected balance.
    double projectedBalance = currentBal * (1 + interestRate);

    return projectedBalance;
}

double Savings::getCurrentBal() const
{
    return currentBal;
}

double Savings::getInterestRate() const
{
    return interestRate;
}

Checking::Checking(const string fn, const string ln, const string type,
double currentBal):
        Account(ln, fn, type)
{
    this->currentBal = currentBal;
}

double Checking::ProjectedBalance() const
{
    // Formula for checking projected balance.
    double projectedBalance = currentBal + 0.1;

    return projectedBalance;
}

double Checking::getCurrentBal() const
{
    return currentBal;
}


Investment::Investment(string fn, string ln, string type, double* etfArr):
        Account(ln, fn, type)
{   
    // Fills the investment accounts member data.
    for(int i = 0; i < 5; i++)
    {   
        // If there are less than 5 ETF's (for garbage data elements)
        if(*(etfArr+i*4+0) > 99999999 || *(etfArr+i*4+0) < -99999999)
            break;

        /* Each row has 4 columns, for the [0] index.
        These set each peice of member data.*/
        invested[i] = *(etfArr+i*4+0);              
        initialValPerShare[i] = *(etfArr+i*4+1);
        currentValPerShare[i] = *(etfArr+i*4+2);
        interestRate[i] = *(etfArr+i*4+3);

        //  Calculates the current value.
        currentVal[i] = ((invested[i]/initialValPerShare[i])
         * currentValPerShare[i]);
    }

}

double Investment::ProjectedBalance() const
{
    double divTotal = 0;
    double currentValTotal = 0;

    // Gets the total dividend yield and the total current value of all ETF's
    for(int i = 0; i < 5; i++)
    {
        // If there are less than 5 ETF's (for garbage data elements)
        if(invested[i] > 99999999 || invested[i] < -99999999)
            break;

        divTotal += (interestRate[i] * invested[i]);
        currentValTotal += currentVal[i];
    }

    /* Formula for investments projected balance 
    (sum of dividends + sum of current value)*/
    int projectedBalance = currentValTotal + divTotal;

    return projectedBalance;
}

double* Investment::getInvested()
{
    double (*ptr)[5];
    ptr = &invested;

    return *ptr;
}

double* Investment::getIVS()
{
    double (*ptr)[5];
    ptr = &initialValPerShare;

    return *ptr;
}

double* Investment::getCVS()
{
    double (*ptr)[5];
    ptr = &currentValPerShare;

    return *ptr;
}

double* Investment::getIR()
{
    double (*ptr)[5];
    ptr = &interestRate;

    return *ptr;
}

double* Investment::getCV()
{
    double (*ptr)[5];
    ptr = &currentVal;

    return *ptr;
}




/*
Name: Daimeun Praytor
FSUID: Dcp18z
Section: 7
*/

#ifndef __ACCOUNT_H
#define __ACCOUNT_H

#include <iostream>
#include <cstring>
#include <string>
#include <iomanip>

using namespace std;

class Account
{
    public:
        virtual ~Account();
        // Used to calculate the projected balance of each account subclass.
        virtual double ProjectedBalance() const =0;

        // Various get functions for derived class member data.
        // Return 0 to avoid compile errors on linprog.    
        virtual double getCurrentBal() const {return 0;};
        virtual double getInterestRate() const {return 0;};
        virtual double* getInvested(){return 0;};
        virtual double* getIVS(){return 0;};
        virtual double* getCVS(){return 0;};
        virtual double* getIR(){return 0;};
        virtual double* getCV(){return 0;};

        // Used to get account member data.
        string getFirstName() const;
        string getLastName() const;
        string getAccType() const;

    protected:
        Account();          // Default constructor.

        // Paramerterized constructor.
        Account(const string fn, const string ln, const string type);  

        string firstName;   // Stores first name of account.
        string lastName;    // Stores last name of account.
        string accType;     // Stores the account type.

};

class Savings : public Account
{
    public:
        // Constructor.
        Savings(const string fn, const string ln, const string type,
         double currentBal, double interestRate);

        double ProjectedBalance() const;      // Calculates the projected balance.

        double getCurrentBal() const;         // Gets current balance.
        double getInterestRate() const;       // Gets the interest rate.


    private:
        double currentBal;       // Stores the current balance.
        double interestRate;     // Stores the intrest rate.
};

class Checking : public Account
{
    public:
        // Constructor
        Checking(const string fn, const string ln, const string type,
         double currentBal);

        double ProjectedBalance() const;  // Calculates the projected balance.

        double getCurrentBal() const;     // Gets the current Balance.

    private:
        double currentBal;      // Stores the current balance.
};

class Investment : public Account
{
    public:
        // Constructor.
        Investment(string fn, string ln, string type, double* arr);

        double ProjectedBalance() const;  // Calculates the projected balance.

        double* getInvested();    // Gets invested array.
        double* getIVS();         // Gets initial value per share array.
        double* getCVS();         // Gets current value per share array.
        double* getIR();          // Gets interest rate array.
        double* getCV();          // Gets the current value array.

    private:
        double invested[5];             // Stores invested ET's
        double initialValPerShare[5];   // Stores initial value per share ET's.
        double currentValPerShare[5];   // Stores current value per share ET's.
        double interestRate[5];         // Stores interest rate ET's
        double currentVal[5];           // Stores current value ET's
};

#endif
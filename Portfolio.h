/*
Name: Daimeun Praytor
FSUID: Dcp18z
Section: 7
*/

#ifndef __PORTFOLIO_H
#define __PORTFOLIO_H

#include "Account.h"

class Portfolio
{
    public:
        Portfolio();    // Default constructor.
        ~Portfolio();   // Destructor.

        /* For importing the file, returns false if the file does not
        exist or cannot be opened. Otherwise return success.*/
        bool importFile(const char* filename);         

        // Creates banking report and writes it to given output file.
        bool createReportFile(const char* filename); 

        // Prints current list of accounts.  
        void showAccounts() const;

        // Sorts the accounts by name.
        void Sort();                    

    private:
        // Prints headers, used in createReportFile.
        void printSummaryHeader(ofstream& outputFile) const;
        
        void Grow();        // Grows the alist array by one.

        int size;           // For the total size of the alist.
        int currentAcc;     // Tracks index of account being entered.
        Account** alist;    // Array of account pointers. 
};

#endif
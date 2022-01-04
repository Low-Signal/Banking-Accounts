/*
Name: Daimeun Praytor
FSUID: Dcp18z
Section: 7
*/

#include "Portfolio.h"
#include <fstream>


Portfolio::Portfolio()
{
    size = 0;
    currentAcc = 0;
    alist = new Account*[1];
}

Portfolio::~Portfolio()
{
    if(alist != nullptr) 
    { 
        for (int i = 0; i < size; i++) 
        {
            delete alist[i];
            alist[i] = nullptr;
        }
        delete[] alist;
        alist = nullptr;
    }
}

bool Portfolio::importFile(const char* filename)
{
    int numAccounts;
    ifstream inputFile;         // Creates a input stream object.

    // Attaches user file to inputFile object in append mode.
    inputFile.open(filename);   

    // If the file name is invalid, return false.
    if (!inputFile)          
    {
        cout << "Invalid file. No data imported" << endl;
        return false;
    }

    inputFile >> numAccounts;   // Gets the number of new accounts.
    inputFile.get();            // Gets rid of newline

    // Creates a account object for each new account.
    for(int i = 0; i < numAccounts; i++)
    {
        Grow();             // Grows the alist array to hold new Accounts.

        string fn;
        string ln;
        string type;
        getline(inputFile, ln, ',');        // Gets the first name.
        inputFile.get();                    // Gets rid of space.
        getline(inputFile, fn);             // Gets the last name.
        getline(inputFile, type, ' ');      // Gets the type.

        // If creating a savings account.
        if(type == "Savings")
        {
            
            double currentBal;          // To store current balance.
            double interestRate;        // To store interest rate.

            inputFile >> currentBal >> interestRate;
            inputFile.get();    // Gets rid of newline.

            // Adds new savings object to alist.
            alist[currentAcc] = new Savings(fn, ln, type, currentBal,
            interestRate);

            currentAcc++;
        }

        // If creating a checking account.
        if(type == "Checking")
        {
            double currentBal;

            inputFile >> currentBal;
            inputFile.get();     // Gets rid of newline.

            // Adds new checking object to alist.
            alist[currentAcc] = new Checking(fn, ln, type, currentBal);
            currentAcc++;

        }

        // If creating an investment account.
        if(type == "Investment")
        {
            double etfArr[5][4];

            for(int j = 0; j < 5; j++)
            {
                // Break if its the end of line.
                if(inputFile.peek() == '\n')
                    break;

                // Fills the 2d array with [etf number][data]
                for(int k = 0; k < 4; k++)
                {
                    inputFile >> etfArr[j][k];
                }

            }

            inputFile.get();    // Gets rid of newline character.

            // Adds new investment object to alist.
            alist[currentAcc] = new Investment(fn, ln, type, (double*)etfArr);
            currentAcc++;
        }

    }

    inputFile.close();
    return true;
}

bool Portfolio::createReportFile(const char* filename)
{
    ofstream outputFile;        // Creates a output stream object.
    outputFile.open(filename);  // Attaches user file to outputFile object.

    if (!outputFile)             // If the file name is invalid, return false.
    {
        cout << "Invalid file. No data exported" << endl;
        return false;
    }

    int numOfSavingsAcc = 0;        // Tracks the number of savings accounts.
    int numOfCheckingAcc = 0;       // Tracks the number of checking accounts.
    int numOfInvestmentAcc = 0;     // Tracks the number of investment accounts

    // Tracks the total projected value of savings accounts.
    double savingsProjTotal = 0;        
    // Tracks the total projected value of checking accounts.
    double checkingProjTotal = 0;       
    // Tracks the total projected value of investment accounts.
    double investmentProjTotal = 0;     


    outputFile << fixed << showpoint << setprecision(2);

    outputFile << "Banking Summary" << endl;
    outputFile << "---------------------" << endl;

    outputFile << "\nSaving Accounts" << endl;
    outputFile << endl;
    printSummaryHeader(outputFile);     // Prints header to file.

    // Prints all savings accounts to file.
    for(int i = 0; i < size; i++)
    {
        if(alist[i]->getAccType() == "Savings")
        {
            string name = alist[i]->getFirstName() + " " 
            + alist[i]->getLastName();

            outputFile << setw(45) << left << name;
            outputFile << setw(15) << right << alist[i]->getCurrentBal();
            outputFile << setw(20) << right << alist[i]->ProjectedBalance();
            outputFile << endl;
            numOfSavingsAcc++;
            savingsProjTotal += alist[i]->ProjectedBalance();
        }
    }
  
    outputFile << "\nChecking Accounts" << endl;
    outputFile << endl;
    printSummaryHeader(outputFile);     // Prints header.

    // Prints all checking accounts to file.
    for(int i = 0; i < size; i++)
    {
        if(alist[i]->getAccType() == "Checking")
        {
            string name = alist[i]->getFirstName() + " " 
            + alist[i]->getLastName();

            outputFile << setw(45) << left << name;
            outputFile << setw(15) << right << alist[i]->getCurrentBal();
            outputFile << setw(20) << right << alist[i]->ProjectedBalance();
            outputFile << endl;
            numOfCheckingAcc++;  
            checkingProjTotal += alist[i]->ProjectedBalance();        
        }
    }

    outputFile << "\nInvestment Accounts" << endl;
    outputFile << endl;
    printSummaryHeader(outputFile);     // Prints header.

    // Prints all investment accounts to file.
    for(int i = 0; i < size; i++)
    {
        if(alist[i]->getAccType() == "Investment")
        {
            double totalInvested = 0;
            double* investedArr = alist[i]->getInvested();

            for(int j = 0; j < 5; j++)
            {   
                // If there are less than 5 ETF's (for garbage data elements)
                if(investedArr[j] > 9999999999 || investedArr[j] < -999999999)
                    break;

                totalInvested += investedArr[j];
            }

            string name = alist[i]->getFirstName() + " " 
            + alist[i]->getLastName();

            outputFile << setw(45) << left << name;
            outputFile << setw(15) << right << totalInvested;
            outputFile << setw(20) << right << alist[i]->ProjectedBalance();
            outputFile << endl;
            numOfInvestmentAcc++; 
            investmentProjTotal += alist[i]->ProjectedBalance();          
        }
    }

    // These get the average projected totals of each account type.
    double savingsProjAvg = savingsProjTotal / numOfSavingsAcc;
    double checkingProjAvg = checkingProjTotal / numOfCheckingAcc;
    double investmentProjAvg = investmentProjTotal / numOfInvestmentAcc;

    outputFile << "\n\nOverall Account distribution" << endl;

    outputFile << setw(16) << left << "Savings:";
    outputFile << setw(4) << left << numOfSavingsAcc;
    outputFile << "-";
    outputFile << setw(11) << right << savingsProjAvg << endl;

    outputFile << setw(16) << left << "Checking";
    outputFile << setw(4) << left << numOfCheckingAcc;
    outputFile << "-";
    outputFile << setw(11) << right << checkingProjAvg << endl;

    outputFile << setw(16) << left << "Investment";
    outputFile << setw(4) << left << numOfInvestmentAcc;
    outputFile << "-";
    outputFile << setw(11) << right << investmentProjAvg << endl;

    outputFile.close();
    return true;
}

void Portfolio::showAccounts() const
{
    cout << setw(41) << left << "Holder";
    cout << setw(17) << left << "Type";
    cout << "Balance\n" << endl;
    
    for(int i = 0; i < size; i++)
    {   
        // For two decimals.
        cout << fixed << showpoint << setprecision(2);

        // These print the last name, first name and account type.          
        cout << setw(20) << left << alist[i]->getLastName();
        cout << setw(21) << left << alist[i]->getFirstName();
        cout << setw(17) << left << alist[i]->getAccType();

        if(alist[i]->getAccType() == "Savings")
        {
            cout << setw(7) << right << alist[i]->getCurrentBal();
        }

        if(alist[i]->getAccType() == "Checking")
        {
            cout << setw(7) << right << alist[i]->getCurrentBal();
        }

        if(alist[i]->getAccType() == "Investment")
        {
            double totalInvested = 0;
            double* investedArr = alist[i]->getInvested();

            for(int j = 0; j < 5; j++)
            {
                // If there are less than 5 ETF's (for garbage data elements)
                if(investedArr[j] > 999999999 || investedArr[j] < -999999999)
                    break;

                totalInvested += investedArr[j];
            }

            cout << setw(7) << right << totalInvested;

        }
        cout << endl;
    }
}

void Portfolio::Sort()
{
    int tempSize = 1;
    Account** tempArr = new Account*[tempSize];     // One element array.

    for(int i = 0; i < currentAcc-1; i++)
    {
        for(int j = i + 1; j < currentAcc; j++)
        {
            // If last names are the same sort by first.
            if(alist[i]->getLastName() == alist[j]->getLastName())
            {   
                // Sorts by first name.
                if(alist[i]->getFirstName() > alist[j]->getFirstName())
                {
                    tempArr[0] = alist[i];      //Stores first in temp.
                    alist[i] = alist[j];        //Second replaces first.
                    alist[j] = tempArr[0];      //Temp then replaces second.
                }
                continue;
            }

            // If last names are different sort by them.
            if(alist[i]->getLastName() > alist[j]->getLastName())
            {
                    tempArr[0] = alist[i];      //Stores first in temp.
                    alist[i] = alist[j];        //Second replaces first.
                    alist[j] = tempArr[0];      //Temp then replaces second.
            }
        }
    }

    delete [] tempArr;
}

void Portfolio::Grow()
{
     Account** tempList = new Account*[size+1];


    // Fills temp array with current lists pointers.
    for(int i = 0; i < size+1; i++)
    {
        tempList[i] = alist[i];
    }

    delete [] alist;     // Clears the old list.

    alist = tempList;    // Sets the current account pointers to the new ones.

    size++;     // Adds one to the size counter.

}

void Portfolio::printSummaryHeader(ofstream& outputFile) const
{
    outputFile << setw(45) << left << "Holder's Name";
    outputFile << setw(15) << left << "Initial Balance";
    outputFile << setw(20) << right << "Projected Balance" << endl;
    outputFile << setw(80) << setfill('-') << "" << endl;
    outputFile << setfill(' ');                     // Resets fill character.
}
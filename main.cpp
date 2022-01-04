/*
Name: Daimeun Praytor
FSUID: Dcp18z
Section: 7
*/

#include <iostream>
#include <cctype>       // For toupper().
#include "Portfolio.h"

void printMenu();       // Prints option menu.
char optionSelect();    // Gets a valid option.

int main()
{
    Portfolio portfolio;

    char option; // For menu option input.

    printMenu();

    do
    {
        option = optionSelect();    // Gets valid menu option

        // Executes functions based on option selected.
        switch (option)
        {
            // For importing file.
            case 'I':   
                char fileName[30];
                cout << "Enter filename: ";
                cin >> fileName;
                portfolio.importFile(fileName);
                break;
            
            // To give a brief summary of accounts.
            case 'S':
                portfolio.showAccounts();
                break;

            // Creates a output file with the account summary.    
            case 'E':
                char fileName2[30];
                cout << "Enter filename: ";
                cin >> fileName2;
                portfolio.createReportFile(fileName2);
                break;

            // Sorts accounts by name.
            case 'O':
                portfolio.Sort();
                break;

            // Prints the menu options.
            case 'M':
                printMenu();
                break;

            // Exits program.
            case 'Q':
                cout << "\nGoodbye" << endl;
                break;
        
            default:
                break;
        }

    }while(option != 'Q');
    
    return 0;
}

void printMenu()
{
    cout << "***Portfolio Managment Menu***\n" << endl;
    cout << "I\tImport accounts from a file" << endl;
    cout << "S\tShow accounts (brief)" << endl;
    cout << "E\tExport a banking report (to file)" << endl;
    cout << "O\tSorts accounts by name" << endl;
    cout << "M\tShow this menu" << endl;
    cout << "Q\tQuit program" << endl;
}

char optionSelect()
{
    char option;

    cout << "\n> ";
    cin >> option;
    option = toupper(option);   // Converts the option to uppercase.

    // Checks if the option is valid.
    while (option != 'I' && option != 'S' && option != 'E'
     && option != 'M' && option != 'Q' && option != 'O')
    {
        cout << "Invalid option. Please re-enter." << endl;
        cout << "> ";
        cin >> option;
        option = toupper(option);
    }

    return option;

}
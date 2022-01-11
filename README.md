# Banking-Accounts
* Keeps track of banking account portfolios (Checking/Savings/Investments) for users and prints a statement.
* Takes in a text file of the portfolio consisting of multiple users and various account types.

# Input file Formatting<br />

The first line represents the number of users on the file to be imported.<br />
After this line is the first of the users last and first name followed by the account type and information on the account for example:<br />

3<br />
Alfaro, Emily-Grace<br />
Savings 900.89 0.01<br />
Jones, Bob<br />
Checking 80<br />
Smith, Julia<br />
Investments 40 80 80.84 0.02 45 20 20 0.2 150 76.3 76 0.05 45 80 76 0.07 408 5 100 0.9<br />


This represents three users in the file, the first named Emily-Grace Alfaro with a savings account that holds $900.89 at a 1% interest rate.  
The second users name is Bob Jones with $80.00 in his account, this account will have the banks default $0.10 added to the projected balance.
The third person, Julia Smith has an investment account with five EFT's. These each have 4 attributes for a total of 4(5)=20 attributes. The
first of Julia's is:

40      The amount of funds purchased in dollars.<br />
80      The initial value of the fund.<br />
80.84   The current value of the fund.<br />
0.02    The % dividend of the fund.<br />
**
This currently requires all five ETF's to be filled out.**

# Features
* File importing to read in new accounts.
* Show a brief summary of all accounts.
* Exports the report to a formatted text file including the overall account distributions.
* Ability to sort the accounts to display in alphabetical order.

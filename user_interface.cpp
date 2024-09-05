/*****************************************************************
//
//  NAME:        Min Jun Han
//
//  HOMEWORK:    Project 2
//
//  CLASS:       ICS 212
//
//  INSTRUCTOR:  Ravi Narayan
//
//  DATE:        April 22, 2024
//
//  FILE:        user_interface.cpp
//
//  DESCRIPTION:
//   This file includes the main function and getAddress function.
//   The main function makes up most of the user interface, prompting
//   the user with options, and asking for inputs like account number,
//   name, and house address. The getAddress function is a helper
//   method that's used to get the house address. A debug mode is
//   also provided to give further information to the tester.
//
*******************************************************************/

#include <iostream>
#include <string>
#include "llist.h"

using namespace std;

void getAddress(char[], int);

/*****************************************************************
//
//  Function name: main
//
//  DESCRIPTION:   The main function primarily serves to provide
//                 the various options of the bank database:
//                 add, printall, find, delete, and quit. These
//                 options all call various functions declared
//                 in the header files, which communicate with the
//                 actual database. 
//
//  Parameters:    argc (int) : The number of arguments in argv
//                 argv (char*[]) : An array of arguments passed
//                                  to the program.
//
//  Return values:  0 : Success
//
*******************************************************************/

int main(int argc, char* argv[])
{
    llist mylist; /* Creates the linked list object and allows methods to be used on it */

    string input;

    int quit = 0;
    int invalid = 0;
    int addRetVal;
    int findRetVal;
    int deleteRetVal;

    int accountNumber;
    char name[25];
    char address[45];

    string add = "add";
    string printall = "printall";
    string find = "find";
    string del = "delete";
    string bye = "quit";

    #ifdef DEBUG
    cout << "---------------------------\n";
    cout << "**CURRENTLY IN DEBUG MODE**\n";
    cout << "---------------------------\n\n";
    #endif

    cout << "Welcome to the Banking System!\n";

    while (quit == 0)
    {
        if (invalid == 1)
        {
            cout << "\nInvalid option\n\n";
            cin.clear();
            cin.ignore(80, '\n');
            invalid = 0;
        }

        cout << "Please choose an option\n\n";
        cout << "add: Add a new record in the database\n";
        cout << "printall: Print all the records in the database\n";
        cout << "find: Find record(s) with a specified account number\n";
        cout << "delete: Delete existing record(s) from the database ";
        cout << "using the account number as a key\n";
        cout << "quit: Quit the program\n\n";

        cin >> input;

        if (input.length() == 0)
        {
            invalid = 1;
        }
        else if (add.compare(0, input.length(), input) == 0)
        {
            cout << "\nPlease enter an account number\n";
            cin >> accountNumber;

            while ((cin.fail()) || (accountNumber <= 0))
            {
                cout << "\nYour input was invalid. Try again\n";
                cin.clear();
                cin.ignore(80, '\n');
                cin >> accountNumber;
            }

            cin.ignore(80, '\n');

            cout << "\nNext, enter your name\n";
            cin.getline(name, 25);

            cout << "\nFinally, enter your address. ";
            cout << "Type the asterisk character '*' and press enter when done\n";

            getAddress(address, 45);

            addRetVal = mylist.addRecord(accountNumber, name, address);

            if (addRetVal == -1)
            {
                cout << "\nCould not add record, account number already exists\n\n";
            }
            else
            {
                cout << "\nSuccessfully added record\n\n";
            }
        }
        else if (printall.compare(0, input.length(), input) == 0)
        {
            cout << mylist;
        }
        else if (find.compare(0, input.length(), input) == 0)
        {
            cout << "\nPlease enter an account number to search for\n";
            cin >> accountNumber;
            cout << endl;

            while ((cin.fail()) || (accountNumber <= 0))
            {
                cout << "\nYour input was invalid. Try again\n";
                cin.clear();
                cin.ignore(80, '\n');
                cin >> accountNumber;
            }

            cin.ignore(80, '\n');

            cout << "Searching for account number " << accountNumber << "..." << endl;
            findRetVal = mylist.findRecord(accountNumber);

            if (findRetVal == -1)
            {
                cout << "\nCould not find record with that account number\n\n";
            }
        }
        else if (del.compare(0, input.length(), input) == 0)
        {
            cout << "\nPlease enter an account number to delete\n";
            cin >> accountNumber;
            cout << endl;

            while ((cin.fail()) || (accountNumber <= 0))
            {
                cout << "\nYour input was invalid. Try again\n";
                cin.clear();
                cin.ignore(80, '\n');
                cin >> accountNumber;
            }

            cin.ignore(80, '\n');

            cout << "Searching for account number " << accountNumber << "..." << endl;
            deleteRetVal = mylist.deleteRecord(accountNumber);

            if (deleteRetVal == -1)
            {
                cout << "Could not find record with that account number\n";
            }
            else
            {
                cout << "Found account, deleting...\n";
            }
            cout << endl;
        }
        else if (bye.compare(0, input.length(), input) == 0)
        {
            cout << "\nQuitting program" << endl;
            quit = 1;
        }
        else
        {
            invalid = 1;
        }
    }
    return 0;
}

/*****************************************************************
//
//  Function name: getAddress
//
//  DESCRIPTION:   The getAddress function behaves by using the
//                 cin.get() method in a while loop, grabbing the
//                 characters typed from the user up until they
//                 type '*' followed by a new line. This way,
//                 the array preserves the user's exact inputs.
//
//  Parameters:    toInsert (char[]) : The address of the house
//                                     address char array
//                 length (int) : The length of the array
//
//  Return values:  None
//
*******************************************************************/

void getAddress(char toInsert[], int length)
{
    char c;
    int incrementer = 0;

    #ifdef DEBUG
    cout << "\n**DEBUG**: Calling the getAddress function with:\n";
    cout << "**DEBUG**: toInsert: " << toInsert << "(nothing in it yet, so garbage data)\n";
    cout << "**DEBUG**: length: " << length << endl << endl;
    #endif

    while ((cin.get(c)) && (c != '*') && (incrementer < length - 1))
    {
        toInsert[incrementer] = c;
        incrementer++;
    }

    toInsert[incrementer] = '\0';
}

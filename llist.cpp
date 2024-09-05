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
//  FILE:        llist.cpp
//  
//   DESCRIPTION:
//    This file includes the methods called by the user interface:
//    addRecord, printAllRecords, findRecord, and deleteRecord. Additionally,
//    it includes writefile, readfile, and cleanup, which are methods
//    used to save, read, and restore the heap. These aren't included
//    in the list of available commands. Furthermore, in the C++ version,
//    there is now constructors, overloaded constructors, a destructor, and
//    overloaded operator methods in order to satisfy the class.
//
*******************************************************************/

#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include "record.h"
#include "llist.h"

using namespace std;

/*****************************************************************
//
//  Function name: llist
//
//  DESCRIPTION:   This is the no-arguments constructor that creates
//                 a new linked list object when called. It initializes
//                 the object by first setting the start to NULL, then
//                 sets the filename to "storage.txt", then finally
//                 calls the readfile() method to set up the linked
//                 list.
//
//  Parameters:    None
//  
//  Return values:  None
//
*******************************************************************/

llist::llist()
{
    #ifdef DEBUG
    cout << "**DEBUG**: Calling the no-arguments constructor for llist\n";
    #endif

    start = NULL;
    strcpy(filename, "storage.txt");
    readfile();
}

/*****************************************************************
//
//  Function name: llist
//
//  DESCRIPTION:   This is the overloaded constructor with one argument,
//                 being the file name of the file you're reading from.
//                 The rest is the same as the no-arguments constructor,
//                 but the filename is set to the given parameter.
//
//  Parameters:    fname (char[]) : The file name of the file
//  
//  Return values:  None
//
*******************************************************************/

llist::llist(char fname[])
{
    #ifdef DEBUG
    cout << "**DEBUG**: Calling the llist constructor with a char[] filename parameter\n";
    #endif

    start = NULL;
    strcpy(filename, fname);
    readfile();
}

/*****************************************************************
//
//  Function name: ~llist
//
//  DESCRIPTION:   This is the destructor for the class, which gets
//                 called when the program exits. It first calls
//                 the writefile() method to write the object
//                 to a file, then frees the heap space by calling
//                 cleanup().
//
//  Parameters:    None
//  
//  Return values:  None
//
*******************************************************************/

llist::~llist()
{
    #ifdef DEBUG
    cout << "\n**DEBUG**: Calling the llist destructor\n";
    #endif

    writefile();
    cleanup();
}

/*****************************************************************
//
//  Function name: llist
//
//  DESCRIPTION:   This is yet another overloaded constructor, but it
//                 takes in an llist object as the parameter. This means
//                 that it copies over all the contents of list, and puts
//                 it into 'this'.
//
//  Parameters:    list (const llist&) : A reference to the llist object
//  
//  Return values:  None
//
*******************************************************************/

llist::llist(const llist& list)
{
    struct record* current = list.start;
    struct record* toAdd = NULL;
    struct record* temp = NULL;

    #ifdef DEBUG
    cout << "**DEBUG**: Calling the llist constructor with a llist& parameter\n";
    #endif

    if (list.start == NULL) /* Nothing in the list */
    {
        this -> start = NULL;
        strcpy(this -> filename, list.filename);
    }
    else /* There's something in the list */
    {
        toAdd = new record; /* Our first record */
        toAdd -> accountno = current -> accountno;
        strcpy(toAdd -> address, current -> address);
        strcpy(toAdd -> name, current -> name);
        toAdd -> next = NULL;

        this -> start = toAdd;
        current = current -> next;

        while (current != NULL) /* If there's more than one record */
        {
            temp = new record;
            toAdd -> next = temp;
            temp -> accountno = current -> accountno;
            strcpy(temp -> address, current -> address);
            strcpy(temp -> name, current -> name);

            if (current -> next == NULL) /* Don't add a next */
            {
                temp -> next = NULL;
            }
            else /* There's more */
            {
                toAdd = temp;
            }

            current = current -> next;
        }
    }
}

/*****************************************************************
//
//  Function name: operator=
//
//  DESCRIPTION:   This method overloads the assignment operator by
//                 providing a llist object as the parameter. This makes
//                 it so that statements like llist l2 = l3 are possible.
//                 The method are almomst the same as the copy constructor.
//
//  Parameters:    list (const llist&) : A reference to the llist object
//  
//  Return values:  None
//
*******************************************************************/

llist& llist::operator=(const llist& list)
{
    struct record* current = list.start;
    struct record* toAdd = NULL;
    struct record* temp = NULL;

    #ifdef DEBUG
    cout << "**DEBUG**: Calling the overloaded = assignment operator\n";
    #endif

    if (list.start == NULL) /* Nothing in the list */
    {
        this -> start = NULL;
        strcpy(this -> filename, list.filename);
    }
    else /* There's something in the list */
    {
        toAdd = new record; /* Our first record */
        toAdd -> accountno = current -> accountno;
        strcpy(toAdd -> address, current -> address);
        strcpy(toAdd -> name, current -> name);
        toAdd -> next = NULL;

        this -> start = toAdd;
        current = current -> next;

        while (current != NULL) /* If there's more than one record */
        {
            temp = new record;
            toAdd -> next = temp;
            temp -> accountno = current -> accountno;
            strcpy(temp -> address, current -> address);
            strcpy(temp -> name, current -> name);

            if (current -> next == NULL) /* Don't add a next */
            {
                temp -> next = NULL;
            }
            else /* There's more */
            {
                toAdd = temp;
            }

            current = current -> next;
        }
    }

    return *this;
}

/*****************************************************************
//
//  Function name: addRecord
//
//  DESCRIPTION:   The addRecord method adds a record to the database.
//
//  Parameters:    accountNum (int) : The account number to associate
//                                    the record with
//                 c1 (char[]) : The character array storing the name
//                 c2 (char[]) : The character array storing the house address
//  
//  Return values:  0 : Success
//                 -1 : Fail
//
*******************************************************************/

int llist::addRecord(int accountNum, char c1[], char c2[])
{
    struct record* temp;
    struct record* current = this -> start;
    struct record* begin = this -> start;
    struct record* prev = NULL;
    int retval = -1;

    #ifdef DEBUG
    cout << "\n**DEBUG**: Calling the addRecord method with:\n";
    cout << "**DEBUG**: accountNum: " << accountNum << endl;
    cout << "**DEBUG**: name: " << c1 << endl;
    cout << "**DEBUG**: address: " << c2 << endl;
    #endif

    if (begin == NULL)
    {
        begin = new record;
        begin -> accountno = accountNum;
        strcpy(begin -> address, c2);
        strcpy(begin -> name, c1);
        begin -> next = NULL;
        this -> start = begin; /* Set the start to the new record */
        retval = 0;
    }
    else if (accountNum < current -> accountno) /* Adding in the front */
    {
        temp = new record;
        temp -> next = current;
        temp -> accountno = accountNum;
        strcpy(temp -> address, c2);
        strcpy(temp -> name, c1);
        this -> start = temp;
        retval = 0;
    }
    else if ((current != NULL) && (current -> accountno < accountNum)) /* Adding to the end */
    {
        while ((current != NULL) && (current -> accountno < accountNum)) /* Find where to insert */
        {
            prev = current;
            current = current -> next;
        }
        if (current == NULL) /* Check if the end is a duplicate before adding */
        {
            if (prev -> accountno == accountNum)
            {
                retval = -1;
            }
            else /* You're good the end isn't a duplicate, add as normal */
            {
                temp = new record;
                temp -> next = current;
                prev -> next = temp;
                temp -> accountno = accountNum;
                strcpy(temp -> address, c2);
                strcpy(temp -> name, c1);
                retval = 0;
            }
        }
        else if (current != NULL) /* Means we're in the middle */
        {
            if (current -> accountno == accountNum)
            {
                retval = -1;
            }
            else
            {
                temp = new record;
                temp -> next = current;
                prev -> next = temp;
                temp -> accountno = accountNum;
                strcpy(temp -> address, c2);
                strcpy(temp -> name, c1);
                retval = 0;
            }
        }
    }
    else if ((current != NULL) && (current -> accountno == accountNum))
    {
        retval = -1;
    }
    return retval;
}

/*****************************************************************
//
//  Function name: printAllRecords
//
//  DESCRIPTION:   The printAllRecords method prints all the records
//                 currently present in the database.
//
//  Parameters:    None
//  
//  Return values:  None
//
*******************************************************************/

void llist::printAllRecords()
{
    struct record* current = this -> start;

    #ifdef DEBUG
    cout << "\n**DEBUG**: Calling the printAllRecords method\n";
    #endif

    if (this -> start == NULL)
    {
        cout << "\nNo records found\n\n";
    }
    else
    {
        cout << "\nRecords:\n\n";
    }

    while (current != NULL)
    {
        cout << "Account Number: " << current -> accountno << endl;
        cout << "Name: " << current -> name << endl;
        cout << "Address: " << current -> address << endl << endl;
        current = current -> next;
    }
}

/*****************************************************************
//
//  Function name: operator<<
//
//  DESCRIPTION:   This function overloads the '<<' operator, which
//                 prints out the contents of a certain type. This function
//                 takes in both the output stream and llist object, and
//                 prints the contents of the llist by iterating through
//                 the list.
//
//  Parameters:    output (ostream&) : The output stream
//                 list (const llist&) : The llist object to print
//  
//  Return values:  None
//
*******************************************************************/

ostream& operator<<(ostream& output, const llist& list)
{
    struct record* current = list.start;

    #ifdef DEBUG
    output << "\n**DEBUG**: Calling the overloaded '<<' operator\n";
    #endif

    if (list.start == NULL)
    {
        output << "\nNo records found\n\n";
    }
    else
    {
        output << "\nRecords:\n\n";
    }

    while (current != NULL)
    {
        output << "Account Number: " << current -> accountno << endl;
        output << "Name: " << current -> name << endl;
        output << "Address: " << current -> address << endl << endl;
        current = current -> next;
    }

    return output;
}

/*****************************************************************
//
//  Function name: findRecord
//
//  DESCRIPTION:   The findRecord method looks for a record
//                 in the database given an account number.
//
//  Parameters:    accountNum (int) : The account number to look for
//  
//  Return values:  0 : Success
//                 -1 : Not found
//
*******************************************************************/

int llist::findRecord(int accountNum)
{
    struct record* current = this -> start;
    int retval = -1;

    #ifdef DEBUG
    cout << "\n**DEBUG**: Calling the findRecord method with:\n";
    cout << "**DEBUG**: accountNum: " << accountNum << endl;
    #endif

    while (current != NULL)
    {
        if (current -> accountno == accountNum)
        {
            retval = 0;
            cout << "\nAccount found:\n\n";
            cout << "Account Number: " << current -> accountno << endl;
            cout << "Name: " << current -> name << endl;
            cout << "Address: " << current -> address << endl << endl;
            current = current -> next;
        }
        else
        {
            current = current -> next;
        }
    }

    return retval;
}

/*****************************************************************
//
//  Function name: deleteRecord
//
//  DESCRIPTION:   The deleteRecord method deletes a record in the
//                 database given an account number.
//
//  Parameters:    accountNum (int) : The account number to delete
//  
//  Return values:  0 : Success
//                 -1 : Not found
//
*******************************************************************/

int llist::deleteRecord(int accountNum)
{
    struct record* current = this -> start;
    struct record* begin = this -> start;
    struct record* prev = NULL;
    struct record* next = NULL;
    int retval = -1;
    int check = 0;

    #ifdef DEBUG
    cout << "\n**DEBUG**: Calling the deleteRecord method with: \n";
    cout << "**DEBUG**: accountNum: " << accountNum << endl << endl;
    #endif

    if (begin != NULL)
    {
        while ((current != NULL) && (check == 0))
        {
            if (current -> accountno == accountNum)
            {
                if (prev == NULL) /* Start of list */
                {
                    if (current -> next == NULL) /* Only item */
                    {
                        delete current;
                        retval = 0;
                        current = NULL;
                        this -> start = NULL;
                    }
                    else /* Deleting first item, multiple items */
                    {
                        begin = current -> next;
                        this -> start = begin;
                        delete current;
                        current = start;
                        retval = 0;
                    }
                }
                else if (next == NULL) /* End of list */
                {
                    prev -> next = NULL;
                    delete current;
                    retval = 0;
                    current = NULL;
                }
                else /* Middle of list */
                {
                    delete current;
                    prev -> next = next;
                    retval = 0;
                    current = begin;
                }
            }
            else if ((current -> accountno < accountNum) && (current -> next != NULL)) /* Less */
            {
                prev = current;
                current = current -> next;
                next = current -> next;
            }
            else if ((current -> accountno < accountNum) && (current -> next == NULL)) /* End */
            {
                check = -1;
            }
            else if (current -> accountno > accountNum)
            {
                check = -1;
            }
        }
    }
    return retval;
}

/*****************************************************************
//
//  Function name: writefile
//
//  DESCRIPTION:   The writefile method takes the existing linked list
//                 and writes its contents to a text file.
//
//  Parameters:    None
//
//  Return values:  0 : Success
//                 -1 : Write failure
//
*******************************************************************/

int llist::writefile()
{
    ofstream outfile(this -> filename, ofstream::out);
    int retval = 0;
    struct record* current = this -> start;

    #ifdef DEBUG
    cout << "**DEBUG**: Calling the writefile method\n";
    #endif

    if (!outfile.is_open())
    {
        retval = -1;
    }
    else
    {
        while (current != NULL)
        {
            outfile << current -> accountno << endl;
            outfile << current -> name << endl;
            outfile << current -> address << "*\n";
            current = current -> next;
        }

        outfile.close();
    }

    return retval;
}

/*****************************************************************
//
//  Function name: readfile
//
//  DESCRIPTION:   The readfile method takes a text file in the correct
//                 format and creates a linked list with all the fields populated.
//
//  Parameters:    None
//
//  Return values:  0 : Success
//                 -1 : Read failure
//
*******************************************************************/

int llist::readfile()
{
    ifstream infile(this -> filename, ifstream::in);
    int retval = 0;
    string temp;
    int tempNumber;
    char tempName[25];
    char tempAddress[45];

    char c;
    int incrementer = 0;

    struct record* prev = NULL;
    struct record* current = this -> start;

    #ifdef DEBUG
    cout << "**DEBUG**: Calling the readfile method\n\n";
    #endif

    if (!infile.is_open())
    {
        retval = -1;
    }
    else
    {
        while (infile >> tempNumber) /* While we're not at EOF */
        {
            infile.ignore(80, '\n'); /* Ignore the newline after reading the number */
            current = new record;
            infile.getline(tempName, 25);

            while ((infile.get(c)) && (c != '*') && (incrementer < 45 - 1))
            {
                tempAddress[incrementer] = c;
                incrementer++;
            }
            tempAddress[incrementer] = '\0'; /* To make it a string */
            incrementer = 0;

            current -> accountno = tempNumber;
            strcpy(current -> name, tempName);
            strcpy(current -> address, tempAddress);
            current -> next = NULL;

            if (this -> start == NULL)
            {
                this -> start = current;
                prev = current;
            }
            else
            {
                prev -> next = current;
                prev = current;
            }
        }

        infile.close();
    }

    return retval;
}

/*****************************************************************
//
//  Function name: cleanup
//
//  DESCRIPTION:   The cleanup method releases all the heap space
//                 at the end of the method.
//
//  Parameters:    None
//
//  Return values:  None
//
*******************************************************************/

void llist::cleanup()
{
    struct record* current;
    struct record* todelete = this -> start;

    #ifdef DEBUG
    cout << "**DEBUG**: Calling the cleanup method\n";
    #endif

    while (todelete != NULL)
    {
        current = todelete;
        todelete = todelete -> next;
        delete current;
    }

    this -> start = NULL;
}

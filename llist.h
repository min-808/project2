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
//  FILE:        llist.h
//
//  DESCRIPTION:
//   This file declares the functions defined in llist.cpp and used
//   in user_interface.cpp. Additionally, it defines both the '='
//   and '<<' overloaded functions.
//
*******************************************************************/

#ifndef LLIST
#define LLIST

#include "record.h"

class llist
{
    private:
    record*     start;
    char        filename[20];
    int         readfile();
    int         writefile();
    void        cleanup();

    public:
    llist();
    llist(char[]);
    llist(const llist&);
    llist& operator=(const llist&);
    ~llist();
    int addRecord(int, char[], char[]);
    int findRecord(int);
    void printAllRecords();
    int deleteRecord(int);
    friend std::ostream& operator<<(std::ostream&, const llist&);
};

#endif

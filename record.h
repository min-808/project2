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
//  FILE:        record.h
//
//  DESCRIPTION:
//   This file defines a struct called record, which includes the
//   account number, name, address, and next variables.
//
*******************************************************************/

#ifndef RECORD
#define RECORD

struct record
{
    int                accountno;
    char               name[25];
    char               address[45];
    struct record*     next;
};

#endif

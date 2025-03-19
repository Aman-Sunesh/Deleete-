#include <iostream>
#include "payload.h"

using std::cout;

int Payload::counter = 0;
const bool REPORT = false;

void Payload::say_born() const
{
 if ( REPORT ){ print(); cout << " is born\n"; }
}

void Payload::say_die() const
{
 if ( REPORT ){ print(); cout << " dies\n"; }
}

void Payload::print() const
{
 cout << '(' ;
 if ( REPORT ) cout << id << ':';
 cout << name << ')';
}
#ifndef SEAT_H
#define SEAT_H

#include <iostream>
#include <string>

using namespace std;

struct Seat {

    int row;
    int number;
    bool booked;
    string customerID;


    Seat();

    Seat(int r, int n);

};

#endif

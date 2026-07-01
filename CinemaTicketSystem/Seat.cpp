#include "Seat.h"


Seat::Seat()
{
    row = 0;
    number = 0;
    booked = false;
    customerID = "";
}


Seat::Seat(int r, int n)
{
    row = r;
    number = n;
    booked = false;
    customerID = "";
}

#include "Customer.h"


Customer::Customer()
{
    id="";
    name="";
    age=0;
    vip=false;
    price=0;

    left=nullptr;
    right=nullptr;
}



Customer::Customer(
    string id,
    string name,
    int age,
    bool vip,
    double price
)
{
    this->id=id;
    this->name=name;
    this->age=age;
    this->vip=vip;
    this->price=price;

    left=nullptr;
    right=nullptr;
}

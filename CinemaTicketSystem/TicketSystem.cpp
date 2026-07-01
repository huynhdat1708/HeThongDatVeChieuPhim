#include "TicketSystem.h"


TicketSystem::TicketSystem()
{
    root = nullptr;


    for(int i=0;i<5;i++)
    {
        for(int j=0;j<5;j++)
        {
            seats[i][j] = Seat(i,j);
        }
    }
}



// ================= BST =================


void TicketSystem::insertCustomer(
    Customer*& node,
    Customer* customer
)
{
    if(node==nullptr)
    {
        node=customer;
        return;
    }


    if(customer->id < node->id)
        insertCustomer(node->left,customer);

    else
        insertCustomer(node->right,customer);
}



Customer* TicketSystem::searchCustomer(
    Customer* node,
    string id
)
{
    if(node==nullptr)
        return nullptr;


    if(node->id==id)
        return node;


    if(id < node->id)
        return searchCustomer(node->left,id);


    return searchCustomer(node->right,id);
}




// ================= GHẾ =================


string TicketSystem::getSeatName(
    int r,
    int c
)
{
    char row='A'+r;

    return string(1,row)+to_string(c+1);
}



void TicketSystem::showSeats()
{

    cout<<"\n========== SEAT MAP ==========\n\n";


    cout<<"   ";

    for(int i=1;i<=5;i++)
        cout<<i<<" ";

    cout<<endl;



    for(int i=0;i<5;i++)
    {
        cout<<char('A'+i)<<"  ";


        for(int j=0;j<5;j++)
        {

            if(seats[i][j].booked)
                cout<<"X ";

            else
                cout<<"O ";

        }

        cout<<endl;
    }

}



// ================= ĐẶT VÉ =================


void TicketSystem::bookTicket()
{

    string id,name;
    int age;
    int vipChoice;


    cout<<"Customer ID: ";
    cin>>id;


    cout<<"Name: ";
    cin>>name;


    cout<<"Age: ";
    cin>>age;


    cout<<"VIP (1 yes / 0 no): ";
    cin>>vipChoice;



    int r,c;


    cout<<"Row (A-E): ";

    char row;
    cin>>row;


    cout<<"Seat number (1-5): ";
    cin>>c;



    r=row-'A';
    c--;



    if(r<0 || r>=5 || c<0 || c>=5)
    {
        cout<<"Invalid seat\n";
        return;
    }



    int priority;


    if(vipChoice)
        priority=1;

    else if(age>=60)
        priority=2;

    else
        priority=3;




    // còn ghế

    if(!seats[r][c].booked)
    {

        seats[r][c].booked=true;

        seats[r][c].customerID=id;



        Customer* customer =
        new Customer(
            id,
            name,
            age,
            vipChoice,
            50000
        );



        insertCustomer(root,customer);



        history.push(
            {
                id,
                getSeatName(r,c),
                "BOOK"
            }
        );



        cout<<"Booking successful!\n";

    }


    else
    {

        cout<<"Seat full. Added to waiting list.\n";


        WaitingCustomer w;


        w.id=id;
        w.name=name;
        w.age=age;
        w.vip=vipChoice;
        w.priority=priority;



        waitingList.push(w);

    }

}





// ================= HỦY VÉ =================


void TicketSystem::cancelTicket()
{

    string id;


    cout<<"Customer ID: ";
    cin>>id;



    Customer* customer =
    searchCustomer(root,id);



    if(customer==nullptr)
    {
        cout<<"Customer not found\n";
        return;
    }




    for(int i=0;i<5;i++)
    {
        for(int j=0;j<5;j++)
        {

            if(
                seats[i][j].customerID==id
            )
            {

                seats[i][j].booked=false;

                seats[i][j].customerID="";


                history.push(
                {
                    id,
                    getSeatName(i,j),
                    "CANCEL"
                });



                cout<<"Ticket cancelled\n";



                // cấp vé cho người chờ


                if(!waitingList.empty())
                {

                    WaitingCustomer w =
                    waitingList.top();


                    waitingList.pop();



                    seats[i][j].booked=true;

                    seats[i][j].customerID=w.id;



                    Customer* newCustomer =
                    new Customer(
                        w.id,
                        w.name,
                        w.age,
                        w.vip,
                        50000
                    );



                    insertCustomer(
                        root,
                        newCustomer
                    );



                    cout
                    <<"Waiting customer "
                    <<w.name
                    <<" received seat "
                    <<getSeatName(i,j)
                    <<endl;

                }


                return;

            }

        }
    }

}




// ================= TÌM KIẾM =================


void TicketSystem::displayCustomer(
    Customer* customer
)
{

    cout<<"\nCustomer found\n";

    cout<<"ID: "
        <<customer->id<<endl;


    cout<<"Name: "
        <<customer->name<<endl;


    cout<<"Age: "
        <<customer->age<<endl;


}



void TicketSystem::search()
{

    string id;


    cout<<"Enter ID: ";

    cin>>id;



    Customer* c =
    searchCustomer(root,id);



    if(c)
        displayCustomer(c);

    else
        cout<<"Not found\n";

}





// ================= DANH SÁCH VÉ =================


void TicketSystem::showTickets()
{

    cout<<"\nBooked seats:\n";


    for(int i=0;i<5;i++)
    {
        for(int j=0;j<5;j++)
        {

            if(seats[i][j].booked)
            {

                cout
                <<getSeatName(i,j)
                <<" - "
                <<seats[i][j].customerID
                <<endl;

            }

        }
    }

}




// ================= THỐNG KÊ =================


void TicketSystem::statistic()
{

    int booked=0;


    for(int i=0;i<5;i++)
    {
        for(int j=0;j<5;j++)
        {

            if(seats[i][j].booked)
                booked++;

        }
    }



    cout<<"\nTotal seats: 25\n";

    cout<<"Booked: "
        <<booked
        <<endl;


    cout<<"Available: "
        <<25-booked
        <<endl;


    cout<<"Revenue: "
        <<booked*50000
        <<" VND\n";


}

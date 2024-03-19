#include <iostream>
#include <string>
#include <cstring>
#include <fstream>
#include <iomanip>

#include "ticket.h"
#include "bus.h"
#include "utils.h"

using namespace std;

void Ticket::generateTicket(char *n, Bus b)
{
    strcpy(name, n);
    strcpy(pnrNo, generatePNR(99999).c_str());
    strcpy(date, getCurrentDate().c_str());
    bus = b;
}

void Ticket::displayTicket()
{
    cout << "\t\t\t\t\t-------------------------------------------------\n";
    cout << "\t\t\t\t\t Name:-> " << getName();
    cout << "\n\t\t\t\t\t PNR No:-> " << getPnrNo();
    cout << "\n\t\t\t\t\t Bus No:-> " << bus.getBusNo();
    cout << "\n\t\t\t\t\t Seat No.:-> " << bus.getBookedSeats();
    cout << "\n\t\t\t\t\t Date:-> " << getDate();
    cout << "\n\t\t\t\t\t From:-> " << bus.getSource();
    cout << "\n\t\t\t\t\t To:-> " << bus.getDestination();
    cout << "\n\t\t\t\t\t Source Time:-> " << bus.getSourceTime();
    cout << "\n\t\t\t\t\t Destination Time:-> " << bus.getDestinationTime();
    cout << fixed << setprecision(2);
    cout << "\n\t\t\t\t\t Bus Fare:-> " << bus.getBusFare();
    cout << "\n\t\t\t\t\t-------------------------------------------------\n";
    cout << "\n";
}

void Ticket::bookTicket()
{
    system("cls");

    char from[20], to[20];
    int chk = 0;

    Bus b;
    fstream busFileStream, ticketFileStream, tempFileStream;

    printHeading("BOOK TICKET");

    busFileStream.open("buses.dat", ios::in | ios::app | ios::binary);
    if (busFileStream.fail())
    {
        cout << "\n\t\t\t\t\t Can't Open File...!!\n";
    }

    else
    {
        cout << "\n\t\t\t\t\t Available Sources: ";
        cout << "\n\t\t\t\t\t     Dhaka";
        cout << "\n\t\t\t\t\t     Sylhet";
        cout << "\n\t\t\t\t\t     Mymensingh";
        cout << "\n\n\t\t\t\t\t Enter Source:-> ";
        cin.ignore();
        cin.getline(from, 20);
        string st=from;
        if(st=="Dhaka"){
            cout << "\n\n\t\t\t\t\t Available Destinations: ";
            cout << "\n\t\t\t\t\t     Sylhet";
            cout << "\n\t\t\t\t\t     Mymensingh";
        }
        else if(st=="Sylhet"){
            cout << "\n\n\t\t\t\t\t Available Destinations: ";
            cout << "\n\t\t\t\t\t     Dhaka";
            cout << "\n\t\t\t\t\t     Mymensingh";
        }
        else{
            cout << "\n\n\t\t\t\t\t Available Destinations: ";
            cout << "\n\t\t\t\t\t     Dhaka";
            cout << "\n\t\t\t\t\t     Sylhet";
        }
        cout << "\n\n\t\t\t\t\t Enter Destination:-> ";
        cin.getline(to, 20);

        system("cls");
        printHeading("AVAILABLE BUSES");

        busFileStream.read((char *)&b, sizeof(b));
        while (!busFileStream.eof())
        {
            if (strcmpi(b.getSource(), from) == 0 && strcmpi(b.getDestination(), to) == 0)
            {
                b.showBusDetails();
                chk = 1;
            }
            busFileStream.read((char *)&b, sizeof(b));
        }

        busFileStream.close();

        if (chk == 0)
        {
            cout << "\n\t\t\t\t\t No Buses Found...!!\n";
        }
        else
        {
            char bNo[10];
            int booked = 0;

            cout << "\n\t\t\t\t\t Enter Bus Number:-> ";
            cin.getline(bNo, 10);

            busFileStream.open("buses.dat", ios::in | ios::app | ios::binary);
            tempFileStream.open("temp.dat", ios::out | ios::app | ios::binary);

            busFileStream.read((char *)&b, sizeof(b));
            while (!busFileStream.eof())
            {
                if (strcmpi(b.getSource(), from) == 0 && strcmpi(b.getDestination(), to) == 0 && strcmp(b.getBusNo(), bNo) == 0)
                {
                    if (b.getBookedSeats() >= 32)
                    {
                        cout << "\n\t\t\t\t\t Seat not available...!!\n";
                        break;
                    }
                    else
                    {
                        system("cls");
                        printHeading("BOOK TICKET");
                        char n[20];
                        cout << "\n\t\t\t\t\t Enter Customer Name :-> ";
                        cin.getline(n, 20);
                        b.setBookedSeats();
                        generateTicket(n, b);
                        ticketFileStream.open("tickets.dat", ios::out | ios::app | ios::binary);
                        ticketFileStream.write((char *)this, sizeof(*this));
                        ticketFileStream.close();
                        tempFileStream.write((char *)&b, sizeof(b));

                        booked = 1;
                        system("cls");
                        printHeading("BOOKING DETAILS");
                        displayTicket();
                        cout << "\n\t\t\t\t\t Ticket Booked Successfully...!!\n";
                    }
                }
                else
                {
                    tempFileStream.write((char *)&b, sizeof(b));
                }
                busFileStream.read((char *)&b, sizeof(b));
            }

            if (booked == 1)
            {
                busFileStream.close();
                tempFileStream.close();
                remove("buses.dat");
                rename("temp.dat", "buses.dat");
            }
        }
        busFileStream.close();
    }
}

void Ticket::cancelTicket()
{
    system("cls");

    char pnr[10];
    int chk = 0;

    fstream busFileStream, ticketFileStream, tempFileStream, busTempFileStream;

    printHeading("CANCEL TICKET");
    cout << "\n\t\t\t\t\t Enter PNR Number:-> ";
    cin.ignore();
    cin.getline(pnr, 10);

    ticketFileStream.open("tickets.dat", ios::in | ios::app | ios::binary);
    tempFileStream.open("temp.dat", ios::out | ios::app | ios::binary);

    if (ticketFileStream.fail())
    {
        cout << "\n\t\t\t\t\t Can't Open File...!!\n";
    }

    else
    {
        ticketFileStream.read((char *)this, sizeof(*this));
        while (!ticketFileStream.eof())
        {
            if (strcmp(getPnrNo(), pnr) != 0)
            {
                tempFileStream.write((char *)this, sizeof(*this));
            }
            else
            {
                Bus b;
                busFileStream.open("buses.dat", ios::in | ios::app | ios::binary);
                busTempFileStream.open("bustemp.dat", ios::out | ios::app | ios::binary);

                busFileStream.read((char *)&b, sizeof(b));
                while (!busFileStream.eof())
                {
                    if (strcmp(b.getBusNo(), bus.getBusNo()) == 0)
                    {
                        b.setCancelTicket();
                        busTempFileStream.write((char *)&b, sizeof(b));
                    }
                    else
                    {
                        busTempFileStream.write((char *)&b, sizeof(b));
                    }
                    busFileStream.read((char *)&b, sizeof(b));
                }
                busFileStream.close();
                busTempFileStream.close();
                remove("buses.dat");
                rename("bustemp.dat", "buses.dat");
                chk = 1;
            }
            ticketFileStream.read((char *)this, sizeof(*this));
        }
        if (chk == 0)
        {
            ticketFileStream.close();
            tempFileStream.close();
            cout << "\n\t\t\t\t\t Ticket Not Found...!!\n";
        }
        else
        {
            ticketFileStream.close();
            tempFileStream.close();
            remove("tickets.dat");
            rename("temp.dat", "tickets.dat");
            cout << "\n\t\t\t\t\t Ticket Cancelled...!!\n";
        }
    }
}

void Ticket::showTicketsByPNR()
{
    system("cls");

    char pnr[10];
    int chk = 0;
    fstream ticketFileStream;

    printHeading("SHOW BOOKINGS BY PNR");
    cout << "\n\t\t\t\t\t Enter PNR Number:-> ";
    cin.ignore();
    cin.getline(pnr, 10);

    system("cls");

    printHeading("BOOKINGS");

    ticketFileStream.open("tickets.dat", ios::in | ios::app | ios::binary);
    if (ticketFileStream.fail())
    {
        cout << "\n\t\t\t\t\t Can't Open File...!!\n";
    }

    else
    {
        ticketFileStream.read((char *)this, sizeof(*this));
        while (!ticketFileStream.eof())
        {
            if (strcmp(getPnrNo(), pnr) == 0)
            {
                displayTicket();
                chk = 1;
            }
            ticketFileStream.read((char *)this, sizeof(*this));
        }
        if (chk == 0)
        {
            cout << "\n\t\t\t\t\t No Bookings...!!\n";
        }
        ticketFileStream.close();
    }
}

void Ticket::showTicketsByName()
{
    system("cls");

    char n[20];
    int chk = 0;
    fstream ticketFileStream;

    printHeading("SHOW BOOKINGS BY NAME");
    cout << "\n\t\t\t\t\t Enter Passenger Name:-> ";
    cin.ignore();
    cin.getline(n, 20);

    system("cls");

    printHeading("BOOKINGS");

    ticketFileStream.open("tickets.dat", ios::in | ios::app | ios::binary);
    if (ticketFileStream.fail())
    {
        cout << "\n\t\t\t\t\t Can't Open File...!!\n";
    }

    else
    {
        ticketFileStream.read((char *)this, sizeof(*this));
        while (!ticketFileStream.eof())
        {
            if (strcmpi(getName(), n) == 0)
            {
                displayTicket();
                chk = 1;
            }
            ticketFileStream.read((char *)this, sizeof(*this));
        }
        if (chk == 0)
        {
            cout << "\n\t\t\t\t\t No Bookings...!!\n";
        }
        ticketFileStream.close();
    }
}

void Ticket:: showTicketsByBus(){
    system("cls");
    char bNo[10];
    int chk = 0;
    fstream ticketFileStream;

    printHeading("SHOW BOOKINGS BY NAME");
    cout << "\n\t\t\t\t\t Enter Bus Number:-> ";
    cin.ignore();
    cin.getline(bNo, 10);

    system("cls");

    printHeading("BOOKINGS");

    ticketFileStream.open("tickets.dat", ios::in | ios::app | ios::binary);
    if (ticketFileStream.fail())
    {
        cout << "\n\t\t\t\t\t Can't Open File...!!\n";
    }

    else
    {
        ticketFileStream.read((char *)this, sizeof(*this));
        while (!ticketFileStream.eof())
        {
            if (strcmp(bus.getBusNo(), bNo) == 0)
            {
                displayTicket();
                chk = 1;
            }
            ticketFileStream.read((char *)this, sizeof(*this));
        }
        if (chk == 0)
        {
            cout << "\n\t\t\t\t\t No Bookings...!!\n";
        }
        ticketFileStream.close();
    }
}

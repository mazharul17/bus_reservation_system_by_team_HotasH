#include <iostream>
#include <string>
#include <cstring>
#include <fstream>
#include <iomanip>

#include "bus.h"
#include "ticket.h"
#include "utils.h"

using namespace std;

void Bus::addBus()
{
    fstream busFileStream;

    system("cls");

    printHeading("ADD BUS");

    cout << "\n\t\t\t\t\t Enter Bus Number:-> ";
    cin.ignore();
    cin.getline(busNo, 10);
    cout << "\n\t\t\t\t\t Available Sources: ";
    cout << "\n\t\t\t\t\t     Dhaka";
    cout << "\n\t\t\t\t\t     Sylhet";
    cout << "\n\t\t\t\t\t     Mymensingh";
    cout << "\n\t\t\t\t\t Enter Source:-> ";
    cin.getline(source, 20);
    string st=source;
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
    cin.getline(destination, 20);
    cout << "\n\n\t\t\t\t\t Available Source Time: Any time";
    cout << "\n\t\t\t\t\t Enter Source Time:-> ";
    cin.getline(sourceTime, 20);
    cout << "\n\n\t\t\t\t\t Available Destination Time: Any time";
    cout << "\n\t\t\t\t\t Enter Destination Time:-> ";
    cin.getline(destinationTime, 20);
    cout << "\n\t\t\t\t\t Enter Bus Fare:-> ";
    cin >> busFare;

    busFileStream.open("buses.dat", ios::out | ios::app | ios::binary);
    busFileStream.write((char *)this, sizeof(*this));
    busFileStream.close();

    cout << "\n\t\t\t\t\t Bus Added Successfully...!!!:-> \n";
}

void Bus::showBusDetails()
{
    cout << "\t\t\t\t\t -------------------------------------------------\n";
    cout << "\t\t\t\t\t Bus No:-> " << getBusNo();
    cout << "\n\t\t\t\t\t Source:-> " << getSource();
    cout << "\n\t\t\t\t\t Destination:-> " << getDestination();
    cout << "\n\t\t\t\t\t Time:-> " << getSourceTime() << " - " << getDestinationTime();
    cout << "\n\t\t\t\t\t Total Seats:-> " << getMaxSeats();
    cout << "\n\t\t\t\t\t Seats Remaining:-> " << (getMaxSeats() - getBookedSeats());
    cout << fixed << setprecision(2);
    cout << "\n\t\t\t\t\t Bus Fare:-> " << getBusFare();
    cout << "\n\t\t\t\t\t-------------------------------------------------\n";
    cout << "\n";
}

void Bus::showAllBus()
{
    system("cls");

    fstream busFileStream;

    busFileStream.open("buses.dat", ios::in | ios::app | ios::binary);
    if (!busFileStream)
        cout << "\n\t\t\t\t\t File Not Found...!!!";
    else
    {
        printHeading("BUSES");

        busFileStream.read((char *)this, sizeof(*this));

        while (!busFileStream.eof())
        {
            showBusDetails();
            busFileStream.read((char *)this, sizeof(*this));
        }
        busFileStream.close();
    }
}

void Bus::viewBusDetails()
{
    system("cls");

    char bNo[10];
    int chk = 0;
    fstream busFileStream;

    printHeading("VIEW BUS INFO");
    cout << "\n\t\t\t\t\t Enter Bus Number:-> ";
    cin.ignore();
    cin.getline(bNo, 10);

    system("cls");
    printHeading("BUS INFO");

    busFileStream.open("buses.dat", ios::in | ios::app | ios::binary);
    if (busFileStream.fail())
    {
        cout << "\n\t\t\t\t\t Can't Open File...!!\n";
    }

    else
    {
        busFileStream.read((char *)this, sizeof(*this));
        while (!busFileStream.eof())
        {
            if (strcmp(getBusNo(), bNo) == 0)
            {
                showBusDetails();
                chk = 1;
            }
            busFileStream.read((char *)this, sizeof(*this));
        }
        if (chk == 0)
        {
            cout << "\n\t\t\t\t\t Bus Not Found...!!\n";
        }
        busFileStream.close();
    }
}

void Bus::deleteBus()
{
    system("cls");

    char bNo[10];
    int chk = 0;
    fstream busFileStream, tempFileStream;

    printHeading("DELETE BUS");
    cout << "\n\t\t\t\t\t Enter Bus No:-> ";
    cin.ignore();
    cin.getline(bNo, 10);

    busFileStream.open("buses.dat", ios::in | ios::app | ios::binary);

    if (busFileStream.fail())
    {
        cout << "\n\t\t\t\t\t Can't Open File...!!";
        system("pause");
    }

    else
    {
        tempFileStream.open("temp.dat", ios::out | ios::app | ios::binary);
        busFileStream.read((char *)this, sizeof(*this));
        while (!busFileStream.eof())
        {
            if (strcmp(getBusNo(), bNo) != 0)
            {
                tempFileStream.write((char *)this, sizeof(*this));
            }
            else
            {
                chk = 1;
            }
            busFileStream.read((char *)this, sizeof(*this));
        }

        if (chk == 0)
        {
            cout << "\n\t\t\t\t\t Bus Not Found...!!\n";
        }
        else
        {
            cout << "\n\t\t\t\t\t Bus Deleted...!!\n";
        }

        busFileStream.close();
        tempFileStream.close();
        remove("buses.dat");
        rename("temp.dat", "buses.dat");
    }
}

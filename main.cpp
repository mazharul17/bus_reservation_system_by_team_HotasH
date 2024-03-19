#include <bits/stdc++.h>

#include "bus.cpp"
#include "ticket.cpp"
#include "utils.h"

using namespace std;

void mainMenu();
void userMenu();
void adminMenu();
void adminLogin();
void viewBookingsMenu();


int main(){
    system("cls");
    system("COLOR BD");

    cout << "\n\n\n\n";
    cout << "\t\t\t\t\t================================================\n";
    cout << "\t\t\t\t\t||                  WELCOME TO                ||\n";
    cout << "\t\t\t\t\t||                                            ||\n";
    cout << "\t\t\t\t\t||       BUS RESERVATION SYSTEM PROJECT       ||\n";
    cout << "\t\t\t\t\t||                                            ||\n";
    cout << "\t\t\t\t\t||                 DEVELOPED BY               ||\n";
    cout << "\t\t\t\t\t||                                            ||\n";
    cout << "\t\t\t\t\t||                 TEAM_HotasH                ||\n";
    cout << "\t\t\t\t\t================================================\n\n\n";

    system("pause");
    mainMenu();

    return 0;
}


void mainMenu(){
    int choice;
    while(1){
        system("cls");
        printHeading("MAIN MENU");
        cout << "\t\t\t\t\t-------------------------------------------------\n";
        cout << "\t\t\t\t\t 1. User Menu                                    \n";
        cout << "\t\t\t\t\t-------------------------------------------------\n";
        cout << "\t\t\t\t\t 2. Admin Menu                                   \n";
        cout << "\t\t\t\t\t-------------------------------------------------\n";
        cout << "\t\t\t\t\t 3. EXIT                                         \n";
        cout << "\t\t\t\t\t-------------------------------------------------\n\n";

        cout << "\n\t\t\t\tEnter your choice:-> ";
        cin >> choice;

        switch(choice){
        case 1:
            userMenu();
            break;
        case 2:
            adminLogin();
            break;
        case 3:
            system("cls");
            cout << "\n\n\n\n\t\t\t\t\t  Thanks for using our project.\n";
            cout << "\n\t\t\t\t\t         Have a nice day.      \t\t\t\n\n";
            exit(0);

        default:
            cout << "\n\n\t\t\t\t\t  Please, choose any valid option!!!\n";
            system("pause");
        }
    }
}


void adminLogin(){
    string adminUname, adminPass;

    system("cls");

    printHeading("ADMIN LOGIN");
    cout << "\n\t\t\t\t\tEnter AdminID:-> ";
    cin >> adminUname;
    cout << "\n\t\t\t\t\tEnter Password:-> ";
    cin >> adminPass;

    if (adminUname == "sustcse" && adminPass == "2024"){
        adminMenu();
    }
    else{
        cout<< "\n\t\t\t\t\tUsername or Password is wrong!!! ";
        cout<<"\n\n\t\t\t\t\tPress any key(without 0) for RETRY: ";
        cout<<"\n\t\t\t\t\tPress 0 for BACK: ";
        int k;
        cin>>k;
        if(k==0)
            mainMenu();
        else
            adminLogin();
        system("pause");
    }
}


void userMenu(){
    int choice;
    while (1)
    {
        system("cls");
        Ticket t;
        printHeading("USER MENU");
        cout << "\t\t\t\t\t-------------------------------------------------\n";
        cout << "\t\t\t\t\t 1. Book Ticket                                  \n";
        cout << "\t\t\t\t\t-------------------------------------------------\n";
        cout << "\t\t\t\t\t 2. View Ticket                                  \n";
        cout << "\t\t\t\t\t-------------------------------------------------\n";
        cout << "\t\t\t\t\t 3. Cancel Ticket                                \n";
        cout << "\t\t\t\t\t-------------------------------------------------\n";
        cout << "\t\t\t\t\t 4. BACK                                         \n";
        cout << "\t\t\t\t\t-------------------------------------------------\n";

        cout << "\n\t\t\t\t\tEnter your choice:-> ";
        cin >> choice;

        switch (choice){
        case 1:
            t.bookTicket();
            system("pause");
            break;
        case 2:
            t.showTicketsByPNR();
            system("pause");
            break;
        case 3:
            t.cancelTicket();
            system("pause");
            break;
        case 4:
            system("cls");
            mainMenu();
            break;
        default:
            cout << "\n\n\t\t\t\t\t  Please, choose any valid option!!!\n";
            system("pause");
            break;
        }
    }
}


void adminMenu(){
    Bus b;
    Ticket t;

    int choice;
    while (1){
        system("cls");
        printHeading("ADMIN MENU");
        cout << "\t\t\t\t\t-------------------------------------------------\n";
        cout << "\t\t\t\t\t 1. Add Bus                                      \n";
        cout << "\t\t\t\t\t-------------------------------------------------\n";
        cout << "\t\t\t\t\t 2. View Buses                                   \n";
        cout << "\t\t\t\t\t-------------------------------------------------\n";
        cout << "\t\t\t\t\t 3. Delete Bus                                   \n";
        cout << "\t\t\t\t\t-------------------------------------------------\n";
        cout << "\t\t\t\t\t 4. View Booking Tickets                         \n";
        cout << "\t\t\t\t\t-------------------------------------------------\n";
        cout << "\t\t\t\t\t 5. Cancel Ticket                                \n";
        cout << "\t\t\t\t\t-------------------------------------------------\n";
        cout << "\t\t\t\t\t 6. BACK                                         \n";
        cout << "\t\t\t\t\t-------------------------------------------------\n\n";

        cout << "\n\t\t\t\t\tEnter your choice:-> ";
        cin >> choice;

        switch (choice){
        case 1:
            b.addBus();
            system("pause");
            break;
        case 2:
            b.showAllBus();
            system("pause");
            break;
        case 3:
            b.deleteBus();
            system("pause");
            break;
        case 4:
            viewBookingsMenu();
            break;
        case 5:
            t.cancelTicket();
            system("pause");
            break;
        case 6:
            system("cls");
            mainMenu();
            break;
        default:
            cout << "\n\n\t\t\t\t\t  Please, choose any valid option!!!\n";
            system("pause");
        }
    }
}


void viewBookingsMenu(){
    Ticket t;

    int choice;
    while(1){
        system("cls");

        printHeading("VIEW BOOKING TICKETS");
        cout << "\t\t\t\t\t-------------------------------------------------\n";
        cout << "\t\t\t\t\t 1. By PNR                                       \n";
        cout << "\t\t\t\t\t-------------------------------------------------\n";
        cout << "\t\t\t\t\t 2. By Name                                      \n";
        cout << "\t\t\t\t\t-------------------------------------------------\n";
        cout << "\t\t\t\t\t 3. By Bus                                       \n";
        cout << "\t\t\t\t\t-------------------------------------------------\n";
        cout << "\t\t\t\t\t 4. BACK                                         \n";
        cout << "\t\t\t\t\t-------------------------------------------------\n\n";
        cout << "\n\t\t\t\t\tEnter your choice:-> ";

        cin >> choice;
        switch (choice){
        case 1:
            t.showTicketsByPNR();
            system("pause");
            break;
        case 2:
            t.showTicketsByName();
            system("pause");
            break;
        case 3:
            t.showTicketsByBus();
            system("pause");
            break;
        case 4:
            system("cls");
            adminMenu();
            break;
        default:
            cout << "\n\n\t\t\t\t\t  Please, choose any valid option!!!\n";
            system("pause");
        }
    }
}

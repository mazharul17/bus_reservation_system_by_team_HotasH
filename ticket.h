#ifndef TICKET_H
#define TICKET_H

#include <iostream>

#include "bus.h"

class Ticket
{
    private:
        char name[20], pnrNo[10], date[20];
        Bus bus;

    public:
        void generateTicket(char *, Bus);
        void displayTicket();
        void bookTicket();
        void cancelTicket();
        void showTicketsByPNR();
        void showTicketsByName();
        void showTicketsByBus();

        char *getName()
        {
            return name;
        }

        char *getPnrNo()
        {
            return pnrNo;
        }

        char *getDate()
        {
            return date;
        }

        // SETTERS
        void setName(char *n)
        {
            if (n && n[0])
                strcpy(name, n);
        }
};
#endif

//
// Created by fotop on 22/10/2023.
//

#ifndef PR1_CD_ROUTE_H
#define PR1_CD_ROUTE_H

#include <iostream>
#include "Airport.h"
#include "Airline.h"

class Airline;

class Route {
private:

    Airport* origin;
    Airport* destination;
    Airline* company;

public:

    Route() {
                origin = nullptr;
                destination = nullptr;
                company = nullptr;
    }

    Route(Airline* company, Airport* _origin, Airport* _destination);

    Route(Route& other);

    const std::string &getCompany() const;

    void setAirline(const std::string &airline);

    Airport *getOrigin() const;

    void setOrigin(Airport *origin);

    Airport *getDestination() const;

    void setDestination(Airport *destination);

    ~Route();

};


#endif //PR1_CD_ROUTE_H

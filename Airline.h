//
// Created by fotop on 07/11/2023.
//

#ifndef AVL_AIRLINE_H
#define AVL_AIRLINE_H

#include <string>
#include "AVL.h"
#include "Route.h"
#include "Dynamic_container.h"
#include <iostream>


class Route;

class Airline {
private:
    unsigned int id;
    std::string icao;
    std::string name;
    std::string country;
public:
    unsigned int getId() const;

    const std::string &getName() const;

    const std::string &getCountry() const;

private:
    bool active;
public:
    bool isActive() const;

private:
    std::vector<Route*> airRoutes;
public:
    Airline();
    Airline(unsigned int _id, std::string _icao, std::string _name,
            std::string _country, bool _active);
    Airline(std::string _icao);

    bool operator!=(const Airline& other);
    bool operator==(const Airline& other);
    bool operator>(const Airline& other);
    bool operator<(const Airline& other);
    friend std::ostream& operator<<(std::ostream &os, const Airline& object);

    const std::string &getIcao() const;
    void setIcao(const std::string &icao);

    Dynamic_container<Airport>& getOrigAirports();
    Dynamic_container<Route>& getAirportRoutes(std::string iataAirport);
    void linkAirRoute(Route* r);



};


#endif //AVL_AIRLINE_H

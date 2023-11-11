//
// Created by fotop on 07/11/2023.
//

#include "Airline.h"

Airline::Airline() {
    id = 0;
    icao = "";
    name = "";
    country = "";
    active = false;
    airRoutes = std::vector<Route*>();
}

Airline::Airline(unsigned int _id, std::string _icao, std::string _name, std::string _country, bool _active):
    id(_id),
    icao(_icao),
    name(_name),
    country(_country),
    active(_active)
    {}

    Airline::Airline(std::string _icao):
    icao(_icao)
    {   id = 0;
        name = "";
        country = "";
        active = false;
    }
bool Airline::operator==(const Airline &other) {
    if (this->icao == other.icao)
        return true;
    return false;
}

bool Airline::operator!=(const Airline &other) {
    if (this->icao != other.icao)
        return true;
    return false;
}

bool Airline::operator<(const Airline &other) {
    if (this->icao < other.icao)
        return true;
    return false;
}

bool Airline::operator>(const Airline &other) {
    if (this->icao > other.icao)
        return true;
    return false;
}

std::ostream& operator<<(std::ostream &os, const Airline& object) {
    os << object.icao;
    return os;
}

const std::string &Airline::getIcao() const {
    return icao;
}

void Airline::setIcao(const std::string &icao) {
    Airline::icao = icao;
}

Dynamic_container<Airport>& Airline::getOrigAirports() {
    Dynamic_container<Airport> result;
    for(unsigned int i = 0; i < airRoutes.size(); i++){
        result.push(*airRoutes[i]->getOrigin());
    }

    return result;
}

Dynamic_container<Route>& Airline::getAirportRoutes(std::string iataAirport) {
    Dynamic_container<Route> result;
    for(unsigned int i = 0; i < airRoutes.size(); i++){
        if (airRoutes[i]->getOrigin()->getIata() == iataAirport
            or
            airRoutes[i]->getDestination()->getIata() == iataAirport)
            result.push(*airRoutes[i]);
    }
    return result;
}

void Airline::linkAirRoute(Route* r) {
    airRoutes.push_back(r);
}

bool Airline::isActive() const {
    return active;
}

unsigned int Airline::getId() const {
    return id;
}

const std::string &Airline::getName() const {
    return name;
}

const std::string &Airline::getCountry() const {
    return country;
}

//
// Created by fotop on 22/10/2023.
//

#include "Route.h"

const std::string &Route::getCompany() const {
    return company->getIcao();
}

void Route::setAirline(const std::string &airline) {
    Route::company->setIcao(airline);
}

Airport *Route::getOrigin() const {
    return origin;
}

void Route::setOrigin(Airport *origin) {
    Route::origin = origin;
}

Airport *Route::getDestination() const {
    return destination;
}

void Route::setDestination(Airport *destination) {
    Route::destination = destination;
}

Route::Route(Airline* _company, Airport* _origin, Airport* _destination) :
    company(_company),
    origin(_origin),
    destination(_destination)
    {}

Route::Route(Route &other) {
    this->company = other.company;
    this->origin = other.origin;
    this->destination = other.destination;
    this->company = other.company;
}

Route::~Route() = default;

//
// Created by fotop on 24/10/2023.
//


#include "VuelaFlight.h"
#include <iostream>
#include "Iterator.h"
#include <fstream>
#include <sstream>
#include <ctime>

VuelaFlight::VuelaFlight(std::string airports_file, std::string routes_file, std::string airlines_file) {

    std::ifstream airports_stream;

    airports_stream.open(airports_file); //project folder
    if (airports_stream.good()) {
        std::string id;
        std::string iata;
        std::string type;
        std::string name;
        std::string strLatitude;
        std::string strLongitude;
        std::string continent;
        std::string country_iso;
        std::stringstream columns_airports;
        std::string line;

        clock_t t_ini = clock();

        while (getline(airports_stream, line)) {

            //¿Exists a new line on the file?
            if (!line.empty()) {

                columns_airports.str(line);

                //Line format: id;iata;type;size;fecha;country_iso

                getline(columns_airports, id, ';'); //we readAVL the line till ';' and omit the caracter
                getline(columns_airports, iata, ';');
                getline(columns_airports, type, ';');
                getline(columns_airports, name, ';');
                getline(columns_airports, strLatitude, ';');
                getline(columns_airports, strLongitude, ';');
                getline(columns_airports, continent, ';');
                getline(columns_airports, country_iso, ';');

                line = "";
                columns_airports.clear();
                UTM location = UTM(strLatitude, strLongitude);
                airports.push(Airport(std::stoi(id), iata, type, name, location, continent, country_iso));
            }
        }

        airports_stream.close();

        std::cout << " Dynamic_container with airports initialized." << std::endl << " Reading Time: " << ((clock() - t_ini) / (float) CLOCKS_PER_SEC) << " secs." << std::endl;
    } else {
        std::cout << "Fatal error opening the file" << std::endl;
    }

    airports.sort_container();


    std::ifstream airlines_stream;
    airlines_stream.open(airlines_file); //project folder
    if (airlines_stream.good()) {
        std::string id;
        std::string icao;
        std::string name;
        std::string country;
        std::string active;
        bool real_active;
        std::stringstream columns_airlines;
        std::string line;

        clock_t t_ini = clock();

        while (getline(airlines_stream, line)) {

            //¿Exists a new line on the file?
            if (!line.empty()) {

                columns_airlines.str(line);


                getline(columns_airlines, id, ';'); //we readAVL the line till ';' and omit the caracter
                getline(columns_airlines, icao, ';');
                getline(columns_airlines, name, ';');
                getline(columns_airlines, country, ';');
                getline(columns_airlines, active, ';');

                if (active == "Y")
                    real_active = true;
                else
                    real_active = false;

                line = "";
                columns_airlines.clear();

                Airline line_airline(std::stoul(id),icao,name,country,real_active);
                work.push(line_airline);

            }
        }

        airports_stream.close();

        std::cout << " AVL with airlines initialized./n Reading Time: " << ((clock() - t_ini) / (float) CLOCKS_PER_SEC) << " secs." << std::endl;
    } else {
        std::cout << "Fatal error opening the file" << std::endl;
    }



    std::ifstream routes_stream;
    routes_stream.open(routes_file); //project folder
    if (routes_stream.good()) {
        std::string airline;
        std::string orig_airport;
        std::string dest_airport;
        std::stringstream columns_routes;
        std::string line;


        clock_t t_ini = clock();

        while (getline(routes_stream, line)) {

            //¿Exists a new line on the file?
            if (!line.empty()) {

                columns_routes.str(line);


                getline(columns_routes, airline, ';'); //we readAVL the line till ';' and omit the caracter
                getline(columns_routes, orig_airport, ';');
                getline(columns_routes, dest_airport, ';');

                line = "";
                columns_routes.clear();

                Airport orig = Airport(orig_airport);
                Airport dest = Airport(dest_airport);
                Airline airlineObject(airline);
                //search in log time the airline needed to build the route
                Airline* realAirline = work.itSearch(airlineObject);
                Route line_route(realAirline,airports.binary_search_dir(orig),airports.binary_search_dir(dest));
                //push the new route on the linkedList
                routes.push_back(line_route);
                //link recent route to his airline.
                realAirline->linkAirRoute(&routes.get_tail());
            }
        }

        airports_stream.close();

        std::cout << " Linked_list with routes initialized./n Reading Time: " << ((clock() - t_ini) / (float) CLOCKS_PER_SEC) << " secs." << std::endl;
    } else {
        std::cout << "Fatal error opening the file" << std::endl;
    }

}

Route& VuelaFlight::origDestRoutesSearch(const std::string& airportIataOrig, const std::string& airportIataDest) {
    Iterator<Route> iterator = routes.iterator();
    unsigned int count = 0;

    while(count < routes.list_size() and !iterator.end()){
        if (iterator.data().getOrigin()->getIata() == airportIataOrig and iterator.data().getDestination()->getIata() == airportIataDest){
            return iterator.data();
        }
        iterator.next();
        count++;
    }
    throw std::invalid_argument("---FATAL ERROR-- Doesn't exist a route in the database specified with the airports given");
}

Dynamic_container<Route> VuelaFlight::origRoutesSearch(std::string airportIataOrig) {
    Iterator<Route> iterator = routes.iterator();
    unsigned int count = 0;
    unsigned int found_count = 0;
    Dynamic_container<Route> found_routes;
    while(count < routes.list_size() and !iterator.end()){
        if (iterator.data().getOrigin()->getIata() == airportIataOrig){
            found_routes.push(iterator.data());
            found_count++;
        }
        iterator.next();
        count++;
    }
    if(found_count == 0){
        throw std::invalid_argument("---FATAL ERROR-- Doesn't exist a route in the database specified with the origin airport given");
    }
    return found_routes;
}

Dynamic_container<Airport> VuelaFlight::countryAirportSearch(std::string country) {
    Iterator<Route> iterator = routes.iterator();
    unsigned int count = 0;
    unsigned int found_count = 0;
    Dynamic_container<Airport> found_airports;
    while(count < routes.list_size() and !iterator.end()){
        if (iterator.data().getOrigin()->getCountryIso() == country or iterator.data().getDestination()->getCountryIso() == country){
            Airport* airport_to_push = iterator.data().getOrigin();
            found_airports.push(*airport_to_push);
            found_count++;
        }
        iterator.next();
        count++;
    }
    if(found_count == 0){
        throw std::invalid_argument("---FATAL ERROR-- Doesn't exist a route in the database specified with the origin airport given");
    }
    return found_airports;
}

void VuelaFlight::addNewRoute(std::string origAirportIata, std::string destAirportIata, std::string airline) {
    Airport orig_to_search(origAirportIata);
    Airport* orig = airports.binary_search_dir(orig_to_search);
    if (orig == nullptr){
        throw std::invalid_argument("---FATAL ERROR-- Doesn't exist a route in the database specified with the origin airport IATA given");
    }
    Airport dest_to_search(destAirportIata);
    Airport* dest = airports.binary_search_dir(dest_to_search);
    if (dest == nullptr){
        throw std::invalid_argument("---FATAL ERROR-- Doesn't exist a route in the database specified with the destination airport IATA given");
    }
    Airline auxAirline(airline);
    Route new_route(work.itSearch(auxAirline),orig,dest);
    routes.push_back(new_route);

}

const Dynamic_container<Airport> &VuelaFlight::getAirports() const {
    return airports;
}

const Linked_list<Route> &VuelaFlight::getRoutes() const {
    return routes;
}

Airline& VuelaFlight::searchAirline(std::string airlineIcao) {
    Airline target(airlineIcao);
    Airline result = *work.itSearch(target);

    std::cout << "Data of airline: Id " << result.getId() << ", Name " << result.getName() << ", country " << result.getCountry() << " and is active? " << result.isActive();
    return result;
}

Dynamic_container<Airline> VuelaFlight::searchActiveAirline() {
    Dynamic_container<Airline*> data = work.readAVL();
    Dynamic_container<Airline> result;
    for (unsigned int i=0; i < data.used_tam();i++){
        if(data[i]->isActive())
            result.push(*data[i]);
    }
    return result;
}



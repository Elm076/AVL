

#include <iostream>
#include <string>
#include <ctime>
#include "Dynamic_container.h"
#include "Airport.h"
#include "Linked_list.h"
#include "Iterator.h"
#include "AVL.h"
#include "VuelaFlight.h"

/**
 * @author Adrián González Pérez agp00118@red.ujaen.es
 */

int main() {

    std::cout << ".....Start of the program 1....." << std::endl;

    AVL<int> intTree;

    int x = 100;
    intTree.push(x);

    for (int i = 0; i < 10; i ++){
        intTree.push(i);
    }

    int a = 5;
    intTree.push(a);
    for (int i = 0; i < 10; i ++){
        intTree.push(i);
    }

    int b = 1782;
    int c = -123;
    int d = 123981;
    int e = 12;
    int f = -1;
    int g = 25;
    int h = 23;
    intTree.push(b);
    intTree.push(c);
    intTree.push(d);
    intTree.push(e);
    intTree.push(f);
    intTree.push(g);
    intTree.push(h);


    Dynamic_container<int*> treeArray = intTree.readAVL();

    AVL<int> intTree2(intTree);

    Dynamic_container<int*> treeArray2 = intTree2.readAVL();

    std::cout << "---Printing treeArray---" <<std::endl;
    for(unsigned int i = 0; i < treeArray.used_tam(); i++){
        std::cout << *treeArray[i] << std::endl;
    }

    std::cout << "---Printing treeArray2---" <<std::endl;
    for(unsigned int i = 0; i < treeArray2.used_tam(); i++){
        std::cout << *treeArray2[i] << std::endl;
    }

    AVL<int> intTree3 = intTree2;
    Dynamic_container<int*> treeArray3 = intTree3.readAVL();

    std::cout << "---Printing treeArray3---" <<std::endl;
    for(unsigned int i = 0; i < treeArray3.used_tam(); i++){
        std::cout << *treeArray3[i] << std::endl;
    }

    try{
        intTree3 = intTree3;
    }
    catch (std::invalid_argument err){
        std::cout << err.what() << std::endl;
    }

    AVL<int> intTree4;
    for (int i = 650; i < 700; i ++){
        intTree4.push(i);
    }

    intTree3 = intTree4;
    Dynamic_container<int*> treeArraylast = intTree3.readAVL();
    std::cout << "---Printing treeArray3---" <<std::endl;
    for(unsigned int i = 0; i < treeArray3.used_tam(); i++){
        std::cout << *treeArray3[i] << std::endl;
    }

    std::cout<< "The height of the Tree1 is: " << intTree.height() << std::endl;
    std::cout<< "The size of the Tree1 is: " << intTree.sizeAVL() << std::endl;

    std::cout<< "The height of the Tree3 is: " << intTree3.height() << std::endl;
    std::cout<< "The size of the Tree3 is: " << intTree3.sizeAVL() << std::endl;


    std::cout << "The element " << b << " was found in the Tree1? Answer: " << *intTree.recSearch(b) << " ." << std::endl;
    try {
        int z = 12831123;
        std::cout << "The element " << z << " was found in the Tree1? Answer: " << *intTree.recSearch(z) << " ." << std::endl;
    }
    catch (std::invalid_argument err){
        std::cout << err.what() << std::endl;
    }
    std::cout << "The element " << b << " was found in the Tree1? Answer: " << *intTree.itSearch(b) << " ." << std::endl;
    try {

        int y = -123141;
        std::cout << "The element " << y << " was found in the Tree1? Answer: " << *intTree.itSearch(y) << " ." << std::endl;
    }
    catch (std::invalid_argument err){
        std::cout << err.what() << std::endl;
    }





    std::cout << std::endl << ".....Start of the program 1....." << std::endl << std::endl;

    VuelaFlight dataBase("..\\aeropuertos_v2.csv", "..\\rutas_v1.csv", "..\\aerolineas_v1.csv");

    dataBase.searchAirline("RYR");

    //Tried to do exercise 4
    // dataBase.searchAirline("IBE");

    std::cout << "----- End of the program -----" << std::endl;
}
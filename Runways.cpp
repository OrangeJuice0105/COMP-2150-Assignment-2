/**
 * This file is the implementation of the Runways.h blueprint.
 * @author: Student name: Duc Cam Thai, Student number: 7851908
 */

#include "Runways.h"

/**
 * Fills the runways array with the heap-allocated runway objects. 
 * Each runway is assigned an ID from 1 to numberOfRunways.
 */
void Runways::fill() {

    //For loop to allocate new runways:
    for (int i = 0; i < numberOfRunways; ++i) {
        runways[i] = new Runway(i + 1);
    }

}

/**
 * Constructs the runway list. Each runway is assigned an ID based on 1-indexing (i.e., from 1 to numberOfRunways)
 * @param numberOfRunways : The number of runways that this list can hold.
 */
Runways::Runways(int numberOfRunways) {
    this->numberOfRunways = numberOfRunways;
    runways = new Runway*[numberOfRunways];
    this->fill();
}

/**
 * Retrieves a Runway based on the input ID.
 * @param id : The id of the runway to look for.
 * @return The runway object with this ID.
 */
Runway *Runways::getRunway(int id){
    return runways[id - 1];
}

/**
 * Performs a linear search and retrieves the first runway in this list that is available to be used.
 * @return The nearest runway that is not occupied by any planes.
 */
Runway *Runways::getUnoccupied() {
    for (int i = 0; i < numberOfRunways; i++) {
        if (runways[i]->isRunwayAvailable()) {
            return runways[i];
        }
    }
    return nullptr;
}

/**
 * Destructor for this list. It first traverses the array to delete any allocated Runway objects, 
 * then deletes the array itself.
 */
Runways::~Runways() {

    //For loop to deallocates the runway objects:
    for (int i = 0; i < numberOfRunways; i++) {
        delete runways[i];
    }

    //Deletes the array itself:
    delete[] runways;
}

/**
 * This file is the implementation of the Runway.h blueprint.
 * @author: Student name: Duc Cam Thai, Student number: 7851908
 */

#include "Runway.h"

/**
 * Constructs the runway based on the input ID.
 * @param id : The id associated with this runway.
 */
Runway::Runway(int id) : available(true) {
	this->id = id;
}

/**
 * Returns the ID associating with this runway.
 * @return This runway's ID.
 */
int Runway::getId() const {
	return this->id;
}

/**
 * Checks if this runway is available or not.
 * @return A boolean value indicating this runway's availablity.
 */
bool Runway::isRunwayAvailable() const {
	return this->available;
}

/**
 * Assigns a plane onto this runway and switch the availibity flag to false temporarily.
 */
void Runway::assignPlane() {
	this->available = false;
}

/**
 * Clears this runway and makes it available to use again.
 */
void Runway::clearRunway() {
	this->available = true;
}

/**
 * Frees this runway back to the memory.
 */
Runway::~Runway() {}

/**
 * Print method. Prints the runway ID. Used for debugging only.
 */
void Runway::print() {
	std::cout << id << std::endl;
}




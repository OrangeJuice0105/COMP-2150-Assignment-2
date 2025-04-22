/*
 * NAME:            Duc Cam Thai
 * STUDENT NUMBER:  7851908
 * COURSE:          COMP 2150   
 * INSTRUCTOR:      Heather Matheson
 * ASSIGNMENT:      2
 * QUESTION:        1
 * 
 * REMARKS: This program uses a hierarchy of classes to perform an event-driven simulation for an airport. The simulation
 * contains the number of runways and an input file to read each request. Both priority queues (one for planes to wait for their 
 * turn and the other to sort the event chronologically) used in this simulation are implemented using
 * an ordered linked list data structure. The Event objects are formed using class hierarchy and polymorphism. 
 * 
 * The input request file and the number of runways evolved in this simulation is read via command-line arguments.
 * 
 * The file is not read all via a while loop as the past assignments indicates. Instead it is only read if the event being
 * handled permitted it to do so in order to create a smooth simulation chronologically.
 */


#include "Simulation.h"

constexpr auto TERMINATE_MESSAGE = "Program terminated normally";

/**
 * Main method to execute our program. Here we use the argv array to input our file name and the number of runways 
 * along with the program execution command. The simulation object is then created to read these inputs and performs
 * the simulation as described.
 * @param argc : The number of arguments (including the run command)
 * @param argv : The input arguments to be run along with this program.
 * 
 * @return 0 if the program terminated normally, 1 if the termination is abnormal.
 */
int main(int argc, const char *argv[]) {

    //Safeguard: terminates early if the command has no arguments:
    if (argc == 1) {
        std::cout << "No arguments have been passed" << std::endl;
        exit(EXIT_FAILURE);
    }

    //Retrieves the input file and parses the runway into an integer:
    std::string fileName = argv[1];
    int runways = std::stoi(argv[2]);

    //Creates an event based on the number of runways then passes this input file to run the simulation:
    Simulation simulation(runways);
    simulation.startSimulation(fileName);

    //Calculates the total wasted time and prints the summary of this simulation:
    int wasted = simulation.getTotalWastedMinutes();
    simulation.printSummary(runways, wasted);

    //Prints the terminate message:
    printf("%s\n", TERMINATE_MESSAGE);

    //Exits normally:
    return EXIT_SUCCESS;
}
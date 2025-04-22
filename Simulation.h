#pragma once

#include <fstream>
#include <sstream>

#include "Runways.h"
#include "EventPriorityQueue.h"
#include "WaitList.h"
#include "RequestEvent.h"
#include "CompleteEvent.h"
#include "ActionEvent.h"

/**
 * Represents the whole airport simulation operation. The input file is read, and each event is created based on the 
 * plane's request. 
 * @author Student name: Duc Cam Thai Student number: 7851908
 */
class Simulation {

    private:
        int numRunways; //Number of runways (retrieved from command-line argument)
        Runways* runways; //The runway manager (storing runways and perform runway-related operations)
        EventPriorityQueue* eventQueue; //The event priority queue that are used to organize the events chronologically
        WaitList *waitList; //The wait list to assign each plane into position to either takeoff or land.
        int currentTime; //The current time to keep track of every event.
        int totalWastedTime; //The amount of time wasted for planes to wait for clearance.
    
    public:

        /**
         * Builds a simulation based on the number of runways.
         * @param numRunways : The number of runways that this simulation holds.
         */
        Simulation(int numRunways);

        /**
         * Handles the given event. The event is typecasted to check for either of the folowing 3 subevents:
         * 
         *      - Request event: The event where the plane makes the request to land or takeoff.
         * 
         *      - Action event: The event where the plane is allowed to take off by the ATC. This includes
         *    the total time it takes to find the runway and clears the turbulence.
         * 
         *      - Complete event: The event where plane has finally cleared the runway that it is allowed to takeoff or land.
         * 
         * Based on the subtypes of the events, it is handled separately by the methods described below:
         * 
         *      Simulation::handleRequest(RequestEvent *requestEvent, std::ifstream& fileStream);
         * 
         *      Simulation::handleAction(ActionEvent *actionEvent);
         * 
         *      Simulation::handleComplete(CompleteEvent *completeEvent);
         *
         * @param event : The event to be handled properly.
         * @param fileStream : The input file stream to be used in reading request if it is not EOF.
         */
        void handleEvent(Event *event, std::ifstream& fileStream);

        /**
         * Starts the simulation by reading the inputFile and perform controlled simulation.
         * The simulation is performed by creating an event from the very first line of this file, then puts it into the 
         * event queue. The event queue is then popped simultaneously until it is empty. Each time an event is removed, it is
         * handled appropriately based on the event type.
         * The current time is updated from each event removed from this queue. The following pseudocode describes this algorithm's
         * actions:
         * 
         *  Initialize Q (waiting line) and EventQueue to be empty
         *  Open data file
         *  Read the first request event from file and put it in the event queue
         *  While event queue is not empty { 
         *      Remove the first event from the event queue 
         *      Process that event, summarize data
         *  }
         *
         * @param inputFile : the input file to handle the file reading actions.
         */
        void startSimulation(const std::string& inputFile);

        /**
         * Handles the RequestEvent type. An event is considered to be a request is when the plane first makes one with the ATC for permission
         * on either landing or takeoff.
         * This method also receives the ifstream associating with the input file passed in the beginning. The pseudocode for this algorithm is:
         * 
         *  Add new plane to waiting line
         *  If one of the runways is available {
         *      get next plane in line
         *      create a Takeoff/Landing event 
         *      Insert this in order in the event queue
         *  }
         *  If not EOF {
         *      Read the next request event from the file and insert that in the event queue
         *  } 
         * 
         * @param requestEvent : The request event to be handled.
         * @param fileStream : The input file stream to be used in reading request if it is not EOF.
         */
        void handleRequest(RequestEvent *requestEvent, std::ifstream& fileStream);

        /**
         * Handles the ActionEvent type. An event is considered to be an action is when the ATC allows plane to either land
         * or take off safely. The following pseudocode describe this action:
         * 
         *  create a Complete event (clearance time = total time spent on runway + the time when this event takes place)
         *  Insert this in the event queue
         * 
         * @param requestEvent : The action event to be handled.
         */
        void handleAction(ActionEvent *actionEvent);

        /**
         * Handles the CompleteEvent type. An event is considered to be completed when the plane has cleared the runway after
         * landing and taking off. The following pseudocode describes the next operations:
         * 
         *  If the waiting line has not become empty (there is one more plane @ the front now) {
         *	    create a Takeoff/Landing event for the next plane
         *      Insert this in the event queue
         *  }
         * 
         * The wasted time is also calculated during this period by getting the current time substracted by the 
         * time that the plane makes the request. It is then added to the total wasted time tally.
         * 
         * @param completeEvent : The complete event to be handled.
         */
        void handleComplete(CompleteEvent *completeEvent);
        
        /**
         * Returns the total amount of wasted time in minutes that planes spend waiting for free runway.
         * @return The total amount of minutes wasted.
         */
        int getTotalWastedMinutes();

        /**
         * Creates a request event based on the contents of this line. The following format is used to create plane
         * and the event associated with this plane:
         *      [time] [callSign] [flightNumber] [size] [requestType]
         * 
         * where: 
         *  [time]: an integer value representing the time (minute) of a plane requesting a runway.
         *  [callSign]: is a string (guaranteed to be one token with no spaces) representing the airline.
         *  [flightNumber]: is an integer value representing the flight number.
         *  [size]: is a string representing the size of the plane. It can only be either small, large, heavy or super.
         *  [requestType]: is a string representing what the plane is requesting. It can only be either takeoff or landing.
         * 
         * A special ATC ID is also assigned to each plane ordinally. The event is then created based on the requestType
         * and returned accordingly.
         * 
         * @param line : The input string containing the plane's information
         * @return The event at the given time associating with this plane.
         */
        Event* createEvent(const std::string& line);

        /**
         * Prints the summary after the simulation has ended. The information contains the number of runways assigned
         * to this simulation and the total amount of time wasted waiting for runways in minutes.
         * 
         * @param numberRunways : The number of runways associated with the simulation
         * @param wastedMinutes : The total amount of wasted time.
         */
        void printSummary(const int& numberRunways, const int& wastedMinutes);

        /**
         * Destroys and frees any resources associating with this simulation: the waitlist, event queue and the runways 
         * object.
         */
        ~Simulation();
        
};




/**
 * This file is the implementation of the Simulation.h blueprint.
 * @author: Student name: Duc Cam Thai, Student number: 7851908
 */

#include "Simulation.h"

#include "RequestLandingEvent.h"
#include "RequestTakeoffEvent.h"
#include "TakeoffEvent.h"
#include "LandingEvent.h"
#include "CompleteEvent.h"

constexpr auto TAGS_DECORATED = 20; //Uses in summary printing only;


static int id = 1; //The ID for each plane created

/**
 * Helper method which destroys the allocated event and assigns it to nullptr. This is a part of the cleanup code.
 * 
 * @param event : the event to be freed back to the memory.
 */
static void destroyEvent(Event *event) {
    delete event;
    event = nullptr;
}

/**
 * Builds a simulation based on the number of runways.
 * @param numRunways : The number of runways that this simulation holds.
 */
Simulation::Simulation(int numRunways) {
    this->numRunways = numRunways;
    this->runways = new Runways(numRunways);
    this->eventQueue = new EventPriorityQueue;
    this->waitList = new WaitList;
    currentTime = 0;
    totalWastedTime = 0;
}

/**
 * Destroys and frees any resources associating with this simulation: the waitlist, event queue and the runways 
 * object.
 */
Simulation::~Simulation() {
    delete runways;
    delete eventQueue;
    delete waitList;
}

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
void Simulation::startSimulation(const std::string& fileName) {

    //Prompts a starting message:
    std::cout << "Starting simulation..." << std::endl;

    std::ifstream inputFile; //The input file stream associating with this simulation

    //Opens the file based on the file name:
    inputFile.open(fileName);

    
    std::string line; //The line read from the file
    Event *event; //The event used in creating and keeping track of dequeuings.

    //If the file contains any lines, proceeds to reads the first line:
    if (std::getline(inputFile, line)) {

        //Creates the event based on the first line, then puts it into the queue:
        event = this->createEvent(line);
        this->eventQueue->enqueue(event);

        //While loop to dequeue each event out until the queue is empty. Processes each event as it is being removed:
        while (!eventQueue->isEmpty()) {
            
            //Retrieves the event and updates the current time:
            event = eventQueue->dequeue();
            currentTime = event->getTime();

            //Handles this event with the given file stream, then deallocates the event once finished:
            handleEvent(event, inputFile);
            destroyEvent(event);

        }

    }

}

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
void Simulation::handleEvent(Event *event, std::ifstream& fileStream) {

    //Prints the event's information to the console:
    event->processEvent();

    // Type cast the given events into their specific subclasses:
    RequestEvent *requestEvent = dynamic_cast<RequestEvent *>(event); //Request event downcast
    ActionEvent *actionEvent = dynamic_cast<ActionEvent *>(event); //Action event downcast
    CompleteEvent *completeEvent = dynamic_cast<CompleteEvent *>(event); //Completer event downcast

    // Any of the dynamic cast of the pointer is non-null, proceeds to handle the required event:
    if (requestEvent != nullptr) {
        this->handleRequest(requestEvent, fileStream);
    } else if (actionEvent != nullptr) {
        this->handleAction(actionEvent);
    } else if (completeEvent != nullptr) {
        this->handleComplete(completeEvent);
    } else {
        throw std::exception();
    }
    
}

/**
 * Returns the total amount of wasted time in minutes that planes spend waiting for free runway.
 * @return The total amount of minutes wasted.
 */
int Simulation::getTotalWastedMinutes() {
    return totalWastedTime;
}

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
void Simulation::handleRequest(RequestEvent *requestEvent, std::ifstream& fileStream) {

    // Retrieves the plane from this event
    Plane plane = requestEvent->getPlane();
 
    Event *event; //The compatible event to be created
    std::string line; //The string storage used to read other line

    //Gets the first unoccupied runway in the list
    Runway *runway = runways->getUnoccupied();

    //Enqueues the current plane into the waitlist:
    waitList->enqueue(plane);

    //If there is a runway available:
    if (runway != nullptr) {

        //Removes the plane from the waitlist and retrieves the runway ID:
        Plane currentPlane = waitList->dequeue();
        int runwayID = runway->getId();

        //Assign the plane to the given runway, making it non-available this time:
        runway->assignPlane();

        //Creates a compatible action event based on the request type:
        if (currentPlane.getRequestType() == "takeoff") {
            event = new TakeoffEvent(currentTime, currentPlane, runwayID);
        } else if (currentPlane.getRequestType() == "landing") {
            event = new LandingEvent(currentTime, currentPlane, runwayID);
        } else {
            throw std::invalid_argument("Request type not found");
        }

        //Enqueues this event once it is created:
        eventQueue->enqueue(event);

    } 

    //If it is not EOF yet, proceeds to process the new event for the next line, then enqueues it to the event queue:
    if (std::getline(fileStream, line)) {
        event = this->createEvent(line);
        this->eventQueue->enqueue(event);
    }

}

/**
 * Handles the ActionEvent type. An event is considered to be an action is when the ATC allows plane to either land
 * or take off safely. The following pseudocode describe this action:
 * 
 *  create a Complete event (clearance time = total time spent on runway + the time when this event takes place)
 *  Insert this in the event queue
 * 
 * @param requestEvent : The action event to be handled.
 */
void Simulation::handleAction(ActionEvent *actionEvent) {

    //Retrieves the runway ID associating with this event
    int id = actionEvent->getRunwayID();

    //Calculates the new time for complete event based on the total amount of time spent and the time when this event occurs
    int newTime = actionEvent->calculateTotalTime() + actionEvent->getTime();

    //Creates a complete event based on this new time and the same plane from the action event, then inserts it into the queue:
    Event *event = new CompleteEvent(newTime, actionEvent->getPlane(), id);
    this->eventQueue->enqueue(event);

}

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
void Simulation::handleComplete(CompleteEvent *completeEvent) {

    //Calculates the current time:
    currentTime = completeEvent->getTime();

    //Retrieves the runway ID and searches for the runway with this ID then clears it back to available:
    int runwayID = completeEvent->getRunwayID();
    Runway *runway = runways->getRunway(runwayID);
    runway->clearRunway();

    //If the waitlist is not empty, proceeds to pull the next plane to takeoff or landing:
    if (!waitList->isEmpty()) {

        //Removes the plane from the waitlist:
        Plane currentPlane = waitList->dequeue();

        Event *event; //Event to be inserted into the queue

        //Assigns the plane to the recently freed runway:
        runway->assignPlane();

        //Calculate the wasted time by taking the difference between the current time and the time that this plane made the request:
        int wastedTime = currentTime - currentPlane.getRequestTime();

        //Adds this time to the total tally:
        totalWastedTime += wastedTime;

        //Creates a compatible action event based on the request type:
        if (currentPlane.getRequestType() == "takeoff") {
            event = new TakeoffEvent(currentTime, currentPlane, runwayID);
        } else if (currentPlane.getRequestType() == "landing") {
            event = new LandingEvent(currentTime, currentPlane, runwayID);
        } else {
            throw std::invalid_argument("Request type not found");
        }

        //Enqueues this event once it is created:
        eventQueue->enqueue(event);

    }

}

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
Event* Simulation::createEvent(const std::string& line) {

    Event *event; //The event to be created 
    std::stringstream strstream(line); //The stream to token the input line
    std::string token; //The tokens to be stored in each read
    int time = 0; //The time where the request occurs
    std::string callSign = ""; //The plane's callsign
    int flightNum = 0; //The plane's flight number
    std::string size = ""; //The size of this plane
    std::string requestType = ""; //The request type for this plane
    static Plane newPlane; //The plane object to be associated with this event.

    strstream >> token;  //grabbing the next token (reading time)
    time = std::stoi(token); //converting time (string format) to an int
    strstream >> callSign;  //grabbing the next token (reading call sign)
    strstream >> token;
    flightNum = stoi(token);  //grabbing the next token (reading flight number)
    strstream >> size;  //grabbing the next token (reading plane size)
    strstream >> requestType;  //grabbing the next token (reading request type, either landing or takeoff)

    //Creates a newPlane based on the input parameters:
    newPlane = Plane(id++, callSign, flightNum, size, requestType, time);

    //Creates a compatible request event based on the request type, then returns this event:
    if (requestType == "takeoff") {
        event = new RequestTakeoffEvent(time, newPlane);
    } else if (requestType == "landing") {
        event = new RequestLandingEvent(time, newPlane);
    } else {
        throw std::invalid_argument("Incompatible request");
    }
    return event;
}

/**
 * Prints the summary after the simulation has ended. The information contains the number of runways assigned
 * to this simulation and the total amount of time wasted waiting for runways in minutes.
 * 
 * @param numberRunways : The number of runways associated with the simulation
 * @param wastedMinutes : The total amount of wasted time.
 */
void Simulation::printSummary(const int &numberRunways, const int &wastedMinutes) {

    //While loop to print '#' 20 times:
    for (int i = 0; i < TAGS_DECORATED; i++) {
        std::cout << "#";
    }
    std::cout << std::endl;

    //Denotes that the simulation has ended:
    std::cout << "The simulation has ended" << std::endl;

    //Prints the number of runways and the wasted time total onto the console:
    printf("The number of runways was %d\n", numberRunways);
    printf("The total amount of time wasted because runways were not available was %d minutes\n", wastedMinutes);

    //While loop to print '#' 20 times:
    for (int i = 0; i < TAGS_DECORATED; i++) {
        std::cout << "#";
    }
    std::cout << std::endl;
    
}
# disc-events-sim-bank

Discrete-events simulator for a bank system with customer arrivals and departures.

## Arguments

The simulator can be used as following:

./simulator -h -d DURATION -i INTERVAL

-h: Prints a help message.

-d: Sets the maximum duration of the simulation to DURATION.

-s: Sets the maximum possible time for randomly generated service time to SERVICE.

-i: Sets the maximum possible time for randomly generated interarrivals time to INTARRV.

-l: Set the number of tellers and therefore lines to service customers.

If any of these parameters is not provided, default values are used.

## Events

There are two types of events: arrivals and departures.

### Arrivals

For arrivals, the new customer is added to the line. In case the new customer is the only one in line, a new service can start right away, so a new departure is scheduled, based on a randomly generated service time.

Whenever an arrival event occur, a random interarrival time is generated, and so another arrival is scheduled.

A new customer is always allocated to the line which has fewer customers.

### Departures

When a departure happens, the number of customers in line decreases by one. If the line is not empty, the teller can begin a new service, and a new departure is scheduled.

## Output

By collecting the total time to serve the customers until the end of the simulation and the number of customers served, the program calculates the average running time and prints it on **stdout**.
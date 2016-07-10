# disc-events-sim-bank

Discrete-events simulator for a bank system with customer arrivals and departures.

## Arguments

The simulator can be used as following:

./simulator [-d DURATION]

DURATION: Maximum duration of the simulation. The default value is 1000.

## Events

There are two types of events: arrivals and departures.

### Arrivals

For arrivals, the new customer is added to the line. In case the new customer is the only one in line, a new service can start right away, so a new departure is scheduled, based on a randomly generated service time.

Whenever an arrival event occur, a random interarrival time is generated, and so another arrival is scheduled.

### Departures

When a departure happens, the number of customers in line decreases by one. If the line is not empty, the teller can begin a new service, and a new departure is scheduled.

## Output

By collecting the total time to serve the customers until the end of the simulation and the number of custormers served, the program calculates the average running time and prints it on **stdout**.
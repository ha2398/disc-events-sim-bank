/*
 * event.h
 */

#include <stdbool.h>

#ifndef EVENT_H
#define EVENT_H

/**
 * struct event - defines an event in the simulation.
 * An event can be a customer arrival or departure.
 * @type: 0 for departure, 1 for arrival.
 * @time: time the event happened.
 */
struct event {
	unsigned short type;
	unsigned long time;
};

/**
 * event_less - compares two events.
 * Returns true if @event1 happened before @event2, and
 * false otherwise.
 */
bool event_less(const void *event1, const void *event2);

/**
 * new_arrival - generates an arrival event and
 * returns a pointer to it.
 * @time: arrival time.
 */
struct event *new_arrival(const unsigned long time);

/**
 * new_departure - generates a departure event and
 * returns a pointer to it.
 * @time: departure time.
 */
struct event *new_departure(const unsigned long time);

#endif /* EVENT_H */

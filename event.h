/*
 * event.h
 */

#ifndef EVENT_H
#define EVENT_H

#include <stdbool.h>

/* Events' codes */
#define DEPT 0
#define ARRV 1

/**
 * struct event - defines an event in the simulation.
 * An event can be a customer arrival or departure.
 * @type: type of the event.
 * @time: time the event happened.
 * @line: line where the event happened.
 */
struct event {
	unsigned short type;
	unsigned long time;
	unsigned long line;
};

/**
 * new_event - generates an event and
 * returns a pointer to it.
 * @type: event type.
 * @time: event time.
 * @line: event line.
 */
struct event *new_event(const unsigned short type, const unsigned long time, 
	const unsigned long line);

/**
 * event_less - compares two events.
 * Returns true if @event1 happened before @event2, and
 * false otherwise.
 */
bool event_less(const void *event1, const void *event2);

#endif /* EVENT_H */

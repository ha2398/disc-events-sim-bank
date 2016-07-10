/*
 * event.c
 */

#include "event.h"
#include <stdlib.h>

bool event_less(const void *event1, const void *event2)
{
	unsigned long time1 = ((struct event *) event1)->time;
	unsigned long time2 = ((struct event *) event2)->time;
	return (time1 < time2) ? true : false;
}

struct event *new_arrival(const unsigned long time)
{
	struct event *new_event;

	new_event = malloc(sizeof(*new_event));
	new_event->type = 1;
	new_event->time = time;

	return new_event;
}

struct event *new_departure(const unsigned long time)
{
	struct event *new_event;

	new_event = malloc(sizeof(*new_event));
	new_event->type = 0;
	new_event->time = time;

	return new_event;
}
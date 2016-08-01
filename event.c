/*
 * event.c
 */

#include "event.h"
#include <stdbool.h>
#include <stdlib.h>

bool event_less(const void *event1, const void *event2)
{
	unsigned long time1 = ((struct event *) event1)->time;
	unsigned long time2 = ((struct event *) event2)->time;

	return (time1 < time2) ? true : false;
}

struct event *new_event(const unsigned short type, const unsigned long time,
	const unsigned long line)
{
	struct event *new;

	new = malloc(sizeof(*new));
	new->type = type;
	new->time = time;
	new->line = line;

	return new;
}

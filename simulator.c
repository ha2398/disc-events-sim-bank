/*
 * simulator.c
 */

#include "event.h"
#include "heap.h"
#include <stdio.h>
#include <stdlib.h>

#define MAX_INTERVAL 50 /* maximum time for service and interarrivals */
#define DURATION 1000 /* default duration of the simulation */

/**
 * die_with_error - prints a @message and finishes execution
 */
static void die_with_error(const char *message)
{
	fprintf(stderr, "%s\n", message);
	exit(EXIT_FAILURE);
}

static void print_usage(const char *file_name)
{
	fprintf(stderr, "Usage:\t%s [-d duration]\n", file_name);
	fprintf(stderr, "duration: Length of the simulation.\n");
}

int main(int argc, char **argv)
{
	unsigned long current_time; /* current simulation time */
	unsigned long customers_line; /* customers currently in line */
	unsigned long duration = DURATION; /* duration of the simulation */
	unsigned long interarrival_time; /* time until next arrival occurs */
	unsigned long service_time; /* time for teller to serve a customer */

	double total_waiting_time;
	double throughput;
	double mean_waiting_time;

	struct event *next_event;
	struct heap *events;

	extern char *optarg;
	extern int optopt;

	int opt;
	opt = getopt(argc, argv, "d:h");
	switch (opt) {
	case 'h':
		print_usage(argv[0]);
		return 1;
	case 'd':
		duration = atoi(optarg);
		break;
	case '?':
		if (optopt == 'd')
			die_with_error("Error: option -d requires an"
				"argument");
	}

	/* Initializations */

	customers_line = 0;
	current_time = 0;
	events = heap_init(event_less);

	total_waiting_time = 0;
	throughput = 0;
	mean_waiting_time = 0;

	srand(0);

	interarrival_time = rand() % MAX_INTERVAL;
	heap_push(events, new_arrival(current_time + interarrival_time));

	/* Simulation */
	while (current_time < duration) {
		unsigned short type;
		unsigned long time;

		next_event = heap_pop(events);
		type = next_event->type;
		time = next_event->time;

		current_time = time;

		switch (type) {
		case 0: /* departure */
			customers_line--;
			throughput++;
			service_time = rand() % MAX_INTERVAL;
			if (customers_line) {
				heap_push(events,new_departure(current_time +
					service_time));
				total_waiting_time += service_time;
			}
			break;
		case 1: /* arrival */
			customers_line++;
			if (customers_line == 1) {
				service_time = rand() % MAX_INTERVAL;
				heap_push(events,new_departure(current_time +
					service_time));
			}
			interarrival_time = rand() % MAX_INTERVAL;
			heap_push(events, new_arrival(current_time +
				interarrival_time));
			break;
		}
	}

	if (throughput)
		mean_waiting_time = total_waiting_time / throughput;

	printf("%f\n", mean_waiting_time);

	return 0;
}


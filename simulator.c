/*
 * simulator.c
 */

#include "event.h"
#include "heap.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Default values */
#define DURATION 1000 /* default duration of the simulation */
#define LINES 1 /* default number of lines */
#define SERV_TIME 50 /* default max time for service */
#define INTARRV_TIME 50 /* default max time for interarrivals */

static void greetings(const char *file_name)
{
	fprintf(stderr, "Discrete-events bank simulator.\n");
	fprintf(stderr, "For usage, run: %s -h\n", file_name);
}

static void print_usage(const char *file_name)
{
	fprintf(stderr, "Usage:\t%s [-h]"
		" [-d duration]"
		" [-s service]"
		" [-i interarrivals]"
		" [-l lines]\n", file_name);

	fprintf(stderr, "h: Prints usage.\n");
	fprintf(stderr, "d: Length of the simulation.\n");
	fprintf(stderr, "s: Maximum time for service.\n");
	fprintf(stderr, "i: Maximum time for interarrivals.\n");
	fprintf(stderr, "l: Number of customer lines (tellers)\n");
}

static unsigned long get_min_line(const unsigned long *lines,
	unsigned long number_lines)
{
	unsigned long i,
		      min_line = 0,
		      len_min_line = lines[0];

	for (i = 1; i < number_lines; i++) {
		if (lines[i] < len_min_line) {
			min_line = i;
			len_min_line = lines[i];
		}
	}

	return min_line;
}

static __attribute__((noinline)) void pin_go(void)
{
        asm ("");
}

static __attribute__((noinline)) void pin_stop(void)
{
        asm ("");
}

int main(int argc, char **argv)
{
	unsigned long current_time; /* current simulation time */
	unsigned long *customer_lines; /* each position represents a line */
	unsigned long duration = DURATION; /* duration of the simulation */
	unsigned long num_lines = LINES; /* number of customer lines */

	unsigned long max_service = SERV_TIME; /* max service time */
	unsigned long max_intarrv = INTARRV_TIME; /* max interarrival time */

	unsigned long interarrival_time; /* time until next arrival occurs */
	unsigned long service_time; /* time for teller to serve a customer */

	unsigned long min_line = 0; /* line with fewer people */
	unsigned long customers_min_line = 0; /* customers in min_line */

	double total_waiting_time;
	double throughput;
	double mean_waiting_time;

	struct event *next_event;
	struct heap *events;

	extern char *optarg;
	extern int optopt;

	int opt;
	char optstring[] = "d:hs:i:l:";
	opt = getopt(argc, argv, optstring);
	while (opt != -1) {
		switch (opt) {
		case 'h':
			print_usage(argv[0]);
			return 0;
		case 'd':
			duration = atoi(optarg);
			break;
		case 's':
			max_service = atoi(optarg);
		case 'i':
			max_intarrv = atoi(optarg);
			break;
		case 'l':
			num_lines = atoi(optarg);
			break;
		case '?':
			if (strchr(optstring, optopt)) {
				print_usage(argv[0]);
				return 1;
			}
		}	

		opt = getopt(argc, argv, optstring);
	}

	greetings(argv[0]);

	/* Initializations */
	customer_lines = calloc(sizeof(*customer_lines), num_lines);
	current_time = 0;
	events = heap_init(event_less);

	total_waiting_time = 0;
	throughput = 0;
	mean_waiting_time = 0;

	srand(0);

	interarrival_time = rand() % max_intarrv;
	heap_push(events, new_event(ARRV, current_time + interarrival_time,
		min_line));

	pin_go();
	/* Simulation */
	while (current_time < duration) {
		unsigned short type;
		unsigned long time;
		unsigned long line;

		pin_stop();
		next_event = heap_pop(events);
		pin_go();

		type = next_event->type;
		time = next_event->time;
		line = next_event->line;

		free(next_event);
		current_time = time;

		switch (type) {
		case DEPT: /* departure */
			customer_lines[line]--;

			if (customer_lines[line] < customers_min_line) {
				min_line = line;
				customers_min_line = customer_lines[line];
			}

			throughput++;

			if (customer_lines[line]) {
				service_time = rand() % max_service;
				pin_stop();
				heap_push(events, new_event(DEPT, current_time
					+ service_time, line));
				pin_go();
				total_waiting_time += service_time;
			}

			break;
		case ARRV: /* arrival */
			customer_lines[line]++;

			pin_stop();
			if (line == min_line)
				min_line = get_min_line(customer_lines, num_lines);

			interarrival_time = rand() % max_intarrv;
			heap_push(events, new_event(ARRV, current_time +
				interarrival_time, min_line));

			pin_go();
			if (customer_lines[line] == 1) {
				service_time = rand() % max_service;
				pin_stop();
				heap_push(events, new_event(DEPT, current_time
					+ service_time, line));
			}

			break;
		}
	}

	if (throughput)
		mean_waiting_time = total_waiting_time / throughput;

	printf("%f\n", mean_waiting_time);

	return 0;
}

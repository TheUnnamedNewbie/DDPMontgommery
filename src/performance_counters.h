/*
 * performance_counters.h
 *
 *  Created on: Apr 26, 2016
 *      Author: pmaene
 */

#ifndef PERFORMANCE_COUNTERS_H_
#define PERFORMANCE_COUNTERS_H_

#include <stdint.h>

static inline void init_performance_counters(uint32_t reset) {
	// Enable all counters (including cycle counter)
	int32_t value = 1;

	if (reset) {
		// Reset all counters to zero
		value |= 2;
		// Reset cycle counter to zero
		value |= 4;
	}

	value |= 16;

	// Program the performance-counter control register
	asm volatile ("MCR p15, 0, %0, c9, c12, 0\t\n" :: "r"(value));

	// Enable all counters
  	asm volatile ("MCR p15, 0, %0, c9, c12, 1\t\n" :: "r"(0x8000000f));

  	// Clear overflows
  	asm volatile ("MCR p15, 0, %0, c9, c12, 3\t\n" :: "r"(0x8000000f));
}

static inline uint32_t get_cycle_counter() {
	unsigned int value;

	// Read CCNT register
	asm volatile ("MRC p15, 0, %0, c9, c13, 0\t\n": "=r"(value));

	return value;
}

#endif /* PERFORMANCE_COUNTERS_H_ */

/*
 * asm_mont_test.c
 *
 *  Created on: Oct 29, 2016
 *      Author: TheUnnamedNewbie
 */
//#include "montgomery.h"
#include "log.h"
#include "performance_counters.h"
#include <stdint.h>
#include <inttypes.h>
#include <stdio.h>
#include "asm_mont.h"
#include "montgomery.h"
#include "mode.h"



int test_montSum(uint32_t a, uint32_t b, uint32_t *t);

int test_montSum(uint32_t a, uint32_t b, uint32_t *t){

	uint32_t S, C;
	uint64_t sum;
	uint32_t tTest[3];


	//Such Loop Unrolling
	tTest[0] = t[0];
	tTest[1] = t[1];
	tTest[2] = t[2];
/*
	uint32_t result = memcpy(t, tTest, 3);
	result = memcmp(t, tTest, 3);
*/

	uint32_t result;


	Log(ASMMONTGOMERY, DEBUG, "Starting test_montSum");

	sum = (uint64_t)t[0] + (uint64_t)a*(uint64_t)b;
	t[0] = (uint32_t)sum;			//TEMP THIS IS NOT HOW THE REAL CODE SHOULD WORK
	C = (uint32_t)(sum>>32);
	addMont(t, 1, C);

	Log(ASMMONTGOMERY, DEBUG, "C-based sum complete");

	montSum(a, b, tTest);


	Log(ASMMONTGOMERY, DEBUG, "AsmBased sum complete");

	LogWithNumH(ASMMONTGOMERY, DEBUG, "t[0]: ", t[0]);
	LogWithNumH(ASMMONTGOMERY, DEBUG, "tTest[0]: ", tTest[0]);
	LogWithNumH(ASMMONTGOMERY, DEBUG, "t[1]: ", t[1]);

	LogWithNumH(ASMMONTGOMERY, DEBUG, "tTest[1]: ", tTest[1]);
	LogWithNumH(ASMMONTGOMERY, DEBUG, "t[2]: ", t[2]);

	LogWithNumH(ASMMONTGOMERY, DEBUG, "tTest[2]: ", tTest[2]);
	LogWithNum(ASMMONTGOMERY, DEBUG, "t[0] == tTest[0]: ", (t[0] == tTest[0]));
	LogWithNum(ASMMONTGOMERY, DEBUG, "t[1] == tTest[1]: ", (t[1] == tTest[1]));
	LogWithNum(ASMMONTGOMERY, DEBUG, "t[2] == tTest[2]: ", (t[2] == tTest[2]));

	if((t[0] == tTest[0]) && (t[1] == tTest[1]) && (t[2] == tTest[2])){result = 1;}
	else {result = 0;}

	return result;

}

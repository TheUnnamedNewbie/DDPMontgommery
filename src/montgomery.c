/*
 * montgomery.c
 *
 */

#include "montgomery.h"
#include "log.h"
#include "performance_counters.h"
#include <stdint.h>
#include <inttypes.h>
#include <stdio.h>
#include "asm_mont.h"
#include "mode.h"



//Declarations


void fips(uint32_t *a, uint32_t *b, uint32_t *n, uint32_t *n0, uint32_t *res, uint32_t SIZE);
void mont(uint32_t *a, uint32_t *b, uint32_t *n, uint32_t *n0, uint32_t *res, uint32_t SIZE);
void addMont(uint32_t *t, uint32_t i, uint32_t C);
void subCondMont(uint32_t *u, uint32_t *n, uint32_t S);
void mont(uint32_t *a, uint32_t *b, uint32_t *n, uint32_t *n0, uint32_t *res, uint32_t SIZE);

void mont(uint32_t *a, uint32_t *b, uint32_t *n, uint32_t *n0, uint32_t *res, uint32_t SIZE){

	#ifdef DebugOnMontgomery
		SetLogLevel(INFO);
	#endif

	fips(a, b, n, n0, res, SIZE);

	#ifdef DebugOnMontgomery
	SetLogLevelDefault();
	#endif

}


/*
 * TODO: MAKE THIS GO FASTER
 * Don't ever remove this, there will always be a way
 *
 */
void fips(uint32_t *a, uint32_t *b, uint32_t *n, uint32_t *n0, uint32_t *res, uint32_t SIZE){

	uint32_t t[3];
	uint32_t m[SIZE+1];
	int i, j;
	t[2]=t[1]=t[0]=0;

	for(i = 0; i<= SIZE; i++){
			m[i] = 0;
	}


	//uint64_t sum;
	//uint32_t S, C;

	for(i=0; i< SIZE; i++){
		for(j = 0; j< i; j++){
			montSum(a[j], b[i-j], m[j], n[i-j], t);
		}
			montSum2(a[i], b[0], m[i], n[0], t, m, i, n0[0]);
	}

	for(i = SIZE; i < 2*SIZE; i++){  // ASUMING THAT SIZE WILL NEVER BE MORE THAN 31 BITS LONG

		for(j = (i - SIZE + 1); j < SIZE; j++){
				montSum(a[j], b[i-j], m[j], n[i-j], t);
		}

		m[i - SIZE] = t[0];

		t[0] = t[1];
		t[1] = t[2];
		t[2] = 0;

	}

	m[SIZE] = t[0];
	uint32_t startsubcond = get_cycle_counter();
	subCondMont(m, n, SIZE);
	uint32_t stopsubcond =  get_cycle_counter();

	LogWithNum(MONTGOMMERY, CRITICAL, "Cycles for subcond: ", stopsubcond - startsubcond);
	for(i = 0; i <SIZE; i++){
		res[i] = m[i];
	}

}


void addMont(uint32_t *t, uint32_t i, uint32_t C){

	uint32_t S;
	uint64_t sum;
	while(C != 0){
		sum = (uint64_t)t[i] + (uint64_t)C;
		S = (uint32_t)sum;
		C = (uint32_t)(sum>>32);
		t[i] = S;
		i++;
	}

}


void subCondMont(uint32_t *u, uint32_t *n, uint32_t SIZE){

	int i;
	uint32_t B;
	uint32_t t[SIZE];

	B = 0;
	for(i = 0; i< SIZE; i++){
			t[i] = 0;
	}
	for(i = 0; i < SIZE; i++){
		uint32_t sub;
		sub = u[i] - n[i] - B;
		if(u[i] >= (n[i] + B)){
			B = 0;
		} else {
			B = 1;

		}
		t[i] = sub;
	}
	if(!B){
		for(i = 0; i<SIZE; i++){
			u[i] = t[i];
		}
	}
	else {
	}
}


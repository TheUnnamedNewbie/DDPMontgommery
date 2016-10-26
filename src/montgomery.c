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




//Declarations


void fips(uint32_t *a, uint32_t *b, uint32_t *n, uint32_t *n0, uint32_t *res, uint32_t SIZE);
void mont(uint32_t *a, uint32_t *b, uint32_t *n, uint32_t *n0, uint32_t *res, uint32_t SIZE);
void addMont(uint32_t *t, uint32_t i, uint32_t C);
void subCondMont(uint32_t *u, uint32_t *n, uint32_t S);
void mont(uint32_t *a, uint32_t *b, uint32_t *n, uint32_t *n0, uint32_t *res, uint32_t SIZE);

void mont(uint32_t *a, uint32_t *b, uint32_t *n, uint32_t *n0, uint32_t *res, uint32_t SIZE){
	//SetLogLevel(INFO);
	fips(a, b, n, n0, res, SIZE);
	SetLogLevelDefault();
}

void fips(uint32_t *a, uint32_t *b, uint32_t *n, uint32_t *n0, uint32_t *res, uint32_t SIZE){



	//	FIPS method
	//  t has 3 elements
	//  m has size + 1



	uint32_t t[3];
	uint32_t m[SIZE+1];
	int i, j;



	// 2: t <- 0
	t[2]=t[1]=t[0]=0;
	// 3: m <- 0
	for(i = 0; i<= SIZE; i++){
			m[i] = 0;
	}


	//while(1!=2){} //WAIT FOR ENTROPY TO DO IT'S THING

	// 4: for 0 <= i < SIZE do

	uint64_t sum;
	uint32_t S, C;

	for(i=0; i< SIZE; i++){


	// 5: for 0 <= j < i do
	// 6: sum <- t[0] + a[j] * b[i-j]
	// 7: C, S <- sum(2w-1...2), sum(w-1...0)
	// 8: ADD(t, 1, C)
	// 9: sum <- S + m[j] * n[i-j]
	// 10: C, S <- sum(2w-1...w), sum(w-1...0)
	// 11: t[0] <- S
	// 12: ADD(t, 1, C)
	// 13: end for



		for(j = 0; j< i; j++){

			sum = (uint64_t)t[0] + (uint64_t)a[j]*(uint64_t)b[i-j];
			S = (uint32_t)sum;
			C = (uint32_t)(sum>>32);
			LogWithNumH(MONTGOMMERY, INFO, "s = ", S);
			LogWithNumH(MONTGOMMERY, INFO, "c = ", C);
			addMont(t, 1, C);
			sum = (uint64_t)S + (uint64_t)m[j]*(uint64_t)n[i-j];
			S = (uint32_t)sum;
			C = (uint32_t)(sum>>32);
			t[0] = S;
			addMont(t, 1, C);
		}

		// 14: sum <- t[0] + a[i]*b[0]

		sum = (uint64_t)t[0] + (uint64_t)a[i]*(uint64_t)b[0];

		// 15: C, S <- sum(2w-1...w), sum(w-1...0)

		S = (uint32_t)sum;
		C = (uint32_t)(sum>>32);

		// 16: ADD(t, 1, C)

		addMont(t, 1, C);

		// 17: m[i] = (S*n0')(w-1..0)

		m[i]= (uint32_t)( n0[0] * S); 		// Because we only need the last 32 bits of n, we can just start of with the last part and ignore the rest (because it will overflow anyways)

		// 18: sum <- S + m[i]*n[0]

		sum = (uint64_t)S + (uint64_t)m[i] * (uint64_t)n[0];

		// 19: C, S <- sum(2w-1...w), sum(w-1...0)

		S = (uint32_t)sum;
		C = (uint32_t)(sum>>32);

		// 20: ADD(t, 1, C)

		addMont(t, 1, C);

		// 21: t[0] <- t[1]
		// 22: t[1] <- t[2]
		// 23: t[2] <- 0

		t[0] = t[1];
		t[1] = t[2];
		t[2] = 0;

		// 24: end for

	}

	// 25: for SIZE <= i < 2*SIZE do

	for(i = SIZE; i < 2*SIZE; i++){  // ASUMING THAT SIZE WILL NEVER BE MORE THAN 31 BITS LONG

		// 26: for i - SIZE + 1 <= j < SIZE do

		for(j = (i - SIZE + 1); j < SIZE; j++){

			// 27: sum <- t[0] + a[j]*b[i-j]

			sum = (uint64_t)t[0] + (uint64_t)a[j]*(uint64_t)b[i-j];

			// 28: C, S <- sum(2w-1...w), sum(w-1...0)

			S = (uint32_t)sum;
			C = (uint32_t)(sum>>32);

			// 29: ADD(t, 1, C)

			addMont(t, 1, C);

			// 30: sum <- S + m[j]*n[i-j]

			sum = (uint64_t)S + (uint64_t)m[j]*(uint64_t)n[i-j];

			// 31: C, S <- sum(2w-1...w), sum(w-1...0)

			S = (uint32_t)sum;
			C = (uint32_t)(sum>>32);

			// 32: t[0] <- S

			t[0] = S;

			// 33: ADD(t, 1, C)

			addMont(t, 1, C);

			// 34: end for

		}

		// 35: m[i - SIZE] <- t[0]

		m[i - SIZE] = t[0];

		// 36: t[0] <- t[1]
		// 37: t[1] <- t[2]
		// 38: t[2] <- 0

		t[0] = t[1];
		t[1] = t[2];
		t[2] = 0;

		// 39: end for

	}

	// 40: m[SIZE] = t[0]

	m[SIZE] = t[0];

	// 41: SUB_COND(m, n, SIZE)

	subCondMont(m, n, SIZE);

	// 42: return m[0], ..., m[SIZE-1]

	for(i = 0; i <SIZE; i++){
		res[i] = m[i];
	}

	//nothing to do here cause pointers

	// 43: end procedure

}


void addMont(uint32_t *t, uint32_t i, uint32_t C){

	uint32_t S;
	uint64_t sum;
	//LogWithNum(MONTGOMMERY, MESSAGE, "addMont C = ", C);

	// 2: while C =/= 0 do

	while(C != 0){

		//LogWithNum(MONTGOMMERY, MESSAGE, "addMont iteration", i);

		// 3: sum <- t[i] + C

		sum = (uint64_t)t[i] + (uint64_t)C;

		// 4: C, S <- sum(2w-1...w), sum(w-1...0)

		S = (uint32_t)sum;
		C = (uint32_t)(sum>>32);

		// 5: t[i] <- S

		t[i] = S;

		// 6: i <- i + 1

		i++;

		// 7: end while
		// 8: return t

	}

}


void subCondMont(uint32_t *u, uint32_t *n, uint32_t SIZE){



	int i;
	uint32_t B;
	uint32_t t[SIZE];



	// 2: B <- 0

	B = 0;

	// 3: t <- 0


	for(i = 0; i< SIZE; i++){
			t[i] = 0;
	}

	// 4: for 0 <=i < SIZE do

	for(i = 0; i < SIZE; i++){

		uint32_t sub;

		// 5: sub <- u[i] - n[i] - B

		sub = u[i] - n[i] - B;

		// 6: if u[i] >= n[i] + B

		if(u[i] >= (n[i] + B)){

			// 7: B <- 0

			B = 0;

			// 8: else

		} else {

			// 9: B <- 1

			B = 1;

		}

		// end if

		// t[i] <- sub

		t[i] = sub;

		// end for

	}

	// if B = 0 then

	if(!B){

		for(i = 0; i<SIZE; i++){
			u[i] = t[i];
		}

	}

	else {

		//return u[0],....,u[SIZE - 1]

	}

}


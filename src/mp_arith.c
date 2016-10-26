/*
 * mp_arith.c
 *
 */


#include <stdint.h>
#include "xil_printf.h"
#include "log.h"






//FUNCTION DECLARATIONS

void mp_add(uint32_t *a, uint32_t *b, uint32_t *res, uint32_t size);
void mp_sub(uint32_t *a, uint32_t *b, uint32_t *res, uint32_t size);
void mod_add(uint32_t *a, uint32_t *b, uint32_t *N, uint32_t *res, uint32_t size);
void mp_mod(uint32_t *res, uint32_t *N, uint32_t size);
void mod_sub(uint32_t *a, uint32_t *b, uint32_t *N, uint32_t *res, uint32_t size);
uint32_t firstNonZero(uint32_t *N, uint32_t size);
void mp_shiftLeft(uint32_t *a, uint32_t size);
uint32_t mp_geq(uint32_t *a, uint32_t *b, uint32_t size);
uint32_t mp_leq(uint32_t *a, uint32_t *b, uint32_t size);


// Calculates res = a + b.
// a and b represent large integers stored in uint32_t arrays
// a and b are arrays of size elements, res has size+1 elements

/* mp_add
 *
 * AUTH JOREN VAES
 * AUTH DANIEL SEMPELS
 * AUTH LENNERT VANMUNSTER
 *
 *
 * Takes two MP numbers a and b stored in arrays of uint32_t and adds them together,
 * the result being stored in res. Size is the length of the arrays a and b. res has a length size+1
 *
 *
 *
 *
 */
void mp_add(uint32_t *a, uint32_t *b, uint32_t *res, uint32_t size)
{
 	uint64_t t, carry;
 	carry = 0;
	int i;
	for(i=0; i<size; i++){
		t = (uint64_t)(*(a+i)) + (uint64_t)(*(b+i)) + carry;
		*(res+i) = (uint32_t)t;
		carry = t>>32;
	}
	*(res+size+1) = (uint32_t)carry;
}




// Calculates res = a - b.
// a and b represent large integers stored in uint32_t arrays
// a, b and res are arrays of size elements


/* mp_sub
 *
 * AUTH JOREN VAES
 * AUTH DANIEL SEMPELS
 * AUTH LENNERT VANMUNSTER
 *
 * Takes two MP format numbers a and b, and subtracts b from a, storing the result in the array res. each has the length size.
 * It is assumed that a > b. Underflow will occur if this is not the case.
 *
 */
void mp_sub(uint32_t *a, uint32_t *b, uint32_t *res, uint32_t size){

	uint64_t carry;
	uint64_t first, second;
	int i;

	if(!(mp_geq(a, b, size))){
		Log(MP_ARITHMATIC, ERROR, "mp_sub: b is greater than a, cannot subtract without underflow occurring. Check calling code.");
	}

	carry = 0;
	first = 0;
	second = 0;


	for(i=0; i<=size; i++){

		first = ((uint64_t)(*(a+i)));
		second = ((uint64_t)(*(b+i))) + carry;
		carry = 0;
		if(first < second){
			carry = 1;
			first = first + (1<<32);
		}

		*(res+i) = (uint32_t)(first - second);

	}

}



// Calculates res = (a + b) mod N.
// a and b represent operands, N is the modulus. They are large integers stored in uint32_t arrays of size elements
void mod_add(uint32_t *a, uint32_t *b, uint32_t *N, uint32_t *res, uint32_t size)
{
	mp_add(a, b, res, size);
	mp_mod(res, N, size);
}



void mp_mod(uint32_t *res, uint32_t *N, uint32_t size){

	while(mp_geq(res, N, size)){
		mp_sub(res, N, res, size);
	}

}


uint32_t firstNonZero(uint32_t *N, uint32_t size){
	uint32_t i;
	for(i = size; (*(N+i))>(uint32_t)0; i--){}
	return i;
}

/*
 *
*/

// Calculates res = (a - b) mod N.
// a and b represent operands, N is the modulus. They are large integers stored in uint32_t arrays of size elements
void mod_sub(uint32_t *a, uint32_t *b, uint32_t *N, uint32_t *res, uint32_t size)
{
	if(!mp_geq(a, b, size)){
		uint32_t temp[size+1];
		mp_add(a, N, temp, size);
		mp_sub(temp, b, res, size);
		mp_mod(res, N, size);
	} else {
		mp_sub(a, b, res, size);
		mp_mod(res, N, size);
	}

}




//returns 1 when a>=b, 0 in all other case

uint32_t mp_geq(uint32_t *a, uint32_t *b, uint32_t size){
	int i;
	for(i = size-1;!(!(i>=1)||((*(a+i)) != (*(b+i)))); i=i-1){}
	return ((*(a+i)) >= (*(b+i)));
}

uint32_t mp_leq(uint32_t *a, uint32_t *b, uint32_t size){
	uint32_t i;
	for(i = size-1;!(!(i>=1)||((*(a+i)) != (*(b+i)))); i=i-1){}
	return ((*(a+i)) <= (*(b+i)));
}




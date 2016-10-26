/*
 * print_mp.c
 *
 *  Created on: Oct 9, 2016
 *      Author: TheUnnamedNewbie
 */
#include <stdint.h>
#include "xil_printf.h"  //Gotta include the original Xilinx print function
#include "log.h"

/* xprintmp
 *
 *
 *
 * AUTH JOREN VAES
 * AUTH DANIEL SEMPELS
 * AUTH LENNERT VANMUNSTER
 *
 * Prints a MP number over the serial port of the system
 *
 * At the moment it always prints them in hex
 * Could edit this later so you can chose other formats as well
 * If we include the posibility of other encodings, it will take some work.
 *
 * Size is the length of the array.
 */


void xprintmp(uint32_t *a, uint32_t size){
	uint32_t i;
	xil_printf("\n\n0x");
	if(*(a+size - 1) != 0){  						//First element may ditch leading zeros
		xil_printf("%x", *(a+size- 1));
	}
	for(i = size-1; i>=1; i--){
		xil_printf("%08x", (*(a+i-1)));		//08x instead of x to force leading zeros.
	}
}


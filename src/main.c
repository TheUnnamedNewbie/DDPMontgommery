/******************************************************************************
*
* Copyright (C) 2009 - 2014 Xilinx, Inc.  All rights reserved.
*
* Permission is hereby granted, free of charge, to any person obtaining a copy
* of this software and associated documentation files (the "Software"), to deal
* in the Software without restriction, including without limitation the rights
* to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
* copies of the Software, and to permit persons to whom the Software is
* furnished to do so, subject to the following conditions:
*
* The above copyright notice and this permission notice shall be included in
* all copies or substantial portions of the Software.
*
* Use of the Software is limited solely to applications:
* (a) running on a Xilinx device, or
* (b) that interact with a Xilinx device through a bus or interconnect.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
* XILINX  BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
* WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF
* OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
* SOFTWARE.
*
* Except as contained in this notice, the name of the Xilinx shall not be used
* in advertising or otherwise to promote the sale, use or other dealings in
* this Software without prior written authorization from Xilinx.
*
******************************************************************************/

/*
 * helloworld.c: simple test application
 *
 * This application configures UART 16550 to baud rate 9600.
 * PS7 UART (Zynq) is not initialized by this application, since
 * bootrom/bsp configures it to baud rate 115200
 *
 * ------------------------------------------------
 * | UART TYPE   BAUD RATE                        |
 * ------------------------------------------------
 *   uartns550   9600
 *   uartlite    Configurable only in HW design
 *   ps7_uart    115200 (configured by bootrom/bsp)
 */

#include <stdio.h>
#include "platform.h"
#include "xil_printf.h"
#include <stdint.h>
#include <inttypes.h>
#include "montgomery.h"
#include "asm_func.h"
#include "mp_arith.h"
#include "mp_print.h"
#include "log.h"
#include "performance_counters.h"
#include "asm_mont_test.h"
#include "mode.h"

#include "test_values.h" //For test values, keeping this code (somewhat) clean.




#define TestSubSystem
//#define TestMultiplier

/*
uint32_t a[32];
uint32_t b[32];
uint32_t N[32];
uint32_t r[33];
uint32_t N_prime0[32];
uint32_t size = 32;
*/

uint32_t SIZE = 32;

int main()
{


    init_platform();
    init_performance_counters(1);



    xil_printf("\r\n\r\n\r\n");

   	Log(MAIN, CRITICAL, "Initializing performance counters" );

	#ifdef TestMultiplier
   		Log(MAIN, CRITICAL, "Testing Full Multiplier");
	#endif

	#ifdef TestSubSystem
   		SetLogLevel(ERROR);
   		Log(MAIN, CRITICAL, "Testing Subsystem!");
	#endif




    //Test mp_arith

/*

    uint32_t start_time = get_cycle_counter();
    mod_sub(test_value_a, test_value_b, test_value_N, r, size);
    uint32_t stop_time = get_cycle_counter();


*/

    //Test montgommery
	#ifdef TestMultiplier

   	    uint32_t result[SIZE+1];

		uint32_t start_time_1 = get_cycle_counter();
		mont(test_mont_a1, test_mont_b1, test_mont_N1, test_mont_n_prime1, result, SIZE);
		uint32_t stop_time_1 = get_cycle_counter();

		if(mp_eq(result, test_mont_mult_result1, SIZE-1)){
			Log(MAIN, DEBUG, "First test successful");
		} else {
			Log(MAIN, CRITICAL, "First test failed");
			xprintmp(result, SIZE);
		}


		uint32_t start_time_2 = get_cycle_counter();
		mont(test_mont_a2, test_mont_b2, test_mont_N2, test_mont_n_prime2, result, SIZE);
		uint32_t stop_time_2 = get_cycle_counter();

		if(mp_eq(result, test_mont_mult_result2, SIZE-1)){
				Log(MAIN, DEBUG, "Second test successful");
		} else {
			Log(MAIN, CRITICAL, "Second test failed");
			xprintmp(result, SIZE);
		}


		uint32_t start_time_3 = get_cycle_counter();
		mont(test_mont_a3, test_mont_b3, test_mont_N3, test_mont_n_prime3, result, SIZE);
		uint32_t stop_time_3 = get_cycle_counter();

		if(mp_eq(result, test_mont_mult_result3, SIZE-1)){
			Log(MAIN, DEBUG, "Third test successful");
		} else {
			Log(MAIN, CRITICAL, "Third test failed");
			xprintmp(result, SIZE);
		}

	    uint32_t totalCycles = ((stop_time_1 - start_time_1) + (stop_time_2 - start_time_2) + (stop_time_3 - start_time_3))/3;
	    LogWithNum(PERFORMANCE, DEBUG, "Cyclecount = ", totalCycles);
	#endif



	#ifdef TestSubSystem
	    //Test subsystem
	    uint32_t hasError = 0;
	    uint32_t t[3], i;
	    t[2]=t[1]=t[0]=0;
	    for(i = 0; i<SIZE; i++){
	    	    	int succes = test_montSum(test_value_a[i], test_value_b[i], t);
	    	    	LogWithNum(ASMMONTGOMERY, CRITICAL, "Starting test number ", i);
	    	    	if(succes){LogWithNum(ASMMONTGOMERY, CRITICAL, "test_montSum successful: ", succes);}
	    	    	else {LogWithNum(ASMMONTGOMERY, CRITICAL, "test_montSum failed: ", succes); hasError ++;}
	    }
	    LogWithNum(ASMMONTGOMERY, CRITICAL, "test_montSum finished with the the following errorcount: ", hasError);

	#endif


    Log(MAIN, CRITICAL, "Program Finished. Cleaning up platform and terminating...");


    cleanup_platform();
    return 0;
}

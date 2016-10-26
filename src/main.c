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


#include "test_values.h" //For test values, keeping this code (somewhat) clean.




uint32_t a[32];
uint32_t b[32];
uint32_t N[32];
uint32_t r[33];
uint32_t N_prime0[32];
uint32_t size = 32;


int main()
{


    init_platform();
    init_performance_counters(1);

    uint32_t SIZE = 32;
    uint32_t result[SIZE+1];
    xil_printf("\r\n\r\n\r\n");
    Log(MAIN, CRITICAL, "Initializing performance counters" );
    Log(MAIN, CRITICAL, "version 1512");

    //Test mp_arith

/*

    uint32_t start_time = get_cycle_counter();
    mod_sub(test_value_a, test_value_b, test_value_N, r, size);
    uint32_t stop_time = get_cycle_counter();


*/

    //Test montgommery

    uint32_t start_time = get_cycle_counter();
    mont(test_mont_a, test_mont_b, test_mont_N, test_mont_n_prime, result, SIZE);
    uint32_t stop_time = get_cycle_counter();



    xprintmp(result, SIZE);
    //LogWithNum(MAIN, ERROR, "MSB RES = ", result[SIZE]);


    uint32_t totalCycles = stop_time - start_time;
    LogWithNum(PERFORMANCE, DEBUG, "Cyclecount = ", totalCycles);
    Log(MAIN, CRITICAL, "version 1512");
    Log(MAIN, CRITICAL, "Program Finished. Cleaning up platform and terminating...");


    cleanup_platform();
    return 0;
}

/*
 * asm_mont.h
 *
 *  Created on: Oct 26, 2016
 *      Author: TheUnnamedNewbie
 */



#ifndef DDPMONTGOMMERY_SRC_ASM_MONT_H_
#define DDPMONTGOMMERY_SRC_ASM_MONT_H_


#include <stdint.h>

void montSum(uint32_t a, uint32_t b, uint32_t m, uint32_t n, uint32_t *t);
void montSum2(uint32_t a, uint32_t b, uint32_t m, uint32_t n, uint32_t *t, uint32_t *f, uint32_t i, uint32_t n0);
//r0 = a
//r1 = b
//r2 = m
//r3 = n
//SP+4 = *t
//i should already be multiplied by 4 -> bitshift 2



#endif /* DDPMONTGOMMERY_SRC_ASM_MONT_H_ */


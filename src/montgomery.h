/*
 * montgomery.h
 *
 */

#ifndef MONTOGOMERY_H_
#define MONTOGOMERY_H_
#include <stdint.h>
#include "mode.h"
#ifdef DebugOnMontgomery
	void addMont(uint32_t *t, uint32_t i, uint32_t C);
	void subCondMont(uint32_t *u, uint32_t *n, uint32_t SIZE);
	void fips(uint32_t *a, uint32_t *b, uint32_t *n, uint32_t *n0, uint32_t *res, uint32_t SIZE);
#endif

void mont(uint32_t *a, uint32_t *b, uint32_t *n, uint32_t *n0, uint32_t *res, uint32_t SIZE);


#endif /* MONTOGOMERY_H_ */

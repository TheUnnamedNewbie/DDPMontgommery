.text

.global montSum
.func montSum, montSum
.type montSum, %function

montSum:
PUSH {r4-r9} 		@6 regs makes for t to be at SP+24
LDR r6, [sp, #24]	@load *t

@r6 contains the pointer to t
LDR r7, [r6], #4   	@r3 = t[0]
LDR r8, [r6], #4	@r4 = t[1]
LDR r9, [r6]		@r5 = t[2]

MOV r4, r7
MOV r5, #0			@C = 0

UMLAL r4, r5, r0, r1 	@sum = t[0] + a*b
ADDS r8, r8, r5			@addmont
ADC r9, r9, #0			@addmont

MOV r5, #0			@C = 0

UMLAL r4, r5, r2, r3
ADDS r8, r8, r5
ADC r9, r9, #0

MOV r7, r4

STR r9, [r6], #-4
STR r8, [r6], #-4
STR r7, [r6]

POP {r4-r9}
BX lr
.endfunc
.text

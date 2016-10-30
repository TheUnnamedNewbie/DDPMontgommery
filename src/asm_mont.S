.text

.global montSum
.func montSum, montSum
.type montSum, %function

montSum:
PUSH {r4-r7}
LDR r3, [r2], #4   	@r3 = t[0]
LDR r4, [r2], #4	@r4 = t[1]
LDR r5, [r2]		@r5 = t[2]

MOV r6, r3			@S = t[0]
MOV r7, #0

UMLAL r6, r7, r0, r1 	@sum = t[0] + a*b
ADDS r4, r4, r7			@addmont
ADC r5, r5, #0			@addmont

MOV r3, r6

STR r5, [r2], #-4
STR r4, [r2], #-4
STR r3, [r2]

POP {r4-r7}
BX lr
.endfunc
.text

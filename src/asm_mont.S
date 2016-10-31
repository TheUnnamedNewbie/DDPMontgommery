.text

.global montSum
.func montSum, montSum
.type montSum, %function

montSum:
PUSH {r4-r9} 		@6 regs makes for t to be at SP+24
LDR r6, [sp, #24]	@load *t

@r6 contains the pointer to t
LDR r4, [r6], #4   	@r3 = t[0]
LDR r8, [r6], #4	@r4 = t[1]
LDR r9, [r6]		@r5 = t[2]

@MOV r4, r7
MOV r5, #0			@C = 0

UMLAL r4, r5, r0, r1 	@sum = t[0] + a*b
ADDS r8, r8, r5			@addmont
ADC r9, r9, #0			@addmont

MOV r5, #0			@C = 0

UMLAL r4, r5, r2, r3
ADDS r8, r8, r5
ADC r9, r9, #0

@MOV r7, r4

STR r9, [r6], #-4
STR r8, [r6], #-4
STR r4, [r6]

POP {r4-r9}
BX lr
.endfunc
.text

.global montSum2
.func montSum2, montSum2
.type montSum2, %function

montSum2:
PUSH {r4-r12} 		@7 regs makes for t to be at SP+28
LDR r6, [sp, #36]	@load *t
LDR r10, [sp, #40]	@load *m
LDR r11, [sp, #44]	@load i
LDR r12, [sp, #48] @load n0



@r6 contains the pointer to t
LDR r4, [r6], #4   	@r3 = t[0]
LDR r8, [r6], #4	@r4 = t[1]
LDR r9, [r6]		@r5 = t[2]

@MOV r4, r7
MOV r5, #0			@C = 0

UMLAL r4, r5, r0, r1 	@sum = t[0] + a*b
ADDS r8, r8, r5			@addmont
ADC r9, r9, #0			@addmont

MUL r2, r12, r4

STR r2, [r10, r11, LSL #2]

MOV r5, #0			@C = 0

UMLAL r4, r5, r2, r3
ADDS r8, r8, r5
ADC r9, r9, #0

MOV r4, #0

STR r4, [r6], #-4
STR r9, [r6], #-4
STR r8, [r6]

POP {r4-r12}
BX lr
.endfunc
.text

.global montSumLoop
.func montSumLoop, montSumLoop
.type montSumLoop, %function

montSumLoop:
PUSH {r4-r12} 		@6 regs makes for t to be at SP+24

LDR r10, [sp, #40] 	@load i
CMP r10, #0
BEQ endMont1
LDR r5, [sp, #36]	@load *t

@r6 contains the pointer to t
LDR r4, [r5], #4   	@r4 = t[0]
LDR r6, [r5], #4	@r6 = t[1]
LDR r7, [r5]		@r7 = t[2]

MOV r11, #0	@r6 is now j


loop:
SUB r12, r10, r11	@store i-j in r12
MOV r5, #0			@C = 0

LDR r8, [r0, r11, LSL #2]	@load a[j]
LDR r9, [r1, r12, LSL #2]	@load b[i-j]

UMLAL r4, r5, r8, r9 	@sum = t[0] + a*b
ADDS r6, r6, r5			@addmont
ADC r7, r7, #0			@addmont

MOV r5, #0			@C = 0

LDR r8, [r2, r11, LSL #2]	@load a[j]
LDR r9, [r3, r12, LSL #2]	@load b[i-j]

UMLAL r4, r5, r8, r9 	@sum = t[0] + a*b
ADDS r6, r6, r5			@addmont
ADC r7, r7, #0			@addmont

ADD r11, #1
CMP r10, r11
BGT loop

LDR r5, [sp, #36]	@load *t

STR r4, [r5], #4
STR r6, [r5], #4
STR r7, [r5]

@MOV r0, r10
@MOV r1, r11
endMont1:
POP {r4-r12}
BX lr
.endfunc
.text

.global montSumLoopSize
.func montSumLoopSize, montSumLoopSize
.type montSumLoopSize, %function

montSumLoopSize:
PUSH {r4-r12} 		@6 regs makes for t to be at SP+24

LDR r10, [sp, #40] 	@load i
CMP r10, #0
BEQ endMont1
LDR r5, [sp, #36]	@load *t

@r6 contains the pointer to t
LDR r4, [r5], #4   	@r4 = t[0]
LDR r6, [r5], #4	@r6 = t[1]
LDR r7, [r5]		@r7 = t[2]

LDR r11, [sp, #44]	@r6 is now j


loop2:
SUB r12, r10, r11	@store i-j in r12
MOV r5, #0			@C = 0

LDR r8, [r0, r11, LSL #2]	@load a[j]
LDR r9, [r1, r12, LSL #2]	@load b[i-j]

UMLAL r4, r5, r8, r9 	@sum = t[0] + a*b
ADDS r6, r6, r5			@addmont
ADC r7, r7, #0			@addmont

MOV r5, #0			@C = 0

LDR r8, [r2, r11, LSL #2]	@load a[j]
LDR r9, [r3, r12, LSL #2]	@load b[i-j]

UMLAL r4, r5, r8, r9 	@sum = t[0] + a*b
ADDS r6, r6, r5			@addmont
ADC r7, r7, #0			@addmont

ADD r11, #1
CMP r11, #32
BLO loop2

LDR r5, [sp, #36]	@load *t

STR r4, [r5], #4
STR r6, [r5], #4
STR r7, [r5]

@MOV r0, r10
@MOV r1, r11
endMont2:
POP {r4-r12}
BX lr
.endfunc
.text

.global montSumComplete
.func montSumComplete, montSumComplete
.type montSumComplete, %function
@void montSumComplete(uint32_t *a, uint32_t *b, uint32_t *m, uint32_t *n, uint32_t *t, uint32_t n0);
@r0 = *a
@r1 = *b
@r2 = *m
@r3 = *n
@SP = *t
@SP+4 = n0
montSumComplete:
PUSH {r4-r12} 				@9 regs makes for t to be at SP+32


@LDR r5, [sp, #36]	@load *t
@r6 contains the pointer to t
@LDR r4, [r5], #4   	@r4 = t[0]
@LDR r6, [r5], #4	@r6 = t[1]
@LDR r7, [r5]		@r7 = t[2]

MOV r4, #0				@t0 = 0
MOV r6, #0					@t1 = 0
MOV r7, #0					@t2 = 0

MOV r10, #0				@r10 is i = 0
MOV r11, #0				@r6 is j = 0
B montSum3				@first time it should skip the first loop

loopComplete1:
SUB r12, r10, r11			@store i-j in r12

MOV r5, #0					@C = 0

LDR r8, [r0, r11, LSL #2]	@load a[j]		LSL for mapping to 4 byte words
LDR r9, [r1, r12, LSL #2]	@load b[i-j]		LSL for mapping to 4 byte words

UMLAL r4, r5, r8, r9 		@sum = t[0] + a*b
ADDS r6, r6, r5			@addmont
ADC r7, r7, #0				@addmont

MOV r5, #0					@C = 0

LDR r8, [r2, r11, LSL #2]	@load r8 with m[j]
LDR r9, [r3, r12, LSL #2]	@load r9 with n[i-j]

UMLAL r4, r5, r8, r9 		@sum = t[0] + m[j]*n[i-j]
ADDS r6, r6, r5			@addmont
ADC r7, r7, #0				@addmont

ADD r11, #1					@increment j by one
CMP r10, r11				@compare i with j
BGT loopComplete1			@if i > j do the loop again

montSum3:

LDR r8, [r0, r10, LSL #2]	@load a[i]
LDR r9, [r1]					@load b[0]
MOV r5, #0					@C = 0

UMLAL r4, r5, r8, r9 		@sum = t[0] + a[i]*b[0]
ADDS r6, r6, r5			@addmont
ADC r7, r7, #0				@addmont

LDR r9, [sp, #40]			@load n0
MUL r8, r9, r4				@m[i]=n0*S
STR r8, [r2, r10, LSL #2]	@store m[i]
LDR r9, [r3]				@Load n[0]
MOV r5, #0					@C = 0
UMLAL r4, r5, r8, r9 		@sum = t[0] + m[i] * n[0]
ADDS r6, r6, r5			@addmont
ADC r7, r7, #0				@addmont

MOV r4, r6					@t[0] = t[1]
MOV r6, r7					@t[1] = t[2]
MOV r7, #0					@t[2] = 0


ADD r10, #1 				@i++
CMP r10, #32				@i<SIZE
MOV r11, #0				@j=0
BLO loopComplete1


LDR r5, [sp, #36]			@load *t  FIX THE STACKPOINTER
STR r4, [r5], #4
STR r6, [r5], #4
STR r7, [r5]
MOV r5, #0
STR r5, [r2, #128]	@store m[i]
STR r5, [r2, #132]


POP {r4-r12}
BX lr
.endfunc
.text







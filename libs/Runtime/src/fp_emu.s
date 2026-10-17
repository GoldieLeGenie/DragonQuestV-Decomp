; Hand-written Metrowerks runtime routines. Branches retain symbolic targets.
.text
.arm
.global _dadd
.type _dadd, @function
.global _ll_ufrom_d
.type _ll_ufrom_d, @function
.global _dmul
.type _dmul, @function
.global _dsub
.type _dsub, @function
.global _fadd
.type _fadd, @function
.global func_0200523c
.type func_0200523c, @function
.global _dls
.type _dls, @function
.global _deq
.type _deq, @function
.global _fgr
.type _fgr, @function
.global _fls
.type _fls, @function
.global _fdiv
.type _fdiv, @function
.global _f2d
.type _f2d, @function
.global _ffix
.type _ffix, @function
.global _ffixu
.type _ffixu, @function
.global _fflt
.type _fflt, @function
.global _fmul
.type _fmul, @function
.global _fsub
.type _fsub, @function
.global func_02004c54
.type func_02004c54, @function
.global func_02005424
.type func_02005424, @function
.global func_02005b08
.type func_02005b08, @function
_dadd:
    stmfd sp!, {r4, lr}
    eors r12, r1, r3
    eormi r3, r3, #0x80000000
    bmi .L_shared_02004c7c
.L_shared_0200455c:
    subs r12, r0, r2
    sbcs lr, r1, r3
    bhs L_2004578
    adds r2, r2, r12
    adc r3, r3, lr
    subs r0, r0, r12
    sbc r1, r1, lr
L_2004578:
    mov lr, #0x80000000
    mov r12, r1, lsr #0x14
    orr r1, lr, r1, lsl #11
    orr r1, r1, r0, lsr #21
    mov r0, r0, lsl #0xb
    movs r4, r12, lsl #0x15
    cmnne r4, #0x200000
    beq L_2004674
    mov r4, r3, lsr #0x14
    orr r3, lr, r3, lsl #11
    orr r3, r3, r2, lsr #21
    mov r2, r2, lsl #0xb
    movs lr, r4, lsl #0x15
    beq L_20046bc
L_20045b0:
    subs r4, r12, r4
    beq L_2004608
    cmp r4, #0x20
    ble L_20045ec
    cmp r4, #0x38
    movge r4, #0x3f
    sub r4, r4, #0x20
    rsb lr, r4, #0x20
    orrs lr, r2, r3, lsl lr
    mov r2, r3, lsr r4
    orrne r2, r2, #1
    adds r0, r0, r2
    adcs r1, r1, #0
    blo L_2004630
    b L_2004614
L_20045ec:
    rsb lr, r4, #0x20
    movs lr, r2, lsl lr
    rsb lr, r4, #0x20
    mov r2, r2, lsr r4
    orr r2, r2, r3, lsl lr
    mov r3, r3, lsr r4
    orrne r2, r2, #1
L_2004608:
    adds r0, r0, r2
    adcs r1, r1, r3
    blo L_2004630
L_2004614:
    add r12, r12, #1
    and r4, r0, #1
    movs r1, r1, rrx
    orr r0, r4, r0, rrx
    mov lr, r12, lsl #0x15
    cmn lr, #0x200000
    beq L_2004840
L_2004630:
    movs r2, r0, lsl #0x15
    mov r0, r0, lsr #0xb
    orr r0, r0, r1, lsl #21
    add r1, r1, r1
    mov r1, r1, lsr #0xc
    orr r1, r1, r12, lsl #20
    tst r2, #0x80000000
    ldmeqfd sp!, {r4, lr}
    bxeq lr
    movs r2, r2, lsl #1
    andeqs r2, r0, #1
    ldmeqfd sp!, {r4, lr}
    bxeq lr
    adds r0, r0, #1
    adc r1, r1, #0
    ldmfd sp!, {r4, lr}
    bx lr
L_2004674:
    cmp r12, #0x800
    movge lr, #0x80000000
    movlt lr, #0
    bics r12, r12, #0x800
    beq L_20046e0
    orrs r4, r0, r1, lsl #1
    bne L_200481c
    mov r4, r3, lsr #0x14
    mov r3, r3, lsl #0xb
    orr r3, r3, r2, lsr #21
    mov r2, r2, lsl #0xb
    movs r4, r4, lsl #0x15
    beq L_2004808
    cmn r4, #0x200000
    bne L_2004808
    orrs r4, r2, r3, lsl #1
    beq L_2004808
    b L_200481c
L_20046bc:
    cmp r4, #0x800
    movge lr, #0x80000000
    movlt lr, #0
    bic r12, r12, #0x800
    bics r4, r4, #0x800
    beq L_200474c
    orrs r4, r2, r3, lsl #1
    bne L_200481c
    b L_2004808
L_20046e0:
    orrs r4, r0, r1, lsl #1
    beq L_2004720
    mov r12, #1
    bic r1, r1, #0x80000000
    mov r4, r3, lsr #0x14
    mov r3, r3, lsl #0xb
    orr r3, r3, r2, lsr #21
    mov r2, r2, lsl #0xb
    movs r4, r4, lsl #0x15
    cmnne r4, #0x200000
    mov r4, r4, lsr #0x15
    orr r4, r4, lr, lsr #20
    beq L_20046bc
    orr r3, r3, #0x80000000
    orr r12, r12, lr, lsr #20
    b L_20045b0
L_2004720:
    mov r12, r3, lsr #0x14
    mov r1, r3, lsl #0xb
    orr r1, r1, r2, lsr #21
    mov r0, r2, lsl #0xb
    movs r4, r12, lsl #0x15
    beq L_20047d4
    cmn r4, #0x200000
    bne L_20047d4
    orrs r4, r0, r1, lsl #1
    beq L_2004808
    b L_2004820
L_200474c:
    orrs r4, r2, r3, lsl #1
    beq L_20047e4
    mov r4, #1
    bic r3, r3, #0x80000000
    cmp r1, #0
    bpl L_2004770
    orr r12, r12, lr, lsr #20
    orr r4, r4, lr, lsr #20
    b L_20045b0
L_2004770:
    adds r0, r0, r2
    adcs r1, r1, r3
    blo L_2004790
    add r12, r12, #1
    and r4, r0, #1
    movs r1, r1, rrx
    mov r0, r0, rrx
    orr r0, r0, r4
L_2004790:
    cmp r1, #0
    subges r12, r12, #1
    movs r2, r0, lsl #0x15
    mov r0, r0, lsr #0xb
    orr r0, r0, r1, lsl #21
    add r1, r1, r1
    orr r1, lr, r1, lsr #12
    orr r1, r1, r12, lsl #20
    ldmeqfd sp!, {r4, lr}
    bxeq lr
    tst r2, #0x80000000
    ldmeqfd sp!, {r4, lr}
    bxeq lr
    movs r2, r2, lsl #1
    andeqs r2, r0, #1
    ldmeqfd sp!, {r4, lr}
    bxeq lr
L_20047d4:
    mov r1, r3
    mov r0, r2
    ldmfd sp!, {r4, lr}
    bx lr
L_20047e4:
    cmp r1, #0
    subges r12, r12, #1
    mov r0, r0, lsr #0xb
    orr r0, r0, r1, lsl #21
    add r1, r1, r1
    orr r1, lr, r1, lsr #12
    orr r1, r1, r12, lsl #20
    ldmfd sp!, {r4, lr}
    bx lr
L_2004808:
    ldr r1, [pc, #0x50]
    orr r1, lr, r1
    mov r0, #0
    ldmfd sp!, {r4, lr}
    bx lr
L_200481c:
    mov r1, r3
L_2004820:
    mvn r0, #0
    bic r1, r0, #0x80000000
    ldmfd sp!, {r4, lr}
    bx lr
    mvn r0, #0
    bic r1, r0, #0x80000000
    ldmfd sp!, {r4, lr}
    bx lr
L_2004840:
    cmp r12, #0x800
    movge lr, #0x80000000
    movlt lr, #0
    ldr r1, [pc, #0xc]
    orr r1, lr, r1
    mov r0, #0
    ldmfd sp!, {r4, lr}
    bx lr
    .word 0x7ff00000
_ll_ufrom_d:
    tst r1, #0x80000000
    bne L_20048c8
    ldr r2, [pc, #0x78]
    subs r2, r2, r1, lsr #20
    blt L_20048e0
    cmp r2, #0x40
    bge L_20048bc
    mov r12, r1, lsl #0xb
    orr r12, r12, #0x80000000
    orr r12, r12, r0, lsr #21
    cmp r2, #0x20
    ble L_20048a4
    sub r2, r2, #0x20
    mov r1, #0
    mov r0, r12, lsr r2
    bx lr
L_20048a4:
    mov r3, r0, lsl #0xb
    mov r1, r12, lsr r2
    mov r0, r3, lsr r2
    rsb r2, r2, #0x20
    orr r0, r0, r12, lsl r2
    bx lr
L_20048bc:
    mov r1, #0
    mov r0, #0
    bx lr
L_20048c8:
    cmn r1, #0x100000
    cmpeq r0, #0
    bhi L_20048e0
    mov r1, #0
    mov r0, #0
    bx lr
L_20048e0:
    mvn r1, #0
    mvn r0, #0
    bx lr
    .word 0x0000043e
_dmul:
    stmfd sp!, {r4, r5, r6, r7, lr}
    eor lr, r1, r3
    and lr, lr, #0x80000000
    mov r12, r1, lsr #0x14
    mov r1, r1, lsl #0xb
    orr r1, r1, r0, lsr #21
    mov r0, r0, lsl #0xb
    movs r6, r12, lsl #0x15
    cmnne r6, #0x200000
    beq L_20049f8
    orr r1, r1, #0x80000000
    bic r12, r12, #0x800
    mov r4, r3, lsr #0x14
    mov r3, r3, lsl #0xb
    orr r3, r3, r2, lsr #21
    mov r2, r2, lsl #0xb
    movs r5, r4, lsl #0x15
    cmnne r5, #0x200000
    beq L_2004a40
    orr r3, r3, #0x80000000
    bic r4, r4, #0x800
L_2004944:
    add r12, r4, r12
    umull r5, r4, r0, r2
    umull r7, r6, r0, r3
    adds r4, r7, r4
    adc r6, r6, #0
    umull r7, r0, r1, r2
    adds r4, r7, r4
    adcs r0, r0, r6
    umull r7, r2, r1, r3
    adc r1, r2, #0
    adds r0, r0, r7
    adc r1, r1, #0
    orrs r4, r4, r5
    orrne r0, r0, #1
    cmp r1, #0
    blt L_2004990
    sub r12, r12, #1
    adds r0, r0, r0
    adc r1, r1, r1
L_2004990:
    add r12, r12, #2
    subs r12, r12, #0x400
    bmi L_2004b2c
    beq L_2004b2c
    mov r6, r12, lsl #0x14
    cmn r6, #0x100000
    bmi L_2004c2c
    movs r2, r0, lsl #0x15
    mov r0, r0, lsr #0xb
    orr r0, r0, r1, lsl #21
    add r1, r1, r1
    orr r1, lr, r1, lsr #12
    orr r1, r1, r12, lsl #20
    ldmeqfd sp!, {r4, r5, r6, r7, lr}
    bxeq lr
    tst r2, #0x80000000
    ldmeqfd sp!, {r4, r5, r6, r7, lr}
    bxeq lr
    movs r2, r2, lsl #1
    andeqs r2, r0, #1
    ldmeqfd sp!, {r4, r5, r6, r7, lr}
    bxeq lr
    adds r0, r0, #1
    adc r1, r1, #0
    ldmfd sp!, {r4, r5, r6, r7, lr}
    bx lr
L_20049f8:
    bics r12, r12, #0x800
    beq L_2004a54
    orrs r6, r0, r1, lsl #1
    bne L_2004be0
    mov r4, r3, lsr #0x14
    mov r3, r3, lsl #0xb
    orr r3, r3, r2, lsr #21
    mov r2, r2, lsl #0xb
    movs r5, r4, lsl #0x15
    beq L_2004a34
    cmn r5, #0x200000
    bne L_2004bcc
    orrs r5, r2, r3, lsl #1
    beq L_2004bcc
    b L_2004be0
L_2004a34:
    orrs r5, r3, r2
    beq L_2004bf4
    b L_2004bcc
L_2004a40:
    bics r4, r4, #0x800
    beq L_2004ae8
    orrs r6, r2, r3, lsl #1
    bne L_2004be0
    b L_2004bcc
L_2004a54:
    orrs r6, r0, r1, lsl #1
    beq L_2004abc
    mov r12, #1
    cmp r1, #0
    bne L_2004a78
    sub r12, r12, #0x20
    movs r1, r0
    mov r0, #0
    bmi L_2004a94
L_2004a78:
    clz r6, r1
    movs r1, r1, lsl r6
    rsb r6, r6, #0x20
    orr r1, r1, r0, lsr r6
    rsb r6, r6, #0x20
    mov r0, r0, lsl r6
    sub r12, r12, r6
L_2004a94:
    mov r4, r3, lsr #0x14
    mov r3, r3, lsl #0xb
    orr r3, r3, r2, lsr #21
    mov r2, r2, lsl #0xb
    movs r5, r4, lsl #0x15
    cmnne r5, #0x200000
    beq L_2004a40
    orr r3, r3, #0x80000000
    bic r4, r4, #0x800
    b L_2004944
L_2004abc:
    mov r4, r3, lsr #0x14
    mov r3, r3, lsl #0xb
    orr r3, r3, r2, lsr #21
    mov r2, r2, lsl #0xb
    movs r5, r4, lsl #0x15
    beq L_2004c40
    cmn r5, #0x200000
    bne L_2004c40
    orrs r6, r2, r3, lsl #1
    beq L_2004bf4
    b L_2004be0
L_2004ae8:
    orrs r5, r2, r3, lsl #1
    beq L_2004c40
    mov r4, #1
    cmp r3, #0
    bne L_2004b0c
    sub r4, r4, #0x20
    movs r3, r2
    mov r2, #0
    bmi L_2004944
L_2004b0c:
    clz r6, r3
    movs r3, r3, lsl r6
    rsb r6, r6, #0x20
    orr r3, r3, r2, lsr r6
    rsb r6, r6, #0x20
    mov r2, r2, lsl r6
    sub r4, r4, r6
    b L_2004944
L_2004b2c:
    cmn r12, #0x34
    beq L_2004bc4
    bmi L_2004c1c
    mov r2, r1
    mov r3, r0
    add r4, r12, #0x34
    cmp r4, #0x20
    movge r2, r3
    movge r3, #0
    subge r4, r4, #0x20
    rsb r5, r4, #0x20
    mov r2, r2, lsl r4
    orr r2, r2, r3, lsr r5
    movs r3, r3, lsl r4
    orrne r2, r2, #1
    rsb r12, r12, #0xc
    cmp r12, #0x20
    movge r0, r1
    movge r1, #0
    subge r12, r12, #0x20
    rsb r4, r12, #0x20
    mov r0, r0, lsr r12
    orr r0, r0, r1, lsl r4
    orr r1, lr, r1, lsr r12
    cmp r2, #0
    ldmeqfd sp!, {r4, r5, r6, r7, lr}
    bxeq lr
    tst r2, #0x80000000
    ldmeqfd sp!, {r4, r5, r6, r7, lr}
    bxeq lr
    movs r2, r2, lsl #1
    andeqs r2, r0, #1
    ldmeqfd sp!, {r4, r5, r6, r7, lr}
    bxeq lr
    adds r0, r0, #1
    adc r1, r1, #0
    ldmfd sp!, {r4, r5, r6, r7, lr}
    bx lr
L_2004bc4:
    orr r0, r0, r1, lsl #1
    b L_2004c04
L_2004bcc:
    ldr r1, [pc, #0x7c]
    orr r1, lr, r1
    mov r0, #0
    ldmfd sp!, {r4, r5, r6, r7, lr}
    bx lr
L_2004be0:
    mov r1, r3
    mvn r0, #0
    bic r1, r0, #0x80000000
    ldmfd sp!, {r4, r5, r6, r7, lr}
    bx lr
L_2004bf4:
    mvn r0, #0
    bic r1, r0, #0x80000000
    ldmfd sp!, {r4, r5, r6, r7, lr}
    bx lr
L_2004c04:
    movs r2, r0
    mov r1, lr
    mov r0, #0
    addne r0, r0, #1
    ldmfd sp!, {r4, r5, r6, r7, lr}
    bx lr
L_2004c1c:
    mov r1, lr
    mov r0, #0
    ldmfd sp!, {r4, r5, r6, r7, lr}
    bx lr
L_2004c2c:
    ldr r1, [pc, #0x1c]
    orr r1, lr, r1
    mov r0, #0
    ldmfd sp!, {r4, r5, r6, r7, lr}
    bx lr
L_2004c40:
    mov r1, lr
    mov r0, #0
    ldmfd sp!, {r4, r5, r6, r7, lr}
    bx lr
    .word 0x7ff00000
func_02004c54:
    eor r1, r1, r3
    eor r3, r1, r3
    eor r1, r1, r3
    eor r0, r0, r2
    eor r2, r0, r2
    eor r0, r0, r2
_dsub:
    stmfd sp!, {r4, lr}
    eors r12, r1, r3
    eormi r3, r3, #0x80000000
    bmi .L_shared_0200455c
.L_shared_02004c7c:
    subs r12, r0, r2
    sbcs lr, r1, r3
    bhs L_2004c9c
    eor lr, lr, #0x80000000
    adds r2, r2, r12
    adc r3, r3, lr
    subs r0, r0, r12
    sbc r1, r1, lr
L_2004c9c:
    mov lr, #0x80000000
    mov r12, r1, lsr #0x14
    orr r1, lr, r1, lsl #11
    orr r1, r1, r0, lsr #21
    mov r0, r0, lsl #0xb
    movs r4, r12, lsl #0x15
    cmnne r4, #0x200000
    beq L_2004ea0
    mov r4, r3, lsr #0x14
    orr r3, lr, r3, lsl #11
    orr r3, r3, r2, lsr #21
    mov r2, r2, lsl #0xb
    movs lr, r4, lsl #0x15
    beq L_2004ee8
L_2004cd4:
    subs r4, r12, r4
    beq L_2004d7c
    cmp r4, #0x20
    ble L_2004d10
    cmp r4, #0x38
    movge r4, #0x3f
    sub r4, r4, #0x20
    rsb lr, r4, #0x20
    orrs lr, r2, r3, lsl lr
    mov r2, r3, lsr r4
    orrne r2, r2, #1
    subs r0, r0, r2
    sbcs r1, r1, #0
    bmi L_2004d38
    b L_2004e28
L_2004d10:
    rsb lr, r4, #0x20
    movs lr, r2, lsl lr
    rsb lr, r4, #0x20
    mov r2, r2, lsr r4
    orr r2, r2, r3, lsl lr
    mov r3, r3, lsr r4
    orrne r2, r2, #1
    subs r0, r0, r2
    sbcs r1, r1, r3
    bpl L_2004e28
L_2004d38:
    movs r2, r0, lsl #0x15
    mov r0, r0, lsr #0xb
    orr r0, r0, r1, lsl #21
    add r1, r1, r1
    mov r1, r1, lsr #0xc
    orr r1, r1, r12, lsl #20
    tst r2, #0x80000000
    ldmeqfd sp!, {r4, lr}
    bxeq lr
    movs r2, r2, lsl #1
    andeqs r2, r0, #1
    ldmeqfd sp!, {r4, lr}
    bxeq lr
    adds r0, r0, #1
    adc r1, r1, #0
    ldmfd sp!, {r4, lr}
    bx lr
L_2004d7c:
    subs r0, r0, r2
    sbc r1, r1, r3
    orrs lr, r1, r0
    beq L_200500c
    mov lr, r12, lsl #0x14
    and lr, lr, #0x80000000
    bic r12, r12, #0x800
    cmp r1, #0
    bmi L_2004e04
    bne L_2004db4
    sub r12, r12, #0x20
    movs r1, r0
    mov r0, #0
    bmi L_2004dd0
L_2004db4:
    clz r4, r1
    movs r1, r1, lsl r4
    rsb r4, r4, #0x20
    orr r1, r1, r0, lsr r4
    rsb r4, r4, #0x20
    mov r0, r0, lsl r4
    sub r12, r12, r4
L_2004dd0:
    cmp r12, #0
    bgt L_2004e0c
    rsb r12, r12, #0xc
    cmp r12, #0x20
    movge r0, r1
    movge r1, #0
    subge r12, r12, #0x20
    rsb r4, r12, #0x20
    mov r0, r0, lsr r12
    orr r0, r0, r1, lsl r4
    orr r1, lr, r1, lsr r12
    ldmfd sp!, {r4, lr}
    bx lr
L_2004e04:
    cmp r1, #0
    subges r12, r12, #1
L_2004e0c:
    mov r0, r0, lsr #0xb
    orr r0, r0, r1, lsl #21
    add r1, r1, r1
    orr r1, lr, r1, lsr #12
    orr r1, r1, r12, lsl #20
    ldmfd sp!, {r4, lr}
    bx lr
L_2004e28:
    mov lr, r12, lsl #0x14
    and lr, lr, #0x80000000
    bic r12, r12, #0x800
    cmp r1, #0
    bne L_2004e4c
    sub r12, r12, #0x20
    movs r1, r0
    mov r0, #0
    bmi L_2004e68
L_2004e4c:
    clz r4, r1
    movs r1, r1, lsl r4
    rsb r4, r4, #0x20
    orr r1, r1, r0, lsr r4
    rsb r4, r4, #0x20
    mov r0, r0, lsl r4
    sub r12, r12, r4
L_2004e68:
    cmp r12, #0
    orrgt r12, r12, lr, lsr #20
    bgt L_2004d38
    rsb r12, r12, #0xc
    cmp r12, #0x20
    movge r0, r1
    movge r1, #0
    subge r12, r12, #0x20
    rsb r4, r12, #0x20
    mov r0, r0, lsr r12
    orr r0, r0, r1, lsl r4
    orr r1, lr, r1, lsr r12
    ldmfd sp!, {r4, lr}
    bx lr
L_2004ea0:
    cmp r12, #0x800
    movge lr, #0x80000000
    movlt lr, #0
    bics r12, r12, #0x800
    beq L_2004f0c
    orrs r4, r0, r1, lsl #1
    bne L_2004fe8
    mov r4, r3, lsr #0x14
    mov r3, r3, lsl #0xb
    orr r3, r3, r2, lsr #21
    mov r2, r2, lsl #0xb
    movs r4, r4, lsl #0x15
    beq L_2004fd4
    cmn r4, #0x200000
    bne L_2004fd4
    orrs r4, r2, r3, lsl #1
    beq L_2004ffc
    b L_2004fe8
L_2004ee8:
    cmp r4, #0x800
    movge lr, #0x80000000
    movlt lr, #0
    bic r12, r12, #0x800
    bics r4, r4, #0x800
    beq L_2004f84
    orrs r4, r2, r3, lsl #1
    bne L_2004fe8
    b L_2004fd4
L_2004f0c:
    orrs r4, r0, r1, lsl #1
    beq L_2004f4c
    mov r12, #1
    bic r1, r1, #0x80000000
    mov r4, r3, lsr #0x14
    mov r3, r3, lsl #0xb
    orr r3, r3, r2, lsr #21
    mov r2, r2, lsl #0xb
    movs r4, r4, lsl #0x15
    cmnne r4, #0x200000
    mov r4, r4, lsr #0x15
    orr r4, r4, lr, lsr #20
    beq L_2004ee8
    orr r3, r3, #0x80000000
    orr r12, r12, lr, lsr #20
    b L_2004cd4
L_2004f4c:
    mov r12, r3, lsr #0x14
    mov r1, r3, lsl #0xb
    orr r1, r1, r2, lsr #21
    mov r0, r2, lsl #0xb
    movs r4, r12, lsl #0x15
    beq L_2004f78
    cmn r4, #0x200000
    bne L_2004fa0
    orrs r4, r0, r1, lsl #1
    bne L_2004fec
    b L_2004fd4
L_2004f78:
    orrs r4, r0, r1, lsl #1
    beq L_200500c
    b L_2004fa0
L_2004f84:
    orrs r4, r2, r3, lsl #1
    beq L_2004fb0
    mov r4, #1
    bic r3, r3, #0x80000000
    orr r12, r12, lr, lsr #20
    orr r4, r4, lr, lsr #20
    b L_2004cd4
L_2004fa0:
    mov r1, r3
    mov r0, r2
    ldmfd sp!, {r4, lr}
    bx lr
L_2004fb0:
    cmp r1, #0
    subges r12, r12, #1
    mov r0, r0, lsr #0xb
    orr r0, r0, r1, lsl #21
    add r1, r1, r1
    orr r1, lr, r1, lsr #12
    orr r1, r1, r12, lsl #20
    ldmfd sp!, {r4, lr}
    bx lr
L_2004fd4:
    ldr r1, [pc, #0x40]
    orr r1, lr, r1
    mov r0, #0
    ldmfd sp!, {r4, lr}
    bx lr
L_2004fe8:
    mov r1, r3
L_2004fec:
    mvn r0, #0
    bic r1, r0, #0x80000000
    ldmfd sp!, {r4, lr}
    bx lr
L_2004ffc:
    mvn r0, #0
    bic r1, r0, #0x80000000
    ldmfd sp!, {r4, lr}
    bx lr
L_200500c:
    mov r1, #0
    mov r0, #0
    ldmfd sp!, {r4, lr}
    bx lr
    .word 0x7ff00000
_fadd:
    eors r2, r0, r1
    eormi r1, r1, #0x80000000
    bmi .L_shared_02005b20
.L_shared_0200502c:
    subs r12, r0, r1
    sublo r0, r0, r12
    addlo r1, r1, r12
    mov r2, #0x80000000
    mov r3, r0, lsr #0x17
    orr r0, r2, r0, lsl #8
    ands r12, r3, #0xff
    cmpne r12, #0xff
    beq L_20050c0
    mov r12, r1, lsr #0x17
    orr r1, r2, r1, lsl #8
    ands r2, r12, #0xff
    beq L_2005100
L_2005060:
    subs r12, r3, r12
    beq L_2005078
    rsb r2, r12, #0x20
    movs r2, r1, lsl r2
    mov r1, r1, lsr r12
    orrne r1, r1, #1
L_2005078:
    adds r0, r0, r1
    blo L_2005098
    and r1, r0, #1
    orr r0, r1, r0, rrx
    add r3, r3, #1
    and r2, r3, #0xff
    cmp r2, #0xff
    beq L_2005208
L_2005098:
    ands r1, r0, #0xff
    add r0, r0, r0
    mov r0, r0, lsr #9
    orr r0, r0, r3, lsl #23
    tst r1, #0x80
    bxeq lr
    ands r1, r1, #0x7f
    andeqs r1, r0, #1
    addne r0, r0, #1
    bx lr
L_20050c0:
    cmp r3, #0x100
    movge r2, #0x80000000
    movlt r2, #0
    ands r3, r3, #0xff
    beq L_2005124
    movs r0, r0, lsl #1
    bne L_2005234
    mov r12, r1, lsr #0x17
    mov r1, r1, lsl #9
    ands r12, r12, #0xff
    beq L_2005228
    cmp r12, #0xff
    blt L_2005228
    cmp r1, #0
    beq L_2005228
    b L_2005234
L_2005100:
    cmp r3, #0x100
    movge r2, #0x80000000
    movlt r2, #0
    and r3, r3, #0xff
    ands r12, r12, #0xff
    beq L_2005180
L_2005118:
    movs r1, r1, lsl #1
    bne L_2005234
    b L_2005228
L_2005124:
    movs r0, r0, lsl #1
    beq L_200515c
    mov r3, #1
    mov r0, r0, lsr #1
    mov r12, r1, lsr #0x17
    mov r1, r1, lsl #8
    ands r12, r12, #0xff
    beq L_2005180
    cmp r12, #0xff
    beq L_2005118
    orr r1, r1, #0x80000000
    orr r3, r3, r2, lsr #23
    orr r12, r12, r2, lsr #23
    b L_2005060
L_200515c:
    mov r3, r1, lsr #0x17
    mov r0, r1, lsl #9
    ands r3, r3, #0xff
    beq L_20051e8
    cmp r3, #0xff
    blt L_20051e8
    cmp r0, #0
    beq L_2005228
    b L_2005220
L_2005180:
    movs r1, r1, lsl #1
    beq L_20051f0
    mov r1, r1, lsr #1
    mov r12, #1
    orr r3, r3, r2, lsr #23
    orr r12, r12, r2, lsr #23
    cmp r0, #0
    bmi L_2005060
    adds r0, r0, r1
    blo L_20051b4
    and r1, r0, #1
    orr r0, r1, r0, rrx
    add r12, r12, #1
L_20051b4:
    cmp r0, #0
    subge r12, r12, #1
    ands r1, r0, #0xff
    add r0, r0, r0
    mov r0, r0, lsr #9
    orr r0, r0, r12, lsl #23
    bxeq lr
    tst r1, #0x80
    bxeq lr
    ands r1, r1, #0x7f
    andeqs r1, r0, #1
    addne r0, r0, #1
    bx lr
L_20051e8:
    mov r0, r1
    bx lr
L_20051f0:
    cmp r0, #0
    subges r3, r3, #1
    add r0, r0, r0
    orr r0, r2, r0, lsr #9
    orr r0, r0, r3, lsl #23
    bx lr
L_2005208:
    cmp r3, #0x100
    movge r2, #0x80000000
    movlt r2, #0
    mov r0, #0xff000000
    orr r0, r2, r0, lsr #1
    bx lr
L_2005220:
    mvn r0, #0x80000000
    bx lr
L_2005228:
    mov r0, #0xff000000
    orr r0, r2, r0, lsr #1
    bx lr
L_2005234:
    mvn r0, #0x80000000
    bx lr
func_0200523c:
    mvn r0, #0x80000000
    bx lr
_dls:
    mov r12, #0x200000
    cmn r12, r1, lsl #1
    bhs L_20052bc
    cmn r12, r3, lsl #1
    bhs L_20052d0
L_2005258:
    orrs r12, r3, r1
    bmi L_2005288
    cmp r1, r3
    cmpeq r0, r2
    movlo r0, #1
    movhs r0, #0
    bx lr
L_2005274:
    mov r0, #0
    mrs r12, cpsr
    orr r12, r12, #0x20000000
    msr cpsr_f, r12
    bx lr
L_2005288:
    orr r12, r0, r12, lsl #1
    orrs r12, r12, r2
    moveq r0, #0
    bne L_20052a8
    mrs r12, cpsr
    orr r12, r12, #0x20000000
    msr cpsr_f, r12
    bxeq lr
L_20052a8:
    cmp r3, r1
    cmpeq r2, r0
    movlo r0, #1
    movhs r0, #0
    bx lr
L_20052bc:
    bne L_2005274
    cmp r0, #0
    bhi L_2005274
    cmn r12, r3, lsl #1
    blo L_2005258
L_20052d0:
    bne L_2005274
    cmp r2, #0
    bhi L_2005274
    b L_2005258
_deq:
    mov r12, #0x200000
    cmn r12, r1, lsl #1
    bhs L_2005348
    cmn r12, r3, lsl #1
    bhs L_200535c
L_20052f4:
    orrs r12, r3, r1
    bmi L_2005324
    cmp r1, r3
    cmpeq r0, r2
    moveq r0, #1
    movne r0, #0
    bx lr
L_2005310:
    mov r0, #0
    mrs r12, cpsr
    bic r12, r12, #0x40000000
    msr cpsr_f, r12
    bx lr
L_2005324:
    orr r12, r0, r12, lsl #1
    orrs r12, r12, r2
    moveq r0, #1
    bxeq lr
    cmp r3, r1
    cmpeq r2, r0
    moveq r0, #1
    movne r0, #0
    bx lr
L_2005348:
    bne L_2005310
    cmp r0, #0
    bhi L_2005310
    cmn r12, r3, lsl #1
    blo L_20052f4
L_200535c:
    bne L_2005310
    cmp r2, #0
    bhi L_2005310
    b L_20052f4
_fgr:
    mov r3, #0xff000000
    cmp r3, r0, lsl #1
    cmphs r3, r1, lsl #1
    blo L_20053b4
    cmp r0, #0
    bicmi r0, r0, #0x80000000
    rsbmi r0, r0, #0
    cmp r1, #0
    bicmi r1, r1, #0x80000000
    rsbmi r1, r1, #0
    cmp r0, r1
    movgt r0, #1
    movle r0, #0
    mrs r12, cpsr
    bicle r12, r12, #0x20000000
    orrgt r12, r12, #0x20000000
    msr cpsr_f, r12
    bx lr
L_20053b4:
    mov r0, #0
    mrs r12, cpsr
    bic r12, r12, #0x20000000
    msr cpsr_f, r12
    bx lr
_fls:
    mov r3, #0xff000000
    cmp r3, r0, lsl #1
    cmphs r3, r1, lsl #1
    blo L_2005410
    cmp r0, #0
    bicmi r0, r0, #0x80000000
    rsbmi r0, r0, #0
    cmp r1, #0
    bicmi r1, r1, #0x80000000
    rsbmi r1, r1, #0
    cmp r0, r1
    movlt r0, #1
    movge r0, #0
    mrs r12, cpsr
    orrge r12, r12, #0x20000000
    biclt r12, r12, #0x20000000
    msr cpsr_f, r12
    bx lr
L_2005410:
    mov r0, #0
    mrs r12, cpsr
    orr r12, r12, #0x20000000
    msr cpsr_f, r12
    bx lr
func_02005424:
    eor r0, r0, r1
    eor r1, r0, r1
    eor r0, r0, r1
_fdiv:
    stmdb sp!, {lr}
    mov r12, #0xff
    ands r3, r12, r0, lsr #23
    cmpne r3, #0xff
    beq L_2005604
    ands r12, r12, r1, lsr #23
    cmpne r12, #0xff
    beq L_2005640
    orr r1, r1, #0x800000
    orr r0, r0, #0x800000
    bic r2, r0, #0xff000000
    bic lr, r1, #0xff000000
L_2005460:
    cmp r2, lr
    movlo r2, r2, lsl #1
    sublo r3, r3, #1
    teq r0, r1
    sub r0, pc, #0x94
    ldrb r1, [r0, lr, lsr #15]
    rsb lr, lr, #0
    mov r0, lr, asr #1
    mul r0, r1, r0
    add r0, r0, #0x80000000
    mov r0, r0, lsr #6
    mul r0, r1, r0
    mov r0, r0, lsr #0xe
    mul r1, lr, r0
    sub r12, r3, r12
    mov r1, r1, lsr #0xc
    mul r1, r0, r1
    mov r0, r0, lsl #0xe
    add r0, r0, r1, lsr #15
    umull r1, r0, r2, r0
    mov r3, r0
    orrmi r0, r0, #0x80000000
    adds r12, r12, #0x7e
    bmi L_2005708
    cmp r12, #0xfe
    bge L_20057bc
    add r0, r0, r12, lsl #23
    mov r12, r1, lsr #0x1c
    cmp r12, #7
    beq L_20055e4
    add r0, r0, r1, lsr #31
    ldmia sp!, {lr}
    bx lr
data_020054e4:
    .word 0xfdfeffff
    .word 0xf9fafbfc
    .word 0xf5f6f7f8
    .word 0xf1f2f3f4
    .word 0xeeeff0f0
    .word 0xeaebeced
    .word 0xe7e8e9ea
    .word 0xe4e5e6e6
    .word 0xe1e2e2e3
    .word 0xdedfdfe0
    .word 0xdbdcdcdd
    .word 0xd8d9d9da
    .word 0xd5d6d7d7
    .word 0xd2d3d4d4
    .word 0xd0d0d1d2
    .word 0xcdcececf
    .word 0xcbcbcccc
    .word 0xc8c9c9ca
    .word 0xc6c6c7c8
    .word 0xc3c4c5c5
    .word 0xc1c2c2c3
    .word 0xbfbfc0c0
    .word 0xbdbdbebe
    .word 0xbabbbcbc
    .word 0xb8b9b9ba
    .word 0xb6b7b7b8
    .word 0xb4b5b5b6
    .word 0xb2b3b3b4
    .word 0xb0b1b1b2
    .word 0xafafafb0
    .word 0xadadaeae
    .word 0xababacac
    .word 0xa9aaaaaa
    .word 0xa7a8a8a9
    .word 0xa6a6a7a7
    .word 0xa4a4a5a5
    .word 0xa2a3a3a4
    .word 0xa1a1a2a2
    .word 0x9fa0a0a0
    .word 0x9e9e9e9f
    .word 0x9c9d9d9d
    .word 0x9b9b9b9c
    .word 0x999a9a9a
    .word 0x98989999
    .word 0x96979798
    .word 0x95959696
    .word 0x94949495
    .word 0x92939393
    .word 0x91919292
    .word 0x90909191
    .word 0x8f8f8f90
    .word 0x8d8e8e8e
    .word 0x8c8c8d8d
    .word 0x8b8b8c8c
    .word 0x8a8a8a8b
    .word 0x8989898a
    .word 0x88888888
    .word 0x86878787
    .word 0x85868686
    .word 0x84858585
    .word 0x83838484
    .word 0x82828383
    .word 0x81818282
    .word 0x80808181
UnkFpDivideResume:
L_20055e4:
    mov r1, r3, lsl #1
    add r1, r1, #1
    rsb lr, lr, #0
    mul r1, lr, r1
    cmp r1, r2, lsl #24
    addmi r0, r0, #1
    ldmia sp!, {lr}
    bx lr
L_2005604:
    eor lr, r0, r1
    and lr, lr, #0x80000000
    cmp r3, #0
    beq L_200565c
    movs r0, r0, lsl #9
    bne L_20057a4
    mov r12, r1, lsr #0x17
    mov r1, r1, lsl #9
    ands r12, r12, #0xff
    beq L_2005794
    cmp r12, #0xff
    blt L_2005794
    cmp r1, #0
    beq L_20057b0
    b L_200578c
L_2005640:
    eor lr, r0, r1
    and lr, lr, #0x80000000
    cmp r12, #0
    beq L_20056c0
L_2005650:
    movs r1, r1, lsl #9
    bne L_200578c
    b L_20057dc
L_200565c:
    movs r2, r0, lsl #9
    beq L_2005690
    clz r3, r2
    movs r2, r2, lsl r3
    rsb r3, r3, #0
    mov r2, r2, lsr #8
    ands r12, r12, r1, lsr #23
    beq L_20056e8
    cmp r12, #0xff
    beq L_2005650
    orr r1, r1, #0x800000
    bic lr, r1, #0xff000000
    b L_2005460
L_2005690:
    mov r12, r1, lsr #0x17
    mov r1, r1, lsl #9
    ands r12, r12, #0xff
    beq L_20056b4
    cmp r12, #0xff
    blt L_20057dc
    cmp r1, #0
    beq L_20057dc
    b L_200578c
L_20056b4:
    cmp r1, #0
    beq L_20057b0
    b L_20057dc
L_20056c0:
    movs r12, r1, lsl #9
    beq L_2005794
    mov lr, r12
    clz r12, lr
    movs lr, lr, lsl r12
    rsb r12, r12, #0
    mov lr, lr, lsr #8
    orr r0, r0, #0x800000
    bic r2, r0, #0xff000000
    b L_2005460
L_20056e8:
    movs r12, r1, lsl #9
    beq L_2005794
    mov lr, r12
    clz r12, lr
    movs lr, lr, lsl r12
    rsb r12, r12, #0
    mov lr, lr, lsr #8
    b L_2005460
L_2005708:
    and r0, r0, #0x80000000
    cmn r12, #0x18
    beq L_200577c
    bmi L_20057d4
    add r1, r12, #0x17
    mov r2, r2, lsl r1
    rsb r12, r12, #0
    mov r3, r3, lsr r12
    orr r0, r0, r3
    rsb lr, lr, #0
    mul r1, lr, r3
    cmp r1, r2
    ldmeqia sp!, {lr}
    bxeq lr
    add r1, r1, lr
    cmp r1, r2
    beq L_2005770
    addmi r0, r0, #1
    subpl r1, r1, lr
    add r1, lr, r1, lsl #1
    cmp r1, r2, lsl #1
    and r3, r0, #1
    addmi r0, r0, #1
    addeq r0, r0, r3
    ldmia sp!, {lr}
    bx lr
L_2005770:
    add r0, r0, #1
    ldmia sp!, {lr}
    bx lr
L_200577c:
    cmn r2, lr
    addne r0, r0, #1
    ldmia sp!, {lr}
    bx lr
L_200578c:
    mov r0, r1
    b L_20057a4
L_2005794:
    mov r0, #0xff000000
    orr r0, lr, r0, lsr #1
    ldmia sp!, {lr}
    bx lr
L_20057a4:
    mvn r0, #0x80000000
    ldmia sp!, {lr}
    bx lr
L_20057b0:
    mvn r0, #0x80000000
    ldmia sp!, {lr}
    bx lr
L_20057bc:
    tst r0, #0x80000000
    mov r0, #0xff000000
    movne r0, r0, asr #1
    moveq r0, r0, lsr #1
    ldmia sp!, {lr}
    bx lr
L_20057d4:
    ldmia sp!, {lr}
    bx lr
L_20057dc:
    mov r0, lr
    ldmia sp!, {lr}
    bx lr
_f2d:
    and r2, r0, #0x80000000
    mov r12, r0, lsr #0x17
    mov r3, r0, lsl #9
    ands r12, r12, #0xff
    beq L_2005818
    cmp r12, #0xff
    beq L_2005844
L_2005804:
    add r12, r12, #0x380
    mov r0, r3, lsl #0x14
    orr r1, r2, r3, lsr #12
    orr r1, r1, r12, lsl #20
    bx lr
L_2005818:
    cmp r3, #0
    bne L_200582c
    mov r1, r2
    mov r0, #0
    bx lr
L_200582c:
    mov r3, r3, lsr #1
    clz r12, r3
    movs r3, r3, lsl r12
    rsb r12, r12, #1
    add r3, r3, r3
    b L_2005804
L_2005844:
    cmp r3, #0
    bhi L_200585c
    ldr r1, [pc, #0x14]
    orr r1, r1, r2
    mov r0, #0
    bx lr
L_200585c:
    mvn r0, #0
    bic r1, r0, #0x80000000
    bx lr
    .word 0x7ff00000
_ffix:
    bic r1, r0, #0x80000000
    mov r2, #0x9e
    subs r2, r2, r1, lsr #23
    ble L_2005894
    mov r1, r1, lsl #8
    orr r1, r1, #0x80000000
    cmp r0, #0
    mov r0, r1, lsr r2
    rsbmi r0, r0, #0
    bx lr
L_2005894:
    mvn r0, r0, asr #31
    add r0, r0, #0x80000000
    bx lr
_ffixu:
    tst r0, #0x80000000
    bne L_20058c4
    mov r1, #0x9e
    subs r1, r1, r0, lsr #23
    blt L_20058d8
    mov r2, r0, lsl #8
    orr r0, r2, #0x80000000
    mov r0, r0, lsr r1
    bx lr
L_20058c4:
    mov r2, #0xff000000
    cmp r2, r0, lsl #1
    movhs r0, #0
    mvnlo r0, #0
    bx lr
L_20058d8:
    mvn r0, #0
    bx lr
_fflt:
    ands r2, r0, #0x80000000
    rsbmi r0, r0, #0
    cmp r0, #0
    bxeq lr
    clz r3, r0
    movs r0, r0, lsl r3
    rsb r3, r3, #0x9e
    ands r1, r0, #0xff
    add r0, r0, r0
    orr r0, r2, r0, lsr #9
    orr r0, r0, r3, lsl #23
    bxeq lr
    tst r1, #0x80
    bxeq lr
    ands r3, r1, #0x7f
    andeqs r3, r0, #1
    addne r0, r0, #1
    bx lr
_fmul:
    eor r2, r0, r1
    and r2, r2, #0x80000000
    mov r12, #0xff
    ands r3, r12, r0, lsr #23
    mov r0, r0, lsl #8
    cmpne r3, #0xff
    beq L_20059a4
    orr r0, r0, #0x80000000
    ands r12, r12, r1, lsr #23
    mov r1, r1, lsl #8
    cmpne r12, #0xff
    beq L_20059e4
    orr r1, r1, #0x80000000
L_200595c:
    add r12, r3, r12
    umull r1, r3, r0, r1
    movs r0, r3
    addpl r0, r0, r0
    subpl r12, r12, #1
    subs r12, r12, #0x7f
    bmi L_2005a70
    cmp r12, #0xfe
    bge L_2005adc
    ands r3, r0, #0xff
    orr r0, r2, r0, lsr #8
    add r0, r0, r12, lsl #23
    tst r3, #0x80
    bxeq lr
    orrs r1, r1, r3, lsl #25
    andeqs r3, r0, #1
    addne r0, r0, #1
    bx lr
L_20059a4:
    cmp r3, #0
    beq L_20059f8
    movs r0, r0, lsl #1
    bne L_2005acc
    mov r12, r1, lsr #0x17
    mov r1, r1, lsl #9
    ands r12, r12, #0xff
    beq L_20059d8
    cmp r12, #0xff
    blt L_2005ac0
    cmp r1, #0
    beq L_2005ac0
    b L_2005acc
L_20059d8:
    cmp r1, #0
    beq L_2005ad4
    b L_2005ac0
L_20059e4:
    cmp r12, #0
    beq L_2005a54
L_20059ec:
    movs r1, r1, lsl #1
    bne L_2005acc
    b L_2005ac0
L_20059f8:
    movs r0, r0, lsl #1
    beq L_2005a30
    mov r0, r0, lsr #1
    clz r3, r0
    movs r0, r0, lsl r3
    rsb r3, r3, #1
    mov r12, r1, lsr #0x17
    mov r1, r1, lsl #8
    ands r12, r12, #0xff
    beq L_2005a54
    cmp r12, #0xff
    beq L_20059ec
    orr r1, r1, #0x80000000
    b L_200595c
L_2005a30:
    mov r12, r1, lsr #0x17
    mov r1, r1, lsl #9
    ands r12, r12, #0xff
    beq L_2005b00
    cmp r12, #0xff
    blt L_2005b00
    cmp r1, #0
    beq L_2005ad4
    b L_2005acc
L_2005a54:
    movs r1, r1, lsl #1
    beq L_2005b00
    mov r1, r1, lsr #1
    clz r12, r1
    movs r1, r1, lsl r12
    rsb r12, r12, #1
    b L_200595c
L_2005a70:
    cmn r12, #0x18
    beq L_2005ab8
    bmi L_2005af8
    cmp r1, #0
    orrne r0, r0, #1
    mov r3, r0
    mov r0, r0, lsr #8
    rsb r12, r12, #0
    orr r0, r2, r0, lsr r12
    rsb r12, r12, #0x18
    movs r1, r3, lsl r12
    bxeq lr
    tst r1, #0x80000000
    bxeq lr
    movs r1, r1, lsl #1
    andeqs r1, r0, #1
    addne r0, r0, #1
    bx lr
L_2005ab8:
    mov r0, r0, lsl #1
    b L_2005ae8
L_2005ac0:
    mov r0, #0xff000000
    orr r0, r2, r0, lsr #1
    bx lr
L_2005acc:
    mvn r0, #0x80000000
    bx lr
L_2005ad4:
    mvn r0, #0x80000000
    bx lr
L_2005adc:
    mov r0, #0xff000000
    orr r0, r2, r0, lsr #1
    bx lr
L_2005ae8:
    movs r1, r0
    mov r0, r2
    addne r0, r0, #1
    bx lr
L_2005af8:
    mov r0, r2
    bx lr
L_2005b00:
    mov r0, r2
    bx lr
func_02005b08:
    eor r0, r0, r1
    eor r1, r0, r1
    eor r0, r0, r1
_fsub:
    eors r2, r0, r1
    eormi r1, r1, #0x80000000
    bmi .L_shared_0200502c
.L_shared_02005b20:
    subs r12, r0, r1
    eorlo r12, r12, #0x80000000
    sublo r0, r0, r12
    addlo r1, r1, r12
    mov r2, #0x80000000
    mov r3, r0, lsr #0x17
    orr r0, r2, r0, lsl #8
    ands r12, r3, #0xff
    cmpne r12, #0xff
    beq L_2005c3c
    mov r12, r1, lsr #0x17
    orr r1, r2, r1, lsl #8
    ands r2, r12, #0xff
    beq L_2005c7c
L_2005b58:
    subs r12, r3, r12
    beq L_2005ba0
    rsb r2, r12, #0x20
    movs r2, r1, lsl r2
    mov r1, r1, lsr r12
    orrne r1, r1, #1
    subs r0, r0, r1
    bpl L_2005be4
    ands r1, r0, #0xff
    add r0, r0, r0
    mov r0, r0, lsr #9
    orr r0, r0, r3, lsl #23
    tst r1, #0x80
    bxeq lr
    ands r1, r1, #0x7f
    andeqs r1, r0, #1
    addne r0, r0, #1
    bx lr
L_2005ba0:
    subs r0, r0, r1
    beq L_2005d48
    mov r2, r3, lsl #0x17
    and r2, r2, #0x80000000
    bic r3, r3, #0x100
    clz r12, r0
    movs r0, r0, lsl r12
    sub r3, r3, r12
    cmp r3, #0
    bgt L_2005bd4
    rsb r3, r3, #9
    orr r0, r2, r0, lsr r3
    bx lr
L_2005bd4:
    add r0, r0, r0
    orr r0, r2, r0, lsr #9
    orr r0, r0, r3, lsl #23
    bx lr
L_2005be4:
    mov r2, r3, lsl #0x17
    and r2, r2, #0x80000000
    bic r3, r3, #0x100
    clz r12, r0
    movs r0, r0, lsl r12
    sub r3, r3, r12
    cmp r3, #0
    bgt L_2005c10
    rsb r3, r3, #9
    orr r0, r2, r0, lsr r3
    bx lr
L_2005c10:
    ands r1, r0, #0xff
    add r0, r0, r0
    orr r0, r2, r0, lsr #9
    orr r0, r0, r3, lsl #23
    bxeq lr
    tst r1, #0x80
    bxeq lr
    ands r1, r1, #0x7f
    andeqs r1, r0, #1
    addne r0, r0, #1
    bx lr
L_2005c3c:
    cmp r3, #0x100
    movge r2, #0x80000000
    movlt r2, #0
    ands r3, r3, #0xff
    beq L_2005ca4
    movs r0, r0, lsl #1
    bne L_2005d7c
    mov r12, r1, lsr #0x17
    mov r1, r1, lsl #9
    ands r12, r12, #0xff
    beq L_2005d70
    cmp r12, #0xff
    blt L_2005d70
    cmp r1, #0
    beq L_2005d84
    b L_2005d7c
L_2005c7c:
    cmp r12, #0x100
    movge r2, #0x80000000
    movlt r2, #0
    and r3, r3, #0xff
    ands r12, r12, #0xff
    beq L_2005d0c
L_2005c94:
    eor r2, r2, #0x80000000
    movs r1, r1, lsl #1
    bne L_2005d7c
    b L_2005d70
L_2005ca4:
    movs r0, r0, lsl #1
    beq L_2005cdc
    mov r0, r0, lsr #1
    mov r3, #1
    mov r12, r1, lsr #0x17
    mov r1, r1, lsl #8
    ands r12, r12, #0xff
    beq L_2005d0c
    cmp r12, #0xff
    beq L_2005c94
    orr r1, r1, #0x80000000
    orr r3, r3, r2, lsr #23
    orr r12, r12, r2, lsr #23
    b L_2005b58
L_2005cdc:
    mov r3, r1, lsr #0x17
    mov r0, r1, lsl #9
    ands r2, r3, #0xff
    beq L_2005d00
    cmp r2, #0xff
    blt L_2005d28
    cmp r0, #0
    bne L_2005d68
    b L_2005d70
L_2005d00:
    cmp r0, #0
    beq L_2005d48
    b L_2005d28
L_2005d0c:
    movs r1, r1, lsl #1
    beq L_2005d30
    mov r1, r1, lsr #1
    mov r12, #1
    orr r12, r12, r2, lsr #23
    orr r3, r3, r2, lsr #23
    b L_2005b58
L_2005d28:
    mov r0, r1
    bx lr
L_2005d30:
    cmp r0, #0
    subges r3, r3, #1
    add r0, r0, r0
    orr r0, r2, r0, lsr #9
    orr r0, r0, r3, lsl #23
    bx lr
L_2005d48:
    mov r0, #0
    bx lr
    cmp r0, #0
    subges r3, r3, #1
    add r0, r0, r0
    mov r0, r0, lsr #9
    orr r0, r0, r3, lsl #23
    bx lr
L_2005d68:
    mvn r0, #0x80000000
    bx lr
L_2005d70:
    mov r0, #0xff000000
    orr r0, r2, r0, lsr #1
    bx lr
L_2005d7c:
    mvn r0, #0x80000000
    bx lr
L_2005d84:
    mvn r0, #0x80000000
    bx lr
.size _dadd, 792
.size _ll_ufrom_d, 140
.size _dmul, 868
.size _dsub, 948
.size _fadd, 540
.size func_0200523c, 8
.size _dls, 156
.size _deq, 140
.size _fgr, 92
.size _fls, 92
.size _fdiv, 952
.size _f2d, 132
.size _ffix, 52
.size _ffixu, 64
.size _fflt, 72
.size _fmul, 480
.size _fsub, 632
.size func_02004c54, 24
.size func_02005424, 12
.size func_02005b08, 12


.global data_020054e4
.global UnkFpDivideResume

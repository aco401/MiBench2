.thumb_func
.globl testfun1
testfun1:
    ;@ clear carry flag
    mov r2,#0
    ror r2,r2
    adc r0,r1
    b returnvcflags
.thumb_func
.globl testfun2
testfun2:
    ;@ set carry flag
    mov r2,#1
    ror r2,r2
    adc r0,r1
    b returnvcflags
.thumb_func
.globl testfun3
testfun3:
    ;@ clear carry flag
    mov r2,#0
    ror r2,r2
    sbc r0,r1
    b returnvcflags
.thumb_func
.globl testfun4
testfun4:
    ;@ set carry flag
    mov r2,#1
    ror r2,r2
    sbc r0,r1
    b returnvcflags
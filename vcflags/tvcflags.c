
#include "../bareBench.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LOG_DEBUG

#ifdef LOG_DEBUG
void PUT32 ( unsigned int, unsigned int );
#endif

#define CPSR_C (1<<29)
#define CPSR_V (1<<28)
unsigned int cpsr;

unsigned int testfun1 ( unsigned int, unsigned int );
unsigned int testfun2 ( unsigned int, unsigned int );
unsigned int testfun3 ( unsigned int, unsigned int );
unsigned int testfun4 ( unsigned int, unsigned int );

#ifdef LOG_DEBUG
#define UART_BASE 0xE0000000
#endif

void add_test ( unsigned int ra, unsigned int rb )
{
    unsigned int rc,rd;
    #ifdef LOG_DEBUG
    PUT32(UART_BASE,ra);
    PUT32(UART_BASE,rb);
    #endif
    rc=testfun1(ra,rb);
    rd=testfun2(ra,rb);
    #ifdef LOG_DEBUG
    PUT32(UART_BASE,rc&0x30000000);
    PUT32(UART_BASE,rd&0x30000000);
    #endif
}

void sub_test ( unsigned int ra, unsigned int rb )
{

    #ifdef LOG_DEBUG
    unsigned int rc,rd;
    PUT32(UART_BASE,ra);
    PUT32(UART_BASE,rb);
    rc=testfun3(ra,rb);
    rd=testfun4(ra,rb);
    PUT32(UART_BASE,rc&0x30000000);
    PUT32(UART_BASE,rd&0x30000000);
    #else
    testfun3(ra,rb);
    testfun4(ra,rb);
    #endif
}

int vcflags_bench ( void )
{
    unsigned int ra,rb;

    for(ra=0;ra<4;ra++)
    {
        for(rb=0;rb<4;rb++)
        {
            add_test(ra<<30,rb<<30);
        }
    }
    for(ra=0x7FFFFFFC;ra<0x80000004;ra++) add_test(ra,0);
    for(ra=0x7FFFFFFC;ra<0x80000004;ra++) add_test(ra,1);
    for(ra=0xFFFFFFFC;ra;ra++) add_test(ra,0);
    for(ra=0;ra<0x04;ra++) add_test(ra,0);
    for(ra=0xFFFFFFFC;ra;ra++) add_test(ra,1);
    for(ra=0;ra<0x04;ra++) add_test(ra,1);
    for(ra=0x7FFFFFFC;ra<0x80000004;ra++) add_test(0,ra);
    for(ra=0x7FFFFFFC;ra<0x80000004;ra++) add_test(1,ra);

    for(ra=0;ra<4;ra++)
    {
        for(rb=0;rb<4;rb++)
        {
            sub_test(ra<<30,rb<<30);
        }
    }

    for(ra=0x7FFFFFFC;ra<0x80000004;ra++) sub_test(ra,0);
    for(ra=0x7FFFFFFC;ra<0x80000004;ra++) sub_test(ra,1);
    for(ra=0xFFFFFFFC;ra;ra++) sub_test(ra,0);
    for(ra=0;ra<0x04;ra++) sub_test(ra,0);
    for(ra=0xFFFFFFFC;ra;ra++) sub_test(ra,1);
    for(ra=0;ra<0x04;ra++) sub_test(ra,1);

    return(0);
}


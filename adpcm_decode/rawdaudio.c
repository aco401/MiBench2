/* testd - Test adpcm decoder */

#include "../adpcm/adpcm.h"
#include <stdio.h>
#include "../bareBench.h"
#include "input.h"



#define NSAMPLES 1000
#define NINC  (NSAMPLES / 2)

short	sbuf[NSAMPLES];

int adpcm_decode_bench(void) {
    struct adpcm_state state = {};
    int n = 0;
    unsigned char * currentN = test_data_decode;
    int maxN = sizeof(test_data_decode);
    
    #ifdef LOG_DEBUG
    printf("Initial valprev=%d, index=%d\n", state.valprev, state.index);
    #endif
    
    while(1) {
        int bytesIntoRead = ((unsigned int)currentN) - ((unsigned int)test_data_decode);
        int testN = bytesIntoRead + NINC;
        n = (testN <= maxN) ? NINC : maxN - bytesIntoRead;

        if ( n == 0 ) break;

        adpcm_decoder(currentN, sbuf, n*2, &state);
        currentN = test_data_decode + bytesIntoRead + n;
        //write(1, sbuf, n*4);
    }
    
    #ifdef LOG_DEBUG
    printf("Final valprev=%d, index=%d\n", state.valprev, state.index);
    #endif
    return 0;
}

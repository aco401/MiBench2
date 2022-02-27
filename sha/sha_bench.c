/* NIST Secure Hash Algorithm */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include "../bareBench.h"
#include "sha.h"
#include "input.h"
#include "sha_bench.h"

int sha_bench()
{
  SHA_INFO sha_info;


  sha_stream(&sha_info, inputString);
  #ifdef BENCH_VERBOSE
  sha_print(&sha_info);
  #endif
  
  return(0);
}

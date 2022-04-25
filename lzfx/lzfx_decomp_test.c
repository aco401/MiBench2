
#include "def_data.h"

#ifdef LOG_DEBUG
extern void uart_init ( void );
extern void hexstring ( unsigned short d );
#endif


int lzfx_decompress_tiny
(
    const unsigned char *ibuf,
    const unsigned int ilen,
    unsigned char *obuf,
    unsigned int *olen
);

unsigned int inf_data_len;
unsigned char inf_data[0x4000];

int lzfx_decompress_test ( void )
{
    int ret;
    unsigned int ra,rb;

    inf_data_len=sizeof(inf_data);
    ret=lzfx_decompress_tiny(def_data,DEF_DATA_LEN,inf_data,&inf_data_len);
    if(ret) return(ret);
    #ifdef LOG_DEBUG
    hexstring(inf_data_len);
    #endif
    if(inf_data_len!=INF_DATA_LEN) return(1);
    rb=0; for(ra=0;ra<inf_data_len;ra++) rb+=inf_data[ra]; rb&=0xFFFF;
    #ifdef LOG_DEBUG
    hexstring(rb);
    #endif
    if(rb!=INF_DATA_CHECKSUM) return(1);
    return(0);
}

int lzfx_bench ( void )
{
    #ifdef LOG_DEBUG
    uart_init();
    hexstring(0x1234);
    #endif
    if(lzfx_decompress_test())
    {
        #ifdef LOG_DEBUG
        hexstring(0x0BAD);
        #endif
    }
    #ifdef LOG_DEBUG
    hexstring(0x1234);
    #endif
    return(0);
}


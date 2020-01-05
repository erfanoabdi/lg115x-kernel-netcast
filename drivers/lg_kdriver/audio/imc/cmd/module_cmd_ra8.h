
#ifndef __MODULE_CMD_RA8_H__
#define __MODULE_CMD_RA8_H__

#include "imc/adec_imc_cmd.h"

#define RA8_CMD_SET_PARAM		ADEC_CMD(0x2000, Ra8CmdSetParam)

#define RA8_CMD_DEBUG_STATUS	ADEC_CMD_SIMP(0x2020)

typedef struct _Ra8CmdSetParam
{
    int nsamples;                /* -n NSAMPLES   transform size */
    int regions;                 /* -r REGIONS    region limit */
    int bits;                    /* -b BITS       bits per frame */
    int cplstart;                /* -c CPLSTART   coupling start region */
    int cplqbits;                /* -q CPLQBITS   coupling quant bits */
    int nchannels;               /* number of channels */
} Ra8CmdSetParam;

#endif // #ifndef __MODULE_CMD_RA8_H__


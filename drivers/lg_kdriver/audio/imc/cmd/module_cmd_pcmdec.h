
#ifndef __MODULE_CMD_PCMDEC_H__
#define __MODULE_CMD_PCMDEC_H__

#include "imc/adec_imc_cmd.h"

#define PCMDEC_CMD_SET_PARAM		ADEC_CMD(0x2000, PcmDecCmdSetParam)

#define PCMDEC_CMD_DEBUG_STATUS	ADEC_CMD_SIMP(0x2020)


typedef struct _PcmDecCmdSetParam
{
    unsigned int i_samp_freq;                /* Sampling frequency of the output */
    unsigned int i_num_chan;                 /* Number of encoded channels in the bitstream */
    unsigned int i_pcm_wd_sz;                /* Sample size of a sample in bits */
    unsigned int i_endian;
    unsigned int i_signed;
} PcmDecCmdSetParam;

#endif // #ifndef __MODULE_CMD_PCMDEC_H__


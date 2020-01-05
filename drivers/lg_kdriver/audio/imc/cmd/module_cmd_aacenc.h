
#ifndef __MODULE_CMD_AACENC_H__
#define __MODULE_CMD_AACENC_H__

#include "imc/adec_imc_cmd.h"

#define AACENC_CMD_SET_PARAM	ADEC_CMD(0x2000, AacEncCmdSetParam)

#define AACENC_CMD_DEBUG_STATUS	ADEC_CMD_SIMP(0x2020)

typedef struct _AacEncCmdSetParam
{
    int i_samp_freq;                /* Sampling frequency of the output */
    int i_pcm_wd_sz;                /* Sample size of a sample in bits */
    int i_num_chan;                 /* Number of encoded channels in the bitstream */
    int i_bitrate;                  /* Data rate of the input stream */
} AacEncCmdSetParam;

#endif // #ifndef __MODULE_CMD_AACENC_H__


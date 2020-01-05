
#ifndef __MODULE_CMD_DTSENC_H__
#define __MODULE_CMD_DTSENC_H__

#include "imc/adec_imc_cmd.h"

#define DTSENC_CMD_SET_PARAM       ADEC_CMD(0x2000, DtsEncCmdSetParam)

#define DTSENC_CMD_DEBUG_STATUS	ADEC_CMD_SIMP(0x2020)

typedef struct _DtsEncCmdSetParam
{
    unsigned int i_samp_freq;                /* Sampling frequency of the output */
    unsigned int i_pcm_wd_sz;                /* Sample size of a sample in bits */
    unsigned int ch_layout;                  /* Encoder channel layout(Front/Surround/LFE) */
#ifdef IC_CERTIFICATION
    unsigned int certi_param;                // IC Certification parameter
#endif // #ifdef IC_CERTIFICATION
} DtsEncCmdSetParam;

#endif // #ifndef __MODULE_CMD_DTSENC_H__


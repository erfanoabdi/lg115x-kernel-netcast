
#ifndef __MODULE_CMD_TP_H__
#define __MODULE_CMD_TP_H__

#include "imc/adec_imc_cmd.h"

#define TP_CMD_SET_PARAM		ADEC_CMD(0x2000, TpCmdSetParam)

#define TP_CMD_DEBUG_STATUS		ADEC_CMD_SIMP(0x2020)


typedef struct _TpCmdSetParam
{
    unsigned int codec_type;            /* PES decoder codec type */
                                        // ADEC_MEDIA_MS10_DDC = 2,
                                        // ADEC_MEDIA_MS10_DDT = 3,
                                        // ADEC_MEDIA_MP3      = 5,
    unsigned int interval;              // TP Timer Interval  : Normal : 0x2000(default), MHEG : 0x200
} TpCmdSetParam;


#endif // #ifndef __MODULE_CMD_TP_H__


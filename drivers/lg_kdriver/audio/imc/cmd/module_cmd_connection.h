/*
	SIC LABORATORY, LG ELECTRONICS INC., SEOUL, KOREA
	Copyright(c) 2010 by LG Electronics Inc.

	This program is free software; you can redistribute it and/or 
	modify it under the terms of the GNU General Public License
	version 2 as published by the Free Software Foundation.

	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of 
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the 
	GNU General Public License for more details.
*/ 

#ifndef __MODULE_CMD_CONNECTION_H__
#define __MODULE_CMD_CONNECTION_H__

#include "imc/adec_imc_cmd.h"

////////////////////////////////////////////////////////////////////////////////
// Connection Manager Connect
////////////////////////////////////////////////////////////////////////////////
#define CM_CMD_CONNECT					ADEC_CMD(0xF000, CmCmdConnect)
typedef struct _CmCmdConnect
{
	unsigned int		input_module;
	unsigned int		input_port;
	unsigned int		output_module;
	unsigned int		output_port;
}CmCmdConnect;


////////////////////////////////////////////////////////////////////////////////
// Connection Manager Disconnect
////////////////////////////////////////////////////////////////////////////////
#define CM_CMD_DISCONNECT				ADEC_CMD(0xF001, CmCmdDisconnect)
typedef struct _CmCmdDisconnect
{
	unsigned int		module;
	unsigned int		port;
}CmCmdDisconnect;



////////////////////////////////////////////////////////////////////////////////
// Connection Manager Allocate Buffer
////////////////////////////////////////////////////////////////////////////////
#define CM_CMD_ALLOC_BUF				ADEC_CMD(0xF010, CmCmdAllocBuf)
typedef struct _CmCmdAllocBuf
{
	unsigned int		module;
	unsigned int		port;
	unsigned int		physical_addr;
	unsigned int		register_addr_offset;
	unsigned int		is_reader;				//!< If reader 1, else 0. (explicit check)
}CmCmdAllocBuf;



////////////////////////////////////////////////////////////////////////////////
// Connection Manager Release Buffer
////////////////////////////////////////////////////////////////////////////////
#define CM_CMD_DEALLOC_BUF				ADEC_CMD(0xF011, CmCmdDeallocBuf)
typedef struct _CmCmdDeallocBuf
{
	unsigned int		module;
	unsigned int		port;
}CmCmdDeallocBuf;


////////////////////////////////////////////////////////////////////////////////
// Connection Manager Create Module
////////////////////////////////////////////////////////////////////////////////
#define CM_CMD_CREATE_MODULE			ADEC_CMD(0xF020, CmCmdCreateModule)
typedef union _CmCmdModuleSpecific
{
	struct{
		unsigned int		media_type;
	}					codec_param;
	struct{
		unsigned int		src_type;			// 0 for SW, 1 for HW
	}					src_param;
}CmCmdModuleSpecific;

typedef struct _CmCmdCreateModule
{
	unsigned int		module_id;
	CmCmdModuleSpecific module_param;
}CmCmdCreateModule;


////////////////////////////////////////////////////////////////////////////////
// Connection Manager Destory Module
////////////////////////////////////////////////////////////////////////////////
#define CM_CMD_DESTROY_MODULE			ADEC_CMD(0xF021, CmCmdDestroyModule)
typedef struct _CmCmdDestroyModule
{
	unsigned int		module_id;
}CmCmdDestroyModule;


////////////////////////////////////////////////////////////////////////////////
// Connection Manager Get Free Client
////////////////////////////////////////////////////////////////////////////////
#define CM_CMD_GET_FREE_CLIENT			ADEC_CMD(0xF080, CmCmdGetFreeClient)
typedef struct _CmCmdGetFreeClient
{
	unsigned int		module;
	unsigned int		out_port;
}CmCmdGetFreeClient;

typedef struct _CmRspGetFreeClient
{
	unsigned int		total;
	unsigned int		num_of_free;
}CmRspGetFreeClient;



////////////////////////////////////////////////////////////////////////////////
// Connection Manager Get Port Info
////////////////////////////////////////////////////////////////////////////////
#define CM_CMD_GET_PORT_INFO			ADEC_CMD(0xF081, CmCmdGetPortInfo)
typedef struct _CmCmdGetPortInfo
{
	unsigned int		module;
	unsigned int		port;
}CmCmdGetPortInfo;

typedef struct _CmRspGetPortInfo
{
	unsigned int		direction; 		//!< if 0 input, else output
	unsigned int		buf_type;		// Refer to ADEC_BUF_TYPE
	// Bellows are valid when connect_type is 0.
	unsigned int		connected_module;
	unsigned int		connected_port;
}CmRspGetPortInfo;



////////////////////////////////////////////////////////////////////////////////
// Connection Manager Register Reference Port
////////////////////////////////////////////////////////////////////////////////
#define CM_CMD_SET_REF_PORTS			ADEC_CMD(0xF090, CmCmdSetRefPorts)
typedef struct _CmCmdSetRefPorts
{
	unsigned int		ref_module;		//!< A module to register reference		
	unsigned int		num_of_ref;		//!< Num of references in this command
	unsigned int		ref_port[4];		
	unsigned int		src_module[4];		 
	unsigned int		src_port[4];		
}CmCmdSetRefPorts;


////////////////////////////////////////////////////////////////////////////////
// Connection Manager Clear Reference Port
////////////////////////////////////////////////////////////////////////////////
#define CM_CMD_CLR_REF_PORTS			ADEC_CMD(0xF091, CmCmdClrRefPorts)
typedef struct _CmCmdClrRefPorts
{
	unsigned int		module;
	unsigned int		num_of_ref;
	unsigned int		ref_port[4];
}CmCmdClrRefPorts;


////////////////////////////////////////////////////////////////////////////////
// Connection Manager Clear All Reference Port
////////////////////////////////////////////////////////////////////////////////
#define CM_CMD_CLR_ALL_REF_PORTS		ADEC_CMD(0xF092, CmCmdClrAllRef)
typedef struct _CmCmdClrAllRef
{
	unsigned int		module;
}CmCmdClrAllRef;

#endif

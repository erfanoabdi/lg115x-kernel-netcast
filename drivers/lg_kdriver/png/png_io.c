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



/*========================================================================================
    Implementation Group : PNG CDEV
========================================================================================*/
static int _ioctl_getCAPs(struct PNG_T* pPNG, unsigned long arg)
{
	unsigned long leftovers = 0;

	PNG_PRINT("[PNG] IOCTL: PNG_IOR_GET_CAPS\n");

	if (pPNG == NULL)
	{
		PNG_ERROR("ASSERT\n");
		return -EIO;
	}

	leftovers = copy_to_user((void __user*)arg, (void *)&pPNG->caps, sizeof(LX_PNG_DECODE_CAPS_T));
	if (leftovers != 0)
	{
		PNG_ERROR("Failed in Copying to user %ld\n", leftovers);
		return -EIO;
	}

	return 0;
}

static int _ioctl_getMemStat(struct PNG_T* pPNG, unsigned long arg)
{
	unsigned long leftovers = 0;
	LX_PNG_MEM_STAT_T	memCfg;

	PNG_PRINT("[PNG] IOCTL: PNG_IOR_GET_MEM_STAT\n");
			
	if (pPNG == NULL)
	{
		PNG_ERROR("ASSERT\n");
		return -EIO;
	}

	memCfg.src_buf_addr = pPNG->src_buf_addr;
	memCfg.src_buf_size = pPNG->src_buf_size;

	leftovers = copy_to_user((void __user *)arg, (void*)&memCfg, sizeof(LX_PNG_MEM_STAT_T));
	if (leftovers != 0)
	{
		PNG_ERROR("Failed in setting data[%ld]\n", leftovers);
		return -EIO;
	}

	return 0;
}

static int _ioctl_getBufSize(struct PNG_T* pPNG, unsigned long arg)
{
	unsigned long leftovers = 0;

	PNG_PRINT("[PNG] IOCTL: PNG_IOR_GET_BUFFER_SIZE\n");
			
	if (pPNG == NULL)
	{
		PNG_ERROR("ASSERT\n");
		return -EIO;
	}

	leftovers = copy_to_user((void __user *)arg, (void*)&pPNG->src_buf_size, sizeof(UINT32));
	if (leftovers != 0)
	{
		PNG_ERROR("Failed in setting data[%ld]\n", leftovers);
		return -EIO;
	}

	return 0;
}

static int _ioctl_getHWState(struct PNG_T* pPNG, unsigned long arg)
{
	unsigned long leftovers = 0;
	
	PNG_PRINT("[PNG] IOCTL: PNG_IOR_GET_HW_STATE\n");
	
	if (pPNG == NULL)
	{
		PNG_ERROR("ASSERT\n");
		return -EIO;
	}

	leftovers = copy_to_user((void __user *)arg, (void*)&pPNG->cur_state, sizeof(LX_PNG_STATE_T));
	if (leftovers != 0)
	{
		PNG_ERROR("Failed in setting data[%ld]\n", leftovers);
		return -EIO;
	}
	
	return 0;
}

static int _ioctl_reset(struct PNG_T* pPNG, unsigned long arg)
{
	PNG_PRINT("[PNG] IOCTL: PNG_IO_RESET\n");
	
	if (pPNG == NULL)
	{
		PNG_ERROR("ASSERT\n");
		return -EIO;
	}

	pPNG->reset(pPNG);
	return RET_OK;
}


static int _ioctl_decodeIDAT(struct PNG_T* pPNG, unsigned long arg)
{
	int	res = 0;
	unsigned long leftovers = 0;
	LX_PNG_DECODE_PARAM_T request;
	LX_PNG_OP_T method = LX_PNG_OP_FULL; 
 	int ret = RET_ERROR;
	
	PNG_PRINT("[PNG] IOCTL: PNG_IOW_DECODE_IDAT\n");
	
	if (pPNG == NULL)
	{
		PNG_ERROR("ASSERT\n");
		return -EIO;
	}

	if (pPNG->cur_state == LX_PNG_STATE_ERROR)
	{
		PNG_ERROR("[png] : pPNG->cur_state [%d]\n", pPNG->cur_state);
		return -ESTALE;
	}
	
	ret = pPNG->changeState(pPNG, LX_PNG_STATE_DECODING);
	if (ret != RET_OK)
	{
		PNG_ERROR("[png] : Failed[%d] to change state\n", ret);
		res = RET_ERROR;
		goto func_exit;
	}

	leftovers = copy_from_user((void *)&request, (void __user *)arg, sizeof(LX_PNG_DECODE_PARAM_T));
	if (leftovers != 0)
	{
		PNG_ERROR("Failed in getting data[%ld]\n", leftovers);
		res = RET_ERROR;
		goto func_exit;
	}

	/* Check if the requested image is possible to decode */
	if(	request.img_hdr.width > pPNG->caps.max_width || request.img_hdr.height > pPNG->caps.max_height)
	{
		PNG_ERROR("[png] : Not possible to decode W[%d], h[%d]\n",
					request.img_hdr.width, request.img_hdr.height);
		res = RET_ERROR;
		goto func_exit;
	}
	
	if(	pPNG->caps.interlacing == LX_PNG_INTERLACING_DISABLED && request.img_hdr.interlace_method != 0)
	{
		PNG_ERROR("[png] : Interaced PNG is not supported[%d]\n",
					request.img_hdr.interlace_method);
		res = RET_ERROR;
		goto func_exit;
	}

	/* Decode if it can */
	method = (request.op_method) & (pPNG->caps.possible_op);
	if (method != 0)
	{
		ret = pPNG->decodeIDAT(pPNG, &request);

		if (ret != RET_OK)
		{
			PNG_ERROR("[png] : Failed[%d] to decode\n", ret);
			res = RET_ERROR;
			goto func_exit;
		}
	}
	else
	{
		PNG_ERROR("[png] not support decode method[%d]\n", request.op_method);
		ret = RET_ERROR;
		goto func_exit;
	}

	return RET_OK;

func_exit:
	return res;
}

static int (*_gpIOCTLfns[])(struct PNG_T* pPNG, unsigned long arg) =
{
/* PNG_IOR_GET_CAPS				0x00 */		_ioctl_getCAPs,
/* PNG_IOR_GET_MEM_STAT			0x01 */		_ioctl_getMemStat,
/* PNG_IOR_GET_BUFFER_SIZE		0x02 */		_ioctl_getBufSize,
/* PNG_IOR_GET_HW_STATE			0x03 */		_ioctl_getHWState,
/* PNG_IO_RESET					0x04 */		_ioctl_reset,
/* PNG_IOW_DECODE_IDAT			0x05 */		_ioctl_decodeIDAT,  //start, middle, end
};

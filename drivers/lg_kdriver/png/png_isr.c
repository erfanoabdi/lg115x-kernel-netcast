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
	Implementation Group : PNG ISR
========================================================================================*/
/** ISR handler of PNG decoder
 *	@note it's called from ISR of venc
 */
irqreturn_t _PNG_ISRhandler(int irq, void *dev_id)
{
	/* read PNG interrupt status */
	(void)_gpPNG->ISRHandler(_gpPNG);
    
	return IRQ_HANDLED;
}

static int _PNG_requestISR(struct PNG_T *pPNG)
{
	int ret = 0;
	ret = request_irq(pPNG->irq_nr, _PNG_ISRhandler, 0, pPNG->module_name, NULL);
	if (ret != 0) 
   	{
		PNG_ERROR("[PNG] failed[%d] to request irq\n", ret);

		return RET_ERROR;
	}
	
	pPNG->enableISR(pPNG);

	return RET_OK;
}

static void	_PNG_freeISR(struct PNG_T *pPNG)
{
	pPNG->disableISR(pPNG);
	disable_irq(pPNG->irq_nr);
	free_irq(pPNG->irq_nr, NULL);
}


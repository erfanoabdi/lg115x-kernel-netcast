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

#ifndef _DE_ARG_h
#define _DE_ARG_h

BOOLEAN isXDigit(char *pString)
{
	BOOLEAN rtn		   = TRUE;
	BOOLEAN thereIsNum = FALSE;

	if ( pString ) {
		if (*pString == '-') pString++;
		if (*pString == '0') {
			pString++;
			if ((toupper(*pString) == 'X') && isxdigit(pString[1])) {
				pString++;
			} else if ((toupper(*pString) == 'U') && isdigit(pString[1])) {
				pString++;
			} else if ((toupper(*pString) == 'Z') && isxdigit(pString[1])) {
				pString++;
			}
			thereIsNum = TRUE;
		} else if ((toupper(*pString) == 'X') && isxdigit(pString[1])) {
			pString++;
			thereIsNum = TRUE;
		} else if ((toupper(*pString) == 'U') && isdigit(pString[1])) {
			pString++;
			thereIsNum = TRUE;
		} else if ((toupper(*pString) == 'Z') && isxdigit(pString[1])) {
			pString++;
			thereIsNum = TRUE;
		} else if (isdigit(*pString)) {
			pString++;
			thereIsNum = TRUE;
		}

		for ( ;*pString != '\0';++pString ) {
			if (isdigit(*pString)) {
				thereIsNum = TRUE;
			} else if (!isxdigit(*pString)) {
				rtn = FALSE;
				break;
			}
		}

//        if (thereIsNum == FALSE) rtn = FALSE;
	}

	return rtn;
}

UINT32 GetBaseX(char *pString)
{
	UINT32 base = 0;

	if ( !isXDigit(pString) ) return base;
	if ( base != 16 ) {
		while ( pString ) {
			if (*pString == '0') {
				pString++;
				base = 8;
				if        ((toupper(*pString) == 'X') && isxdigit(pString[1])) {
					base = 16;
                } else if ((toupper(*pString) == 'U') && isxdigit(pString[1])) {
					*pString = '0';
					base = 10;
                } else if ((toupper(*pString) == 'Z') && isxdigit(pString[1])) {
					*pString = '0';
					base = 2;
				}
				break;
			} else if ((toupper(*pString) == 'X') && isxdigit(pString[1])) {
				*pString = '0';
				base = 16;
			} else if ((toupper(*pString) == 'U') && isxdigit(pString[1])) {
				*pString = '0';
				base = 10;
			} else if ((toupper(*pString) == 'Z') ) {
				*pString = '0';
				base = 2;
			} else {
				base = 16;
			}
			break;
		}

		if (base == 8) base = 16;
	}

	return base;
}
#endif

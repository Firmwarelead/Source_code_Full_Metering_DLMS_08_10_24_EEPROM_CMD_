/***********************************************************************************************************************
* DISCLAIMER
* This software is supplied by Renesas Electronics Corporation and is only intended for use with Renesas products.
* No other uses are authorized. This software is owned by Renesas Electronics Corporation and is protected under all
* applicable laws, including copyright laws. 
* THIS SOFTWARE IS PROVIDED "AS IS" AND RENESAS MAKES NO WARRANTIESREGARDING THIS SOFTWARE, WHETHER EXPRESS, IMPLIED
* OR STATUTORY, INCLUDING BUT NOT LIMITED TO WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
* NON-INFRINGEMENT.  ALL SUCH WARRANTIES ARE EXPRESSLY DISCLAIMED.TO THE MAXIMUM EXTENT PERMITTED NOT PROHIBITED BY
* LAW, NEITHER RENESAS ELECTRONICS CORPORATION NOR ANY OF ITS AFFILIATED COMPANIES SHALL BE LIABLE FOR ANY DIRECT,
* INDIRECT, SPECIAL, INCIDENTAL OR CONSEQUENTIAL DAMAGES FOR ANY REASON RELATED TO THIS SOFTWARE, EVEN IF RENESAS OR
* ITS AFFILIATES HAVE BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGES.
* Renesas reserves the right, without notice, to make changes to this software and to discontinue the availability 
* of this software. By using this software, you agree to the additional terms and conditions found by accessing the 
* following link:
* http://www.renesas.com/disclaimer
*
* Copyright (C) 2013, 2016 Renesas Electronics Corporation. All rights reserved.
***********************************************************************************************************************/

/***********************************************************************************************************************
* File Name    : r_dlms_wrapper_conversion_ip.c
* Version      : <Version>
* Device(s)    : <'RL78/I1C'>
* Tool-Chain   : <'CCRL'>
* H/W Platform : <'RL78/I1C Energy Meter Platform'>
* Description  : <Description of file>
************************************************************************************************************************
* History      : DD.MM.YYYY Version Description
***********************************************************************************************************************/

/***********************************************************************************************************************
Includes   <System Includes> , "Project Includes"
***********************************************************************************************************************/
#include "typedef.h"
#include "r_dlms_ip.h"

/***********************************************************************************************************************
Macro definitions
***********************************************************************************************************************/

/***********************************************************************************************************************
Typedef definitions
***********************************************************************************************************************/

/***********************************************************************************************************************
Imported global variables and functions (from other files)
***********************************************************************************************************************/

/***********************************************************************************************************************
Exported global variables and functions (to be accessed by other files)
***********************************************************************************************************************/

/***********************************************************************************************************************
Private global variables and functions
***********************************************************************************************************************/

void R_DLMS_ReverseBuffer(uint8_t *p_buffer, uint8_t length)
{
	uint8_t temp;
	uint8_t i, j;
	for (i = 0, j = length-1; i < j; i++, j--)
    {
        temp = *(p_buffer+i);
        *(p_buffer+i) = *(p_buffer+j);
        *(p_buffer+j) = temp;
    }
}

static int8_t R_DLMS_asciiToHex(uint8_t c)
{
    if (c >= '0' && c <= '9') {
        return c - '0';
    } else if (c >= 'a' && c <= 'f') {
        return (c - 'a') + 10;
	} else if (c >= 'A' && c <= 'F') {
		return (c - 'A') + 10;
    } else {
        return -1;
    }
}

/******************************************************************************
* Function Name : ConvertUnsignedToString
* Interface     : void ConvertUnsignedToString(
*               :     uint8_t value, uint8_t * buffer
*               : );
* Description   :
* Arguments     :
* Function Calls:
* Return Value  :
******************************************************************************/
uint8_t R_DLMS_ConvertU16ToString ( uint16_t input, uint8_t * p_buffer )
{
    uint8_t temp;
    uint8_t length = 0;

    uint8_t * p_out;
    uint8_t i, j;

    if (p_buffer == NULL)
    {
        return 0;
    }
	if (input == 0)
	{
		*p_buffer++ = '0';
		return 1;
	}

    p_out = p_buffer;
    while (input > 0)
    {
        *p_out++ = input % 10 + '0';
        input /=  10;
        length++;
    }

	R_DLMS_ReverseBuffer(p_buffer, length);

    return length;
}

/******************************************************************************
* Function Name : ConvertStringToU8
* Interface     : uint8_t ConvertStringToU8(
*               :     uint8_t *p_buffer
*               : );
* Description   :
* Arguments     :
* Function Calls:
* Return Value  :
******************************************************************************/
uint8_t R_DLMS_ConvertStringToU16 ( uint16_t *p_out, uint8_t *p_buffer)
{
	uint8_t pos;
	uint8_t pos_value;
	uint16_t temp = 0;

	if (p_buffer == NULL || p_out == NULL)
	{
		return FALSE;
	}

	pos = 0;
	while ( pos < 5 )
	{
		if ( *(p_buffer+pos) >= '0' && *(p_buffer+pos) <= '9')
		{
			temp = (temp * 10 ) + *(p_buffer+pos) - '0';
		}
		else if ((pos > 0) && 
				( *(p_buffer+pos) == '.' || *(p_buffer+pos) == ':'  || *(p_buffer+pos) == 0))
		{
			break;
		}
		else
		{
			return 0;
		}
		pos++;
	}

	*p_out = temp;

	return pos;
}

/******************************************************************************
* Function Name : R_DLMS_TwoHexCharsToByte
* Interface     : static uint8_t R_DLMS_TwoHexCharsToByte(uint8_t *two_hex_chars)
* Description   : 
* Arguments     : uint8_t * two_hex_chars:
* Function Calls: 
* Return Value  : static uint8_t
******************************************************************************/
uint8_t R_DLMS_TwoHexCharsToByte(uint8_t *p_out , uint8_t *two_hex_chars)
{
	uint8_t result = 0;

	uint8_t count = 0;
	uint8_t u8;

	if (two_hex_chars == NULL) {
		return FALSE;
	}

	while (count < 2)
	{
		u8 = *two_hex_chars++;
		result <<= 4;

		if ((u8 >= 'a') && (u8 <= 'f')) {
			result += 10 + (u8 - 'a');
		}
		else if ((u8 >= 'A') && (u8 <= 'F')) {
			result += 10 + (u8 - 'A');
		}
		else if ((u8 >= '0') && (u8 <= '9')) {
			result += u8 - '0';
		} else {
			return FALSE;
		}
		count++;
	}

	*p_out = result;

	return TRUE;
}

/******************************************************************************
* Function Name : R_DLMS_ByteToHexStr
* Interface     : static void R_DLMS_ByteToHexStr(uint8_t *buffer, uint8_t byte)
* Description   : 
* Arguments     : uint8_t * buffer:
*               : uint8_t byte    :
* Function Calls: 
* Return Value  : static void
******************************************************************************/
static uint8_t R_DLMS_ByteToHexStr(uint8_t *buffer, uint8_t byte)
{
	uint8_t count = 0;
	uint8_t u8;

	if (buffer == NULL) {
		return FALSE;
	}

	while (count < 2)
	{
		u8 = byte >> ((1 - count) * 4);
		u8 &= 0x0F;

		if (u8 >= 10) {
			*buffer++ = (u8 - 10 + 'A');
		}
		else {
			*buffer++ = u8 + '0';
		}

		count++;
	}
	return TRUE;
}


/******************************************************************************
* Function Name : R_R_DLMS_ConvertIpAddressToString
* Interface     : void R_R_DLMS_ConvertIpAddressToString(
*               :     IpAddressPtr ipaddr, uint8_t p_output
*               : );
* Description   :
* Arguments     :
* Function Calls:
* Return Value  :
******************************************************************************/
uint8_t R_DLMS_ConvertIpAddressToString ( uint8_t *p_out, uint16_t *p_out_len, IpAddressPtr ipaddr  )
{
    uint8_t i;
    uint16_t length = 0;
    uint8_t temp_len;

    if ( (p_out == NULL) ||
         (ipaddr->size != 4  && ipaddr->size != 16)	||
         (ipaddr->size == 4  && *p_out_len < 15)	||
         (ipaddr->size == 16 && *p_out_len < 47)    )
    {
        return FALSE;
    }

    for ( i = 0 ; i < ipaddr->size; i++)
    {
        if (ipaddr->size == 4)
        {
            temp_len = R_DLMS_ConvertU16ToString((uint16_t)ipaddr->p_addr[i], p_out);
        }
        else
        {
            R_DLMS_ByteToHexStr(p_out, ipaddr->p_addr[i]);
            temp_len = 2;
        }
        p_out += temp_len;
        length += temp_len;
        if (i < (ipaddr->size-1))
        {
            if (ipaddr->size == 4)
            {
                *p_out++ = '.';
                length++;
            }
            else if (i % 2 != 0 && i > 0)
            {
                *p_out++ = ':';
                length++;
            }
        }
    }
    *p_out_len = length;
    return TRUE;
}

/******************************************************************************
* Function Name : R_DLMS_ConvertStringToIpAddress
* Interface     : void R_DLMS_ConvertStringToIpAddress(
*               :     	IpAddressPtr ipaddr, uint8_t *p_buff, uint16_t length
*               : );
* Description   :
* Arguments     :
* Function Calls:
* Return Value  :
******************************************************************************/
uint8_t R_DLMS_ConvertStringToIpAddress(
	IpAddressPtr 	ipaddr,
	uint8_t			*p_buff,
	uint16_t		length
)
{
	uint8_t i, j;

	uint32_t num = 0;
	uint8_t step = 0;
	uint8_t *p_u8;
	uint16_t *p_port;
	uint8_t found = FALSE;
	uint16_t u16;
    uint8_t pos = 0;

	uint8_t temp_len;
	uint8_t * p_head = p_buff;
    uint8_t u16_ipv6[4];

    uint8_t ip6_type = FALSE;
    uint8_t dot_count = 0;
    uint8_t colon_count = 0;
    int8_t i8val;

	if (ipaddr == NULL || ipaddr->p_addr == NULL || p_buff == NULL || length < 4)
	{
		return 0;
	}

    for (i = 1 ; i < length ; i++)
    {
        if (*(p_buff+i) == '.')
        {
            dot_count++;
        }
        if (p_buff[i] == ':') {
            ip6_type = TRUE;
            if (p_buff[i-1] == ':') {
                colon_count = 14;
            } else if (colon_count) {
                colon_count -= 2;
            }
        } else if (p_buff[i] == 0) {
            break;
        }
        if (p_buff[i] == ']' || p_buff[i] == 0)
        {
            length = i;
            break;
        }
    }
    
    if (dot_count == 0  && ip6_type == FALSE)
    {
		if (length == 18 || length == 4)
		{
			length -= 2;
		}
        if ((length == 16) || (length == 4))
        {
            memcpy(ipaddr->p_addr, p_buff, length);
            ipaddr->size = length;
            p_buff += length;
            return 0xFF;
        }
        if (length == 6)
        {
            memcpy(ipaddr->p_addr, p_buff, 4);
            ipaddr->size = 4;
            p_buff += 4;
			return 0xFF;
        } 
        else
        {
            return 0;
        }
    }
	if ((dot_count >= 3) && (length < 25))
	{
		p_u8 = ipaddr->p_addr;
		for ( i = 0 ; i < 4 ; i++ )
		{
			temp_len = R_DLMS_ConvertStringToU16( &u16, p_buff);
			if ( temp_len == 0  || u16 > 0xFF)
			{
				return 0;
			}
			*p_u8++ = (uint8_t)u16;
			p_buff += temp_len;
            if (i < 3)
            {
                p_buff++;
            }
		}
		ipaddr->size = 4;
	}
	else if (ip6_type == TRUE)
	{
		p_u8 = ipaddr->p_addr;
        u16 = 0;
        memset(ipaddr->p_addr, 0 , 16);
		for ( i = 0 ; (i <= length) && (pos < 16) ; i++)
		{
            if (p_buff[i] == ':' || p_buff[i] == 0 || p_buff[i] == ']' || p_buff[i] == '/') {
                ipaddr->p_addr[pos] = u16 >> 8;
                ipaddr->p_addr[pos+1] = u16;
                u16 = 0;
                if (colon_count && i && p_buff[i-1] == ':') {
                    pos = colon_count;
                } else {
                    pos += 2;
                }
            } else {
                i8val = R_DLMS_asciiToHex(p_buff[i]);
                if (i8val == -1) {
                    return 0;
                } else {
                    u16 <<= 4;
                    u16 |= i8val;
                }
            }

			if (p_buff[i] == 0 || p_buff[i] == ']' || p_buff[i] == '/')
                break;
		}
        p_buff += i;
		ipaddr->size = 16;
	}
	return (p_buff - p_head);
}


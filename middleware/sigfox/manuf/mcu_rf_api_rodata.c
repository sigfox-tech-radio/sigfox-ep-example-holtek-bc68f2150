/*!*****************************************************************
 * \file    mcu_rf_rodata.c
 * \brief   rodata file.
 *******************************************************************
 * \copyright
 *
 * Copyright (c) 2022, UnaBiz SAS
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 *  1 Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 *  2 Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *  3 Neither the name of UnaBiz SAS nor the names of its contributors may be
 *    used to endorse or promote products derived from this software without
 *    specific prior written permission.
 *
 * NO EXPRESS OR IMPLIED LICENSES TO ANY PARTY'S PATENT RIGHTS ARE GRANTED BY
 * THIS LICENSE. THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND
 * CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A
 * PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR
 * BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER
 * IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 *******************************************************************/

#include "mcu_rf_api_rodata.h"

const MCU_RF_RODATA_t __attribute__((at(0x1E00)))  mcu_rf_rodata = {
	.id 		= {	0xFE, 0xDC, 0xBA,  0x98},
	.key 		= {	0x01, 0x23, 0x45, 0x67, 0x89, 0xAB, 0xCD, 0xEF, 0x01, 0x23, 0x45, 0x67, 0x89, 0xAB, 0xCD, 0xEF},	
	.testkey	= {	0x01, 0x23, 0x45, 0x67, 0x89, 0xAB, 0xCD, 0xEF, 0x01, 0x23, 0x45, 0x67, 0x89, 0xAB, 0xCD, 0xEF},
	.pac	 	= {	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
	.pwrTab		= {	0x26,0x26,0x26,0x26,0x26,0x26,0x26,0x26,0x26,0x26,
					0x26,0x26,0x26,0x26,0x26,0x26,0x26,0x26,0x26,0x26,
					0x26,0x26,0x26,0x26,0x26,0x26,0x26,0x26,0x26,0x26,
					0x26,0x26,0x26,0x26,0x26,0x26,0x26,
					0x66,0x66,0x66,0x66,0x66,0x66,0x66,0x66,0x66,0x66,0x66,0x66,0x66,0x66,0x66,0x66,
					0xA6,0xA6,0xA6,0xA6,0xA6,0xA6,0xA6,0xA6,0xA6,
					0xE6,0xE6,0xE6,0xE6,0xE6,0xE6,
					0x56,0x56,0x56,0x56,0x56,0x56,
					0x54,0x54,0x54,0x54,0x54, 
	                0x94,0x94,0x94,
	                0xD4,0xD4,0xD4,
	                0x92,0x92,
	                0x10,0x10,
	                0x50,
	                0x90,
	                0x06,0x06,
					0x04,
					0x02,
					0x42,
					0xC2,0xC2,
					0xC0,0xC0,
					},
	.version	= "HOLTEK BC68F2150 V1.0",
	.empty		= {0x00},			
};

const unsigned short __attribute__((at(0x1F00))) nvm[256]= {0x0000};
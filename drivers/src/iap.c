/*!*****************************************************************
 * \file    iap.c
 * \brief   In Application Programming driver.
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
 
#include "iap.h"
#include "BC68F2150.h"

IAP_status_t IAP_ew_en_proc(void) {
	_fmod0 = 0;
	_fmod1 = 1;
	_fmod2 = 1;
  	_fwpen = 1;
	_fd1l = 0x00;
  	_fd1h = 0x04;
  	_fd2l = 0x0d;
  	_fd2h = 0x09;
  	_fd3l = 0xc3;
  	_fd3h = 0x40;
  	while (_fwpen) 
  		GCC_CLRWDT();
  	if (_cfwen == 0)
  		return IAP_ERROR;
  	else
  		return IAP_SUCCESS;
}
IAP_status_t IAP_read(unsigned short add, unsigned short *flash_word, unsigned char len) {
	//Configure to read program memory and set flash memory read enable bit
	_fc0 &= 0b10001101;
	_fc0 |= 0b00110010;
  	while(len != 0) {
  		//Set address to read
  		_farh = (add >> 8) & 0x1F;
  		_farl = (add) & 0xFF;
  		_frd = 1;
  		//Wait read process completed 
  		while (_frd)
    		GCC_CLRWDT();
    	//Read lower byte	
  		*flash_word = (_fd0l & 0x00FF);
  		//Read upper byte
 		*flash_word |= ((_fd0h << 8) & 0xFF00);
 		flash_word++;
 		len --;
  		//Incr address to next 2 or 1 bytes	
  		add += 1;
  	}; 
  	//Clear read enable bit
  	_frden = 0;
	return IAP_SUCCESS;
}

IAP_status_t IAP_write(unsigned short add, unsigned short *flash_word, unsigned char len, char erase_before) {
	
	if (IAP_ew_en_proc() != IAP_SUCCESS)
		return IAP_ERROR;
	
	if (erase_before) {
  	//Erase Block
  		_farh = (add >> 8) & 0x1F;
  		_farl = (add) & 0xFF;
		_fmod0 = 1;
		_fmod1 = 0;
		_fmod2 = 0;
		_fwt = 1;
	    while (_fwt != 0);	    
	}
	
	while(len != 0) {
		_fmod0 = 0;
    	_fmod1 = 0;
   	 	_fmod2 = 0;
   	 	_fd0l = 0xFF;
	  	_fd0h = 0xFF;
		_fd1l = 0xFF;
	  	_fd1h = 0xFF;
	  	_fd2l = 0xFF;
	  	_fd2h = 0xFF;
	  	_fd3l = 0xFF;
	  	_fd3h = 0xFF;

		_fd0l = (*flash_word) & 0xFF;
		_fd0h = (*flash_word >> 8) &  0xFF;
		flash_word++;
		len--;
		if (len == 0) {
			_fwt = 1;
			while (_fwt != 0);	
			continue;
		}
		_fd1l = (*flash_word) & 0xFF;
		_fd1h = (*flash_word >> 8) &  0xFF;
		flash_word++;
		len--;
		if (len == 0) {
			_fwt = 1;
			while (_fwt != 0);	
			continue;
		}
		_fd2l = (*flash_word) & 0xFF;
		_fd2h = (*flash_word >> 8) &  0xFF;
		flash_word++;
		len--;
		if (len == 0) {
			_fwt = 1;
			while (_fwt != 0);	
			continue;
		}
		_fd3l = (*flash_word) & 0xFF;
		_fd3h = (*flash_word >> 8) &  0xFF;
		flash_word++;
		len--;
		_fwt = 1;
		while (_fwt != 0);
	}
	_cfwen = 0;
	return IAP_SUCCESS;
}

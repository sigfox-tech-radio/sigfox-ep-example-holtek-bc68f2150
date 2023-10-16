/*!*****************************************************************
 * \file    main.c
 * \brief   Main program.
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

#include "BC68F2150.h"
static const __attribute__((at(0x1D00))) unsigned char frame[12] = {0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA};
#include "sigfox_rc.h"
#include "sigfox_ep_api.h"

static void _delay_ms(unsigned short delay_ms) {
	unsigned short count_ms;
	for (count_ms=0 ; count_ms<delay_ms ; count_ms++) {
		GCC_DELAY(4000);	
	}
}


void main() {
	SIGFOX_EP_API_application_message_t SIGFOX_EP_API_application_message;
	SIGFOX_EP_API_config_t SIGFOX_EP_API_config; 
	//Watchdog
	_wdtc 	= 0b10101000;	//Disable WatchDog
	
	//Oscillator
	_rf_xo1 = 0b10000011;
	_hxtc	= 0b00000001;
	while(!_hxtf);
	_scc	= 0b00001000;	//Fh HXT
	
	//Inpout Output Port
	_pa_wake = 1;
	_pac 	= 0b11111111;
	_papu	= 0b11111111;
	_pawu   = 0b11111111;
	_pbc 	= 0b00000000;
	_pb 	= 0b00001111;
	
	_delay_ms(1000);
	_pb 	= 0b00000000;	
	SIGFOX_EP_API_config.rc = &SIGFOX_RC1;
	SIGFOX_EP_API_open(&SIGFOX_EP_API_config);
	SIGFOX_EP_API_application_message.common_parameters.t_ifu_ms = 500;
	SIGFOX_EP_API_application_message.common_parameters.tx_power_dbm_eirp = 12;
	SIGFOX_EP_API_application_message.type = SIGFOX_APPLICATION_MESSAGE_TYPE_BYTE_ARRAY;
	SIGFOX_EP_API_application_message.common_parameters.number_of_frames= 1;
	SIGFOX_EP_API_application_message.ul_payload_size_bytes = 12;
	SIGFOX_EP_API_application_message.ul_payload = frame;

	while(1) {
		// Trigger send with button.
		while (_pa1 != 0);
		_delay_ms(2000);
		SIGFOX_EP_API_open(&SIGFOX_EP_API_config);		
		SIGFOX_EP_API_send_application_message(&SIGFOX_EP_API_application_message);
		SIGFOX_EP_API_close();
	}
}

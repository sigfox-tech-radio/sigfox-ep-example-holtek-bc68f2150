/*!*****************************************************************
 * \file    rf_api.c
 * \brief   Radio drivers.
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

#include "manuf/rf_api.h"
#include "BC68F2150.h"
#include "mcu_rf_api_rodata.h"
#ifdef USE_SIGFOX_EP_FLAGS_H
#include "sigfox_ep_flags.h"
#endif
#include "sigfox_types.h"
#include "sigfox_error.h"

#if (defined ASYNCHRONOUS) || (defined BIDIRECTIONAL) || (defined ERROR_STACK)\
 || (defined REGULATORY) || (defined LOW_LEVEL_OPEN_CLOSE) || (defined RC3C)\
 || (!defined MESSAGE_COUNTER_ROLLOVER)
	#error "BC68F2150 flag ERROR"
#endif

const MCU_RF_table_const_t *const_table_ptr; 

static void _RF_power_on_sequence(void) {
	_rf_pdb = 1;
	_dir_en = 1;
	_sx_en = 1;
	//10µS
	GCC_DELAY(160);
	_rf_pdb = 0;
	_dir_en = 0;
	_sx_en = 0;	
}

RF_API_status_t RF_API_wake_up(void) {
#ifdef ERROR_CODES
    RF_API_status_t status = RF_API_SUCCESS;
#endif
	_RF_power_on_sequence();
	//Step 1 
	_rf_xo2	= 0b00100011; //discordance with datasheet but limit spectrum template
	_xclk_en = 1;
	_xclkd2 = 0;
	//Step 2
	_rf_pdb = 1;
	//Step 3
	if (_hxten == 1)
		while(!_hxtf);
	_rf_clk2= 0b00000000;
	//Step 4
	_rf_od1 = 0x00; //See datasheet for 915/868 Band
	_rf_ldo	= 0x64; //See datasheet for 915/868 Band
	_rf_dfc_cal = 0b11000000;//Set MMD to high voltage to limit spectrum template
	_xodiv2 = 0;
	_rf_tx2 = 0xC0; //Set to minimum output power
	
	RETURN();
}

/*******************************************************************/
RF_API_status_t RF_API_sleep(void) {
#ifdef ERROR_CODES
    RF_API_status_t status = RF_API_SUCCESS;
#endif
	//Step 12
	GCC_DELAY(160);
	_xclk_en = 0;
	_rf_pdb = 0;
	
	RETURN();
}
//double tmp;
/*******************************************************************/
RF_API_status_t RF_API_init(RF_API_radio_parameters_t *radio_parameters) {
#ifdef ERROR_CODES
    RF_API_status_t status = RF_API_SUCCESS;
#endif
	
	unsigned long dk;	
	//Init modulation variable
	if (radio_parameters->bit_rate_bps == 100) {
		
		_ctmc0	= 0b00101000;
		_ctmc1	= 0b11000001;
		_ctmal	= (49 & 0x00FF);
		_ctmah	= (49 >> 8) & 0xFF;
		_cton = 0;
		if ((radio_parameters->tx_power_dbm_eirp >= 12 ) && (radio_parameters->tx_power_dbm_eirp < 14 ))
			const_table_ptr = &mcu_rf_rodata.pwrtab_100bps_LP;
		else if (radio_parameters->tx_power_dbm_eirp >= 14)
			const_table_ptr = &mcu_rf_rodata.pwrtab_100bps_HP;
	} else {
		_ctmc0	= 0b00011000;
		_ctmc1	= 0b11000001;
		_ctmal	= (605 & 0x00FF);
		_ctmah	= (605 >> 8) & 0xFF;
		_cton = 0;
		const_table_ptr = &mcu_rf_rodata.pwrtab_600bps_LP;
	}
	//Step 4-2 (Compute frequency)	
	_rf_sx1 = radio_parameters->frequency_hz / 16000000;
	//tmp = (((double)radio_parameters->frequency_hz / 16000000.0) - _rf_sx1);
	dk =(unsigned long)((((double)radio_parameters->frequency_hz / 16000000.0) - _rf_sx1) * 1048576.0);
	_rf_sx2 = (dk) & 0xFF;		
	_rf_sx3 = (dk >> 8) & 0xFF;	
	_rf_sx4 = (dk >> 16) & 0xFF;
	//Step 5
	_acal_en = 1;		//Start cal
	while(_acal_en);	//Wait end of cal
	//Step 6 
	_dtxd = 1; 			//Load first bit
	//Step 7
	_dir_en = 1;		//Direct mode
	_fsk_en	= 0;		//OOK mode
	//Step 8	
	_sx_en = 1;
	GCC_DELAY(160);
	//Step 9
	_tx_en = 1;

	RETURN();
}

/*******************************************************************/
RF_API_status_t RF_API_de_init(void) {
#ifdef ERROR_CODES
    RF_API_status_t status = RF_API_SUCCESS;
#endif
    //In case of Continous Wave, reset PA configuration and turn off LED
    _pb3 = 0;
    _rf_tx2 = 0xC0;
	//Step 11
	_dtxd = 0;
	_tx_en = 0;
	GCC_DELAY(16);
	_sx_en = 0;

	RETURN();
}

/*******************************************************************/
RF_API_status_t RF_API_send(RF_API_tx_data_t *tx_data) {
#ifdef ERROR_CODES
    RF_API_status_t status = RF_API_SUCCESS;
#endif
	unsigned char flipflop = 0;
	unsigned char sample_cnt = 0;
	unsigned char bitCnt = 0x00;
	unsigned char byteCnt = 0x00;	
	unsigned long dk = 0x00000000;
	unsigned short deltaf;

	deltaf = const_table_ptr->delta_f;
	dk |= _rf_sx4;
	dk = dk << 8;
	dk |= _rf_sx3;
	dk = dk << 8;
	dk |= _rf_sx2;
	//Step 10	
	_cton = 1;
	_ctmaf = 0;
	//RampUP
	for(sample_cnt = 0; sample_cnt < (const_table_ptr->size * 2); sample_cnt++) {
		_pb3 = ~_pb3;
		
		if (sample_cnt < const_table_ptr->size) { 
			_rf_tx2 = const_table_ptr->tab[((const_table_ptr->size - 1) - sample_cnt)];
		} else {
			_rf_tx2 = const_table_ptr->tab[0];
		}
		while(_ctmaf != 1);
		_ctmaf = 0;
	}
	//Data
	for (byteCnt = 0; byteCnt < tx_data->bitstream_size_bytes; byteCnt++) { 
		for (bitCnt = 0; bitCnt < 8; bitCnt++) {
			for(sample_cnt = 0; sample_cnt < (const_table_ptr->size * 2); sample_cnt++) {
				_pb3 = ~_pb3;
				while(_ctmaf != 1);
				_ctmaf = 0;
				if ((tx_data->bitstream[byteCnt] & (0x80 >> bitCnt) ) == 0x00) {
					if (sample_cnt < (const_table_ptr->size - 1)) { //Table Up
						_rf_tx2= const_table_ptr->tab[sample_cnt];
					//	_dtxd = 1;
						_rf_sx4 = (dk >> 16) & 0xFF;	//DK[2]
						_rf_sx3 = (dk >> 8) & 0xFF;	//DK[1]
						_rf_sx2 = (dk) & 0xFF;		//DK[0]
						
					} else if (sample_cnt == (const_table_ptr->size - 1)) { //Table change frequency +/-10khz =>656
						_rf_tx2 = const_table_ptr->tab[sample_cnt]; 
					//	_dtxd = 0;

						if (flipflop == 1) { //Negative frequency
							_rf_sx4 = ((dk - deltaf) >> 16) & 0xFF;	//DK[2]
							_rf_sx3 = ((dk - deltaf) >> 8) & 0xFF;	//DK[1]
							_rf_sx2 = (dk - deltaf) & 0xFF;			//DK[0]
							flipflop = 0;
						} else {			//Positive frequency
							_rf_sx4 = ((dk + deltaf) >> 16) & 0xFF;	//DK[2]
							_rf_sx3 = ((dk + deltaf) >> 8) & 0xFF;	//DK[1]
							_rf_sx2 = (dk + deltaf) & 0xFF;			//DK[0]
							flipflop = 1;
						}
					} else{	//Table Down
						_rf_tx2 = const_table_ptr->tab[const_table_ptr->size - (sample_cnt - (const_table_ptr->size - 1))];
					//	_dtxd = 1;
						_rf_sx4 = (dk >> 16) & 0xFF;	//DK[2]
						_rf_sx3 = (dk >> 8) & 0xFF;	//DK[1]
						_rf_sx2 = (dk) & 0xFF;		//DK[0]
					}
				}	
			}
		}
	}
	//RampDown
	for(sample_cnt = 0; sample_cnt < (const_table_ptr->size * 2); sample_cnt++) {
		_pb3 = ~_pb3;
		while(_ctmaf != 1);
		_ctmaf = 0;
		
		if (sample_cnt < const_table_ptr->size) { 
			_rf_tx2 = const_table_ptr->tab[0];
		} else {
			_rf_tx2 = const_table_ptr->tab[sample_cnt - const_table_ptr->size];
		}
	}
	_pb3 = 0;
	while(_ctmaf != 1);
	_ctmaf = 0;
	_cton = 0;
	
	RETURN();
}

#if (defined TIMER_REQUIRED) && (defined LATENCY_COMPENSATION)
/*******************************************************************/
RF_API_status_t RF_API_get_latency(RF_API_latency_t latency_type, sfx_u32 *latency_ms) {
#ifdef ERROR_CODES
    RF_API_status_t status = RF_API_SUCCESS;
#endif

	RETURN();
}
#endif

#ifdef CERTIFICATION
/*******************************************************************/
RF_API_status_t RF_API_start_continuous_wave(void) {
#ifdef ERROR_CODES
	RF_API_status_t status = RF_API_SUCCESS;
#endif
    //Turn on LED and set PA according to the define table
    _pb3 = 1;
    _rf_tx2 = const_table_ptr->tab[0];
	RETURN();
}
#endif

#ifdef VERBOSE
/*******************************************************************/
RF_API_status_t RF_API_get_version(sfx_u8 **version, sfx_u8 *version_size_char) {
#ifdef ERROR_CODES
    RF_API_status_t status = RF_API_SUCCESS;
#endif

	RETURN();
}
#endif

#ifdef ERROR_CODES
/*******************************************************************/
void RF_API_error(void) {
	/* To be implemented by the device manufacturer */
}
#endif

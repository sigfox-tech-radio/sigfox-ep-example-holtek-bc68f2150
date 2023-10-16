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

#include "manuf/mcu_api.h"
#include "sigfox_types.h"
#include "sigfox_error.h"
#include "mcu_rf_api_rodata.h"
#include "TI_aes_128_encr_only.h"
#include "BC68F2150.h"
#include "iap.h"

#ifdef TIMER_REQUIRED
MCU_API_status_t MCU_API_timer_start(MCU_API_timer_t *timer) {
#ifdef ERROR_CODES
    MCU_API_status_t status = MCU_API_SUCCESS;
#endif
	unsigned short i;
	
	for(i = 0; i < timer->duration_ms; i++) {
		GCC_DELAY(4000);
	}
	
	RETURN();
}
#endif

#ifdef TIMER_REQUIRED
MCU_API_status_t MCU_API_timer_stop(MCU_API_timer_instance_t timer_instance) {
#ifdef ERROR_CODES
    MCU_API_status_t status = MCU_API_SUCCESS;
#endif
	
	RETURN();
}
#endif

#if (defined TIMER_REQUIRED) && !(defined ASYNCHRONOUS)
MCU_API_status_t MCU_API_timer_status(MCU_API_timer_instance_t timer_instance, sfx_bool *timer_has_elapsed) {
#ifdef ERROR_CODES
    MCU_API_status_t status = MCU_API_SUCCESS;
#endif

	RETURN();
}
#endif

#if (defined TIMER_REQUIRED) && !(defined ASYNCHRONOUS)
MCU_API_status_t MCU_API_timer_wait_cplt(MCU_API_timer_instance_t timer_instance) {
#ifdef ERROR_CODES
    MCU_API_status_t status = MCU_API_SUCCESS;
#endif

	RETURN();
}
#endif

MCU_API_status_t MCU_API_aes_128_cbc_encrypt(MCU_API_encryption_data_t *aes_data) {
#ifdef ERROR_CODES
    MCU_API_status_t status = MCU_API_SUCCESS;
#endif

#ifdef PUBLIC_KEY_CAPABLE
    if (aes_data->key == SIGFOX_EP_KEY_PRIVATE) {
        aes_encrypt(aes_data->data, (sfx_u8 *)mcu_rf_rodata.key);
    } else if ((aes_data->key == SIGFOX_EP_KEY_PUBLIC)) {
        aes_encrypt(aes_data->data, (sfx_u8 *)SIGFOX_EP_PUBLIC_KEY);
    }
#else
    aes_encrypt(aes_data->data, (sfx_u8 *) mcu_rf_rodata.key);
#endif

	RETURN();
}

MCU_API_status_t MCU_API_get_ep_id(sfx_u8 *ep_id, sfx_u8 ep_id_size_bytes) {
#ifdef ERROR_CODES
    MCU_API_status_t status = MCU_API_SUCCESS;
#endif
	
	IAP_read(0x1E00, (unsigned short*)ep_id, ep_id_size_bytes / 2);

	RETURN();
}

MCU_API_status_t MCU_API_get_nvm(sfx_u8 *nvm_data, sfx_u8 nvm_data_size_bytes) {
#ifdef ERROR_CODES
    MCU_API_status_t status = MCU_API_SUCCESS;
#endif
	IAP_read(0x1F00, (unsigned short*)nvm_data, nvm_data_size_bytes / 2);
	
	RETURN();
}

MCU_API_status_t MCU_API_set_nvm(sfx_u8 *nvm_data, sfx_u8 nvm_data_size_bytes) {
#ifdef ERROR_CODES
    MCU_API_status_t status = MCU_API_SUCCESS;
#endif
	IAP_write(0x1F00, (unsigned short*)nvm_data, nvm_data_size_bytes / 2, 1);
	
	RETURN();
}

#ifdef VERBOSE
MCU_API_status_t MCU_API_get_initial_pac(sfx_u8 *initial_pac, sfx_u8 initial_pac_size_bytes) {
#ifdef ERROR_CODES
    MCU_API_status_t status = MCU_API_SUCCESS;
#endif

	RETURN();
}
#endif

#ifdef VERBOSE
MCU_API_status_t MCU_API_get_version(sfx_u8 **version, sfx_u8 *version_size_char) {
#ifdef ERROR_CODES
    MCU_API_status_t status = MCU_API_SUCCESS;
#endif

	/* To be implemented by the device manufacturer */
    (*version) = (sfx_u8*) mcu_rf_rodata.version;
    (*version_size_char) = (sfx_u8) sizeof(mcu_rf_rodata.version);
    
    RETURN();
}
#endif

#ifdef ERROR_CODES
/*******************************************************************/
void MCU_API_error(void) {
	/* To be implemented by the device manufacturer */
}
#endif
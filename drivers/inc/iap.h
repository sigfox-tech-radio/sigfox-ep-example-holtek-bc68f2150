/*!*****************************************************************
 * \file    iap.h
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

#ifndef __IAP_H__
#define __IAP_H__

/*** IAP structures ***/

/*!******************************************************************
 * \enum IAP_status_t
 * \brief In Application Programming error codes.
 *******************************************************************/
typedef enum {
	IAP_SUCCESS = 0,
	IAP_ERROR 	= 1,
} IAP_status_t;

/*!******************************************************************
 * \fn IAP_status_t IAP_ew_en_proc(void)
 * \brief In Application Programming erase write enable procedure.
 * \param[in]  	none
 * \param[out] 	none
 * \retval		Function execution status.
 *******************************************************************/
IAP_status_t IAP_ew_en_proc(void);

/*!******************************************************************
 * \fn IAP_status_t IAP_read(unsigned short add, unsigned short *flash_word, unsigned char len)
 * \brief In Application Programming read procedure.
 * \param[in]  	add:Address to read data
 * \param[out] 	*flash_word:Reading data pointer
 * \param[in] 	len:Size to read
 * \retval		Function execution status.
 *******************************************************************/
IAP_status_t IAP_read(unsigned short add, unsigned short *flash_word, unsigned char len);

/*!******************************************************************
 * \fn IAP_status_t IAP_write(unsigned short add, unsigned short *flash_word, unsigned char len, char erase_before)
 * \brief In Application Programming write procedure(warning the IAP drivers support only write data bloc of 4 word or 8 bytes).
 * \param[in]  	add:Address to write data
 * \param[out] 	*flash_word:Writing data pointer
 * \param[in] 	len:Size to write
 * \param[in] 	erase_before:Erase page or not before
 * \retval		Function execution status.
 *******************************************************************/
IAP_status_t IAP_write(unsigned short add, unsigned short *flash_word, unsigned char len, char erase_before);

#endif /* __IAP_H__ */

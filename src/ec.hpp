/* SPDX-License-Identifier: ISC */
/**
 * Copyright (c) 2020 Abderraouf Adjal <abderraouf.adjal@gmail.com>
 *
 * Permission to use, copy, modify, and distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */

#ifndef EC_H
#define EC_H


#ifdef EC_BK_CONF
# error "EC_BK_CONF macro was defined"
#endif /* EC_BK_CONF */

#define EC_DBG DEBUGV

/* CONSTANTS */
#define EC_BK_ESP8266_ARD_LFS_NATIVE   0x10
/* NOTE: SPIFFS since ESP8266 Arduino core v2.7.1 is DEPRECATED. */
#define EC_BK_ESP8266_ARD_SPIFFS_NATIVE   0x11

//#define EC_BK_ESP8266_ARD_LFS_JSON    0x12 /* TODO */
//#define EC_BK_ESP8266_ARD_SPIFFS_JSON    0x13 /* TODO */
//#define EC_BK_ESP8266_ARD_EEPROM_JSON 0x14 /* TODO */

//#define EC_BK_ESP32_ARD_FFAT_NATIVE    0x20 /* TODO */
//#define EC_BK_ESP32_ARD_FFAT_JSON    0x21 /* TODO */


/* EC_BK_CONF: Define what backend to use. */
/* CONFIG EC_BK_CONF: */
#include "../config_bk.hpp"

#if EC_BK_CONF == EC_BK_ESP8266_ARD_LFS_NATIVE
# include "../backends/esp8266_ard_fs_native.hpp"
#elif EC_BK_CONF == EC_BK_ESP8266_ARD_SPIFFS_NATIVE /* DEPRECATED. */
# include "../backends/esp8266_ard_fs_native.hpp"
#else 
# error "Use valid EC_BK_CONF macro"
#endif /* EC_BK_CONF */


#endif /* EC_H */

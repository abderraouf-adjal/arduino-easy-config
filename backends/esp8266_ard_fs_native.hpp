/* SPDX-License-Identifier: ISC */
/**
 * Copyright (c) 2020 Abderraouf Adjal <abderraouf.adjal@gmail.com>
 *
 * Permission to use, copy, modify, and/or distribute this software for any
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

#ifndef EC_BK_H
#define EC_BK_H


#ifndef EC_BK_CONF
# error "Must define valid EC_BK_CONF macro"
#endif /* EC_BK_CONF */

/* This backend is for ESP8266 SoC using Arduino core. */
#if (! defined(ESP8266)) || (! defined(ARDUINO_ARCH_ESP8266))
# error "This EC_ backend is for ESP8266"
#endif /* ESP8266 */

#if EC_BK_CONF == EC_BK_ESP8266_ARD_LFS_NATIVE
# include <LittleFS.h>
# define EC_FS_IMPL LittleFS
# define EC_FS_IMPL_NAME_MAX LFS_NAME_MAX
#elif EC_BK_CONF == EC_BK_ESP8266_ARD_SPIFFS_NATIVE
/* NOTE: SPIFFS in 'ESP8266 Arduino core' is DEPRECATED since v2.7.1. */
/* NOTE: No such thing as directories on SPIFFS. */
# include <FSImpl.h>
# include <spiffs/spiffs_config.h>
# define EC_FS_IMPL SPIFFS
# define EC_FS_IMPL_NAME_MAX SPIFFS_OBJ_NAME_LEN
#else 
# error "Use valid EC_BK_CONF macro"
#endif /* EC_BK_CONF */


#ifndef EC_DB_LOC
# define EC_DB_LOC "/_c" /* Consider the FS implementation limits. */
#endif


#include "generic.hpp"


#endif /* EC_BK_H */

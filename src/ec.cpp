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


#include "ec.hpp"

#if EC_BK_CONF == EC_BK_ESP8266_ARD_LFS_NATIVE
# include "../backends/esp8266_ard_fs_native.cpp"
#elif EC_BK_CONF == EC_BK_ESP8266_ARD_SPIFFS_NATIVE
# include "../backends/esp8266_ard_fs_native.cpp"
#else 
# error "Must define valid EC_BK_CONF macro"
#endif /* EC_BK_CONF */

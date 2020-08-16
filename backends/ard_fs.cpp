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

#ifndef EC_ARD_FS
#define EC_ARD_FS


/******************************************************************************/
/********************************** STORAGE ***********************************/
/******************************************************************************/
/** _ec_FS_pathValid()
 * Check if FS path is valid for EC_.
 * Return: `true` if valid, `false` if not.
 */
inline bool
_ec_FS_pathValid(const char* path)
{
    if ((! path)
        || (path[0] != '/')
        || (strnlen(path, EC_FS_IMPL_NAME_MAX) >= EC_FS_IMPL_NAME_MAX)) {
        return false; /* No starting slash, or too long. */
    }
    return true;
}

bool
ec_storage_mount(void)
{
    if (! EC_FS_IMPL.begin()) {
        EC_DBG("Unable to mount FS.\n");
        return false;
    }
    return true;
}

void
ec_storage_unmount(void)
{
    EC_FS_IMPL.end();
}

bool
ec_storage_format(bool safe)
{
    if (safe) {
        if (ec_storage_mount()) {
            EC_DBG("Existing mountable FS, no format.\n");
            ec_storage_unmount();
            return true;
        }
    }
    EC_DBG("Trying to format storage...\n");
    if (! EC_FS_IMPL.format()) {
        EC_DBG("Unable to format FS.\n");
        return false;
    }
    if (! ec_storage_mount()) {
        EC_DBG("Unable to mount FS.\n");
        return false;
    }
    ec_storage_unmount();
    EC_DBG("Succeed: FS formated.\n");
    return true;
}
bool
ec_storage_format(void)
{
    return ec_storage_format(true); /* safe=true */
}


#endif /* EC_ARD_FS */

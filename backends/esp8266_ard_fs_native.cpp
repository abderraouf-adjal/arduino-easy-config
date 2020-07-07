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

#ifndef EC_BK
#define EC_BK


#include "esp8266_ard_fs_native.hpp"

/******************************************************************************/
/********************************** STORAGE ***********************************/
/******************************************************************************/
#include "ard_fs.cpp"


/******************************************************************************/
/************************************ DB **************************************/
/******************************************************************************/

bool
ec_db_init(void)
{
    if (EC_FS_IMPL.exists(EC_DB_LOC)) {
        EC_DBG("ec_db_init: WARNING: Existing EC_DB_LOC.\n");
        return true;
    }
#if EC_BK_CONF == EC_BK_ESP8266_ARD_LFS_NATIVE
    if (! EC_FS_IMPL.mkdir(EC_DB_LOC)) {
        EC_DBG("ec_db_init: Could not create EC_DB_LOC or not mounted FS.\n");
        return false;
    }
#endif /* EC_BK_CONF */
    return true;
}

bool
ec_db_is_ready(void)
{
    if (! ec_storage_mount()) {
        EC_DBG("ec_db_is_ready: Unable to mount FS.\n");
        return false;
    }
#if EC_BK_CONF == EC_BK_ESP8266_ARD_LFS_NATIVE
    if (! EC_FS_IMPL.exists(EC_DB_LOC)) {
        EC_DBG("ec_db_is_ready: DB is not initialized.\n");
        return false;
    }
#endif /* EC_BK_CONF */
    EC_DBG("ec_db_is_ready: ec_db_is_ready == true.\n");
    return true;
}

/* Functions for one item managment. */
bool
ec_db_add(const char* item)
{
    int l;
    char item_fullpath[EC_FS_IMPL_NAME_MAX];
    File file;
    
#if EC_BK_CONF == EC_BK_ESP8266_ARD_LFS_NATIVE
    if (! EC_FS_IMPL.exists(EC_DB_LOC)) {
        EC_DBG("ec_db_add: Nonexistent path or not mounted FS.\n");
        return false;
    }
#endif /* EC_BK_CONF */
    l = snprintf(item_fullpath, sizeof(item_fullpath),
                 "%s/%s", EC_DB_LOC, item);
    if ((l < 0) || (! _ec_FS_pathValid(item_fullpath))) {
        EC_DBG("ec_db_add: Invalid FS fullpath.\n");
        return false;
    }
    if (EC_FS_IMPL.exists(item_fullpath)) {
        EC_DBG("ec_db_add: Existing item path in FS.\n");
        return true;
    }
    file = EC_FS_IMPL.open(item_fullpath, "w");
    if (! file) {
        EC_DBG("ec_db_add: Make item_fullpath in FS fail.\n");
        file.close();
        return false;
    }
    file.close();
    return true;
}

bool
ec_db_remove(const char* item)
{
    int l;
    char item_fullpath[EC_FS_IMPL_NAME_MAX];
    File file;
    
#if EC_BK_CONF == EC_BK_ESP8266_ARD_LFS_NATIVE
    if (! EC_FS_IMPL.exists(EC_DB_LOC)) {
        EC_DBG("ec_db_remove: Nonexistent path or not mounted FS.\n");
        return false;
    }
#endif /* EC_BK_CONF */
    l = snprintf(item_fullpath, sizeof(item_fullpath),
                 "%s/%s", EC_DB_LOC, item);
    if ((l < 0) || (! _ec_FS_pathValid(item_fullpath))) {
        EC_DBG("ec_db_remove: Invalid FS fullpath.\n");
        return false;
    }
    if (! EC_FS_IMPL.exists(item_fullpath)) {
        EC_DBG("ec_db_remove: Nonexistent item path in FS.\n");
        return true;
    }
    if (! EC_FS_IMPL.remove(item_fullpath)) {
        EC_DBG("ec_db_remove: Remove item_fullpath error.\n");
        return false;
    }
    return true;
}

ssize_t
ec_db_size(const char* item)
{
    int l;
    size_t data_len;
    char item_fullpath[EC_FS_IMPL_NAME_MAX];
    File file;
    
#if EC_BK_CONF == EC_BK_ESP8266_ARD_LFS_NATIVE
    if (! EC_FS_IMPL.exists(EC_DB_LOC)) {
        EC_DBG("ec_db_size: Nonexistent path or not mounted FS.\n");
        return -1;
    }
#endif /* EC_BK_CONF */
    l = snprintf(item_fullpath, sizeof(item_fullpath),
                 "%s/%s", EC_DB_LOC, item);
    if ((l < 0) || (! _ec_FS_pathValid(item_fullpath))) {
        EC_DBG("ec_db_size: Invalid FS fullpath.\n");
        return -2;
    }
    if (! EC_FS_IMPL.exists(item_fullpath)) {
        EC_DBG("ec_db_size: Nonexistent item path in FS.\n");
        return -3;
    }
    file = EC_FS_IMPL.open(item_fullpath, "r");
    if (! file) {
        EC_DBG("ec_db_size: Open (r) item_fullpath in FS fail.\n");
        file.close();
        return -4;
    }
    data_len = file.size();
    file.close();
    return data_len;
}

ssize_t
ec_db_read(const char* item, uint8_t* buf, size_t buf_lenmax)
{
    int l;
    size_t data_len;
    char item_fullpath[EC_FS_IMPL_NAME_MAX];
    File file;
    
#if EC_BK_CONF == EC_BK_ESP8266_ARD_LFS_NATIVE
    if (! EC_FS_IMPL.exists(EC_DB_LOC)) {
        EC_DBG("ec_db_read: Nonexistent path or not mounted FS.\n");
        return -1;
    }
#endif /* EC_BK_CONF */
    l = snprintf(item_fullpath, sizeof(item_fullpath),
                 "%s/%s", EC_DB_LOC, item);
    if ((l < 0) || (! _ec_FS_pathValid(item_fullpath))) {
        EC_DBG("ec_db_read: Invalid FS fullpath.\n");
        return -2;
    }
    if (! EC_FS_IMPL.exists(item_fullpath)) {
        EC_DBG("ec_db_read: Nonexistent item path in FS.\n");
        return -3;
    }
    file = EC_FS_IMPL.open(item_fullpath, "r");
    if (! file) {
        EC_DBG("ec_db_read: Open (r) item_fullpath in FS fail.\n");
        file.close();
        return -4;
    }
    if (file.size() == 0) {
        file.close();
        return 0; /* Empty file. */
    } else if (file.position() != 0) {
        if (! file.seek(0, SeekSet)) {
            EC_DBG("ec_db_read: Zero FS seek() error.\n");
            file.close();
            return -5;
        }
    }
    data_len = file.read(buf, buf_lenmax);
    if (data_len == 0) {
        EC_DBG("ec_db_read: Read from item_fullpath in FS fail.\n");
        file.close();
        return -6;
    }
    file.close();
    return data_len;
}

ssize_t
ec_db_write(const char* item,
              const uint8_t* buf, size_t buf_len)
{
    int l;
    size_t data_len;
    char item_fullpath[EC_FS_IMPL_NAME_MAX];
    File file;
    
#if EC_BK_CONF == EC_BK_ESP8266_ARD_LFS_NATIVE
    if (! EC_FS_IMPL.exists(EC_DB_LOC)) {
        EC_DBG("ec_db_write: Nonexistent path or not mounted FS.\n");
        return -1;
    }
#endif /* EC_BK_CONF */
    l = snprintf(item_fullpath, sizeof(item_fullpath),
                 "%s/%s", EC_DB_LOC, item);
    if ((l < 0) || (! _ec_FS_pathValid(item_fullpath))) {
        EC_DBG("ec_db_write: Invalid FS fullpath.\n");
        return -2;
    }
    if (! EC_FS_IMPL.exists(item_fullpath)) {
        EC_DBG("ec_db_write: Nonexistent item path in FS.\n");
        return -3;
    }
    /* Open in "w" mode will truncate(0) (remove file content). */
    file = EC_FS_IMPL.open(item_fullpath, "w");
    if (! file) {
        EC_DBG("ec_db_write: Open (w) item_fullpath in FS fail.\n");
        file.close();
        return -4;
    }
    data_len = file.write(buf, buf_len);
    if (data_len != buf_len) {
        EC_DBG("ec_db_write: Write to item_fullpath in FS fail.\n");
        file.close();
        return -5;
    }
    file.close();
    return data_len;
}

bool
ec_db_memzero(const char* item)
{
    int l;
    size_t fsz;
    char item_fullpath[EC_FS_IMPL_NAME_MAX];
    File file;
    
#if EC_BK_CONF == EC_BK_ESP8266_ARD_LFS_NATIVE
    if (! EC_FS_IMPL.exists(EC_DB_LOC)) {
        EC_DBG("ec_db_memzero: Nonexistent path or not mounted FS.\n");
        return false;
    }
#endif /* EC_BK_CONF */
    l = snprintf(item_fullpath, sizeof(item_fullpath),
                 "%s/%s", EC_DB_LOC, item);
    if ((l < 0) || (! _ec_FS_pathValid(item_fullpath))) {
        EC_DBG("ec_db_memzero: Invalid FS fullpath.\n");
        return false;
    }
    if (! EC_FS_IMPL.exists(item_fullpath)) {
        EC_DBG("ec_db_memzero: Nonexistent item path in FS.\n");
        return false;
    }
    /* Open in "w" mode will truncate(0) (remove file content). */
    file = EC_FS_IMPL.open(item_fullpath, "r+");
    if (! file) {
        EC_DBG("ec_db_memzero: Open (r+) item_fullpath in FS fail.\n");
        file.close();
        return false;
    }
    fsz = file.size();
    if (fsz == 0) {
        EC_DBG("ec_db_memzero: Item size is 0.\n");
        file.close(); /* Nothing todo. */
        return true;
    }
    if (file.position() != 0) {
         EC_DBG("ec_db_memzero: Item FS CUR position != 0.\n");
        if (! file.seek(0, SeekSet)) {
            EC_DBG("Zero FS seek() error.\n");
            file.close();
            return false;
        }
    }
    /* Zero the file content. */
    for (size_t i = 0; i < fsz; i++) {
        if (file.write(0x00) != 1) {
            EC_DBG("ec_db_memzero: Zero FS file write() error.\n");
            file.close();
            return false;
        }
    }
    //file.flush();
    file.close();
    return true;
}


#endif /* EC_BK */

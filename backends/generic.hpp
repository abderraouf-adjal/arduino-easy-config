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

#ifndef EC_GENERIC_H
#define EC_GENERIC_H


#ifndef EC_BK_CONF
# error "Must define valid EC_BK_CONF macro"
#endif /* EC_BK_CONF */

/******************************************************************************/
/********************************** STORAGE ***********************************/
/******************************************************************************/

/** ec_storage_mount()
 * Open (mount) the storage/file-system.
 * Return: `true` if succeed, `false` if fail.
 */
bool
ec_storage_mount(void);

/** ec_storage_unmount()
 * Unmount (close) the storage/file-system.
 */
void
ec_storage_unmount(void);

/** ec_storage_format()
 * Create a storage envirement for EC_ system.
 * For this backend, "LittleFS" will be used to manage data,
 * and it will overwrite the storage with zeros.
 * Return: `true` if succeed, `false` if fail.
 */
bool
ec_storage_format(bool safe);
bool
ec_storage_format(void);


/******************************************************************************/
/************************************ DB **************************************/
/******************************************************************************/

/** ec_db_init()
 * Make EC_ database in a well formated storage system,
 * this backend create a file for each item (FS as DB).
 * Storage FS must be mounted.
 * Return: `true` if succeed formating
 *          or mountable FS while `safe==True`, `false` if fail.
 */
bool
ec_db_init(void);

/** ec_db_is_ready()
 * Check if the storage is formated and mountable, and if the DB is initialized.
 * Return: `true` if formating and DB init done before, `false` if not.
 */
bool
ec_db_is_ready(void);

/* Functions for single item managment */
/** ec_db_add()
 * Add a new item in EC_ database.
 * Storage FS must be mounted.
 * Return: `true` if succeed, `false` if fail.
 */
bool
ec_db_add(const char* item);

/** ec_db_remove()
 * Remove an item in EC_ database.
 * Storage FS must be mounted.
 * Return: `true` if succeed or already existing, `false` if fail.
 */
bool
ec_db_remove(const char* item);

/** ec_db_size()
 * Get an item size in EC_ database.
 * Storage FS must be mounted.
 * Return: Length if succeed or already non-existing,
 *         and negative value if fail.
 */
ssize_t
ec_db_size(const char* item);

/** ec_db_read()
 * Read an item `buf_lenmax` bytes in EC_ database.
 * Storage FS must be mounted.
 * Return: Read length if succeed, and negative value if fail.
 */
ssize_t
ec_db_read(const char* item,
            uint8_t* buf, size_t buf_lenmax);

/** ec_db_write()
 * Write to an item `buf_len` bytes in EC_ database.
 * Storage FS must be mounted.
 * Return: Write length if succeed, and negative value if fail.
 */
ssize_t
ec_db_write(const char* item,
              const uint8_t* buf, size_t buf_len);

/** ec_db_memzero()
 * Overwrite an item content (but not its metadata) with 0x00.
 * Storage FS must be mounted.
 * Return: `true` if succeed, `false` if fail.
 */
bool
ec_db_memzero(const char* item);


#endif /* EC_GENERIC_H */

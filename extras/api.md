# Arduino easy-config library (EC) library API
C-style API **ec_\***, **EC_\***.

---

## Constants to notice
- EC_BK_CONF
  - EC_BK_ESP8266_ARD_LFS_NATIVE
  - EC_BK_ESP8266_ARD_SPIFFS_NATIVE
- EC_FS_IMPL
- EC_FS_IMPL_NAME_MAX
- EC_DB_LOC

---

## Storage
- `bool ec_storage_format()`
- `bool ec_storage_mount()`
- `void ec_storage_unmount()`
  
- `bool ec_db_init()`
- `bool ec_db_is_ready()`
  
- `bool ec_db_add()`
- `bool ec_db_remove()`
- `ssize_t ec_db_size()`
- `ssize_t ec_db_read()`
- `ssize_t ec_db_write()`
- `bool ec_db_memzero()`

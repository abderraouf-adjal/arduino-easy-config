# OpenBootArguments (OBA) library API
C-style API **oba_\***, **OBA_\***.

---

## Constants
- OBA_BK_CONF
  - OBA_BK_ESP8266_ARD_LFS_NATIVE
  - OBA_BK_ESP8266_ARD_SPIFFS_NATIVE
- OBA_FS_IMPL
- OBA_FS_IMPL_NAME_MAX
- OBA_DB_LOC

---

## Storage
- `bool oba_storage_format()`
- `bool oba_storage_mount()`
- `void oba_storage_unmount()`
  
- `bool oba_db_init()`
- `bool oba_db_is_ready()`
  
- `bool oba_db_add()`
- `bool oba_db_remove()`
- `ssize_t oba_db_size()`
- `ssize_t oba_db_read()`
- `ssize_t oba_db_write()`
- `bool oba_db_memzero()`

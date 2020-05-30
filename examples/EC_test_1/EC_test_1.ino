/* The used backend can be configured by `EC_BK_CONF` inside <ec.hpp> */
#include <ec.hpp>

#define item_1 "item_1"
const uint8_t content_0[5] = {0x00, 0x00, 0x00, 0x00, 0x00};
const uint8_t content_1[5] = {'T', 'E', 'S', 'T', '1'};

void setup() {
  uint8_t* buf;
  volatile ssize_t sz, sz_r;
  
  Serial.begin(115200);
  Serial.print("\n\n\n");
  Serial.println("EC TEST 01");

  // if ec_db_is_ready()==true, storage will be mounted,
  // if not, make storage and/or DB ready to use.
  while (! ec_db_is_ready()) {
    Serial.println("Warning: ec_db_is_ready() == false");
    // Try to mount storage
    while (! ec_storage_mount()) {
      // If FS isn't formated (Can not be mounted), format it.
      // safe==true => Format only if FS can not be mounted.
      if (! ec_storage_format(true)) {
        Serial.println("Error: ec_storage_format().");
      }
      delay(1000);
      yield();
    }
    // FS mounted, Get ODF DB ready (initialized)
    while (! ec_db_init()) {
      Serial.println("Error: ec_db_init().");
      delay(1000);
      yield();
    }
    delay(1000);
  }


  // Add an empty item in DB
  if (! ec_db_add(item_1)) {
    Serial.println("Error: ec_db_add().");
  }

  
  // Write content in an item
  // ec_db_write() Return: Write length if succeed, and negative value if fail.
  if (ec_db_write(item_1, (const uint8_t*)content_1, sizeof(content_1)) < 0) {
    Serial.println("Error: ec_db_write().");
  }

  
  // Get an item size then alloc buffer for its content
  sz = ec_db_size(item_1);
  buf = new uint8_t[sz <= 4096 ? sz : 4096];

  
  // Read all item content with a max size limit
  // ec_db_read() Return: Read length if succeed, and negative value if fail.
  sz_r = ec_db_read(item_1, buf, sz);
  // Compare the data with content_1...
  if ((sz_r != sz) || memcmp((const uint8_t*)content_1, (const uint8_t*)buf, sz)) {
    Serial.println("Error: ec_db_read(): data is invalid.");
  } else {
    Serial.println("ec_db_read(): All Okay.");
  }
  

  // Replace item_1 content with zeros 
  if (! ec_db_memzero(item_1)) {
    Serial.println("Error: ec_db_memzero().");
  } else {
    // Compare the data with zeros buffer...
    sz_r = ec_db_read(item_1, buf, sz);
    if ((sz_r != sz) || memcmp(buf, content_0, sizeof(content_0))) {
      Serial.println("Error: ec_db_memzero(): memcmp(item_1, zeros) != 0");
    } else {
      Serial.println("ec_db_memzero(): All Okay.");
    }
  }
  delete[] buf;


  // Test removing
  if (! ec_db_remove(item_1)) {
    Serial.println("Error: ec_db_remove(item_1).");
  } else {
    Serial.println("ec_db_remove(item_1): All Okay.");
  }


  // unmount FS in storage if we don't need it.
  ec_storage_unmount();
  Serial.println("Done testing.");
}

void loop() {
  // put your main code here, to run repeatedly:
  yield();
  ESP.deepSleep(0);
}

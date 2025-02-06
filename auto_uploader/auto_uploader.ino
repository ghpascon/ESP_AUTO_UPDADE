#include "libs.h"
#include "vars.h"

void setup() {
  esp_task_wdt_init(WATCHDOG_TIMEOUT, true);
  esp_task_wdt_add(NULL);

  serial_commands.setup();
  esp_wifi.setup();

    if (!LittleFS.begin()) {
    Serial.println("Failed to mount LittleFS file system");
    return;
  }
}

void loop() {
  esp_task_wdt_reset();
  esp_wifi.check_connection();
}


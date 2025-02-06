#include <WiFi.h>
#include <ArduinoJson.h>
#include "mbedtls/base64.h"

#include <Arduino.h>
#include "mbedtls/sha1.h"
#include "esp_spi_flash.h"

#define FLASH_FIRMWARE_ADDR 0x10000
#define FIRMWARE_SIZE 512 * 1024

#include <Update.h>

#include <HTTPClient.h>
HTTPClient http;

const char *ssid = "SmartXcomercial";
const char *password = "Smtx321$";
const String url = "https://api.github.com/repos/ghpascon/ESP_AUTO_UPDADE/contents/auto_uploader/build/esp32.esp32.esp32s3";
const String host = "api.github.com";
const String user_agent = "ESP32";

const String sha_file = "/sha.txt";
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

const String sha_file = "/sha.txt";
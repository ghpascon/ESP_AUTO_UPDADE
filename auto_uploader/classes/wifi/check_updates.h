#include "update_firmware.h"

class check_updates : private updater
{
public:
    void get_url()
    {
        http.begin(url);
        http.addHeader("Host", host);
        http.addHeader("User-Agent", user_agent);
        http.addHeader("Authorization", decodeBase64(token));

        int httpCode = http.GET();

        if (httpCode > 0)
        {
            String payload = http.getString();
            Serial.println("PAYLOAD:");
            Serial.println(payload);
            payload_handler(payload);
        }
        else
        {
            Serial.printf("Error on HTTP request: %s\n", http.errorToString(httpCode).c_str());
        }
        http.end();
    }

private:
    void payload_handler(String payload)
    {
        DynamicJsonDocument doc(2048); // Adjust the size based on the response
        DeserializationError error = deserializeJson(doc, payload);
        if (error)
        {
            Serial.print("Failed to parse JSON: ");
            Serial.println(error.c_str());
            return;
        }

        JsonArray files = doc.as<JsonArray>();
        for (JsonObject file : files)
        {
            String fileContent;
            serializeJson(file, fileContent);
            Serial.println(fileContent);

            if (!file.containsKey("name") || !file.containsKey("download_url"))
                continue;

            String filename = file["name"].as<String>();
            if (filename.endsWith(".ino.bin"))
            {
                Serial.println("File name: " + filename);
                String download_path = file["download_url"].as<String>();
                String sha = file["sha"].as<String>();
                update_firmware(download_path, sha);
            }
        }
    }
};
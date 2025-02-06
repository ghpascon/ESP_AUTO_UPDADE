#include "vars.h"
#include "secrets.h"
#include "check_updates.h"

// class ESP_POST : private post_cmd
class ESP_WIFI : private check_updates
{
public:
    void setup()
    {
        WiFi.begin(ssid, password);
    }

    void check_connection()
    {
        static bool last_connected = false;
        bool connected = WiFi.status() == WL_CONNECTED;

        if (last_connected == connected)
            return;
        last_connected = connected;

        if (connected)
        {
            Serial.println("Conectado ao WiFi");
            Serial.print("Endereço IP do ESP32: ");
            Serial.println(WiFi.localIP());
            get_url();
        }
        else
        {
            Serial.println("WIFI DISCONNECTED");
        }
    }
};
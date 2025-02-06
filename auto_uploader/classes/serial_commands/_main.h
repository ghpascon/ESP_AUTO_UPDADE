#include "vars.h"

class SERIAL_COMMANDS
{
public:
    void setup()
    {
        Serial.begin(115200);
    }

    void check_commands()
    {
        if (!Serial.available())
            return;
        String cmd = Serial.readStringUntil('\n');
        cmd.toLowerCase();
        cmd.replace(" ", "");
        cmd.replace("\r", "");
        cmd.replace("\n", "");

        cmd_handler(cmd);
    }

private:
    void cmd_handler(String cmd)
    {
    }
};

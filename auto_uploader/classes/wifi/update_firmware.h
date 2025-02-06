class updater
{
public:
    String decodeBase64(String encoded)
    {
        size_t decodedLen;
        unsigned char decodedOutput[200]; // Ajuste conforme necessário

        mbedtls_base64_decode(decodedOutput, sizeof(decodedOutput), &decodedLen,
                              (const unsigned char *)encoded.c_str(), encoded.length());

        Serial.println(String((char *)decodedOutput).substring(0, decodedLen));
        return String((char *)decodedOutput).substring(0, decodedLen);
    }

    String read_sha()
    {
        File arquivo = LittleFS.open(sha_file, "r");
        if (!arquivo)
        {
            Serial.println("Erro ao abrir o arquivo para leitura");
            return "";
        }

        Serial.println("Conteúdo do arquivo:");

        String sha = arquivo.readString(); // Lê todo o conteúdo do arquivo corretamente
        arquivo.close();

        // Remove espaços, quebras de linha e retornos de carro
        sha.replace(" ", "");
        sha.replace("\n", "");
        sha.replace("\r", "");

        Serial.println(sha);
        return sha;
    }

    void save_sha(const String conteudo)
    {
        File arquivo = LittleFS.open(sha_file, "w");
        if (!arquivo)
        {
            Serial.println("Erro ao abrir o arquivo para escrita");
            return;
        }
        arquivo.println(conteudo);
        arquivo.close();
        Serial.println("Conteúdo escrito com sucesso!");
        Serial.println(conteudo);
    }

    void update_firmware(String download_path, const String sha)
    {
        if (read_sha() == sha)
        {
            Serial.println("Firmware already updated");
            return;
        }
        http.begin(download_path);
        http.addHeader("Host", host);
        http.addHeader("User-Agent", user_agent);
        http.addHeader("Authorization", decodeBase64(token));

        int httpCode = http.GET();

        if (httpCode == HTTP_CODE_OK)
        {
            WiFiClient *stream = http.getStreamPtr();
            size_t contentLength = http.getSize();

            if (contentLength > 0)
            {
                Serial.printf("Starting firmware update. File size: %d bytes\n", contentLength);
                if (Update.begin(contentLength))
                {
                    size_t written = Update.writeStream(*stream);
                    if (written == contentLength)
                    {
                        Serial.println("Firmware update successful. Rebooting...");
                        save_sha(sha);
                        if (Update.end())
                        {
                            Update.printError(Serial);
                            ESP.restart();
                        }
                        else
                        {
                            Serial.println("Error during update end.");
                        }
                    }
                    else
                    {
                        Serial.printf("Update failed: %d bytes written, %d expected\n", written, contentLength);
                        Update.printError(Serial);
                    }
                }
                else
                {
                    Serial.println("Not enough space for firmware update.");
                    Update.printError(Serial);
                }
            }
            else
            {
                Serial.println("Invalid content length for firmware update.");
            }
        }
        else
        {
            Serial.printf("Error downloading file: %s\n", http.errorToString(httpCode).c_str());
        }

        http.end();
    }
};
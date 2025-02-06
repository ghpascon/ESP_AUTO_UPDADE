# ESP_AUTO_UPDADE
Este projeto consiste em fazer um upload para o esp32 a partir da web utilizando o github

# COMO FUNCIONA?
Ao se conectar ao wifi ele verifica o link do seu github para identificar o arquivo .ino.bin e após isso realiza o upload do firmware

# ALTERAÇÕES NECESSARIAS
Dentro da pasta classes/wifi renomeie o arquivo secrets_.h para secrets.h e coloque seu token do github codificada em base64

https://github.com/settings/tokens

https://www.base64encode.org/

# IMPORTANTE
Para gerar os arquivos binários no arduino IDE dentro da aba scketch seleciona Export Compiled Binary

Necessário fazer o UPLOAD para o esp32 uma vez via cabo para começar a funcionar

No arquivo classes/wifi/secrets.h alterar o ssid, password, url para seus dados

O código está definido para o esp32S3 caso necessite para o esp32 alterar dentro do arquivo classes/wifi/vars.h:
#define FLASH_FIRMWARE_ADDR 0x10000 -> #define FLASH_FIRMWARE_ADDR 0x1000

E dentro de classes/wifi/secrets.h alterar o url

Ao fazer o upload para o github, sempre que o esp32 reiniciar ele vai buscar por novas atualizações.

Caso existam Diversos ESP32 todos vão fazer o upload automatico
#include "LoRa_E220.h"
#define RXD2 16
#define TXD2 17
#include "FS.h"
#include "SD.h"
#include "SPI.h"
int cont = 0;
unsigned long temp;
unsigned long tempa1;
String converte;
String msgsalva;
String msg;
String getValue(String data, char separator, int index)
{
    int found = 0;
    int strIndex[] = { 0, -1 };
    int maxIndex = data.length() - 1;

    for (int i = 0; i <= maxIndex && found <= index; i++)
    {
        if (data.charAt(i) == separator || i == maxIndex)
        {
            found++;
            strIndex[0] = strIndex[1] + 1;
            strIndex[1] = (i == maxIndex) ? i+1 : i;
        }
    }
    return found > index ? data.substring(strIndex[0], strIndex[1]) : "";
}
void writeFile(fs::FS &fs, const char * path, const char * message)
{
    Serial.printf("Writing file: %s\n", path);
    File file = fs.open(path, FILE_WRITE);
    if(!file)
    {
        Serial.println("Failed to open file for writing");
        return;
    }
    if(file.print(message))
    {
        Serial.println("File written");
    }
    else
    {
        Serial.println("Write failed");
    }
    file.close();
}
void appendFile(fs::FS &fs, const char * path, const char * message)
{
    Serial.printf("Appending to file: %s\n", path);
    File file = fs.open(path, FILE_APPEND);
    if(!file)
    {
        Serial.println("Failed to open file for appending");
        return;
    }
    if(file.print(message))
    {
        Serial.println("Message appended");
    }
    else
    {
        Serial.println("Append failed");
    }
    file.close();
}
void setup()
{
    tempa1 = millis();
    Serial.begin(9600);
    Serial2.begin(9600, SERIAL_8N1, RXD2, TXD2);
    pinMode(12, OUTPUT);
    if(!SD.begin())
    {
        Serial.println("Card Mount Failed");
        return;
    }
    uint8_t cardType = SD.cardType();
    if(cardType == CARD_NONE)
    {
        Serial.println("No SD card attached");
        return;
    }
    Serial.print("SD Card Type: ");
    if(cardType == CARD_MMC)
    {
        Serial.println("MMC");
    }
    else if(cardType == CARD_SD)
    {
        Serial.println("SDSC");
    }
    else if(cardType == CARD_SDHC)
    {
        Serial.println("SDHC");
    }
    else
    {
        Serial.println("UNKNOWN");
    }
    uint64_t cardSize = SD.cardSize() / (1024 * 1024);
    Serial.printf("SD Card Size: %lluMB\n", cardSize);
}
void loop()
{
    temp = millis();
    cont = cont + 1;
    if (Serial2.available()>0)
    {
        String recebe = Serial2.readString();
        converte = getValue(recebe, ',', 0);
        msg = recebe + " | tempo de chegada: " + temp +"&";
        if(converte=="B")
        {
            digitalWrite(12, HIGH);
            appendFile(SD, "/dados.txt", msg.c_str());
        }
        else if(converte!= "B")
        {
            digitalWrite(12, LOW);
        }
    }
            converte == "";
            msg == "";
    if ((millis()-tempa1)>5000)
    {
        digitalWrite(12, LOW);
        tempa1 = millis();
    }
}

/*
 replace sensitive information with yours, do not forget to change sender email and info from Gsender.h
*/
#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <DHT.h>
#include "Gsender.h"

#define DHTTYPE DHT11



DHT dht(4, DHT11);

#pragma region Globals
const char* ssid = "*********";                           // WIFI network name
const char* password = "********";                       // WIFI network password
uint8_t connection_state = 0;                    // Connected to WIFI or not
uint16_t reconnect_interval = 10000;             // If not connected wait time to try again
#pragma endregion Globals
ESP8266WiFiMulti WiFiMulti;

uint8_t WiFiConnect(const char* nSSID = nullptr, const char* nPassword = nullptr)
{
    static uint16_t attempt = 0;
    Serial.print("Connecting to ");
    if(nSSID) {
        WiFi.begin(nSSID, nPassword);  
        Serial.println(nSSID);
    } else {
      dht.begin();
      WiFi.enableInsecureWEP();
      WiFi.mode(WIFI_STA);
      WiFiMulti.addAP(ssid, password);
        WiFi.begin(ssid, password);
        Serial.println(ssid);
    }

    uint8_t i = 0;
    while(WiFi.status()!= WL_CONNECTED && i++ < 50)
    {
        delay(200);
        Serial.print(".");
    }
    ++attempt;
    Serial.println("");
    if(i == 51) {
        Serial.print("Connection: TIMEOUT on attempt: ");
        Serial.println(attempt);
        if(attempt % 2 == 0)
            Serial.println("Check if access point available or SSID and Password\r\n");
        return false;
    }
    Serial.println("Connection: ESTABLISHED");
    Serial.print("Got IP address: ");
    Serial.println(WiFi.localIP());
    return true;
}

void Awaits()
{
    uint32_t ts = millis();
    while(!connection_state)
    {
        delay(50);
        if(millis() > (ts + reconnect_interval) && !connection_state){
            connection_state = WiFiConnect();
            ts = millis();
        }
    }
}

void setup()
{
    Serial.begin(115200);
    dht.begin();
    
}

void loop(){
   float h = dht.readHumidity();
   float f = dht.readTemperature(true);
   float hif = dht.computeHeatIndex(f, h);
   String stringf= (String) f;
   String stringh= (String) h;
   String stringhif = (String) hif; 
   int date = 5;
   int next = date + 1;
   String nextday = (String) next;
   String today = "Today is June " + nextday + ", 2019";
   String todaystemp = "Today's tempurature is " + stringf + " the humidity is " + stringh + " -BIG PUMBA.";
      connection_state = WiFiConnect();
    if(!connection_state)  // if not connected to WIFI
        Awaits();          // constantly trying to connect

    Gsender *gsender = Gsender::Instance();    // Getting pointer to class instance
    String subject = "Subject is optional!";
    if(gsender->Subject(today)->Send("sender@gmail.com", todaystemp)) {
        Serial.println("Message send.");
    } else {
        Serial.print("Error sending message: ");
        Serial.println(gsender->getError());
    }
    delay(86305000);
  }

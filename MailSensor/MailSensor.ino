String DomoSoft = "4.2";
String SensorSoft = "3.3";
String build = "BN1-15022020";

String version = DomoSoft + "<br>SensorSoft: " + SensorSoft + "<br>Build: " + build;



#define PushPGR 4

/* CHANGELOG
  - Migliorato il funzionamento dell'interfaccia web
*/
int isUpdate = 0;
#include <PubSubClient.h>
#include <ESP8266HTTPClient.h>
#include <EEPROM.h>
#include <ESP8266HTTPUpdateServer.h>
#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include "FS.h"
#include <DNSServer.h>
#include <EMailSender.h>
#include <ArduinoJson.h>
DNSServer dnsServer;
IPAddress apIP(192, 168, 1, 1);
const byte DNS_PORT = 53;

// MQTT variabili ----------------------------
String mqtt_server = "";
String mqtt_user = "";
String mqtt_password = "";


String devname;
String devname2;

byte discovered;

String hassio_prefix;

File Main;

int stopS;
int wifi_ok;
int aptend;

long lastReconnectAttempt = 0;
String sensor_status_topic;
String vdd_status_topic;
String perc_status_topic;

String SMTPmail;
String SMTPassword;
String subject;
String messaggio;
String email;

const char* update_path = "/settings/firmware";

byte PgrMode;
byte mail_conf;

MDNSResponder mdns;
int mqtt_conf = 1;
String st;
String content;
int statusCode;

//SICUREZZA

String username = "";
String password = "";
const char* realm = "DomoSoft";


//Bootloader
int bootMode_add = 97;
int bootMode = 0;

//this ssid and Password is for Hotspot connection

WiFiClient httpclient;
ESP8266WebServer server(80);
PubSubClient client(httpclient);
ESP8266HTTPUpdateServer httpUpdater;


int perc;

int E_MQ = 0;

float vdd;

void setup(void) {
  Serial.begin(115200);
  EEPROM.begin(512);
  delay(100);
  SPIFFS.begin();
 
  pinMode(PushPGR, INPUT_PULLUP);
  PgrMode = digitalRead(PushPGR);
  if (!SPIFFS.exists("/Config_ok")) {
    Serial.println("ERROR 02: FileSystem Error, Reload the code!");
    ESP.deepSleep(  ESP.deepSleepMax(), WAKE_RF_DISABLED);
  }

  mqtt_conf = EEPROM.read(202);
  mail_conf = EEPROM.read(204);
 WiFi.mode(WIFI_STA);
  if (PgrMode) {
   
    Serial.println("Send data mode");
    if (WiFi.SSID() == "") {
      return;
    }
    while (WiFi.status() != WL_CONNECTED) { 
     delay(250);
    }
    Serial.println("Connected");
    bootConfig();
    if (mail_conf) {
      Serial.println("Send mail");
      
      SendMail();
    }
    if (mqtt_conf) {
      Serial.println("Send MQTT");
      MQTT_sync();
    }
    Serial.println("Go sleep");
    WiFi.mode(WIFI_OFF);
    ESP.deepSleep(  ESP.deepSleepMax(), WAKE_RF_DISABLED);
  }
  Serial.println("Config Mode");
  for (int i = 166; i < 180; ++i)
  {
    username += char(EEPROM.read(i));
    delay(10);
  }
  Serial.println(username);
  for (int i = 181; i < 199; ++i)
  {
    password += char(EEPROM.read(i));
    delay(10);
  }

  bootMode = EEPROM.read(bootMode_add);


  delay(10);




  if (testWifi()) {
    bootConfig();
     Serial.print("WIFI IP: ");
    Serial.println(WiFi.localIP());
 
    return;
  }

  setupAP();



}

void loop(void) {


  if (wifi_ok == 0) {
    digitalWrite(LED_BUILTIN, LOW);
    dnsServer.processNextRequest();
  } else {

    if (mqtt_conf == 1) {
      client.loop();
      while (!client.connected()) {
        aptend++;

        E_MQ = 1;

        if (mqtt_conn()) {

          E_MQ = 0;
        }
        if (aptend == 10) {
          E_MQ = 1;
          lastReconnectAttempt = millis();
          break;
        }
      }
    }

    long now = millis();

  }
  server.handleClient();


}


void testSys() {
  Serial.println("TEST mode STARTED");
  
  
 
    if (mail_conf) {
      Serial.println("Send mail");
      
      SendMail();
    }
    if (mqtt_conf) {
      Serial.println("Send MQTT");
      MQTT_sync();
    }
    Serial.println("TEST FINISH");
}

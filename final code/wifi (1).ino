#include <ESP8266wifi.h>
#include <SerialESP8266wifi.h>
#include <FirebaseArduino.h> 
abcd

// Set these to run example.gffff

#define FIREBASE_HOST "arduino-8f9a2.firebaseio.com"

#define FIREBASE_AUTH "Ypf2lgSXcxhrb5dqz6K75ebJtXSz5Zenz3ggFFux"

#define WIFI_SSID "Mubeen Ahmed"
swqaas
#define WIFI_PASSWORD "mubeen777"

#define LED 2

void setup() {

pinMode(LED,OUTPUT);

digitalWrite(LED,0);

Serial.begin(9600);

WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

Serial.print("connecting");

while (WiFi.status() != WL_CONNECTED) {

Serial.print(".");


}

Serial.println();

Serial.print("connected: ");

Serial.println(WiFi.localIP());

Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);

Firebase.setInt("LEDStatus",0);

}

void loop() {

if(Firebase.getInt("LEDStatus"))

{

digitalWrite(LED,HIGH);

}

else

{

digitalWrite(LED,LOW);

}

if (Firebase.failed()){ // Check for errors 

Serial.print("setting /number failed:");

Serial.println(Firebase.error());

return;

}

delay(1000);

}

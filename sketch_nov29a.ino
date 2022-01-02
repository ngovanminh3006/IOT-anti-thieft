// Template ID, Device Name and Auth Token are provided by the Blynk.Cloud
// See the Device Info tab, or Template settings
#define BLYNK_TEMPLATE_ID "TMPLJ0i8yfa-"
#define BLYNK_DEVICE_NAME "Quickstart Template"
#define BLYNK_AUTH_TOKEN "KdMh5LzIRKXp78fRYG3i3YC3IafYWnUg"
#include <ESP8266WiFi.h>
#include <WiFiManager.h>
#include <BlynkSimpleEsp8266.h>

// Comment this out to disable prints and save space
#define BLYNK_PRINT Serial
char auth[] = BLYNK_AUTH_TOKEN;

BlynkTimer timer;
WiFiServer server(80);

//define the pins
int PIR = 13;
int buzzerPin = 12;
int Congtat1;
int Congtat2;
// This function is called every time the Virtual Pin 0 state changes
BLYNK_WRITE(V0)
{
  // Set incoming value from pin V0 to a variable
  int value = param.asInt();
  if(value == 1)
  {
    Blynk.virtualWrite(V1, "OFF BUZZER");
    digitalWrite(buzzerPin,HIGH);
    Congtat1 = 1;
    }
  else{
    Blynk.virtualWrite(V1, "ON BUZZER");
    digitalWrite(buzzerPin,LOW);
    Congtat1 = 0;
    
    }
  // Update state
  Blynk.virtualWrite(V1, value);
}

BLYNK_WRITE(V2)
{
  // Set incoming value from pin V0 to a variable
  int value = param.asInt();
  if(value == 1)
  {
    Blynk.virtualWrite(V1, "OFF BUZZER");
    digitalWrite(buzzerPin,HIGH);
    
    }
  else{
    Blynk.virtualWrite(V1, "ON BUZZER");
    digitalWrite(buzzerPin,LOW);
    }
  // Update state
  Blynk.virtualWrite(V1, value);
}



void setup() {
  // Debug console
  Serial.begin(115200);
  WiFiManager wifimanager;
  wifimanager.autoConnect("autoConnectAP");
  String ssid =  WiFi.SSID();
  String pass =  WiFi.psk();
  int str_ssid = ssid.length() + 1; 
  int str_pass = pass.length() + 1; 
  char char_arrays[str_ssid];
  char char_arrayp[str_pass];
  ssid.toCharArray(char_arrays, str_ssid);
  pass.toCharArray(char_arrayp, str_pass);
  Blynk.begin(auth,char_arrays,char_arrayp);
  
  //define the sensor pin as input
  pinMode(PIR, INPUT);
  pinMode(buzzerPin, OUTPUT);
  server.begin();
  
}

void loop() {
    Blynk.run();
    timer.run();
  // put your main code here, to run repeatedly:
   //using the digitalRead function we will read the signal of the sensor
  int value = digitalRead(PIR);
   Serial.println(value);
   if (Congtat1 == 1){
    Blynk.virtualWrite(V3, "TURN ON THE DEVICE");
      if (value == HIGH){
    Blynk.virtualWrite(V1, "Có người ở gần!");
    Serial.println("Có người ở gần");
    digitalWrite(buzzerPin,LOW);
    
        
//    delay(1000);
  }
  else {
    //digitalWrite(LED, LOW);
    Blynk.virtualWrite(V1, "Không có ai!");
    Serial.println("Không có ai");
    digitalWrite(buzzerPin,HIGH);
    
        
//    delay(1000);
  }
    }

    else{
      Blynk.virtualWrite(V3, "TURN OFF THE DEVICE");
      digitalWrite(buzzerPin,HIGH);
      }


  delay(2000);
}

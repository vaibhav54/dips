#include <Defs.h>
#include <GenericMux.h>
#include <Mux.h>
#include <Series4000Mux.h>
#include <Type4051Mux.h>
#include <Type4067Mux.h>
#include "MUX74HC4067.h"
#include "MQ7.h"
#define BLYNK_PRINT Serial
#include <BlynkSimpleEsp8266.h>
#include <ESP8266WiFi.h>

char auth[] = "6a198d0bfc954f61bd5da698fca83016";
char ssid[] = "real";
char pass[] = "12345678";



MUX74HC4067 mux(4, 12, 13, 14,15);


void setup()
{
  Serial.begin(115200);  
  Blynk.begin(auth, ssid, pass);
 
  mux.signalPin(A0, INPUT, ANALOG);
}
    int x;
    BLYNK_WRITE(V7) {
      x = param.asInt();
      Serial.println("working...");
    }

void loop()
{
    
int dataMq4,dataMq7;
 if (x == 1) {
    
    for (int i = 0; i < 2; ++i)
  {Serial.println();

    if(i==0)
   { dataMq4 = mux.read(i);
    Serial.print("VALUE = ");
    Serial.print(i);
    Serial.print(" is at ");
    Serial.print(dataMq4);}
else{
  dataMq7 = mux.read(i);
  Serial.print("VALUE = ");
    Serial.print(i);
    Serial.print(" is at ");
    Serial.print(dataMq7);
}
  }
Blynk.virtualWrite(V5, dataMq7);    
Blynk.virtualWrite(V2, dataMq4);
if (dataMq4 > 650) {
      Blynk.setProperty(V3, "opacity", 100);
    } else
      Blynk.setProperty(V3, "opacity", 0);
    digitalWrite(13, HIGH);
   
   if (dataMq7 > 375) {
      Blynk.setProperty(V1, "opacity", 100);
    } else
      Blynk.setProperty(V1, "opacity", 0);
  
  
    
   delay(1500);
    
}Blynk.run();
}

#include <ESP8266WiFi.h>
const char* ssid     = "neng wifi";
const char* password = "tennis87";

int LEDD0 = D0; // ขา D0


void setup() {
  
  pinMode(LEDD0, OUTPUT); // กำหนดการทำงานของขา D0 ให้เป็น Output
  
  digitalWrite(LEDD0, LOW);

   Serial.begin(115200);
   Serial.println("Starting...");

   WiFi.begin(ssid, password);
   while (WiFi.status() != WL_CONNECTED) 
   {
      delay(250);
      Serial.print(".");
      
   }
   digitalWrite(LEDD0, HIGH); // สั่งให้ ขา D0 ปล่อยลอจิก 1 ไฟ LED ติด
   Serial.println("WiFi connected");  
   Serial.println("IP address: ");
   Serial.println(WiFi.localIP());
  
}
void loop()
{
  
  
}

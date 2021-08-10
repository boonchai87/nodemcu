/*
 * HTTPS Secured Client POST Request
 * Copyright (c) 2019, circuits4you.com
 * All rights reserved.
 * https://circuits4you.com 
 * Connects to WiFi HotSpot. */

#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h> 
#include <ESP8266WebServer.h>
#include <ESP8266HTTPClient.h>

/* Set these to your desired credentials. */
const char *ssid = "neng wifi";  //ENTER YOUR WIFI SETTINGS
const char *password = "tennis87";

//Link to read data from https://jsonplaceholder.typicode.com/comments?postId=7
//Web/Server address to read/write from 
//const char *host = "postman-echo.com";
const char* host = "google.com";
const char* fingerpr = "5E 0B 46 9E 55 07 70 5A C3 40 12 66 06 89 9A 92 E8 C2 15 E4";

const int httpsPort = 443;  //HTTPS= 443 and HTTP = 80


//SHA1 finger print of certificate use web browser to view and copy
//const char fingerprint[] PROGMEM = "A6 5A 41 2C 0E DC FF C3 16 E8 57 E9 F2 C3 11 D2 71 58 DF D9";
//const char fingerprint[] PROGMEM = "5E 0B 46 9E 55 07 70 5A C3 40 12 66 06 89 9A 92 E8 C2 15 E4";

//=======================================================================
//                    Power on setup
//=======================================================================

void setup() {
  delay(1000);
  Serial.begin(9600);
  WiFi.mode(WIFI_OFF);        //Prevents reconnection issue (taking too long to connect)
  delay(1000);
  WiFi.mode(WIFI_STA);        //Only Station No AP, This line hides the viewing of ESP as wifi hotspot
  
  WiFi.begin(ssid, password);     //Connect to your WiFi router
  Serial.println("");

  Serial.print("Connecting");
  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  //If connection successful show IP address in serial monitor
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());  //IP address assigned to your ESP
}

//=======================================================================
//                    Main Program Loop
//=======================================================================
void loop() {
   delay(5000);

    Serial.print("connecting to ");
    Serial.println(host);
  
    // Use WiFiClient class to create TCP connections
    WiFiClientSecure client;
    const int httpPort = 443; // 80 is for HTTP / 443 is for HTTPS!
    
    client.setInsecure(); // this is the magical line that makes everything work
    
    if (!client.connect(host, httpPort)) { //works!
      Serial.println("connection failed");
      return;
    }
  
    // We now create a URI for the request
    String url = "/arduino.php";
    url += "?data=";
    url += "aaaa";
  
  
    Serial.print("Requesting URL: ");
    Serial.println(url);
  
    // This will send the request to the server
    client.print(String("GET ") + url + " HTTP/1.1\r\n" +
                 "Host: " + host + "\r\n" + 
                 "Connection: close\r\n\r\n");
  
    while (client.connected()) {
    String line = client.readStringUntil('\n');
    
    if (line == "\r") {
      Serial.println("headers received");
      break;
    }
  }

  String line;
  while(client.available()){        
    line = client.readStringUntil('\n');  //Read Line by Line
    Serial.println(line); //Print response
  }
  
    Serial.println("closing connection");
}

/*  doBit_110            doBits Labs - Humdan Bakhshi
    version 1.1.0        12/21/2016
    Description:
    First Integration of nodeMCUWifi and WifiManager

    v110:

*/


#include <ESP8266WiFi.h>
#include <DNSServer.h>
#include <ESP8266WebServer.h>
#include <WiFiManager.h>
#include <Ticker.h> // for LED status
Ticker ticker; // ticker LED object  (Built in LED D0)
WiFiServer server(301); //server Object with desired port

//NODE MCU pin defintions:
#define D0 16
#define D1 5 // I2C Bus SCL (clock)
#define D2 4 // I2C Bus SDA (data)
#define D3 0
#define D4 2 // Same as "LED_BUILTIN", but inverted logic
#define D5 14 // SPI Bus SCK (clock)
#define D6 12 // SPI Bus MISO
#define D7 13 // SPI Bus MOSI
#define D8 15 // SPI Bus SS (CS)
#define D9 3 // RX0 (Serial console)
#define D10 1 // TX0 (Serial console)

int led = D0;

// all functions here /**************************/
void tick() // used for LED state changer dependencies
{
  //toggle state
  int state = digitalRead(BUILTIN_LED);  // get the current state of GPIO1 pin
  digitalWrite(BUILTIN_LED, !state);     // set pin to the opposite state
}// close tick()

//gets called when WiFiManager enters configuration mode
void configModeCallback (WiFiManager *myWiFiManager) {
  Serial.println("Entered config mode");
  Serial.println(WiFi.softAPIP());
  //if you used auto generated SSID, print it
  Serial.println(myWiFiManager->getConfigPortalSSID());
  //entered config mode, make led toggle faster
  ticker.attach(0.2, tick);
}

//***********************************************/





void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  pinMode(BUILTIN_LED, OUTPUT);
  ticker.attach(0.6, tick);// start ticker to indicate AP mode

  pinMode(led,OUTPUT); // tester LED D7
  digitalWrite(led, LOW);  //initial set LED to OFF
  
  // WIFI manager
  WiFiManager wifiManager; //local initialization
  wifiManager.resetSettings();  //reset settings - for testing
  //set callback that gets called when connecting to previous WiFi fails, and enters Access Point mode
  wifiManager.setAPCallback(configModeCallback);
  //fetches ssid and pass and tries to connect
  //if it does not connect it starts an access point with the specified name
  //here  "AutoConnectAP"
  //and goes into a blocking loop awaiting configuration
  if (!wifiManager.autoConnect("doBits_0")) {
    Serial.println("failed to connect and hit timeout");
    //reset and try again, or maybe put it to deep sleep
    ESP.reset();
    delay(1000);
  }// close if autoconnect
    //if you get here you have connected to the WiFi
  Serial.println("connected...yeey :)");
  ticker.detach(); //we no longer need the ticker object after connectivity
  digitalWrite(BUILTIN_LED, LOW); //set PIN to OFF to show connected

  // nodeWiFi stuff from setup
    Serial.println(WiFi.localIP());   //print ip of esp
     while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
    }
    Serial.println("");
    Serial.println("WiFi connected");
    // Start the server
    server.begin();
    Serial.println("Server started");
     // Print the IP address to serial port
    Serial.println(WiFi.localIP());
      
  
}// close setup()

void loop() {
  // Check if a client has connected
  
  WiFiClient client = server.available();
  if (!client) {
    return;
  }

  // Wait until the client sends some data
  while (!client.available()) {
    delay(1);
  }

  // Read the first line of the request
  String req = client.readStringUntil('\r');
  client.flush();

  // Match the request
  if (req.indexOf("") != -10) {  //checks if you're on the main page

    if (req.indexOf("/OFF") != -1) { //checks if you clicked OFF
      digitalWrite(led, LOW);
      Serial.println("You clicked OFF");
    }
    if (req.indexOf("/ON") != -1) { //checks if you clicked ON
      digitalWrite(led, HIGH);
      Serial.println("You clicked ON");
    }
  }

  else {
    Serial.println("invalid request");
   client.stop();
    return;
  }

  // Prepare the HTML response
 String s = "HTTP/1.1 200 OK\r\n";
  s += "Content-Type: text/html\r\n\r\n";
  s += "<!DOCTYPE HTML>\r\n<html>\r\n";
  s += "<br><input type=\"button\" name=\"bl\" value=\"Turn LED ON \" onclick=\"location.href='/ON'\">";
  s += "<br><br><br>";
  s += "<br><input type=\"button\" name=\"bl\" value=\"Turn LED OFF\" onclick=\"location.href='/OFF'\">";
  s += "</html>\n";

  client.flush();


  // Send the response to the client
  client.print(s);
  delay(1);


}


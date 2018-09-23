void setup() {

  Serial2.begin(9600); // ESP8266 
  Serial.begin(115200); // Arduino serial 
}


void loop() { // copy from and to each port
  while(Serial2.available()) Serial.write(Serial2.read());
  while(Serial.available()) Serial2.write(Serial.read());
}


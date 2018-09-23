void setup() {
   Serial.begin(9600);
   delay(1000);
   Serial.print("AT+NAMEBT 001");
   delay(1000);
   Serial.print("AT+PIN4321");
   delay(1000);
   Serial.print("AT+BAUD7");
}


void loop() {
}

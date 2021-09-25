// 201533631 김도균
#define LED 9

void setup() {
	pinMode(LED, OUTPUT);
	Serial.begin(9600);
}

void loop() {
	if(Serial.available()){
		int count = Serial.parseInt();
		String msg = "Start blinking: ";
		msg.concat(count);
		Serial.println(msg);

		for(int i=0; i<count; i++){
			digitalWrite(LED, HIGH);
			delay(500);
			digitalWrite(LED, LOW);
			delay(500);
		}
		Serial.println("Done");
	}
}

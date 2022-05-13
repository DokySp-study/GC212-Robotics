// 201533631 김도균

void setup() {
	Serial.begin(9600);
}

void loop() {
	
	Serial.println(( 5.0 * analogRead(A0) * 100 ) / 1024);
	
}

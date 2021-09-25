// 201533631 김도균

void setup() {
    pinMode(13, OUTPUT);
    pinMode(8, INPUT);
}

void loop() {
	digitalWrite(13, digitalRead(8));
}

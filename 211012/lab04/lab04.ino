// 201533631 김도균

void setup() {
	pinMode(9, OUTPUT);
    pinMode(10, OUTPUT);
    pinMode(11, OUTPUT);
}

void loop() {

    analogWrite(9, map(analogRead(A0), 0, 1023, 0, 255));
    analogWrite(10, map(analogRead(A1), 0, 1023, 0, 255));
    analogWrite(11, map(analogRead(A2), 0, 1023, 0, 255));

}

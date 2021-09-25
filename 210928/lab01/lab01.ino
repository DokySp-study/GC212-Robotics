// 201533631 김도균
#define DIGIT1 3

void setup() {
    pinMode(DIGIT1, OUTPUT);
}

void loop() {
    digitalWrite(DIGIT1, HIGH);
    delay(1000);
    digitalWrite(DIGIT1, LOW);
    delay(1000);
}

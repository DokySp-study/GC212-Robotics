// 201533631 김도균

int digitPin1 = 12;
int digitPin2 = 13;

void setup() {
    pinMode(digitPin1, OUTPUT);
    pinMode(digitPin2, OUTPUT);
}

void loop() {
    digitalWrite(digitPin1, HIGH);
    digitalWrite(digitPin2, LOW);
    delay(100);
    digitalWrite(digitPin1, LOW);
    digitalWrite(digitPin2, HIGH);
    delay(100);
}

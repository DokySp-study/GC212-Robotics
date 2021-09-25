// 201533631 김도균

void setup() {
    Serial.begin(9600);
}

void loop() {
    static int sec = 0;
    Serial.println(sec++);
    delay(1000);
}

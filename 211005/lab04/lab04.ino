// 201533631 김도균

#define LED_R 3
#define LED_G 4
#define LED_B 5

#define LED_BUTTON_R 8
#define LED_BUTTON_G 9
#define LED_BUTTON_B 10

void setup() {
	pinMode(LED_R, OUTPUT);
    pinMode(LED_G, OUTPUT);
    pinMode(LED_B, OUTPUT);
    pinMode(LED_BUTTON_R, INPUT);
    pinMode(LED_BUTTON_G, INPUT);
    pinMode(LED_BUTTON_B, INPUT);
}

void loop() {
    digitalWrite(LED_R, digitalRead(LED_BUTTON_R));
    digitalWrite(LED_G, digitalRead(LED_BUTTON_G));
    digitalWrite(LED_B, digitalRead(LED_BUTTON_B));
}

// 201533631 김도균

int digitPinR = 9;
int digitPinG = 10;
int digitPinB = 11;

void setup() {
    pinMode(digitPinR, OUTPUT);
    pinMode(digitPinG, OUTPUT);
    pinMode(digitPinB, OUTPUT);
}

void loop() {
    
    for(int i = 0; i<256; i++){
        analogWrite(digitPinR, i);
        analogWrite(digitPinB, 255-i);
        delay(3);
    }

    for(int i = 0; i<256; i++){
        analogWrite(digitPinG, i);
        analogWrite(digitPinR, 255-i);
        delay(3);
    }

    for(int i = 0; i<256; i++){
        analogWrite(digitPinB, i);
        analogWrite(digitPinG, 255-i);
        delay(3);
    }

}

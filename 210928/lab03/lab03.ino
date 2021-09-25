// 201533631 김도균

int digitPin1 = 10;
int digitPin2 = 11;

void setup() {
    pinMode(digitPin1, OUTPUT);
    pinMode(digitPin2, OUTPUT);
}

void loop() {
    static int isOdd = 1;

    analogWrite(digitPin1, isOdd ? 0 : 255);
    analogWrite(digitPin2, isOdd ? 255 : 0);
    
    for(int i = 0; i < 256; i++){
        analogWrite(digitPin1, isOdd ? i : 255 - i);
        analogWrite(digitPin2, isOdd ? 255 - i : i);
        delay(3);
    }
    isOdd = isOdd ? 0 : 1;
}

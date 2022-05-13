// 201533631 김도균

void setup() {
    pinMode(9, OUTPUT);
    pinMode(10, INPUT);
}

void loop() {
    static bool isTurnOn = false;
    static bool isButtonPushed = false;

    if(!isButtonPushed && digitalRead(10) == HIGH){
        isButtonPushed = true;
        isTurnOn = !isTurnOn;
    }

    if(digitalRead(10) == LOW) isButtonPushed = false;

    if(isTurnOn){    
        analogWrite(9, map(analogRead(A1), 0, 1023, 0, 255));
    } else {
        analogWrite(9, 0);
    }

}

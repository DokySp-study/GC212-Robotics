// 201533631 김도균

void setup() {
    pinMode(13, OUTPUT);
}

void loop() {
    
    if(analogRead(A0) > 511){
        digitalWrite(13, HIGH);
    } else {
        digitalWrite(13, LOW);
    }

}

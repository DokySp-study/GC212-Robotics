// 201533631 김도균

void setup() {
    pinMode(2, OUTPUT); // trig
    pinMode(3, INPUT); // echo
    pinMode(8, OUTPUT);
}

double scale[] = {
    0,
    261.63,
    329.63,
    392.00,
    523.25,
};

void loop() {
    
    digitalWrite(2, HIGH);
    delayMicroseconds(50);
    digitalWrite(2, LOW);

    double metric = pulseIn(3, HIGH) / 58.2;

    if(5 <= metric && metric <= 10) {
        tone(8, scale[1], 250);
    } else if (15 <= metric && metric <= 20) {
        tone(8, scale[2], 250);
    } else if (25 <= metric && metric <= 30) {
        tone(8, scale[3], 250);
    } else if (35 <= metric && metric <= 40) {
        tone(8, scale[4], 250);
    } else {
        tone(8, scale[0], 250);
    }

}

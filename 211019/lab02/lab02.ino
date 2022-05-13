// 201533631 김도균
#include <Servo.h>

Servo servo;

void setup() {
    servo.attach(9);
}

void loop() {
    servo.write(map(analogRead(A0), 0, 1023, 0, 180));
}

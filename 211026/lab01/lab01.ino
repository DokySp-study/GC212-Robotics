// 201533631 김도균

void setup() {}

double scale[] = {
    0,
    261.63,
    293.66,
    329.63,
    349.23,
    392.00,
    440.00,
    493.88,
};

void loop() {

    static boolean isOdd = true;
    
    tone(8, scale[5], 450);
    delay(500);
    tone(8, scale[5], 450);
    delay(500);

    tone(8, scale[6], 450);
    delay(500);
    tone(8, scale[6], 450);
    delay(500);

    tone(8, scale[5], 450);
    delay(500);
    tone(8, scale[5], 450);
    delay(500);

    tone(8, scale[3], 900);
    delay(1000);
    
    if(isOdd){

        tone(8, scale[5], 450);
        delay(500);
        tone(8, scale[5], 450);
        delay(500);

        tone(8, scale[3], 450);
        delay(500);
        tone(8, scale[3], 450);
        delay(500);

        tone(8, scale[2], 1350);
        delay(2000);

    } else {
        tone(8, scale[5], 450);
        delay(500);
        tone(8, scale[3], 450);
        delay(500);

        tone(8, scale[2], 450);
        delay(500);
        tone(8, scale[3], 450);
        delay(500);

        tone(8, scale[1], 1350);
        delay(2000);
        noTone(8);
    }
    isOdd = !isOdd;
}

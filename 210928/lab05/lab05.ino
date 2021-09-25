// 201533631 김도균
int pinNum[] = {8, 9, 10, 11, 12, 6, 7, 5};

void write7Segment(String input) {
    int result[8] = {1, 1, 1, 1, 1, 1, 1, 1};

    for(int i = 0; i < input.length(); i++)
        result[(int)(input[i] - 'a')] = 0;
    
    for(int i=0; i < 8; i++)
        digitalWrite(pinNum[i], result[i]);

    return;
}


void setup() {
    Serial.begin(9600);
    for(int i = 0; i < 8; i++)
        pinMode(pinNum[i], OUTPUT);
}


void loop() {
    
    write7Segment("");

    for(int j=0; j<3; j++){
        for(int i=0; i<256; i++){
            analogWrite(pinNum[7], 255 - i);
            delayMicroseconds(800);
        }
        for(int i=0; i<256; i++){
            analogWrite(pinNum[7], i);
            delayMicroseconds(800);
        }

    }
    delay(1000);

    // 9
    write7Segment("abcdfg");
    delay(1000);

    // 8
    write7Segment("abcdefg");
    delay(1000);

    // 7
    write7Segment("abcf");
    delay(1000);

    // 6
    write7Segment("acdegf");
    delay(1000);

    // 5
    write7Segment("acdfg");
    delay(1000);

    // 4
    write7Segment("bcfg");
    delay(1000);

    // 3
    write7Segment("abcdg");
    delay(1000);

    // 2
    write7Segment("abdeg");
    delay(1000);

    // 1
    write7Segment("bc");
    delay(1000);

    // 0
    write7Segment("abcdef");
    delay(1000);

    // off
    write7Segment("");
    delay(1000);

}



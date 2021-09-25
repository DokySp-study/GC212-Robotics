// 201533631 김도균

void setup() {
    Serial.begin(9600);
    pinMode(8, INPUT);
    pinMode(9, INPUT);
}


void loop() {
    static int counter = 0;
    static bool is8Clicked = false;    
    static bool is9Clicked = false;
    
    if(digitalRead(8)){
        is8Clicked = true;
        Serial.println(++counter);

        while(is8Clicked){
            is8Clicked = digitalRead(8);
            delay(50);
        }
    }
	    
    if(digitalRead(9)){
        is9Clicked = true;
        counter = 0;
        Serial.println(counter);

        while(is9Clicked){
            is9Clicked = digitalRead(9);
            delay(50);
        }
    }

    
}

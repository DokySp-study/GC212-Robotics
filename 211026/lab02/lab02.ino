// 201533631 김도균

#define DO 2
#define RE 3
#define MI 4

void setup() {
    pinMode(DO, INPUT);
    pinMode(RE, INPUT);
    pinMode(MI, INPUT);
}

double scale[] = {
    0,
    0,
    261.63,
    293.66,
    329.63,
};

void loop() {
    static int pushedIdx = 0;
    static bool isButtonPushed = false;

    if(!isButtonPushed && digitalRead(DO) == HIGH){
        isButtonPushed = true;
        pushedIdx = DO;
        while(digitalRead(DO) != LOW){
            tone(8, scale[pushedIdx], 10);
        }
        
        isButtonPushed = false;
        pushedIdx = 0;
    }



    if(!isButtonPushed && digitalRead(RE) == HIGH){
        isButtonPushed = true;
        pushedIdx = RE;
        while(digitalRead(RE) != LOW){
            tone(8, scale[pushedIdx], 10);
        }
        
        isButtonPushed = false;
        pushedIdx = 0;
    }


    if(!isButtonPushed && digitalRead(MI) == HIGH){
        isButtonPushed = true;
        pushedIdx = MI;
        while(digitalRead(MI) != LOW){
            tone(8, scale[pushedIdx], 10);
        }
        
        isButtonPushed = false;
        pushedIdx = 0;
    }

}

// 201533631 김도균
#include <LiquidCrystal.h>

LiquidCrystal display(12, 11, 5, 4, 3, 2);

void setup() {
    display.begin(16, 2);
    display.setCursor(0, 0);
    display.print("Hello World!");
}

void loop() {

    if(analogRead(A0) > 512) {
        display.display();
    } else {
        display.noDisplay();
    }

}

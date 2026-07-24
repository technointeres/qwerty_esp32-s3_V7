void LAYOUT_IND() {
    //if(numButton1 == 15 && (millis() - timeLayout) > 200) {
                         if(layout == 1) {layout = 2; strip1.setPixelColor(5, strip1.Color(   0,  55,  0)); //strip1.show(); //RU
                                                      strip1.setPixelColor(6, strip1.Color( 155,   0,  0)); strip1.show(); //EN 
                                  } else {layout = 1; strip1.setPixelColor(5, strip1.Color( 155,   0,  0)); //strip1.show(); //RU
                                                      strip1.setPixelColor(6, strip1.Color(   0,  55,  0)); strip1.show(); //EN 
                                  } timeLayout = millis();
                                  //}
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CHANGE_COLOR_TOP() {

strip1.setBrightness(255);
colorWipe1(strip1.Color(0,  0,  0), 0); //

 //pinMode(0, INPUT_PULLUP);
    //if(digitalRead(0) == 0 && (millis() - timeColorT) > 200) {
                        if(colorNextT == 1) {
                         strip1.setPixelColor(0, strip1.Color(255,  0,  0)); //
                         strip1.setPixelColor(1, strip1.Color(255,  0,  0)); //
                         strip1.setPixelColor(2, strip1.Color(255,  0,  0)); //
                         strip1.setPixelColor(3, strip1.Color(255,  0,  0)); //
                         strip1.setPixelColor(4, strip1.Color(255,  0,  0)); //
                         strip1.setPixelColor(5, strip1.Color(255,  0,  0)); //
                         strip1.setPixelColor(6, strip1.Color(255,  0,  0)); strip1.show(); 
                         colorNextT = 2; timeColorT = millis(); goto daT;
                                           }
                        if(colorNextT == 2) {
                         strip1.setPixelColor(0, strip1.Color(  0,255,  0)); //
                         strip1.setPixelColor(1, strip1.Color(  0,255,  0)); //
                         strip1.setPixelColor(2, strip1.Color(  0,255,  0)); //
                         strip1.setPixelColor(3, strip1.Color(  0,255,  0)); //
                         strip1.setPixelColor(4, strip1.Color(  0,255,  0)); //
                         strip1.setPixelColor(5, strip1.Color(  0,255,  0)); //
                         strip1.setPixelColor(6, strip1.Color(  0,255,  0)); strip1.show(); 
                         colorNextT = 3; timeColorT = millis(); goto daT;
                                           }
                        if(colorNextT == 3) {
                         strip1.setPixelColor(0, strip1.Color(  0,  0,255)); //
                         strip1.setPixelColor(1, strip1.Color(  0,  0,255)); //
                         strip1.setPixelColor(2, strip1.Color(  0,  0,255)); //
                         strip1.setPixelColor(3, strip1.Color(  0,  0,255)); //
                         strip1.setPixelColor(4, strip1.Color(  0,  0,255)); //
                         strip1.setPixelColor(5, strip1.Color(  0,  0,255)); //
                         strip1.setPixelColor(6, strip1.Color(  0,  0,255)); strip1.show(); 
                         colorNextT = 4; timeColorT = millis(); goto daT;
                                           }
                        if(colorNextT == 4) {
                         strip1.setPixelColor(0, strip1.Color(255,  0,255)); //
                         strip1.setPixelColor(1, strip1.Color(255,  0,255)); //
                         strip1.setPixelColor(2, strip1.Color(255,  0,255)); //
                         strip1.setPixelColor(3, strip1.Color(255,  0,255)); //
                         strip1.setPixelColor(4, strip1.Color(255,  0,255)); //
                         strip1.setPixelColor(5, strip1.Color(255,  0,255)); //
                         strip1.setPixelColor(6, strip1.Color(255,  0,255)); strip1.show(); 
                         colorNextT = 1; timeColorT = millis(); goto daT;
                                           }
                                                           //} 
                                                           daT:
}
void CHANGE_COLOR_MODULE() {
    // pinMode(0, INPUT_PULLUP);
    // if(digitalRead(0) == 0 && (millis() - timeColor) > 200) {
                        if(colorNext == 1) {
                         strip.setPixelColor(0, strip1.Color(255,  0,  0)); //strip.show(); 
                         strip.setPixelColor(1, strip1.Color(255,  0,  0)); //strip.show(); 
                         strip.setPixelColor(2, strip1.Color(255,  0,  0)); //strip.show();
                         strip.setPixelColor(3, strip1.Color(255,  0,  0)); strip.show(); 
                         colorNext = 2; timeColor = millis(); goto da;
                                           }
                        if(colorNext == 2) {
                         strip.setPixelColor(0, strip1.Color(  0,255,  0)); //strip.show(); 
                         strip.setPixelColor(1, strip1.Color(  0,255,  0)); //strip.show(); 
                         strip.setPixelColor(2, strip1.Color(  0,255,  0)); //strip.show();
                         strip.setPixelColor(3, strip1.Color(  0,255,  0)); strip.show(); 
                         colorNext = 3; timeColor = millis(); goto da;
                                           }
                        if(colorNext == 3) {
                         strip.setPixelColor(0, strip1.Color(  0,  0,255)); //strip.show(); 
                         strip.setPixelColor(1, strip1.Color(  0,  0,255)); //strip.show(); 
                         strip.setPixelColor(2, strip1.Color(  0,  0,255)); //strip.show();
                         strip.setPixelColor(3, strip1.Color(  0,  0,255)); strip.show(); 
                         colorNext = 4; timeColor = millis(); goto da;
                                           }
                        if(colorNext == 4) {
                         strip.setPixelColor(0, strip1.Color(255,  0,255)); //strip.show(); 
                         strip.setPixelColor(1, strip1.Color(255,  0,255)); //strip.show(); 
                         strip.setPixelColor(2, strip1.Color(255,  0,255)); //strip.show();
                         strip.setPixelColor(3, strip1.Color(255,  0,255)); strip.show(); 
                         colorNext = 1; timeColor = millis(); goto da;
                                           }
                                                           //}
                                                            da: 
}
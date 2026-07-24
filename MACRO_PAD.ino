
// const int buttonPin1 = 7;
// //int previousButtonState1 = LOW;
// const int buttonPin2 = 6;
// i//nt previousButtonState2 = LOW;
// const int buttonPin3 = 5;
// //int previousButtonState3 = LOW;

void MACRO_PAD() {
   pinMode(buttonPin1, INPUT_PULLDOWN);  pinMode(buttonPin2, INPUT_PULLDOWN);  pinMode(buttonPin3, INPUT_PULLDOWN);
   //ConsumerControl.begin();
   //Keyboard.begin();
   //USB.begin();
   //pinMode(buttonPin1, INPUT_PULLDOWN);  pinMode(buttonPin2, INPUT_PULLDOWN);  pinMode(buttonPin3, INPUT_PULLDOWN);
int xq = -5; //VERTICAL SHIFT
int pc = 1;

strip.setBrightness(100);
colorWipe(strip.Color(0,  0,  0), 0); //MODULE
strip.setPixelColor(0, strip.Color(255,  0,255)); //PIXEL 1
strip.setPixelColor(1, strip.Color(255,  0,255)); //PIXEL 2
strip.setPixelColor(2, strip.Color(255,  0,255)); //PIXEL 3
strip.setPixelColor(3, strip.Color(255,  0,255)); //PIXEL 3
strip.show();
DispW = 320; tft.setRotation(1);
uint16_t wall = color565(185,0,0); tft.fillScreen(wall);
  startX = 2; startY = 1; scaleX = 2; scaleY = 1; charColo = color565(255,0,255); symbolDraw(168); //>>
  startX = 292; startY = 1; scaleX = 2; scaleY = 1; charColo = color565(255,0,255); symbolDraw(167); //<<
  startX = 45; startY = 1; scaleX = 2; scaleY = 1; charColo = color565(255,0,255); MyText = "MACRO PAD"; event(); //X=45

  startX = 34;  startY = xq+31; scaleX = 1; scaleY = 2; charColo = color565(255,255,255); MyText = "VOL-"; event(); 
  startX = 121; startY = xq+31; scaleX = 1; scaleY = 2; charColo = color565(255,255,255); MyText = "PLAY/P"; event();  
  startX = 232; startY = xq+31; scaleX = 1; scaleY = 2; charColo = color565(255,255,255); MyText = "VOL+"; event(); 

  startX = 34;  startY = xq+84; scaleX = 1; scaleY = 2; charColo = color565(255,255,255); MyText = "COPY"; event(); 
  startX = 126; startY = xq+84; scaleX = 1; scaleY = 2; charColo = color565(255,255,255); MyText = "PASTE"; event();  
  startX = 227; startY = xq+84; scaleX = 1; scaleY = 2; charColo = color565(255,255,255); MyText = "CLOSE"; event(); 

  startX = 34;  startY = xq+137; scaleX = 1; scaleY = 2; charColo = color565(255,255,255); MyText = "LEFT"; event(); 
  startX = 132; startY = xq+137; scaleX = 1; scaleY = 2; charColo = color565(255,255,255); MyText = "MENU"; event(); 
  startX = 227; startY = xq+137; scaleX = 1; scaleY = 2; charColo = color565(255,255,255); MyText = "RIGHT"; event(); 

  startX = 34;  startY = xq+190; scaleX = 1; scaleY = 2; charColo = color565(255,255,255); MyText = "BROW"; event(); 
  startX = 132; startY = xq+190; scaleX = 1; scaleY = 2; charColo = color565(255,255,255); MyText = " UP "; event(); 
  startX = 231; startY = xq+190; scaleX = 1; scaleY = 2; charColo = color565(255,255,255); MyText = "DOWN"; event(); 

  startX = 0;   startY = xq+16;  scaleX = 2; scaleY = 3; charColo = color565(255,255,255); MyText = "["; event();
  startX = 100; startY = xq+30;  scaleX = 1; scaleY = 2; charColo = color565(0,80,255); MyText = "/       /"; event();
  startX = 292; startY = xq+16;  scaleX = 2; scaleY = 3; charColo = color565(255,255,255); MyText = "]"; event();
  startX = 100; startY = xq+83;  scaleX = 1; scaleY = 2; charColo = color565(0,80,255); MyText = "/       /"; event();
  startX = 100; startY = xq+136; scaleX = 1; scaleY = 2; charColo = color565(0,80,255); MyText = "/       /"; event();
  startX = 100; startY = xq+189; scaleX = 1; scaleY = 2; charColo = color565(0,80,255); MyText = "/       /"; event();

     while(numButton1 != 13 && numButton0 != 5) { PressedButton(1); PressedButton(2);
if(digitalRead(0) == 0 && (millis() - timeColorT) > 200) {CHANGE_COLOR_TOP();}
if(numButton1 == 15 && (millis() - timeLayout) > 200)    {LAYOUT_IND();}
if(numButton4 == 12 && (millis() - timeColor) > 200)     {CHANGE_COLOR_MODULE();}
////////////////

////////////////

      if(numButton0 == 4 && pc < 4) { pc ++ ; //DOWN
      tft.fillRect(0,  25, 21, 217, wall);
      tft.fillRect(299,25, 21, 217, wall);
  startX = 0;   startY = xq+(pc*53)-37;  scaleX = 2; scaleY = 3; charColo = color565(255,255,255); MyText = "["; event();
  startX = 292; startY = xq+(pc*53)-37;  scaleX = 2; scaleY = 3; charColo = color565(255,255,255); MyText = "]"; event();
  delay(150);
                                    }
      if(numButton0 == 3 && pc > 1) { pc -- ; //UP
      tft.fillRect(0,  25, 21, 217, wall);
      tft.fillRect(299,25, 21, 217, wall);
  startX = 0;   startY = xq+(pc*53)-37;  scaleX = 2; scaleY = 3; charColo = color565(255,255,255); MyText = "["; event();
  startX = 292; startY = xq+(pc*53)-37;  scaleX = 2; scaleY = 3; charColo = color565(255,255,255); MyText = "]"; event();
  delay(150);
                                    }   

  int buttonState1 = digitalRead(buttonPin1); //LEFT COLUMN
  if ((buttonState1 == HIGH)) {
   switch (pc) {
  case 1:
         ConsumerControl.press(CONSUMER_CONTROL_VOLUME_DECREMENT);
         ConsumerControl.release(); delay(50);
  break;
  case 2:
      Keyboard.press(KEY_LEFT_CTRL);
      Keyboard.press('c'); delay(20);
      Keyboard.releaseAll(); delay(150);
  break;
  case 3:
      Keyboard.press(KEY_LEFT_ARROW); delay(20);
      Keyboard.releaseAll(); delay(50);
  break;
  case 4:
      ConsumerControl.press(CONSUMER_CONTROL_LOCAL_BROWSER); delay(20);
      ConsumerControl.release(); delay(150);
  break;
               }
                              } //LEFT COLUMN
/////                            
  int buttonState2 = digitalRead(buttonPin2); //MIDDLE COLUMN
  if ((buttonState2 == HIGH)) {
   switch (pc) {
  case 1:
        ConsumerControl.press(CONSUMER_CONTROL_PLAY_PAUSE);
        ConsumerControl.release(); delay(200); 
  break;
  case 2:
      Keyboard.press(KEY_LEFT_CTRL);
      Keyboard.press('v'); delay(20);
      Keyboard.releaseAll(); delay(150);
  break;
  case 3:
      Keyboard.press(KEY_LEFT_GUI); delay(20);
      Keyboard.releaseAll(); delay(170);
  break;
  case 4:
      Keyboard.press(KEY_UP_ARROW); delay(20);
      Keyboard.releaseAll(); delay(170);
  break;
               }
                              } //MIDDLE COLUMN
/////                       
  int buttonState3 = digitalRead(buttonPin3); //RIGHT COLUMN
  if ((buttonState3 == HIGH)) {
   switch (pc) {
  case 1:
         ConsumerControl.press(CONSUMER_CONTROL_VOLUME_INCREMENT);
         ConsumerControl.release(); delay(50);
  break;
  case 2:
      Keyboard.press(KEY_LEFT_ALT);
      Keyboard.press(KEY_F4); delay(20);
      Keyboard.releaseAll(); delay(150);
  break;
  case 3:
      Keyboard.press(KEY_RIGHT_ARROW); delay(20);
      Keyboard.releaseAll(); delay(50);
  break;
  case 4:
      Keyboard.press(KEY_DOWN_ARROW); delay(20);
      Keyboard.releaseAll(); delay(50);
  break;
               }
                              } //RIGHT COLUMN
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//   CHECK_SYMBOL();   
      //Keyboard.releaseAll(); delay(50);
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
} //
DispW = 240; tft.setRotation(0); 
scaleX = 1; scaleY = 1; 
colorWipe(strip.Color(0,  0,  0), 0); //MODULE   
// pinMode(buttonPin1, INPUT);  
// pinMode(buttonPin2, INPUT);  
// pinMode(buttonPin3, INPUT);
   //ConsumerControl.end();
   //Keyboard.end();
}


void CHECK_SYMBOL() {       
  int pa = 170;
  Ex = digitalRead(47); Sh = digitalRead(21);
    if(numButton0 == 6) {Keyboard.press(KEY_RETURN); delay(20); Keyboard.releaseAll(); delay(pa); goto forfast;}
    //if(numButton0 == 5) {Keyboard.press(KEY_ESC); delay(20); Keyboard.releaseAll(); delay(pa); goto forfast;}
    if(numButton0 == 2) {Keyboard.press(KEY_UP_ARROW ); delay(20); Keyboard.releaseAll(); delay(pa); goto forfast;}
    if(numButton0 == 3) {Keyboard.press(KEY_RIGHT_ARROW ); delay(20); Keyboard.releaseAll(); delay(pa); goto forfast;}
    if(numButton0 == 4) {Keyboard.press(KEY_LEFT_ARROW ); delay(20); Keyboard.releaseAll(); delay(pa); goto forfast;}
    if(numButton0 == 1) {Keyboard.press(KEY_DOWN_ARROW ); delay(20); Keyboard.releaseAll(); delay(pa); goto forfast;}


    if(numButton1 == 16){Keyboard.press('`'); if(Sh == 1) {Keyboard.press('~');} if(Ex == 1) {Keyboard.press('~');} Keyboard.releaseAll(); delay(pa); goto forfast;}
    if(numButton1 == 14){Keyboard.press(KEY_BACKSPACE); delay(20); Keyboard.releaseAll(); delay(pa); goto forfast;}
    
    //if(numButton1 == 13){} //MENU
    if(numButton1 == 12){Keyboard.press('+'); if(Sh == 1) {Keyboard.press('/');} if(Ex == 1) {Keyboard.press('=');} Keyboard.releaseAll(); delay(pa); goto forfast;}                   
    if(numButton1 == 11){Keyboard.press('-'); if(Sh == 1) {Keyboard.press('\134');} if(Ex == 1) {Keyboard.press('|');} Keyboard.releaseAll(); delay(pa); goto forfast;}
    if(numButton1 == 10){Keyboard.press('0'); if(Sh == 1) {Keyboard.press(')');} if(Ex == 1) {Keyboard.press(')');} Keyboard.releaseAll(); delay(pa); goto forfast;}
    if(numButton1 == 9) {Keyboard.press('9'); if(Sh == 1) {Keyboard.press('(');} if(Ex == 1) {Keyboard.press('(');} Keyboard.releaseAll(); delay(pa); goto forfast;}
    if(numButton1 == 7) {Keyboard.press('8'); if(Sh == 1) {Keyboard.press('*');} if(Ex == 1) {Keyboard.press('*');} Keyboard.releaseAll(); delay(pa); goto forfast;}
    if(numButton1 == 6) {Keyboard.press('7'); if(Sh == 1) {Keyboard.press('?');} if(Ex == 1) {Keyboard.press('&');} Keyboard.releaseAll(); delay(pa); goto forfast;} 
    if(numButton1 == 5) {Keyboard.press('6'); if(Sh == 1) {Keyboard.press(':');} if(Ex == 1) {Keyboard.press('^');} Keyboard.releaseAll(); delay(pa); goto forfast;}
    if(numButton1 == 4) {Keyboard.press('5'); if(Sh == 1) {Keyboard.press('%');} if(Ex == 1) {Keyboard.press('%');} Keyboard.releaseAll(); delay(pa); goto forfast;} 
    if(numButton1 == 3) {Keyboard.press('4'); if(Sh == 1) {Keyboard.press(';');} if(Ex == 1) {Keyboard.press('$');} Keyboard.releaseAll(); delay(pa); goto forfast;}
    if(numButton1 == 2) {Keyboard.press('3'); if(Sh == 1) {Keyboard.press('#');} if(Ex == 1) {Keyboard.press('№');} Keyboard.releaseAll(); delay(pa); goto forfast;} 
    if(numButton1 == 1) {Keyboard.press('2'); if(Sh == 1) {Keyboard.press('\42');} if(Ex == 1) {Keyboard.press('@');} Keyboard.releaseAll(); delay(pa); goto forfast;}
    if(numButton1 == 0) {Keyboard.press('1'); if(Sh == 1) {Keyboard.press('!');} if(Ex == 1) {Keyboard.press('!');} Keyboard.releaseAll(); delay(pa); goto forfast;} 

    if(numButton2 == 12){Keyboard.press(']'); if(Sh == 1) {Keyboard.press('}');} if(Ex == 1) {Keyboard.press('}');} Keyboard.releaseAll(); delay(pa); goto forfast;}
    if(numButton2 == 11){Keyboard.press('['); if(Sh == 1) {Keyboard.press('{');} if(Ex == 1) {Keyboard.press('{');} Keyboard.releaseAll(); delay(pa); goto forfast;}     
    if(numButton2 == 10){Keyboard.press('p'); if(Sh == 1) {Keyboard.press('P');} if(Ex == 1) {} Keyboard.releaseAll(); delay(pa); goto forfast;}
    if(numButton2 == 9) {Keyboard.press('o'); if(Sh == 1) {Keyboard.press('O');} if(Ex == 1) {} Keyboard.releaseAll(); delay(pa); goto forfast;}
    if(numButton2 == 8) {Keyboard.press('i'); if(Sh == 1) {Keyboard.press('I');} if(Ex == 1) {} Keyboard.releaseAll(); delay(pa); goto forfast;}
    if(numButton2 == 7) {Keyboard.press('u'); if(Sh == 1) {Keyboard.press('U');} if(Ex == 1) {} Keyboard.releaseAll(); delay(pa); goto forfast;}
    if(numButton2 == 5) {Keyboard.press('y'); if(Sh == 1) {Keyboard.press('Y');} if(Ex == 1) {} Keyboard.releaseAll(); delay(pa); goto forfast;}
    if(numButton2 == 4) {Keyboard.press('t'); if(Sh == 1) {Keyboard.press('T');} if(Ex == 1) {} Keyboard.releaseAll(); delay(pa); goto forfast;} 
    if(numButton2 == 3) {Keyboard.press('r'); if(Sh == 1) {Keyboard.press('R');} if(Ex == 1) {} Keyboard.releaseAll(); delay(pa); goto forfast;}
    if(numButton2 == 2) {Keyboard.press('e'); if(Sh == 1) {Keyboard.press('E');} if(Ex == 1) {} Keyboard.releaseAll(); delay(pa); goto forfast;} 
    if(numButton2 == 1) {Keyboard.press('w'); if(Sh == 1) {Keyboard.press('W');} if(Ex == 1) {} Keyboard.releaseAll(); delay(pa); goto forfast;}
    if(numButton2 == 0) {Keyboard.press('q'); if(Sh == 1) {Keyboard.press('Q');} if(Ex == 1) {} Keyboard.releaseAll(); delay(pa); goto forfast;} 

    if(numButton3 == 12){Keyboard.press('\40'); if(Sh == 1) {Keyboard.press('_');}   if(Ex == 1) {Keyboard.press('_');}  Keyboard.releaseAll(); delay(pa); goto forfast;}
    if(numButton3 == 11){Keyboard.press('\42'); if(Sh == 1) {Keyboard.press('\42');} if(Ex == 1) {Keyboard.press('\42');} Keyboard.releaseAll(); delay(pa); goto forfast;}
    if(numButton3 == 10){Keyboard.press(';');   if(Sh == 1) {Keyboard.press(':');}   if(Ex == 1) {Keyboard.press(':');}  Keyboard.releaseAll(); delay(pa); goto forfast;}
    if(numButton3 == 9) {Keyboard.press('l');   if(Sh == 1) {Keyboard.press('L');}   if(Ex == 1) {} Keyboard.releaseAll(); delay(pa); goto forfast;}
    if(numButton3 == 8) {Keyboard.press('k');   if(Sh == 1) {Keyboard.press('K');}   if(Ex == 1) {} Keyboard.releaseAll(); delay(pa); goto forfast;}
    if(numButton3 == 7) {Keyboard.press('j');   if(Sh == 1) {Keyboard.press('J');}   if(Ex == 1) {} Keyboard.releaseAll(); delay(pa); goto forfast;} 
    if(numButton3 == 5) {Keyboard.press('h');   if(Sh == 1) {Keyboard.press('H');}   if(Ex == 1) {} Keyboard.releaseAll(); delay(pa); goto forfast;} 
    if(numButton3 == 4) {Keyboard.press('g');   if(Sh == 1) {Keyboard.press('G');}   if(Ex == 1) {} Keyboard.releaseAll(); delay(pa); goto forfast;}
    if(numButton3 == 3) {Keyboard.press('f');   if(Sh == 1) {Keyboard.press('F');}   if(Ex == 1) {} Keyboard.releaseAll(); delay(pa); goto forfast;} 
    if(numButton3 == 2) {Keyboard.press('d');   if(Sh == 1) {Keyboard.press('D');}   if(Ex == 1) {} Keyboard.releaseAll(); delay(pa); goto forfast;}
    if(numButton3 == 1) {Keyboard.press('s');   if(Sh == 1) {Keyboard.press('S');}   if(Ex == 1) {} Keyboard.releaseAll(); delay(pa); goto forfast;}  
    if(numButton3 == 0) {Keyboard.press('a');   if(Sh == 1) {Keyboard.press('A');}   if(Ex == 1) {} Keyboard.releaseAll(); delay(pa); goto forfast;}            

    //if(numButton4 == 12){   if(Sh == 1) {}   if(Ex == 1) {} Keyboard.releaseAll(); delay(pa); goto forfast;}  //BRIGHTNESS
    //if(numButton4 == 11){   if(Sh == 1) {}   if(Ex == 1) {} Keyboard.releaseAll(); delay(pa); goto forfast;}  //BRIGHTNESS
    if(numButton4 == 10){Keyboard.press('.');   if(Sh == 1) {Keyboard.press(',');}   if(Ex == 1) {Keyboard.press('?');} Keyboard.releaseAll(); delay(pa); goto forfast;}
    if(numButton4 == 9) {Keyboard.press('.');   if(Sh == 1) {Keyboard.press('>');}   if(Ex == 1) {Keyboard.press('.');} Keyboard.releaseAll(); delay(pa); goto forfast;}
    if(numButton4 == 8) {Keyboard.press(',');   if(Sh == 1) {Keyboard.press('<');}   if(Ex == 1) {Keyboard.press(',');} Keyboard.releaseAll(); delay(pa); goto forfast;}
    if(numButton4 == 7) {Keyboard.press('m');   if(Sh == 1) {Keyboard.press('M');}   if(Ex == 1) {} Keyboard.releaseAll(); delay(pa); goto forfast;} 
    if(numButton4 == 5) {Keyboard.press('n');   if(Sh == 1) {Keyboard.press('N');}   if(Ex == 1) {} Keyboard.releaseAll(); delay(pa); goto forfast;} 
    if(numButton4 == 4) {Keyboard.press('b');   if(Sh == 1) {Keyboard.press('B');}   if(Ex == 1) {} Keyboard.releaseAll(); delay(pa); goto forfast;}
    if(numButton4 == 3) {Keyboard.press('v');   if(Sh == 1) {Keyboard.press('V');}   if(Ex == 1) {} Keyboard.releaseAll(); delay(pa); goto forfast;} 
    if(numButton4 == 2) {Keyboard.press('c');   if(Sh == 1) {Keyboard.press('C');}   if(Ex == 1) {} Keyboard.releaseAll(); delay(pa); goto forfast;}
    if(numButton4 == 1) {Keyboard.press('x');   if(Sh == 1) {Keyboard.press('X');}   if(Ex == 1) {} Keyboard.releaseAll(); delay(pa); goto forfast;}  
    if(numButton4 == 0) {Keyboard.press('z');   if(Sh == 1) {Keyboard.press('Z');}   if(Ex == 1) {} Keyboard.releaseAll(); delay(pa); goto forfast;}                 
    
      
   forfast:     
}





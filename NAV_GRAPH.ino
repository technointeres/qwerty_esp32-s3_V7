void NAV_GRAPH() {
 uint16_t SGColor = color565(255,255,255);
 uint16_t rectColor = color565(255,0,255);
 numButton0 = -1; numButton1 = -1; delay(200);
tft.fillScreen(BackColor);
MyText = "Мониторинг опт-х"; startX = 16; startY = 2; charColo = TFT_WHITE; event();
MyText = "сенсоров"; startX = 65; startY = 24; charColo = TFT_WHITE; event();
MyText = "Esc"; startX = 20; startY = 238; charColo = TFT_WHITE; event();
MyText = "Enter"; startX = 167; startY = 238; charColo = TFT_WHITE; event();
MyText = "Sp = на весь экран"; startX = 3; startY = 270; charColo = TFT_WHITE; event();
MyText = "Меню = выход"; startX = 39; startY = 295; charColo = TFT_WHITE; event();
startX = 20; startY = 61; symbolDraw(167);
startX = 210; startY = 61; symbolDraw(168);
startX = 113; startY = 61; symbolDraw(169);
startX = 113; startY = 241; symbolDraw(170);

tft.drawRect(2, 89, 77, 70, rectColor);
tft.drawRect(82, 89, 77, 70, rectColor);
tft.drawRect(162, 89, 77, 70, rectColor);
tft.drawRect(2, 167, 77, 70, rectColor);
tft.drawRect(82, 167, 77, 70, rectColor);
tft.drawRect(162, 167, 77, 70, rectColor);

 double timDraw = millis(); int memo[241]; int r = 0; int vShift = 147;
 int memo1[241]; int memo2[241]; int memo3[241]; int memo4[241]; int memo5[241];
 for (int q = 0; q < 241; q++) {memo[q] = -1; memo1[q] = -1; memo2[q] = -1; memo3[q] = -1; memo4[q] = -1; memo5[q] = -1;}

//PressedButton(0);
    while(numButton1 != 13) { PressedButton(2); //PressedButton(1);
                             if(numButton3 == 12) {GRAPH_FULL(); break;} //GO TO MENU
                                         

     if((millis() - timDraw) > 0) {
//////////////////////////////////////////////////////////////////////////////////////////////////////////////      
                                                if(r < -19) {r = 0;}
                   for (int z=r; z < 240; z+= 20) {tft.fillRect(z,162, 2,2,BackColor);} r -= 1; 
                   for (int z=r; z < 240; z+= 20) {tft.fillRect(z,162, 2,2,TFT_WHITE);} //DOTS                                      
//////////////////////////////////////////////////////////////////////////////////////////////////////////////                                             
                                                for (int x = 3; x < 78; x++) { //LEFT       
                                                                tft.drawFastVLine(x,vShift - memo[x],10, BackColor);
                                                                if(x != 77) {memo[x] = memo[x+1];
                                                                  if(memo[x] != -1) {tft.drawFastVLine(x,vShift - memo[x],10, SGColor);}}
                                                                if(x == 77) {memo[x] = analogRead(2)/75+0; tft.drawFastVLine(x,vShift - memo[x],10, SGColor);} 
                                                                              } //timDraw = millis();
                                                                              //if(analogRead(7) > 3000) {}
                                                                              //else {}

                                                for (int y = 3+80; y < 78+80; y++) { //UP        
                                                                tft.drawFastVLine(y,vShift - memo1[y],10, BackColor);
                                                                if(y != 77+80) {memo1[y] = memo1[y+1];
                                                                  if(memo1[y] != -1) {tft.drawFastVLine(y,vShift - memo1[y],10, SGColor);}}
                                                                if(y == 77+80) {memo1[y] = analogRead(14)/75+0; tft.drawFastVLine(y,vShift - memo1[y],10, SGColor);} 
                                                                              } //timDraw = millis();
                                                                              
                                                for (int m = 3+160; m < 78+160; m++) { //RIGHT          
                                                                tft.drawFastVLine(m,vShift - memo2[m],10, BackColor);
                                                                if(m != 77+160) {memo2[m] = memo2[m+1];
                                                                  if(memo2[m] != -1) {tft.drawFastVLine(m,vShift - memo2[m],10, SGColor);}}
                                                                if(m == 77+160) {memo2[m] = analogRead(13)/75+0; tft.drawFastVLine(m,vShift - memo2[m],10, SGColor);} 
                                                                              } //timDraw = millis();
                                                                              //if(analogRead(5) > 3000) {}
                                                                              //else {} 
                                                for (int x1 = 3; x1 < 78; x1++) { //ESC          
                                                                tft.drawFastVLine(x1,vShift - memo3[x1],10, BackColor);
                                                                if(x1 != 77) {memo3[x1] = memo3[x1+1];
                                                                  if(memo3[x1] != -1) {tft.drawFastVLine(x1,vShift - memo3[x1],10, SGColor);}}
                                                                if(x1 == 77) {memo3[x1] = analogRead(12)/75-77; tft.drawFastVLine(x1,vShift - memo3[x1],10, SGColor);} 
                                                                              } //timDraw = millis();

                                                for (int y1 = 3+80; y1 < 78+80; y1++) { //DOWN    
                                                                tft.drawFastVLine(y1,vShift - memo4[y1],10, BackColor);
                                                                if(y1 != 77+80) {memo4[y1] = memo4[y1+1];
                                                                  if(memo4[y1] != -1) {tft.drawFastVLine(y1,vShift - memo4[y1],10, SGColor);}}
                                                                if(y1 == 77+80) {memo4[y1] = analogRead(11)/75-77; tft.drawFastVLine(y1,vShift - memo4[y1],10, SGColor);} 
                                                                              } //timDraw = millis();
                                                                              
                                                for (int m1 = 3+160; m1 < 78+160; m1++) { //ENTER          
                                                                tft.drawFastVLine(m1,vShift - memo5[m1],10, BackColor);
                                                                if(m1 != 77+160) {memo5[m1] = memo5[m1+1];
                                                                  if(memo5[m1] != -1) {tft.drawFastVLine(m1,vShift - memo5[m1],10, SGColor);}}
                                                                if(m1 == 77+160) {memo5[m1] = analogRead(10)/75-77; tft.drawFastVLine(m1,vShift - memo5[m1],10, SGColor);} 
                                                                              } timDraw = millis();  
                                                                                                  
                                  }   
                                                } // END WHILE
                     }
//////////////////////////////////////////////////////////////////////////////////////////////////////////
void GRAPH_FULL() {

 numButton0 = -1; numButton1 = -1; delay(200);
 //tft.setTextSize(3);
 int dat;
 uint16_t BColor = color565(  0,  0, 0);
 uint16_t GColor = color565(255,255,255);
 tft.fillScreen(BColor);
                                               tft.setFont(&fonts::Orbitron_Light_24);
                                               //tft.setTextColor(0xFFFFFFU, 0);
                                               tft.setTextDatum( textdatum_t::top_center); // 
                                               //tft.setFont(&fonts::Font4);
                                               //tft.setCursor(0, 0);
                                               //tft.setTextSize(3);
                                               tft.setTextPadding(100); //
  // &fonts::Font0                   
  // &fonts::Font2                  
  // &fonts::Font4                  
  // &fonts::Font6                  
  // &fonts::Font7                  
  // &fonts::Font8                  
  // &fonts::TomThumb              
  // &fonts::FreeMono9pt7b          
  // &fonts::FreeMonoBold9pt7b      
  // &fonts::FreeMonoOblique9pt7b   
  // &fonts::FreeMonoBoldOblique9pt7b
  // &fonts::FreeSans9pt7b           
  // &fonts::FreeSansBold9pt7b      
  // &fonts::FreeSansOblique9pt7b   
  // &fonts::FreeSansBoldOblique9pt7b
  // &fonts::FreeSerif9pt7b          
  // &fonts::FreeSerifBold9pt7b      
  // &fonts::FreeSerifItalic9pt7b   
  // &fonts::FreeSerifBoldItalic9pt7b
  // &fonts::Orbitron_Light_24       
  // &fonts::Roboto_Thin_24          
  // &fonts::Satisfy_24             
  // &fonts::Yellowtail_32 
//tft.drawBitmap(0, 0,  PHOTORESISTOR_BIG_PIC, 101, 83, TFT_WHITE);
//tft.drawFastHLine(0,86, 240, color565(255,255,255)); //CHART AREA TOP
//tft.drawFastHLine(0,188,240, color565(255,255,255)); //CHART AREA BOTTOM

                       //tft.setFreeFont(FM12); //OPTIONAL FONT //THE FONT FILE MUST BE IN THE FOLDER
                       //tft.setTextWrap(true);
                       //tft.setTextSize(1);
//                       tft.setCursor(0, 212);   tft.setTextColor(TFT_WHITE); tft.print("GND");
//                       tft.setCursor(198, 212); tft.setTextColor(TFT_WHITE); tft.print("3V3");
//tft.drawFastHLine(42,206, 17, color565(255,255,255)); //GND-
//tft.drawRect(59,198, 32,17, color565(255,255,255)); //RESISTOR
//tft.drawFastHLine(91,206, 55, color565(255,255,255)); //--
//tft.drawBitmap(146, 193,  PHOTORESISTOR_PIC, 32, 26, TFT_WHITE);
//tft.drawFastHLine(178,206,20, color565(255,255,255)); //-3V3 
//tft.drawCircle(120,206, 2, color565(255,255,255));    // DOT
//tft.drawFastVLine(120,206,13, color565(255,255,255)); // |

//startX = 204; startY = 15; scaleX = 2; scaleY = 2; MyText = "%"; event();
int Raw = 0, relRaw = 0, RawPrev = 0, relRawPrev = 0, Raw0 = 0, istab = 0; double timDraw = millis(); int memo[241]; int r = 0; int vShift = 0; int next = 0;//
                                                                                 for (int q = 0; q < 241; q++) {memo[q]   = -1;}
//charColo = TFT_WHITE; scaleX = 2; scaleY = 2;
                       //tft.setTextSize(1); tft.setFreeFont(FM24);
                       //tft.setCursor(206, 52); tft.setTextColor(TFT_WHITE); tft.print("%"); //%
//PressedButton(1);
    while(numButton1 != 13) { PressedButton(2); //PressedButton(1); //while(numButton0 != 5) { PressedButton(1); 
    istab += 1;
    dat = analogRead(10);
    Raw0 = Raw0 + dat; 
      if(istab > 4) { next = 1;//> 7
           Raw = Raw0/(istab);
           //relRaw = Raw/12.8-320;
           //if(relRaw > 100) {relRaw = 100;} if(relRaw < 0) {relRaw = 0;} // %
           
                   //if(relRaw != relRawPrev) {}//scaleX = 2; scaleY = 2; startX = 110; startY = 17;  MyText = relRawPrev; charColo = BackColor; event(); 
                                             //tft.setCursor(125, 52);  tft.setTextColor(BackColor); tft.print(relRawPrev); 
                                             //tft.setTextColor(BackColor, BackColor); tft.drawNumber(relRawPrev, 125, 22, 6);
                                             //scaleX = 2; scaleY = 2; startX = 110; startY = 17;  MyText = relRaw;     charColo = TFT_WHITE;     event(); relRawPrev = relRaw;} 
                                             //tft.setCursor(125, 52);  
                                             //tft.setTextColor(TFT_WHITE, BackColor); tft.drawNumber(relRaw, 125, 22, 6); relRawPrev = relRaw;}    //tft.print(relRaw); relRawPrev = relRaw;} //%  
                   //if(Raw != RawPrev)       {}//scaleX = 2; scaleY = 1; startX = 70;  startY = 215; MyText = RawPrev;    charColo = BackColor; event();  
                                             //tft.setCursor(66, 234); tft.setTextColor(BackColor);  tft.print(RawPrev);
                                             //tft.setTextColor(BackColor, BackColor); tft.drawNumber(RawPrev, 95, 220, 4);     
                                             //scaleX = 2; scaleY = 1; startX = 70;  startY = 215; MyText = Raw;        charColo = TFT_WHITE;     event(); RawPrev = Raw;} 
                                             //tft.setCursor(66, 234);  
                                             //tft.setTextColor(TFT_WHITE, BackColor); tft.drawNumber(Raw, 95, 220, 4); RawPrev = Raw;}//      tft.print(Raw);    RawPrev = Raw;}       //RAW 
                     istab = 0; Raw0 = 0;       
                    }

     if((millis() - timDraw) > 0 && next > 0) {
                                                tft.drawNumber(Raw, 120, 10);

                                                if(r < -19) {r = 0;}
                   for (int z=r; z < 240; z+= 20) {tft.fillRect(z,106, 2,2,BColor);    tft.fillRect(z,213, 2,2,BColor);   } r -= 1; 
                   for (int z=r; z < 240; z+= 20) {tft.fillRect(z,106, 2,2,TFT_WHITE); tft.fillRect(z,213, 2,2,TFT_WHITE);} //DOTS                                      
                                                
                                                for (int x = 0; x < 240; x++) {          
                                                                tft.drawFastVLine(x,vShift - memo[x],10, BColor);//tft.fillRect(x,vShift - memo[x], 1,10, BackColor); //BackColor
                                                                if(x != 239) {memo[x] = memo[x+1];
                                                                  if(memo[x] != -1) {tft.drawFastVLine(x,vShift - memo[x],10, GColor);}}//tft.fillRect(x,vShift - memo[x], 1,10, 
                                                                if(x == 239) {memo[x] = Raw/12.8-320; tft.drawFastVLine(x,vShift - memo[x],10, GColor);}//tft.fillRect(x,vShift - memo[x], 1,10,  
                                                                              } timDraw = millis();
                                              next = 0;                                
                                             }   
                                                } // END WHILE

}
//////////////////////////////////////////////////////////////////////////////////////////////////////////


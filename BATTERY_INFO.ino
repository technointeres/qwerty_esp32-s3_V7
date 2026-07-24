
void BATTERY_INFO() {

  //pinMode(1, INPUT);
 numButton0 = -1; numButton1 = -1; delay(200);
 //tft.setTextSize(3);
 int dat;
 uint16_t BColor = color565(  0,  0, 50);
 uint16_t GColor = color565(255,255,255);
 double temp_celsius; double voltage;
 tft.fillScreen(BColor);
  startX = 1; startY = 296; MyText = "темп. чипа:"; charColo = color565(255,255,255); event();
  startX = 220; startY = 296; MyText = "C"; charColo = color565(255,255,255); event();
                                               tft.setFont(&fonts::Orbitron_Light_24);
                                               //tft.setTextColor(0xFFFFFFU, 0);
                                               tft.setTextDatum( textdatum_t::top_center); // 
                                               //tft.setFont(&fonts::Font4);
                                               //tft.setCursor(0, 0);
                                               //tft.setTextSize(3);
                                               tft.setTextPadding(100); //
 
int Raw = 0, relRaw = 0, RawPrev = 0, relRawPrev = 0, Raw0 = 0, istab = 0; double timDraw = millis(); int memo[241]; int r = 40; int vShift = 0; int next = 0;//
                                                                                 for (int q = 0; q < 241; q++) {memo[q]   = -1;}
 startX = 2; startY = 38; tft.fillRect(startX,startY,30,25,color565(55,0,55));
 MyText = "4V"; charColo = color565(255,255,255); event();
 startX = 2; startY = 111; tft.fillRect(startX,startY,30,25,color565(55,0,55));
 MyText = "3V"; charColo = color565(255,255,255); event();

    while(numButton1 != 13 && numButton0 != 5) {  PressedButton(1); PressedButton(2); //
    istab += 1;
    dat = analogRead(1);
    Raw0 = Raw0 + dat; 
      if(istab > 4) { next = 1;//> 7
           Raw = Raw0/(istab);
                     istab = 0; Raw0 = 0;       
                    }
                    voltage = Raw/875.0; voltage = voltage+((3.886-voltage)/7); //FROM CALC

     if((millis() - timDraw) > 300 && next > 0) {
                                                tft.drawNumber(Raw, 120, 260);
                                                 startX = 93; startY = 232; tft.fillRect(startX,startY,69,22,BColor);
                                                MyText = voltage; charColo = color565(255,255,255); event(); 
                                                //tft.drawNumber(voltage, 120, 227);

                                                if(r < 41) {tft.fillRect(r,50, 2,2,BColor); tft.fillRect(r,123, 2,2,BColor); //START DOT REDRAW
                                                            r = 60;}
                   for (int z=r; z < 240; z+= 20) {tft.fillRect(z,50, 2,2,BColor);    tft.fillRect(z,123, 2,2,BColor);   } r -= 1; 
                   for (int z=r; z < 240; z+= 20) {tft.fillRect(z,50, 2,2,TFT_WHITE); tft.fillRect(z,123, 2,2,TFT_WHITE);} //DOTS                                      
                                                
                                                for (int x = 40; x < 240; x++) {          
                                                                tft.drawFastVLine(x,vShift - memo[x],10, BColor);//tft.fillRect(x,vShift - memo[x], 1,10, BackColor); //BackColor
                                                                if(x != 239) {memo[x] = memo[x+1];
                                                                  if(memo[x] != -1) {tft.drawFastVLine(x,vShift - memo[x],10, GColor);}}//tft.fillRect(x,vShift - memo[x], 1,10, 
                                                                if(x == 239) {memo[x] = Raw/12.8-320; tft.drawFastVLine(x,vShift - memo[x],10, GColor);}//tft.fillRect(x,vShift - memo[x], 1,10,  
                                                                              } timDraw = millis();
                                              next = 0;                                
                                             
if(temperatureRead() != temp_celsius) {                                         
temp_celsius = temperatureRead()/1.0;
startX = 147; startY = 296; tft.fillRect(startX,startY,69,22,BColor);
MyText = temp_celsius; charColo = color565(255,255,255); event();  
  }                                            }                 
                                                } // END WHILE

}
//////////////////////////////////////////////////////////////////////////////////////////////////////////





void WIFI_CONFIG() {
  ret_here://REDRAW AFTER RETURN
        tft.fillScreen(BackColor); 
        charColo = inactElem; 
   startX = 19; startY = 2;  MyText = "Connect"; event();
   startX = 19; startY = 24; MyText = "Disconnect"; event();
     charColo = color565(255,255,255); 
   startX = 19; startY = 46; MyText = "Edit ssid"; event();
   startX = 19; startY = 68; MyText = "Edit password"; event();
   rectMenuX = 0; rectMenuY = 0;//CURSOR
    tft.fillRect(rectMenuX, rectMenuY+3, 17, 22,color565(255,255,255));//FIRST 
    //if(WiFi.status() == WL_CONNECTED) {tft.drawBitmap(214, 0,  NET_PIC, 25, 21, WHITE);}
    delay(300);
    double pau = millis();
    PressedButton(1); PressedButton(2);
    while(numButton1 != 13 && numButton0 != 5) { PressedButton(1); PressedButton(2); 
    //while(numButton1 != 10) { PressedButton(0); if(numButton1 == 2) {return;}
     if((numButton0 == 1) && rectMenuY < 62 && millis() - pau > 120) {tft.fillRect(0, 0, 17, 92,BackColor); //TO BACKGROUND COLOR 3 ROWS
                             rectMenuY+=22; tft.fillRect(rectMenuX, rectMenuY+3, 17, 22,color565(255,255,255));
                             pau = millis();}//NEXT    
     if((numButton0 == 2) && rectMenuY > 10 && millis() - pau > 120) {tft.fillRect(0, 0, 17, 92,BackColor); //TO BACKGROUND COLOR 3 ROWS
                             rectMenuY-=22; tft.fillRect(rectMenuX, rectMenuY+3, 17, 22,color565(255,255,255));
                             pau = millis();}//PREV 

                                   //IF ENTER KEY PRESSED
                                    //if(numButton1 == 5 && rectMenuY == 0)  {CONNECT_WIFI(0); if(numButton1 == 2) {return;} WIFI_CONFIG(); PressedButton(0); break;}//GO TO CONNECT_WIFI()
                                    //if(numButton1 == 5 && rectMenuY == 22) {DISCONNECT_WIFI(); if(numButton1 == 2) {return;} WIFI_CONFIG(); PressedButton(0); break;}//
                                    if(numButton0 == 6 && rectMenuY == 44) {SSID_EDIT(2);      goto ret_here;}//TO EDIT SSID//HERE AFTER 
                                    if(numButton0 == 6 && rectMenuY == 66) {PASSWORD_EDIT(2);  goto ret_here;}//TO EDIT PASSWORD//HERE AFTER                 
                                                       
                          }//END WHILE 
                          InMenu = 0;
}
void NOTE(int i) { 
  LAYOUT_IND();
 wall = color565(100,0,90); tft.fillScreen(wall);
  //strip1.setPixelColor(5, strip1.Color( 55,  0,  0)); //strip1.show(); //RU
  //strip1.setPixelColor(6, strip1.Color(  0, 55,  0)); strip1.show(); //EN 

  startX = 40; startY = 128; scaleX = 2; scaleY = 1; charColo = color565(130,0,120); MyText = "DEVICE"; event();
  startX = 65; startY = 160; scaleX = 2; scaleY = 1; charColo = color565(130,0,120); MyText =  "7799";  event();
 
noteStr = EEPROM.readString(0); //
TEXT_EDIT();

                          EEPROM.writeString(0, noteStr);   EEPROM.commit(); 
                          noteStr = ""; MyText = "";                           
                 }//END;
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void EDIT_STRING_LED() {
  LAYOUT_IND();
  wall = color565(100,0,90); tft.fillScreen(wall);
  startX = 40; startY = 128; scaleX = 2; scaleY = 1; charColo = color565(130,0,120); MyText = "DEVICE"; event();
  startX = 65; startY = 160; scaleX = 2; scaleY = 1; charColo = color565(130,0,120); MyText =  "7799";  event();

  noteStr = EEPROM.readString(900); TEXT_EDIT(); EEPROM.writeString(900, noteStr); EEPROM.commit(); noteStr = ""; MyText = "";

  scaleX = 1;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void STATION_EDIT(int numStation) {
  LAYOUT_IND();
  wall = color565(100,0,90); tft.fillScreen(wall);
  startX = 40; startY = 128; scaleX = 2; scaleY = 1; charColo = color565(130,0,120); MyText = "DEVICE"; event();
  startX = 65; startY = 160; scaleX = 2; scaleY = 1; charColo = color565(130,0,120); MyText =  "7799";  event();
if(numStation == 0) {noteStr = EEPROM.readString(500); TEXT_EDIT(); EEPROM.writeString(500, noteStr); EEPROM.commit(); noteStr = ""; MyText = "";}
if(numStation == 1) {noteStr = EEPROM.readString(600); TEXT_EDIT(); EEPROM.writeString(600, noteStr); EEPROM.commit(); noteStr = ""; MyText = "";}
if(numStation == 2) {noteStr = EEPROM.readString(700); TEXT_EDIT(); EEPROM.writeString(700, noteStr); EEPROM.commit(); noteStr = ""; MyText = "";}
if(numStation == 3) {noteStr = EEPROM.readString(800); TEXT_EDIT(); EEPROM.writeString(800, noteStr); EEPROM.commit(); noteStr = ""; MyText = "";}
tft.fillScreen(BackColor);
startX = 2; startY = 2;  MyText = "Сохранено"; charColo = color565(255,255,255); event(); 
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SSID_EDIT(int i) { 
  LAYOUT_IND();
  wall = color565(100,0,90); tft.fillScreen(wall);
  startX = 40; startY = 128; scaleX = 2; scaleY = 1; charColo = color565(130,0,120); MyText = "DEVICE"; event();
  startX = 65; startY = 160; scaleX = 2; scaleY = 1; charColo = color565(130,0,120); MyText =  "7799";  event();
noteStr = EEPROM.readString(400); //
TEXT_EDIT();
                          EEPROM.writeString(400, noteStr);   EEPROM.commit(); 
                          noteStr = ""; MyText = "";          
                      }//END;
void PASSWORD_EDIT(int i) { 
  LAYOUT_IND();
  wall = color565(100,0,90); tft.fillScreen(wall);
  startX = 40; startY = 128; scaleX = 2; scaleY = 1; charColo = color565(130,0,120); MyText = "DEVICE"; event();
  startX = 65; startY = 160; scaleX = 2; scaleY = 1; charColo = color565(130,0,120); MyText =  "7799";  event();
noteStr = EEPROM.readString(450); //
TEXT_EDIT();
                          EEPROM.writeString(450, noteStr);   EEPROM.commit(); 
                          noteStr = ""; MyText = "";          
                         }//END;  
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void TEXT_EDIT() {
  //uint16_t wall = color565(100,0,90); tft.fillScreen(wall);
  uint16_t curCol = color565(0,200,250); //CURSOR
  int curW = 8, curH = 22; //layout = 1; 
  MyText = "";
  charColo = TFT_WHITE;
  startX = 2; startY = 0; scaleX = 1; scaleY = 1;
  int add = 0; int prevX, prevY; //ADD = SHIFT Y
  MyText = noteStr; event(); //PRINT DATA
  tft.fillRect(startX, startY+2, curW, curH, curCol);
  timeCursor = millis();
  int AFT = 0;
  //PressedButton(2);
  while(numButton1 != 13 && numButton0 != 5) {
 
    AFT = 0;                                                                       
    PressedButton(1); PressedButton(2); 
                      if(millis() - timeCursor < 200) {continue;} //PAUSE FOR COMFORT
                      if(numButton1 == -1 && numButton2 == -1 && numButton3 == -1 && numButton4 == -1) {continue;} //NOTHING PRESSED
                      //if(numButton1 != -1 || numButton2 != -1 || numButton3 != -1 || numButton4 != -1) {timeCursor = millis();} //
 
//if((numButton1 == 7 || numButton1 == 8) && (numButton0 == -1 && numButton2 == -1 && numButton3 == -1)) {goto forfaster;} //SHIFT OR EXTRA AND NOTHING ELSE
if(digitalRead(0) == 0 && (millis() - timeColorT) > 200) {CHANGE_COLOR_TOP();}
if(numButton1 == 15 && (millis() - timeLayout) > 200) {LAYOUT_IND(); timeCursor = millis(); continue;}
    // if(numButton1 == 15){if(layout == 1) {layout = 2; strip1.setPixelColor(5, strip1.Color(  0, 55,  0)); //strip1.show(); //RU
    //                                                   strip1.setPixelColor(6, strip1.Color(155,  0,  0)); strip1.show(); //EN 
    //                               } else {layout = 1; strip1.setPixelColor(5, strip1.Color(155,  0,  0)); //strip1.show(); //RU
    //                                                   strip1.setPixelColor(6, strip1.Color(  0, 55,  0)); strip1.show(); //EN 
    //} timeCursor = millis(); continue;} //RU EN
if(layout == 1) { 
    if(numButton1 == 16){MyText = "`"; if(Sh == 1) {MyText = "~";} if(Ex == 1) {MyText = "~";} AFT=1; goto forfaster;}
    //if(numButton1 == 13){} //MENU
    if(numButton1 == 12){MyText = "+"; if(Sh == 1) {MyText = "/";} if(Ex == 1) {MyText = "=";} AFT=1; goto forfaster;}                    
    if(numButton1 == 11){MyText = "-"; if(Sh == 1) {MyText = "\134";} if(Ex == 1) {MyText = "|";} AFT=1; goto forfaster;}
    if(numButton1 == 10){MyText = "0"; if(Sh == 1) {MyText = ")";} if(Ex == 1) {MyText = ")";} AFT=1; goto forfaster;}
    if(numButton1 == 9) {MyText = "9"; if(Sh == 1) {MyText = "(";} if(Ex == 1) {MyText = "(";} AFT=1; goto forfaster;}
    if(numButton1 == 7) {MyText = "8"; if(Sh == 1) {MyText = "*";} if(Ex == 1) {MyText = "*";} AFT=1; goto forfaster;}
    if(numButton1 == 6) {MyText = "7"; if(Sh == 1) {MyText = "?";} if(Ex == 1) {MyText = "&";} AFT=1; goto forfaster;} 
    if(numButton1 == 5) {MyText = "6"; if(Sh == 1) {MyText = ":";} if(Ex == 1) {MyText = "^";} AFT=1; goto forfaster;}
    if(numButton1 == 4) {MyText = "5"; if(Sh == 1) {MyText = "%";} if(Ex == 1) {MyText = "%";} AFT=1; goto forfaster;} 
    if(numButton1 == 3) {MyText = "4"; if(Sh == 1) {MyText = ";";} if(Ex == 1) {MyText = "$";} AFT=1; goto forfaster;}
    if(numButton1 == 2) {MyText = "3"; if(Sh == 1) {MyText = "#";} if(Ex == 1) {MyText = "№";} AFT=1; goto forfaster;} 
    if(numButton1 == 1) {MyText = "2"; if(Sh == 1) {MyText = "\42";} if(Ex == 1) {MyText = "@";} AFT=1; goto forfaster;}
    if(numButton1 == 0) {MyText = "1"; if(Sh == 1) {MyText = "!";} if(Ex == 1) {MyText = "!";} AFT=1; goto forfaster;} 

    if(numButton2 == 12){MyText = "]"; if(Sh == 1) {MyText = "}";} if(Ex == 1) {MyText = "}";} AFT=1; goto forfaster;}
    if(numButton2 == 11){MyText = "["; if(Sh == 1) {MyText = "{";} if(Ex == 1) {MyText = "{";} AFT=1; goto forfaster;}     
    if(numButton2 == 10){MyText = "p"; if(Sh == 1) {MyText = "P";} if(Ex == 1) {MyText = "";} AFT=1; goto forfaster;}
    if(numButton2 == 9) {MyText = "o"; if(Sh == 1) {MyText = "O";} if(Ex == 1) {MyText = "";} AFT=1; goto forfaster;}
    if(numButton2 == 8) {MyText = "i"; if(Sh == 1) {MyText = "I";} if(Ex == 1) {MyText = "";} AFT=1; goto forfaster;}
    if(numButton2 == 7) {MyText = "u"; if(Sh == 1) {MyText = "U";} if(Ex == 1) {MyText = "";} AFT=1; goto forfaster;}
    if(numButton2 == 5) {MyText = "y"; if(Sh == 1) {MyText = "Y";} if(Ex == 1) {MyText = "";} AFT=1; goto forfaster;}
    if(numButton2 == 4) {MyText = "t"; if(Sh == 1) {MyText = "T";} if(Ex == 1) {MyText = "";} AFT=1; goto forfaster;} 
    if(numButton2 == 3) {MyText = "r"; if(Sh == 1) {MyText = "R";} if(Ex == 1) {MyText = "";} AFT=1; goto forfaster;}
    if(numButton2 == 2) {MyText = "e"; if(Sh == 1) {MyText = "E";} if(Ex == 1) {MyText = "";} AFT=1; goto forfaster;} 
    if(numButton2 == 1) {MyText = "w"; if(Sh == 1) {MyText = "W";} if(Ex == 1) {MyText = "";} AFT=1; goto forfaster;}
    if(numButton2 == 0) {MyText = "q"; if(Sh == 1) {MyText = "Q";} if(Ex == 1) {MyText = "";} AFT=1; goto forfaster;} 

    if(numButton3 == 12){MyText = "\40"; if(Sh == 1) {MyText = "_";}   if(Ex == 1) {MyText = "_";}  AFT=1; goto forfaster;}
    if(numButton3 == 11){MyText = "'";   if(Sh == 1) {MyText = "\42";} if(Ex == 1) {MyText = "\42";} AFT=1; goto forfaster;}
    if(numButton3 == 10){MyText = ";";   if(Sh == 1) {MyText = ":";}   if(Ex == 1) {MyText = ":";}  AFT=1; goto forfaster;}
    if(numButton3 == 9) {MyText = "l";   if(Sh == 1) {MyText = "L";}   if(Ex == 1) {MyText = "";} AFT=1; goto forfaster;}
    if(numButton3 == 8) {MyText = "k";   if(Sh == 1) {MyText = "K";}   if(Ex == 1) {MyText = "";} AFT=1; goto forfaster;}
    if(numButton3 == 7) {MyText = "j";   if(Sh == 1) {MyText = "J";}   if(Ex == 1) {MyText = "";} AFT=1; goto forfaster;} 
    if(numButton3 == 5) {MyText = "h";   if(Sh == 1) {MyText = "H";}   if(Ex == 1) {MyText = "";} AFT=1; goto forfaster;} 
    if(numButton3 == 4) {MyText = "g";   if(Sh == 1) {MyText = "G";}   if(Ex == 1) {MyText = "";} AFT=1; goto forfaster;}
    if(numButton3 == 3) {MyText = "f";   if(Sh == 1) {MyText = "F";}   if(Ex == 1) {MyText = "";} AFT=1; goto forfaster;} 
    if(numButton3 == 2) {MyText = "d";   if(Sh == 1) {MyText = "D";}   if(Ex == 1) {MyText = "";} AFT=1; goto forfaster;}
    if(numButton3 == 1) {MyText = "s";   if(Sh == 1) {MyText = "S";}   if(Ex == 1) {MyText = "";} AFT=1; goto forfaster;}  
    if(numButton3 == 0) {MyText = "a";   if(Sh == 1) {MyText = "A";}   if(Ex == 1) {MyText = "";} AFT=1; goto forfaster;}            

    //if(numButton4 == 12){MyText = "";   if(Sh == 1) {MyText = "";}   if(Ex == 1) {MyText = "";} AFT=1; goto forfaster;}  //BRIGHTNESS
    //if(numButton4 == 11){MyText = "";   if(Sh == 1) {MyText = "";}   if(Ex == 1) {MyText = "";} AFT=1; goto forfaster;}  //BRIGHTNESS
    if(numButton4 == 10){MyText = ".";   if(Sh == 1) {MyText = ",";}   if(Ex == 1) {MyText = "?";} AFT=1; goto forfaster;}
    if(numButton4 == 9) {MyText = ".";   if(Sh == 1) {MyText = ">";}   if(Ex == 1) {MyText = ".";} AFT=1; goto forfaster;}
    if(numButton4 == 8) {MyText = ",";   if(Sh == 1) {MyText = "<";}   if(Ex == 1) {MyText = ",";} AFT=1; goto forfaster;}
    if(numButton4 == 7) {MyText = "m";   if(Sh == 1) {MyText = "M";}   if(Ex == 1) {MyText = "";} AFT=1; goto forfaster;} 
    if(numButton4 == 5) {MyText = "n";   if(Sh == 1) {MyText = "N";}   if(Ex == 1) {MyText = "";} AFT=1; goto forfaster;} 
    if(numButton4 == 4) {MyText = "b";   if(Sh == 1) {MyText = "B";}   if(Ex == 1) {MyText = "";} AFT=1; goto forfaster;}
    if(numButton4 == 3) {MyText = "v";   if(Sh == 1) {MyText = "V";}   if(Ex == 1) {MyText = "";} AFT=1; goto forfaster;} 
    if(numButton4 == 2) {MyText = "c";   if(Sh == 1) {MyText = "C";}   if(Ex == 1) {MyText = "";} AFT=1; goto forfaster;}
    if(numButton4 == 1) {MyText = "x";   if(Sh == 1) {MyText = "X";}   if(Ex == 1) {MyText = "";} AFT=1; goto forfaster;}  
    if(numButton4 == 0) {MyText = "z";   if(Sh == 1) {MyText = "Z";}   if(Ex == 1) {MyText = "";} AFT=1; goto forfaster;}                  
                }
if(layout == 2) {                       
    if(numButton1 == 16){MyText = "ё"; if(Sh == 1) {MyText = "Ё";} if(Ex == 1) {MyText = "`";} AFT=1; goto forfaster;}
    //if(numButton1 == 13){} //MENU
    if(numButton1 == 12){MyText = "+"; if(Sh == 1) {MyText = "/";} if(Ex == 1) {MyText = "=";} AFT=1; goto forfaster;}                    
    if(numButton1 == 11){MyText = "-"; if(Sh == 1) {MyText = "\134";} if(Ex == 1) {MyText = "|";} AFT=1; goto forfaster;}
    if(numButton1 == 10){MyText = "0"; if(Sh == 1) {MyText = ")";} if(Ex == 1) {MyText = ")";} AFT=1; goto forfaster;}
    if(numButton1 == 9) {MyText = "9"; if(Sh == 1) {MyText = "(";} if(Ex == 1) {MyText = "(";} AFT=1; goto forfaster;}
    if(numButton1 == 7) {MyText = "8"; if(Sh == 1) {MyText = "*";} if(Ex == 1) {MyText = "*";} AFT=1; goto forfaster;}
    if(numButton1 == 6) {MyText = "7"; if(Sh == 1) {MyText = "?";} if(Ex == 1) {MyText = "&";} AFT=1; goto forfaster;} 
    if(numButton1 == 5) {MyText = "6"; if(Sh == 1) {MyText = ":";} if(Ex == 1) {MyText = "^";} AFT=1; goto forfaster;}
    if(numButton1 == 4) {MyText = "5"; if(Sh == 1) {MyText = "%";} if(Ex == 1) {MyText = "%";} AFT=1; goto forfaster;} 
    if(numButton1 == 3) {MyText = "4"; if(Sh == 1) {MyText = ";";} if(Ex == 1) {MyText = "$";} AFT=1; goto forfaster;}
    if(numButton1 == 2) {MyText = "3"; if(Sh == 1) {MyText = "#";} if(Ex == 1) {MyText = "№";} AFT=1; goto forfaster;} 
    if(numButton1 == 1) {MyText = "2"; if(Sh == 1) {MyText = "\42";} if(Ex == 1) {MyText = "@";} AFT=1; goto forfaster;}
    if(numButton1 == 0) {MyText = "1"; if(Sh == 1) {MyText = "!";} if(Ex == 1) {MyText = "!";} AFT=1; goto forfaster;} 

    if(numButton2 == 12){MyText = "ъ"; if(Sh == 1) {MyText = "Ъ";} if(Ex == 1) {MyText = "]";} AFT=1; goto forfaster;}
    if(numButton2 == 11){MyText = "х"; if(Sh == 1) {MyText = "Х";} if(Ex == 1) {MyText = "[";} AFT=1; goto forfaster;}     
    if(numButton2 == 10){MyText = "з"; if(Sh == 1) {MyText = "З";} if(Ex == 1) {MyText = "";} AFT=1; goto forfaster;}
    if(numButton2 == 9) {MyText = "щ"; if(Sh == 1) {MyText = "Щ";} if(Ex == 1) {MyText = "";} AFT=1; goto forfaster;}
    if(numButton2 == 8) {MyText = "ш"; if(Sh == 1) {MyText = "Ш";} if(Ex == 1) {MyText = "";} AFT=1; goto forfaster;}
    if(numButton2 == 7) {MyText = "г"; if(Sh == 1) {MyText = "Г";} if(Ex == 1) {MyText = "";} AFT=1; goto forfaster;}
    if(numButton2 == 5) {MyText = "н"; if(Sh == 1) {MyText = "Н";} if(Ex == 1) {MyText = "";} AFT=1; goto forfaster;}
    if(numButton2 == 4) {MyText = "е"; if(Sh == 1) {MyText = "Е";} if(Ex == 1) {MyText = "";} AFT=1; goto forfaster;} 
    if(numButton2 == 3) {MyText = "к"; if(Sh == 1) {MyText = "К";} if(Ex == 1) {MyText = "";} AFT=1; goto forfaster;}
    if(numButton2 == 2) {MyText = "у"; if(Sh == 1) {MyText = "У";} if(Ex == 1) {MyText = "";} AFT=1; goto forfaster;} 
    if(numButton2 == 1) {MyText = "ц"; if(Sh == 1) {MyText = "Ц";} if(Ex == 1) {MyText = "";} AFT=1; goto forfaster;}
    if(numButton2 == 0) {MyText = "й"; if(Sh == 1) {MyText = "Й";} if(Ex == 1) {MyText = "";} AFT=1; goto forfaster;} 

    if(numButton3 == 12){MyText = "\40"; if(Sh == 1) {MyText = "_";}   if(Ex == 1) {MyText = "_";}  AFT=1; goto forfaster;}
    if(numButton3 == 11){MyText = "э";   if(Sh == 1) {MyText = "Э";}   if(Ex == 1) {MyText = "\42";} AFT=1; goto forfaster;}
    if(numButton3 == 10){MyText = "ж";   if(Sh == 1) {MyText = "Ж";}   if(Ex == 1) {MyText = ":";}  AFT=1; goto forfaster;}
    if(numButton3 == 9) {MyText = "д";   if(Sh == 1) {MyText = "Д";}   if(Ex == 1) {MyText = "";} AFT=1; goto forfaster;}
    if(numButton3 == 8) {MyText = "л";   if(Sh == 1) {MyText = "Л";}   if(Ex == 1) {MyText = "";} AFT=1; goto forfaster;}
    if(numButton3 == 7) {MyText = "о";   if(Sh == 1) {MyText = "О";}   if(Ex == 1) {MyText = "";} AFT=1; goto forfaster;} 
    if(numButton3 == 5) {MyText = "р";   if(Sh == 1) {MyText = "Р";}   if(Ex == 1) {MyText = "";} AFT=1; goto forfaster;} 
    if(numButton3 == 4) {MyText = "п";   if(Sh == 1) {MyText = "П";}   if(Ex == 1) {MyText = "";} AFT=1; goto forfaster;}
    if(numButton3 == 3) {MyText = "а";   if(Sh == 1) {MyText = "А";}   if(Ex == 1) {MyText = "";} AFT=1; goto forfaster;} 
    if(numButton3 == 2) {MyText = "в";   if(Sh == 1) {MyText = "В";}   if(Ex == 1) {MyText = "";} AFT=1; goto forfaster;}
    if(numButton3 == 1) {MyText = "ы";   if(Sh == 1) {MyText = "Ы";}   if(Ex == 1) {MyText = "";} AFT=1; goto forfaster;}  
    if(numButton3 == 0) {MyText = "ф";   if(Sh == 1) {MyText = "Ф";}   if(Ex == 1) {MyText = "";} AFT=1; goto forfaster;}            

    //if(numButton4 == 12){MyText = "";   if(Sh == 1) {MyText = "";}    if(Ex == 1) {MyText = "";} AFT=1; goto forfaster;}  //BRIGHTNESS
    //if(numButton4 == 11){MyText = "";   if(Sh == 1) {MyText = "";}    if(Ex == 1) {MyText = "";} AFT=1; goto forfaster;}  //BRIGHTNESS
    if(numButton4 == 10){MyText = ".";  if(Sh == 1) {MyText = ",";}   if(Ex == 1) {MyText = "?";} AFT=1; goto forfaster;}
    if(numButton4 == 9) {MyText = "ю";  if(Sh == 1) {MyText = "Ю";}   if(Ex == 1) {MyText = ".";} AFT=1; goto forfaster;}
    if(numButton4 == 8) {MyText = "б";  if(Sh == 1) {MyText = "Б";}   if(Ex == 1) {MyText = ",";} AFT=1; goto forfaster;}
    if(numButton4 == 7) {MyText = "ь";  if(Sh == 1) {MyText = "Ь";}   if(Ex == 1) {MyText = "";} AFT=1; goto forfaster;} 
    if(numButton4 == 5) {MyText = "т";  if(Sh == 1) {MyText = "Т";}   if(Ex == 1) {MyText = "";} AFT=1; goto forfaster;} 
    if(numButton4 == 4) {MyText = "и";  if(Sh == 1) {MyText = "И";}   if(Ex == 1) {MyText = "";} AFT=1; goto forfaster;}
    if(numButton4 == 3) {MyText = "м";  if(Sh == 1) {MyText = "М";}   if(Ex == 1) {MyText = "";} AFT=1; goto forfaster;} 
    if(numButton4 == 2) {MyText = "с";  if(Sh == 1) {MyText = "С";}   if(Ex == 1) {MyText = "";} AFT=1; goto forfaster;}
    if(numButton4 == 1) {MyText = "ч";  if(Sh == 1) {MyText = "Ч";}   if(Ex == 1) {MyText = "";} AFT=1; goto forfaster;}  
    if(numButton4 == 0) {MyText = "я";  if(Sh == 1) {MyText = "Я";}   if(Ex == 1) {MyText = "";} AFT=1; goto forfaster;}   
                }
    forfaster:
    if(AFT == 1) {timeCursor = millis();
                  noteStr = noteStr + MyText; 
                  tft.fillRect(startX,startY+2,curW,curH,wall); event(); 
                  tft.fillRect(startX,startY+2,curW,curH,curCol); AFT = 0;}
 
    if(numButton1 == 14) { //IF BACKSPACE
                         if(noteStr.charAt(noteStr.length()-2) == '\320' || 
                            noteStr.charAt(noteStr.length()-2) == '\321'   ) { tft.fillRect(startX,startY+2,curW,curH,wall); //DELETE CURSOR                   
                             MyText = noteStr.substring(noteStr.length()-2), noteStr.substring(noteStr.length()-1); //RU CHAR
                                                                           charColo = wall;
                                                                           if(startX < 3 && startY > 1+add) {startX = 223; startY-=22; event();} //MOVE CURSOR TO CLEAR SYMBOL[BACKGROUND COLOR]
                                                                           else{if(startX < 3 && startY < 1+add) {startX = 2; startY = 0+add; event();}}
                                                                           if(startX > 2) {startX-=13; event();}
                                                                           if(startX < 3 && startY > 1+add) {startX = 223; startY-=22;         } //MOVE CURSOR AGAIN TO PRINT ANY NEW SYMBOL
                                                                           else{if(startX < 3 && startY < 1+add) {startX = 2;   startY = 0+add;         }}
                                                                           if(startX > 2) {startX-=13;         }
                             noteStr.remove(noteStr.length()-2,2); //REMOVE LAST RU CHAR
                                                                               tft.fillRect(startX,startY+2,curW,curH,curCol); //REDRAW CURSOR 
                                                                             } 
                                        /////////////////////////////////////////////////////////////                                                   
                                                                        else { tft.fillRect(startX,startY+2,curW,curH,wall); //DELETE CURSOR
                             MyText = noteStr.charAt(noteStr.length()-1);                                          //ENG CHAR OR SYMBOL
                                                                           charColo = wall;
                                                                           if(startX < 3 && startY > 1+add) { startX = 223; startY-=22; event();} //MOVE CURSOR TO CLEAR SYMBOL[BACKGROUND COLOR]
                                                                           else{if(startX < 3 && startY < 1+add) {startX = 2; startY = 0+add; event();}}
                                                                           if(startX > 2) {startX-=13; event();}
                                                                           if(startX < 3 && startY > 1+add) {startX = 223; startY-=22;         } //MOVE CURSOR AGAIN TO PRINT ANY NEW SYMBOL
                                                                           else{if(startX < 3 && startY < 1+add) {startX = 2;   startY = 0+add;         }}
                                                                           if(startX > 2) {startX-=13;         }                                             
                             noteStr.remove(noteStr.length()-1,1);   //REMOVE LAST OTHER CHAR  
                                                                                    tft.fillRect(startX,startY+2,curW,curH,curCol); //REDRAW CURSOR                                             
                                                                             }    
                          timeCursor = millis(); MyText = noteStr; //event();
                         }
                          charColo = TFT_WHITE;  
                           
                          }//END WHILE 
}


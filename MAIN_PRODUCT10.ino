#define ARDUINO_USB_MODE 1
#include "USB.h"
#include "USBHIDKeyboard.h"
USBHIDKeyboard Keyboard;
#include "USBHIDConsumerControl.h"
USBHIDConsumerControl ConsumerControl;

////////////////////////////////////////////////////////////////////////////////
const byte interruptPinESC =   12; // Пин для прерывания //ESC
const byte interruptPinUP =    14; // Пин для прерывания //UP
const byte interruptPinDOWN =  11; // Пин для прерывания //DOWN
const byte interruptPinENTER = 10; // Пин для прерывания //DOWN
volatile byte intESC = LOW;
volatile byte intUP = LOW;
volatile byte intDOWN = LOW;
volatile byte intENTER = LOW;
int LEDpreset = 1;
////////////////////////////////////////////////////////////////////////////////
#define LGFX_USE_V1
#include <LovyanGFX.hpp>
#include <lgfx_user/LGFX_ESP32_sample.hpp> 
//static LGFX lcd;
LGFX tft;
////////////////////////////////////////////////////////////////////////////////
#include <Adafruit_NeoPixel.h>
#define LED_PIN 45 //MODULE
#define LED_PIN1 46
#define LED_COUNT 234 //MODULE
#define LED_COUNT1 7
Adafruit_NeoPixel strip(LED_COUNT,   LED_PIN,  NEO_GRB + NEO_KHZ800); //MODULE
Adafruit_NeoPixel strip1(LED_COUNT1, LED_PIN1, NEO_GRB + NEO_KHZ800);
////////////////////////////////////////////////////////////////////////////////
#include <SPI.h>
//#include "Free_Fonts.h" // Include the header file attached to this sketch
#include <Wire.h>
//#include "WRITETEXT.h"
#include "NOTO_FONT_ALL.h"
// #include "TEMP_PIC.h"
// #include "H_PIC.h"
// #include "NET_PIC.h"
// #include "PHOTORESISTOR_PIC.h"
// #include "PHOTORESISTOR_BIG_PIC.h"
#include "EEPROM.h"
//#include <HTTPClient.h>
//#include <ArduinoJson.h> 
#include "Arduino.h"
#include "WiFi.h"
#include "Audio.h"
//#include <WiFiUdp.h>
//  WiFiUDP ntpUDP;
#include "image_right.h"
#include "image_left.h"
#include "image_center.h"
#include "sky.h"

const int im_width = 70;
const int im_height = 130;
const int im_width_cen = 156;
const int im_height_cen = 130;

int DispW = 240;
int h = 27-1;//HEIGHT IMAGE 
int w = 2506;//WIDTH IMAGE
int layout = 1;//ENG ON START
String apiC = "Moscow";
String apiCountry = "ru";
String apiKey = "";
String InText = "";     
bool stringComplete = false; 
bool originalCol = false;
int numButton0 = -1;
int numButton1 = -1;
int numButton2 = -1;
int numButton3 = -1;
int numButton4 = -1;
char previous_char;
float p = 3.1415926;
int startX = 2; 
int startY = 0;
int scaleX = 1; // 1/2/3/4
int scaleY = 1; // 1/2/3/4
String MyText = "";
String substrSpecific; 
String noteStr;
int rectMenuX = 0;
int rectMenuY = 0;
int rectMenuX2 = 0; //RIGHT COLUMN
int rectMenuY2 = 0; //RIGHT COLUMN
int selectMenuP = 0;
int selectMenuP2 = 0; //RIGHT COLUMN
int mod = 0; //1=RIGHT COLUMN
unsigned long timePast = 0;
int InMenu = 0;
uint16_t charColo = TFT_WHITE;
uint16_t BackColor;
uint32_t BaCol; //BACK CURSOR = MENU
uint16_t CursCol; //CURSOR = MENU
uint16_t inactElem;
uint16_t wall;//FOR TEXT_EDIT
int BRIG = -1;
int BRIG_LAYOUT = -1;
String StrToBLE;
int Ex; int Sh;
double timeColorT;
double timeColor;
double timeCursor;
double timeLayout;
double timeVol;
int colorNext = 1;
int colorNextT = 1;
int colorNextTQ = 1;
const int buttonPin1 = 7;
//int previousButtonState1 = LOW;
const int buttonPin2 = 6;
//int previousButtonState2 = LOW;
const int buttonPin3 = 5;
//int previousButtonState3 = LOW;
void setup()   { 
  EEPROM.begin(1200);
  if(EEPROM.read(0) == 255)   {EEPROM.writeString(0,  ""); EEPROM.commit();}//NOTE
  if(EEPROM.read(400) == 255) {EEPROM.writeString(400,""); EEPROM.commit();}//SSID
  if(EEPROM.read(450) == 255) {EEPROM.writeString(450,""); EEPROM.commit();}//PASSWORD
  if(EEPROM.read(500) == 255) {EEPROM.writeString(500,"http://listen.radio.tomsk.ru:8000/jazz"); EEPROM.commit();}//STATION1
  if(EEPROM.read(600) == 255) {EEPROM.writeString(600,"https://royalradio.space/986FM"); EEPROM.commit();}//STATION2
  if(EEPROM.read(700) == 255) {EEPROM.writeString(700,"http://87.76.5.59:8000/live"); EEPROM.commit();}//STATION3
  if(EEPROM.read(800) == 255) {EEPROM.writeString(800,"http://94.190.4.232:8000/Master.128"); EEPROM.commit();}//STATION4
  if(EEPROM.read(900) == 255) {EEPROM.writeString(900,"TECHNOINTERES  DEVICE 7799  ***QWERTYUIOPASDFGHJKLZXCVBNM 0123456789"); EEPROM.commit();}//STRING_LED MODULE
/////////////////////////////////////////////////////////
  tft.init();
  tft.setRotation(0);
/////////////////////////////////////////////////////////
    pinMode(buttonPin1, INPUT_PULLDOWN);  pinMode(buttonPin2, INPUT_PULLDOWN);  pinMode(buttonPin3, INPUT_PULLDOWN);
    ConsumerControl.begin();
    Keyboard.begin();
    USB.begin();
/////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////
  pinMode(1, INPUT); //VOLTAGE_BATTERY
  pinMode(0, INPUT_PULLUP); //boot button
  pinMode(47, INPUT);
  pinMode(21, INPUT);
  pinMode(45, OUTPUT);
  pinMode(46, OUTPUT);
  pinMode(48, OUTPUT); 
  analogWrite(48, 255); //DISPLAY BRIGHTNESS 
/////////////////////////////////////////////////////////
  strip.begin(); //MODULE          
  strip.show(); //MODULE           
  strip.setBrightness(255); //MODULE
  strip1.begin();           
  strip1.show();            
  strip1.setBrightness(255); 
  //colorWipe(strip.Color(0,  0,  0), 0); //MODULE
  //colorWipe1(strip1.Color(255,  0,  0), 0); //
 
  strip1.setPixelColor(0, strip1.Color(255,  0,255)); //strip1.show(); //BACK
  strip1.setPixelColor(1, strip1.Color(255,  0,255)); //strip1.show(); //NAV
  strip1.setPixelColor(2, strip1.Color(255,  0,255)); //strip1.show(); //NAV 
  strip1.setPixelColor(3, strip1.Color(255,  0,255)); //strip1.show(); //FOOTER
  strip1.setPixelColor(4, strip1.Color(255,  0,255)); //strip1.show(); //FOOTER
  strip1.setPixelColor(5, strip1.Color(155,  0,  0)); //strip1.show(); //RU
  strip1.setPixelColor(6, strip1.Color(  0, 55,  0)); strip1.show(); //EN
/////////////////////////////////////////////////////////
  uint16_t time = millis();
  BackColor = color565(0,0,70); //DEFAULT THEME
  inactElem = color565(180,180,180);

  //NOTE(1); 
  startMenu();
  //while(true);
}
void drawBack()
{
  tft.startWrite();
  tft.setAddrWindow(0, 0, 128, 320); //LEFT
  for (int y = 0; y < 320; ++y) {
    for (int x = 0; x < 128; ++x) {
      tft.writeColor(tft.color888(x+0, 0, 129-x), 1);
    }
  }
  tft.setAddrWindow(128, 0, 112, 320); //RIGHT
  for (int y = 0; y < 320; ++y) {
    for (int x = 0; x < 112; ++x) {
      tft.writeColor(tft.color888(x+0, 0, 129-x), 1);
    }
    }
  tft.endWrite();
}

void loop() {//while(true);

  if(numButton1 == 13 || numButton0 == 5) {InMenu = 0; startMenu(); delay(200); //numButton0==5(ESC KEY)// 13 = MENU KEY
                                           //analogWrite(3, BRIG_LAYOUT);  //RU
                                           //analogWrite(10, BRIG_LAYOUT); //ENG
                                          }                                       
                                           numButton0 = -1; //NAV 
                                           numButton1 = -1; numButton2 = -1; numButton3 = -1; numButton4 = -1; //KEYBOARD                                        
PressedButton(1); //NAV 
PressedButton(2); //KEYBOARD
////////////////
if(digitalRead(0) == 0 && (millis() - timeColorT) > 200) {CHANGE_COLOR_TOP();}
if(numButton1 == 15 && (millis() - timeLayout) > 200) {LAYOUT_IND();}
////////////////
if(numButton0 > -1) {if(InMenu < 0.5) {moveCursor();}
                     if(numButton0 == 6 && selectMenuP < 14) {//6 = ENTER
                      chooseMenu();                           //AFTER RETURN 
                      InMenu = 0; numButton0 = -1; numButton1 = -1; numButton2 = -1; numButton3 = -1; numButton4 = -1; startMenu(); delay(200);} }

}

void startMenu() {       
  drawBack(); //tft.fillScreen(BackColor);
  startX = 0; startY = 0; MyText = "МЕНЮ"; charColo = TFT_WHITE; event();  
  tft.drawFastHLine(0,24,240, color565(255,0,0)); tft.drawFastHLine(0,25,240, color565(255,0,0));
  tft.drawFastVLine(128,0,320, color565(255,0,0)); tft.drawFastVLine(129,0,320, color565(255,0,0));
  int numMenu = 1; int numModule = 1; startY = 25; InMenu = 0; rectMenuX = 0; rectMenuY = 0; scaleX = 1; scaleY = 1; charColo = TFT_WHITE;
  while(numMenu <= 13) {drawMenu(numMenu); numMenu ++; startY += 22;}
  startY = 25;
  while(numModule <= 12) {drawModules(numModule); numModule ++; startY += 22;}
  startX = 131; startY = 0; MyText = "МОДУЛИ"; event(); 
    rectMenuY =  25; startY = rectMenuY; selectMenuP  = 1; 
    rectMenuY2 = 25; rectMenuX2 = 131; selectMenuP2 = 1;
    //if(WiFi.status() == WL_CONNECTED) {tft.drawBitmap(214, 0,  NET_PIC, 25, 21, TFT_WHITE);}
    if(mod == 0) {tft.fillRect(rectMenuX,rectMenuY+1,   13, 22,color565(255,255,255) );} //CURSOR //FIRST [MENU] LEFT   
    if(mod == 1) {tft.fillRect(rectMenuX2,rectMenuY2+1, 13, 22,color565(255,255,255) );} //CURSOR //FIRST [MENU] RIGHT  
        startX = 151; startY = 252; MyText = "boot="; charColo = color565(255,0,0); event();
        startX = 151; startY = 272; MyText = "смена"; charColo = color565(255,0,0); event();
        startX = 151; startY = 292; MyText = "цвета"; charColo = color565(255,0,0); event(); charColo = TFT_WHITE;

                 }
/////////////////////////////////////////////////////////////////////////////////////////////////////////////// 
void drawMenu(int numMenu){
  if(numMenu == 1)  {startX = 13; MyText = "Wi-Fi"; event();}
  if(numMenu == 2)  {startX = 13; MyText = "Заметка"; event();}
  if(numMenu == 3)  {startX = 13; MyText = "Графики"; event();}// scaleX = 2; symbolDraw(166); scaleX = 1; MyText =" HUMIDITY"; event();}
  if(numMenu == 4)  {startX = 13; MyText = "Визуал-я"; event();} 
  if(numMenu == 5)  {startX = 13; MyText = "Игра"; event();} //tft.drawBitmap(195, 63,  PHOTORESISTOR_PIC, 32, 26, TFT_WHITE);} //Игры /// games //charColo = inactElem; charColo = TFT_WHITE; tft.drawBitmap(195, 205,  PHOTORESISTOR_PIC, 32, 26, TFT_WHITE);
  if(numMenu == 6)  {startX = 13; MyText = "BT/USB"; event();}
  if(numMenu == 7)  {startX = 13; MyText = "Аккум-р"; event();}
  if(numMenu == 8)  {startX = 13; MyText = "ESP NOW"; event();}//UART chat РУ+EN
  if(numMenu == 9)  {startX = 13; MyText = "RGB"; event();}
  if(numMenu == 10) {startX = 13; MyText = "Погода"; event();}
  if(numMenu == 11) {startX = 13; MyText = "Настро-и"; event();}
  //if(numMenu == 11) {startX = 13; MyText = "МОЙ УМНЫЙ ДОМ "; charColo = inactElem; event(); scaleX = 2; symbolDraw(171); scaleX = 1; charColo = TFT_WHITE;}
  if(numMenu == 12) {startX = 13; MyText = "Часы"; event();}
  if(numMenu == 13) {startX = 13; MyText = "Кальк-р"; event();}              
                          }  
void drawModules(int numModule) {
  if(numModule == 1)  {startX = 144; MyText = "Аудио"; event();}
  if(numModule == 2)  {startX = 144; MyText = "234 LED"; event();}
  if(numModule == 3)  {startX = 144; MyText = "Макро"; event();} 
  if(numModule == 4)  {startX = 144; MyText = "MicroSD"; event();}
  if(numModule == 5)  {startX = 144; MyText = "Прото"; event();}
  if(numModule == 6)  {startX = 144; MyText = "Мульт-р"; event();}
  if(numModule == 7)  {startX = 144; MyText = "Атмо"; event();}
  if(numModule == 8)  {startX = 144; MyText = "Прогр-р"; event();}
  if(numModule == 9)  {startX = 144; MyText = "VFD"; event();}
  if(numModule == 10) {startX = 144; MyText = "Футбол"; event();}  
  if(numModule == 11) {startX = 144; MyText = ""; event();} //tft.drawBitmap(195, 63,  PHOTORESISTOR_PIC, 32, 26, TFT_WHITE);} //Игры /// games //charColo = inactElem; charColo = TFT_WHITE; tft.drawBitmap(195, 205,  PHOTORESISTOR_PIC, 32, 26, TFT_WHITE);
  if(numModule == 12) {startX = 144; MyText = ""; event();}     
                                }  

/////////////////////////////////////////////////////////////////////////////////////////////////////////////// 
void moveCursor() {
  BaCol = tft.color888(0, 0, 129);
  CursCol = tft.color888(255,255,255);

  int PAU = 120;
  if(numButton0 == 1 && millis() - timePast > PAU && selectMenuP < 13 && mod == 0) {//NEXT MENU AND DELAY
                timePast = millis()-1;
                      tft.fillRect(rectMenuX,rectMenuY+1,   13,22,BaCol);
                      rectMenuY += 22; selectMenuP ++; 
                      tft.fillRect(rectMenuX,rectMenuY+1,   13,22,CursCol );
                     }
  if(numButton0 == 2 && millis() - timePast > PAU && selectMenuP > 1 && mod == 0) {//PREVIOUS MENU AND DELAY 
                timePast = millis()-1;
                      tft.fillRect(rectMenuX,rectMenuY+1,   13,22,BaCol);
                      rectMenuY -= 22; selectMenuP --; 
                      tft.fillRect(rectMenuX,rectMenuY+1,   13,22,CursCol );                            
                     }
///
  if(numButton0 == 3 && millis() - timePast > PAU && mod == 0) {//
                timePast = millis()-1;
                      tft.fillRect(rectMenuX,rectMenuY+1,   13,22,BaCol);
                      tft.fillRect(rectMenuX2,rectMenuY2+1,   13,22,BaCol);
                      mod = 1; rectMenuY2 = rectMenuY;
                      tft.fillRect(rectMenuX2,rectMenuY2+1,   13,22,CursCol );                            
                     }
  if(numButton0 == 4 && millis() - timePast > PAU && mod == 1) {//
                timePast = millis()-1;
                      tft.fillRect(rectMenuX,rectMenuY+1,   13,22,BaCol);
                      tft.fillRect(rectMenuX2,rectMenuY2+1,   13,22,BaCol);
                      mod = 0;  rectMenuY = rectMenuY2;
                      tft.fillRect(rectMenuX,rectMenuY+1,   13,22,CursCol );                            
                     }
///
  if(numButton0 == 1 && millis() - timePast > PAU && selectMenuP < 13 && mod == 1) {//NEXT MENU AND DELAY
                timePast = millis()-1;
                      tft.fillRect(rectMenuX2,rectMenuY2+1,   13,22,BaCol);
                      rectMenuY2 += 22; selectMenuP ++;
                      tft.fillRect(rectMenuX2,rectMenuY2+1,   13,22,CursCol );
                     }
  if(numButton0 == 2 && millis() - timePast > PAU && selectMenuP > 1 && mod == 1) {//PREVIOUS MENU AND DELAY 
                timePast = millis()-1;
                      tft.fillRect(rectMenuX2,rectMenuY2+1,   13,22,BaCol);
                      rectMenuY2 -= 22; selectMenuP --;
                      tft.fillRect(rectMenuX2,rectMenuY2+1,   13,22,CursCol );                            
                     }
                  }
/////////////////////////////////////////////////////////////////////////////////////////////////////////////// 
///////////////////////////////////////////////////////////////////////////////////////////////////////////////      
void PressedButton(int which) {//1 = NAV 2 = KEYBOARD
  int times0 = 3; //HOW MANY [NAV]
  int times = 15; //HOW MANY [KEYBOARD]
//////////////////////////////Ex and Sh//////////////////////////////
Ex = digitalRead(47); Sh = digitalRead(21);
/////////////////////////////////////////////////////////////////////
  if(which == 1) {//CHECK ONLY NAV
  numButton0 = -1;
  int i1 = 0, i2 = 0, i3 = 0, i4 = 0, i5 = 0, i6 = 0;
  int inf1 = 0, inf2 = 0, inf3 = 0, inf4 = 0, inf5 = 0, inf6 = 0;
  int Point = 2277; //
  inf1=analogRead(11); inf2=analogRead(14); inf3=analogRead(13); 
  inf4=analogRead(2); inf5=analogRead(12); inf6=analogRead(10);

if(inf1 > Point) {while(i1 < times0) {inf1=analogRead(11); //DOWN
                      if(inf1 < Point) {i1 = 0; numButton0 = -1; break;} i1++;    
                      if(i1 == times0) {numButton0 = 1; i1 = 0; break;} }
                 } 
if(inf2 > Point) {while(i2 < times0) {inf2=analogRead(14); //UP
                      if(inf2 < Point) {i2 = 0; numButton0 = -1; break;} i2++;    
                      if(i2 == times0) {numButton0 = 2; i2 = 0; break;} } 
                 }
if(inf3 > Point) {while(i3 < times0) {inf3=analogRead(13); //RIGHT
                      if(inf3 < Point) {i3 = 0; numButton0 = -1; break;} i3++;    
                      if(i3 == times0) {numButton0 = 3; i3 = 0; break;} }
                 } 
if(inf4 > Point) {while(i4 < times0) {inf4=analogRead(2); //LEFT
                      if(inf4 < Point) {i4 = 0; numButton0 = -1; break;} i4++;    
                      if(i4 == times0) {numButton0 = 4; i4 = 0; break;} } 
                 }   
if(inf5 > Point) {while(i5 < times0) {inf5=analogRead(12); //ESC
                      if(inf5 < Point) {i5 = 0; numButton0 = -1; break;} i5++;    
                      if(i5 == times0) {numButton0 = 5; i5 = 0; break;} }
                 } 
if(inf6 > Point) {while(i6 < times0) {inf6=analogRead(10); //ENTER
                      if(inf6 < Point) {i6 = 0; numButton0 = -1; break;} i6++;    
                      if(i6 == times0) {numButton0 = 6; i6 = 0; break;} } 
                 }   
                 return;        
                }

  if(which == 2) {//CHECK KEYBOARD
  numButton1 = -1; numButton2 = -1; numButton3 = -1; numButton4 = -1;
  int ix1 = 0, ix2 = 0, ix3 = 0, ix4 = 0;
  int w1 = -1, w2 = -1, w3 = -1, w4 = -1;
  int w1p = -1, w2p = -1, w3p = -1, w4p = -1;
  w1=round(analogRead(16)/115.0); w2=round(analogRead(15)/154.0); w3=round(analogRead(18)/154.0); w4=round(analogRead(17)/154.0);

if(w1 != 8) {while(ix1 < times) {w1p = w1; w1=round(analogRead(16)/115.0); if(w1p != w1) {break;} w1p = w1;
                      if(w1 == 8) {ix1 = 0; numButton1 = -1; break;} ix1++;    
                      if(ix1 == times) {numButton1 = w1; ix1 = 0; break;} }
              } 
if(w2 != 6) {while(ix2 < times) {w2p = w2; w2=round(analogRead(15)/154.0); if(w2p != w2) {break;} w2p = w2;
                      if(w2 == 6) {ix2 = 0; numButton2 = -1;  break;} ix2++;    
                      if(ix2 == times) {numButton2 = w2; ix2 = 0; break;} }
              }
if(w3 != 6) {while(ix3 < times) {w3p = w3; w3=round(analogRead(18)/154.0); if(w3p != w3) {break;} w3p = w3;
                      if(w3 == 6) {ix3 = 0; numButton3 = -1;  break;} ix3++;    
                      if(ix3 == times) {numButton3 = w3; ix3 = 0; break;} }
              }
if(w4 != 6) {while(ix4 < times) {w4p = w4; w4=round(analogRead(17)/154.0); if(w4p != w4) {break;} w4p = w4;
                      if(w4 == 6) {ix4 = 0; numButton4 = -1;  break;} ix4++;    
                      if(ix4 == times) {numButton4 = w4; ix4 = 0; break;} }
              } 
              return;          
  }

}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////                    
void colorWipe(uint32_t color, int wait) { //MODULE
  for(int in=0; in<strip.numPixels(); in++) { 
    strip.setPixelColor(in, color);         
    //strip.show();                          
    //delay(wait);                           
  } strip.show();
}
void colorWipe1(uint32_t color, int wait) { //TOP BOARD
  for(int ic=0; ic<strip1.numPixels(); ic++) { 
    strip1.setPixelColor(ic, color);         
    //strip1.show();                          
    //delay(wait);                           
  } strip1.show();
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////  


                   

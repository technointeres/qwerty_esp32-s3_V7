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

#define WIDTH 26
#define HEIGHT 9
#define IMG_SIZE 26
/////////////////////

///////////////////// FOR CASE 3
#define MAX_SNOW   25
struct Snowflake {
  float x, y, speed;
  uint32_t baseColor;
  bool active;
};
Snowflake snow[MAX_SNOW];
int rotationMode = 0; // 0: 0°, 1: 90°, 2: 180°, 3: 270°

void updateSnow() {
  for (int i = 0; i < MAX_SNOW; i++) {
    if (!snow[i].active) {
      snow[i].x = random(WIDTH);
      snow[i].y = -1.5; 
      snow[i].speed = (random(150, 350) / 1000.0); 
      snow[i].baseColor = (random(2) == 0) ? 0x6666FF : 0x0000FF; 
      snow[i].active = true;
    }
    snow[i].y += snow[i].speed;
    if (snow[i].y > HEIGHT + 1) snow[i].active = false;
  }
}

void drawAA(int x, int y, uint32_t color, float alpha) {
  if (y < 0 || y >= HEIGHT || x < 0 || x >= WIDTH || alpha <= 0.01) return;
  int idx = (y % 2 == 0) ? (y * WIDTH + x) : (y * WIDTH + (WIDTH - 1 - x));
  uint8_t r = ((color >> 16) & 0xFF) * alpha, g = ((color >> 8) & 0xFF) * alpha, b = (color & 0xFF) * alpha;
  uint32_t oldColor = strip.getPixelColor(idx);
  uint8_t oR = (oldColor >> 16) & 0xFF, oG = (oldColor >> 8) & 0xFF, oB = oldColor & 0xFF;
  strip.setPixelColor(idx, strip.Color(min(255, r + oR), min(255, g + oG), min(255, b + oB)));
}

void drawFrame(float faceY, bool showFace) {
  strip.clear();
  for (int i = 0; i < MAX_SNOW; i++) {
    if (snow[i].active) {
      int x = (int)snow[i].x, yU = (int)snow[i].y;
      float f = snow[i].y - yU;
      drawAA(x, yU, snow[i].baseColor, 1.0 - f);
      drawAA(x, yU + 1, snow[i].baseColor, f);
    }
  }

  if (showFace) {
    float centerX = 12.5, centerY_base = faceY; 
    float radius = 13.0;

    for (int y = 0; y < HEIGHT; y++) {
      for (int x = 0; x < WIDTH; x++) {
        // Базовые смещения относительно центра круга
        float dx_orig = x - centerX;
        float dy_orig = y - centerY_base;
        float dx, dy;

        // ЛОГИКА ПОВОРОТА КООРДИНАТ
        if (rotationMode == 0) { dx = dx_orig; dy = dy_orig; }           // 0°
        else if (rotationMode == 1) { dx = dy_orig; dy = -dx_orig; }     // 90°
        else if (rotationMode == 2) { dx = -dx_orig; dy = -dy_orig; }    // 180°
        else { dx = -dy_orig; dy = dx_orig; }                            // 270°

        float dist = sqrt(dx*dx + dy*dy);
        if (dist <= radius) {
          int idx = (y % 2 == 0) ? (y * WIDTH + x) : (y * WIDTH + (WIDTH - 1 - x));
          float alpha = constrain(radius - dist, 0.0, 1.0);
          
          bool isPupilL = (abs(dy + 3.0) < 1.0 && abs(dx + 4.5) < 1.6);
          bool isPupilR = (abs(dy + 3.0) < 1.0 && abs(dx - 4.5) < 1.6);
          bool isSmile = (abs(dy - (-(dx*dx/7.0)+6.0)) < 1.0 && abs(dx) < 5.5);

          if (isPupilL || isPupilR || isSmile) strip.setPixelColor(idx, 0, 0, 0); 
          else strip.setPixelColor(idx, strip.Color(255 * alpha, 140 * alpha, 0));
        }
      }
    }
  }
  if(intESC != LOW || intUP != LOW || intDOWN != LOW) {return;}
  strip.show();
}

///////////////////// FOR CASE 6
// Полный шрифт 5x9 (каждая буква — 9 байт).
// Двумерный массив символов ASCII от ' ' (код 32) до 'Z' (код 90).
const uint8_t font[][9] = {
  // --- Спецсимволы (ASCII 32 - 47) ---
  {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // 0: ' ' (Пробел)
  {0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x00, 0x04, 0x00}, // 1: '!'
  {0x0A, 0x0A, 0x0A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // 2: '"'
  {0x0A, 0x0A, 0x1F, 0x0A, 0x1F, 0x0A, 0x0A, 0x00, 0x00}, // 3: '#'
  {0x04, 0x0E, 0x15, 0x14, 0x0E, 0x05, 0x15, 0x0E, 0x04}, // 4: '$'
  {0x18, 0x19, 0x02, 0x04, 0x08, 0x10, 0x13, 0x03, 0x00}, // 5: '%'
  {0x0C, 0x12, 0x12, 0x0C, 0x15, 0x12, 0x12, 0x15, 0x0D}, // 6: '&'
  {0x04, 0x04, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // 7: '''
  {0x02, 0x04, 0x08, 0x08, 0x08, 0x08, 0x08, 0x04, 0x02}, // 8: '('
  {0x08, 0x04, 0x02, 0x02, 0x02, 0x02, 0x02, 0x04, 0x08}, // 9: ')'
  {0x04, 0x15, 0x0E, 0x04, 0x0E, 0x15, 0x04, 0x00, 0x00}, // 10: '*'
  {0x00, 0x04, 0x04, 0x04, 0x1F, 0x04, 0x04, 0x04, 0x00}, // 11: '+'
  {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x06, 0x04, 0x08}, // 12: ','
  {0x00, 0x00, 0x00, 0x00, 0x1F, 0x00, 0x00, 0x00, 0x00}, // 13: '-'
  {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0C, 0x0C}, // 14: '.'
  {0x01, 0x02, 0x04, 0x08, 0x04, 0x02, 0x01, 0x00, 0x00}, // 15: '/'

  // --- Цифры 0-9 (ASCII 48 - 57) ---
  {0x0E, 0x11, 0x13, 0x15, 0x19, 0x11, 0x11, 0x11, 0x0E}, // 16: '0'
  {0x04, 0x0C, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x0E}, // 17: '1'
  {0x0E, 0x11, 0x01, 0x02, 0x04, 0x08, 0x10, 0x10, 0x1F}, // 18: '2'
  {0x1F, 0x01, 0x02, 0x04, 0x02, 0x01, 0x01, 0x11, 0x0E}, // 19: '3'
  {0x04, 0x0C, 0x14, 0x14, 0x1F, 0x04, 0x04, 0x04, 0x04}, // 20: '4' (Исправлена по схеме)
  {0x1F, 0x10, 0x10, 0x1E, 0x01, 0x01, 0x01, 0x11, 0x0E}, // 21: '5'
  {0x0E, 0x11, 0x10, 0x1E, 0x11, 0x11, 0x11, 0x11, 0x0E}, // 22: '6'
  {0x1F, 0x01, 0x01, 0x01, 0x03, 0x06, 0x0C, 0x18, 0x10}, // 23: '7' (Оригинал)
  {0x0E, 0x11, 0x11, 0x0E, 0x11, 0x11, 0x11, 0x11, 0x0E}, // 24: '8'
  {0x1F, 0x11, 0x00, 0x11, 0x1F, 0x06, 0x0C, 0x18, 0x10}, // 25: '9' (Оригинал)

  // --- Дополнительные знаки препинания (ASCII 58 - 64) ---
  {0x00, 0x0C, 0x0C, 0x00, 0x00, 0x00, 0x0C, 0x0C, 0x00}, // 26: ':'
  {0x00, 0x0C, 0x0C, 0x00, 0x00, 0x00, 0x06, 0x04, 0x08}, // 27: ';'
  {0x02, 0x04, 0x08, 0x10, 0x08, 0x04, 0x02, 0x00, 0x00}, // 28: '<'
  {0x00, 0x00, 0x1F, 0x00, 0x00, 0x1F, 0x00, 0x00, 0x00}, // 29: '='
  {0x08, 0x04, 0x02, 0x01, 0x02, 0x04, 0x08, 0x00, 0x00}, // 30: '>'
  {0x0E, 0x11, 0x01, 0x02, 0x04, 0x04, 0x00, 0x04, 0x00}, // 31: '?'
  {0x0E, 0x11, 0x01, 0x0D, 0x15, 0x15, 0x0D, 0x10, 0x0F}, // 32: '@'

  // --- Буквы A-Z (ASCII 65 - 90) ---
  {0x04, 0x0A, 0x11, 0x11, 0x1F, 0x11, 0x11, 0x11, 0x11}, // 33: 'A'
  {0x1E, 0x11, 0x11, 0x1E, 0x11, 0x11, 0x11, 0x11, 0x1E}, // 34: 'B'
  {0x0E, 0x11, 0x10, 0x10, 0x10, 0x10, 0x10, 0x11, 0x0E}, // 35: 'C' (Оригинал)
  {0x1E, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x1E}, // 36: 'D' (Оригинал)
  {0x1F, 0x10, 0x10, 0x10, 0x1E, 0x10, 0x10, 0x10, 0x1F}, // 37: 'E' (Оригинал)
  {0x1F, 0x10, 0x10, 0x10, 0x1E, 0x10, 0x10, 0x10, 0x10}, // 38: 'F' (Исправлена по схеме)
  {0x0F, 0x10, 0x10, 0x10, 0x17, 0x11, 0x11, 0x11, 0x0F}, // 39: 'G'
  {0x11, 0x11, 0x11, 0x11, 0x1F, 0x11, 0x11, 0x11, 0x11}, // 40: 'H' (Оригинал)
  {0x0E, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x0E}, // 41: 'I' (Оригинал)
  {0x0F, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x12, 0x0C}, // 42: 'J'
  {0x11, 0x11, 0x12, 0x14, 0x18, 0x14, 0x12, 0x11, 0x11}, // 43: 'K' (Исправлена по схеме)
  {0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x1F}, // 44: 'L'
  {0x11, 0x1B, 0x15, 0x15, 0x11, 0x11, 0x11, 0x11, 0x11}, // 45: 'M'
  {0x11, 0x11, 0x19, 0x15, 0x15, 0x15, 0x13, 0x11, 0x11}, // 46: 'N' (Оригинал)
  {0x0E, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x0E}, // 47: 'O' (Оригинал)
  {0x1E, 0x11, 0x11, 0x11, 0x1E, 0x10, 0x10, 0x10, 0x10}, // 48: 'P'
  {0x0E, 0x11, 0x11, 0x11, 0x11, 0x15, 0x13, 0x11, 0x0D}, // 49: 'Q'
  {0x1E, 0x11, 0x11, 0x11, 0x1E, 0x14, 0x12, 0x11, 0x11}, // 50: 'R' (Оригинал)
  {0x0F, 0x10, 0x10, 0x10, 0x0E, 0x01, 0x01, 0x01, 0x1E}, // 51: 'S' (Оригинал)
  {0x1F, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04}, // 52: 'T' (Оригинал)
  {0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x0E}, // 53: 'U'
  {0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x0A, 0x0A, 0x04}, // 54: 'V' (Оригинал)
  {0x11, 0x11, 0x11, 0x15, 0x15, 0x15, 0x15, 0x1F, 0x11}, // 55: 'W'
  {0x11, 0x11, 0x0A, 0x04, 0x04, 0x04, 0x0A, 0x11, 0x11}, // 56: 'X'
  {0x11, 0x11, 0x0A, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04}, // 57: 'Y'
  {0x1F, 0x01, 0x02, 0x04, 0x08, 0x10, 0x10, 0x10, 0x1F}  // 58: 'Z'
};

int getCharIndex(char c) {
  if (c >= 'a' && c <= 'z') c &= ~0x20; // Перевод строчных букв a-z в заглавные A-Z
  return (c >= ' ' && c <= 'Z') ? (c - ' ') : -1;
}

uint32_t Wheel(byte WheelPos) {
  WheelPos = 255 - WheelPos;
  if(WheelPos < 85) return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  if(WheelPos < 170) { WheelPos -= 85; return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3); }
  WheelPos -= 170; return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
}

int getIndex1(int x, int y) {
  if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT) return -1;
  return (y % 2 == 0) ? (y * WIDTH + x) : (y * WIDTH + (WIDTH - 1 - x));
}

void drawSoftPixel(float x, float y, uint32_t color) {
  int x1 = (int)x; int y1 = (int)y;
  float x_f = x - x1; float y_f = y - y1;
  uint8_t r = (color >> 16) & 0xFF, g = (color >> 8) & 0xFF, b = color & 0xFF;

  for (int i = 0; i <= 1; i++) {
    for (int j = 0; j <= 1; j++) {
      int tx = x1 + i; int ty = y1 + j;
      int idx = getIndex1(tx, ty);
      if (idx != -1) {
        float weight = (i == 0 ? 1.0f - x_f : x_f) * (j == 0 ? 1.0f - y_f : y_f);
        uint32_t c = strip.getPixelColor(idx);
        strip.setPixelColor(idx, min(255, (int)((c >> 16 & 0xFF) + r * weight)),
                                 min(255, (int)((c >> 8 & 0xFF) + g * weight)),
                                 min(255, (int)((c & 0xFF) + b * weight)));
      }
    }
  }
}

//String text = EEPROM.readString(900);
float offset = WIDTH;
byte hueOffset = 0;

///////////////////// FOR CASE 4
int STA = 1;
uint32_t colo;
int myMatrixq[9][26] = {
  {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 1, 1, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1 }, // Строка 0
  {1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1 }, // Строка 1
  {1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1 }, // Строка 2
  {1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1 },
  {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1 },
  {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1 },
  {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
  {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
  {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 }
};
int wi = 26;
int dob;
int napr;
int sme = -8; // HOR
int sme1 = 0; // VERT

///////////////////// FOR CASE 5
// #define WIDTH 26
// #define HEIGHT 9
int getIndex(int x, int y) {
  if (y % 2 == 0) return y * WIDTH + x;
  else return y * WIDTH + (WIDTH - 1 - x);
}

////////////////////////////////////////////////////////////////////////////////
void LEDMOD() {

  attachInterrupt(digitalPinToInterrupt(interruptPinESC),  INTFESC,   RISING);
  attachInterrupt(digitalPinToInterrupt(interruptPinUP),   INTFUP,    RISING);
  attachInterrupt(digitalPinToInterrupt(interruptPinDOWN), INTFDOWN,  RISING);
  attachInterrupt(digitalPinToInterrupt(interruptPinENTER),INTFENTER, RISING);

///////////////////////////////////////////////////
LEDpreset = 1;
redrawAfterEdit: //SAVE NEW STRING
String text = EEPROM.readString(900); //FOR 6
///////////////////////////////////////////////////
  tft.startWrite();
  tft.setAddrWindow(0, 0, 240, 320);
  for (int y = 0; y < 320; ++y) {for (int x = 0; x < 240; ++x) {
      tft.writeColor(tft.color888(255-(y+7)/1.38,x+7,(x+y)/9), 1); } }
  tft.endWrite();
/////
int yCir = 270;
  for (int a = 0; a < 300; a+=30) {
  tft.drawSpot(a, yCir, 60, tft.color888(a/1.18 ,0 , 255-(a/1.18)));
  }
///////////////////////////////////////////////////
  //uint16_t wall = color565(90,255,90); tft.fillScreen(wall);
///////////////////////////////////////////////////////
MyText = "B [<>]"; startX = 17; startY = 2; charColo = color565(255,255,255); event(); startY += 20;
MyText = "G [<>]"; startX = 17; charColo = color565(255,255,255); event(); startY += 20;
MyText = "R [<>]"; startX = 17; charColo = color565(255,255,255); event(); startY += 20;
MyText = "фонарик [<>]"; startX = 17; charColo = color565(255,255,255); event(); startY += 20;
MyText = "лист"; startX = 17; charColo = color565(255,255,255); event(); startY += 20;
MyText = "часы"; startX = 17; charColo = color565(255,255,255); event(); startY += 20;
MyText = "смайл"; startX = 17; charColo = color565(255,255,255); event(); startY += 20;
MyText = "сердечко [<>]"; startX = 17; charColo = color565(255,255,255); event(); startY += 20;
MyText = "закат"; startX = 17; charColo = color565(255,255,255); event(); startY += 20;
MyText = "бег. строка [ENT]"; startX = 17; charColo = color565(255,255,255); event();
  for (int a = 0; a < 10; a+=1) {startX = 1; startY = 2+(20*a); charColo = color565(0,55,0); symbolDraw(168);} //>
                                 startX = 1; startY = 2+(20*(LEDpreset+3)); charColo = color565(255,255,255); symbolDraw(168); //> WHITE //+3 to 0-10 [case -3-6]
///////////////////////////////////////////////////////

  startX = 40; startY = 228; scaleX = 2; scaleY = 1; charColo = color565(255,255,255); MyText = "DEVICE"; event();
  startX = 65; startY = 260; scaleX = 2; scaleY = 1; charColo = color565(255,255,255); MyText =  "7799";  event();

///////////////////// FOR CASE 1
// #define WIDTH 26
// #define HEIGHT 9
// #define IMG_SIZE 26

uint8_t currentBrightness[LED_COUNT];
float angle = 0;
float colorPos = 0;

const uint8_t matrixData[IMG_SIZE][IMG_SIZE] PROGMEM = {
  { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
  { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
  { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
  { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 2, 2, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
  { 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 1, 1, 2, 2, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
  { 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 1, 1, 2, 1, 2, 2, 2, 1, 1, 1, 1, 1, 1, 1, 1 },
  { 1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 1, 1, 1, 2, 1, 1, 2, 2, 2, 1, 1, 1, 1, 1, 1, 1 },
  { 1, 1, 1, 1, 1, 1, 1, 2, 2, 1, 2, 1, 1, 1, 1, 2, 1, 2, 2, 1, 1, 1, 1, 1, 1, 1 },
  { 1, 1, 1, 1, 1, 1, 1, 2, 2, 1, 1, 2, 1, 2, 1, 1, 1, 2, 2, 1, 1, 1, 1, 1, 1, 1 },
  { 1, 1, 1, 1, 1, 1, 1, 2, 2, 1, 1, 1, 2, 2, 1, 2, 1, 2, 2, 1, 1, 1, 1, 1, 1, 1 },
  { 1, 2, 2, 1, 1, 1, 1, 2, 2, 1, 1, 1, 1, 2, 2, 1, 1, 2, 2, 1, 1, 1, 1, 2, 2, 1 },
  { 1, 2, 2, 2, 2, 2, 1, 2, 2, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 1, 2, 2, 2, 2, 2, 1 },
  { 2, 2, 2, 1, 2, 2, 2, 1, 2, 1, 1, 1, 1, 2, 1, 1, 1, 2, 1, 2, 2, 2, 1, 2, 2, 2 },
  { 2, 2, 1, 2, 1, 1, 2, 2, 2, 2, 1, 1, 1, 1, 1, 1, 2, 2, 2, 2, 1, 1, 2, 1, 2, 2 },
  { 2, 2, 2, 1, 2, 1, 1, 2, 2, 2, 1, 1, 1, 2, 1, 1, 2, 2, 2, 2, 1, 2, 1, 2, 2, 2 },
  { 1, 2, 2, 1, 1, 1, 2, 1, 2, 2, 1, 1, 1, 2, 1, 1, 2, 2, 1, 1, 1, 1, 1, 2, 2, 1 },
  { 1, 2, 2, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 1, 1, 2, 2, 2, 1 },
  { 1, 1, 2, 2, 2, 1, 1, 1, 2, 1, 1, 1, 1, 2, 1, 1, 1, 1, 2, 1, 1, 2, 2, 2, 1, 1 },
  { 1, 1, 1, 2, 2, 2, 1, 1, 1, 2, 1, 1, 1, 2, 1, 1, 2, 1, 1, 1, 2, 2, 2, 1, 1, 1 },
  { 1, 1, 2, 2, 1, 1, 2, 1, 1, 1, 2, 1, 1, 2, 1, 2, 1, 1, 1, 1, 1, 2, 2, 2, 1, 1 },
  { 1, 2, 2, 2, 1, 1, 1, 1, 1, 2, 1, 2, 2, 2, 2, 1, 2, 1, 2, 1, 1, 1, 2, 2, 2, 1 },
  { 1, 1, 2, 2, 2, 2, 1, 1, 1, 1, 1, 2, 2, 2, 2, 2, 1, 1, 1, 1, 2, 2, 2, 2, 1, 1 },
  { 1, 1, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1, 1, 1 },
  { 1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 2, 2, 1, 1, 1, 2, 2, 2, 2, 2, 1, 1, 1, 1, 1, 1 },
  { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
  { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 }
};
 //strip.setBrightness(40);
 memset(currentBrightness, 0, LED_COUNT);

///////////////////// FOR CASE 2
//  uint32_t colo;
 int myMatrix[9][26] = {
  {1, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0 }, // Строка 0
  {0, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 1, 1, 1, 1 }, // Строка 1
  {0, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 0, 0, 1, 1, 1, 1, 1, 0, 1, 0, 1, 1, 1, 1 }, // Строка 2
  {0, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 1, 1, 1, 1 },
  {0, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 0, 0, 0, 0 },
  {0, 1, 1, 1, 0, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 0 },
  {0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 0, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 0 },
  {0, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0 },
  {1, 0, 0, 0, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0 }
                       };
  //wi = 26;
  //dob;
  //napr;
  //sme =  0; //HOR
  //sme1 = -8; //VERT
  //obr;
  //obr1;
/////////////////////
  int brightnessFlash = 10; int upLimit = 27; int doLimit = 1;
  newPRESET:
  
  numButton0 = -1; intESC = LOW; intUP = LOW; intDOWN = LOW; intENTER = LOW;
  for (int a = 0; a < 10; a+=1) {startX = 1; startY = 2+(20*a); scaleX = 1; charColo = color565(0,55,0); symbolDraw(168);} //>
                                 startX = 1; startY = 2+(20*(LEDpreset+3)); charColo = color565(255,255,255); symbolDraw(168); //> WHITE //+3 to 0-10 [case -3-6]

   switch (LEDpreset) {
////////////////////////////////////////////////////////////   
  case -3:
  strip.setBrightness(brightnessFlash);
  colorWipe(strip.Color(  0,  0,255), 0); 
  while(intESC == LOW && intUP == LOW && intDOWN == LOW) {
    PressedButton(1); //NAV
    if(numButton0 == 3) {brightnessFlash++; if(brightnessFlash > upLimit) {brightnessFlash = upLimit;} strip.setBrightness(brightnessFlash);}
    if(numButton0 == 4) {brightnessFlash--; if(brightnessFlash < doLimit) {brightnessFlash = doLimit;} strip.setBrightness(brightnessFlash);} 
    strip.show(); delay(100);  
  }
  break;
////////////////////////////////////////////////////////////   
  case -2:
  strip.setBrightness(brightnessFlash);
  colorWipe(strip.Color(  0,255,  0), 0);
  while(intESC == LOW && intUP == LOW && intDOWN == LOW) {
    PressedButton(1); //NAV
    if(numButton0 == 3) {brightnessFlash++; if(brightnessFlash > upLimit) {brightnessFlash = upLimit;} strip.setBrightness(brightnessFlash);}
    if(numButton0 == 4) {brightnessFlash--; if(brightnessFlash < doLimit) {brightnessFlash = doLimit;} strip.setBrightness(brightnessFlash);} 
    strip.show(); delay(100);   
  }
  break;
////////////////////////////////////////////////////////////   
  case -1:
  strip.setBrightness(brightnessFlash);
  colorWipe(strip.Color(255,  0,  0), 0);
  while(intESC == LOW && intUP == LOW && intDOWN == LOW) {
    PressedButton(1); //NAV
    if(numButton0 == 3) {brightnessFlash++; if(brightnessFlash > upLimit) {brightnessFlash = upLimit;} strip.setBrightness(brightnessFlash);}
    if(numButton0 == 4) {brightnessFlash--; if(brightnessFlash < doLimit) {brightnessFlash = doLimit;} strip.setBrightness(brightnessFlash);} 
    strip.show(); delay(100);   
  }
  break;
////////////////////////////////////////////////////////////   
  case 0:
  if(brightnessFlash > upLimit-10) {brightnessFlash = upLimit-10;} //WHITE TOO BRIGHT
  strip.setBrightness(brightnessFlash);
  colorWipe(strip.Color(255,255,255), 0);
  while(intESC == LOW && intUP == LOW && intDOWN == LOW) {
    PressedButton(1); //NAV
    if(numButton0 == 3) {brightnessFlash++; if(brightnessFlash > upLimit-10) {brightnessFlash = upLimit-10;} strip.setBrightness(brightnessFlash);}
    if(numButton0 == 4) {brightnessFlash--; if(brightnessFlash < doLimit) {brightnessFlash = doLimit;} strip.setBrightness(brightnessFlash);} 
    strip.show(); delay(100);  
  }
  break;
////////////////////////////////////////////////////////////   
  case 1:
  angle = 0;
  colorPos = 0;
  strip.setBrightness(40);
  colorWipe(strip.Color(0,  0,  0), 0);
  memset(currentBrightness, 0, LED_COUNT);

     while(intESC == LOW && intUP == LOW && intDOWN == LOW) {
  float s = sin(angle);
  float c = cos(angle);

  float centerX = 13.0, centerY = 13.0;
  float dispCenterX = 13.0;

  // Старт: -3.5. Общее смещение 18.0. Финиш: 14.5.
  float dispCenterY = -3.5 + (colorPos * 18.0);

  uint8_t frameTarget[LED_COUNT];
  memset(frameTarget, 0, LED_COUNT);

  // 1. Расчет вращения
  for (int y = 0; y < HEIGHT; y++) {
    for (int x = 0; x < WIDTH; x++) {
      float dx = x - dispCenterX;
      float dy = y - dispCenterY;
      int srcX = (int)(dx * c + dy * s + centerX);
      int srcY = (int)(-dx * s + dy * c + centerY);

      if (srcX >= 1 && srcX < IMG_SIZE - 1 && srcY >= 1 && srcY < IMG_SIZE - 1) {
        if (pgm_read_byte(&(matrixData[srcY][srcX])) == 2) {
          if (pgm_read_byte(&(matrixData[srcY - 1][srcX])) == 1 || pgm_read_byte(&(matrixData[srcY + 1][srcX])) == 1 || pgm_read_byte(&(matrixData[srcY][srcX - 1])) == 1 || pgm_read_byte(&(matrixData[srcY][srcX + 1])) == 1) {

            int ledIdx = (y % 2 == 0) ? (y * WIDTH + x) : (y * WIDTH + (WIDTH - 1 - x));
            frameTarget[ledIdx] = 1;
          }
        }
      }
    }
  }

  // 2. Отрисовка
  for (int i = 0; i < LED_COUNT; i++) {
    if (frameTarget[i]) {
      if (currentBrightness[i] < 20) currentBrightness[i] += 10;
      else currentBrightness[i] = 25;
    } else {
      if (currentBrightness[i] > 6) currentBrightness[i] -= 6;
      else currentBrightness[i] = 0;
    }

    if (currentBrightness[i] > 0) {
      // Плавная смена G -> R (colorPos 0.0 -> 1.0)
      strip.setPixelColor(i, strip.Color((uint8_t)(currentBrightness[i] * colorPos), (uint8_t)(currentBrightness[i] * (1.0 - colorPos)), 0));
    } else {
      strip.setPixelColor(i, 0);
    }
  }

  strip.show();
  angle += 0.06;
  colorPos += 0.002;  // Подобрано для плавного перехода
  if (colorPos > 1.0) colorPos = 0;

  delay(15);
                                                            } 
  colorWipe(strip.Color(0,  0,  0), 0);
  break;
//////////////////////////////////////////////////////////////////////////////  
  case 2:
  // strip.begin();          // INITIALIZE NeoPixel strip object (REQUIRED)
  // strip.show();           // Turn OFF all pixels ASAP
  strip.setBrightness(4); // Set BRIGHTNESS to about 1/5 (max = 255)
  colorWipe(strip.Color(0,  0,  0), 0);
  colo = strip.Color(25, 0, 255); 

  //wi = 26;
  sme = 0; //HOR
  //sme1 = -8; //VERT

  for (int it = 0; it < 9; it++) { // Проход по строкам (0, 1, 2)
      if((it+1)==1) {dob = wi*0;   napr =  1;} // row1
      if((it+1)==2) {dob = wi*2-1; napr = -1;} // row2
      if((it+1)==3) {dob = wi*2;   napr =  1;}
      if((it+1)==4) {dob = wi*4-1; napr = -1;}
      if((it+1)==5) {dob = wi*4;   napr =  1;}
      if((it+1)==6) {dob = wi*6-1; napr = -1;}
      if((it+1)==7) {dob = wi*6;   napr =  1;}
      if((it+1)==8) {dob = wi*8-1; napr = -1;}
      if((it+1)==9) {dob = wi*8;   napr =  1;}
    for (int st = 0; st < 26; st++) { // Проход по столбцам (0, 1)
      if(myMatrix[it][st] == 0) {
      strip.setPixelColor(dob + ((st+sme)*napr), colo); //strip.show();
                                }                               
                                    }
                                }
 strip.show();  
     while(intESC == LOW && intUP == LOW && intDOWN == LOW) {
   
                                                            }
// strip.clear();
// strip.show();          // Гасим ленту
// strip.updateLength(0); // Освобождаем RAM
// pinMode(39, OUTPUT); // Освобождаем пин  
 colorWipe(strip.Color(0,  0,  0), 0);
  break; 
  //////////////////////////////////////////////////////             
  case 3:

  colorWipe(strip.Color(0,  0,  0), 0); 

  strip.setBrightness(10);
  randomSeed(analogRead(0));

     while(intESC == LOW && intUP == LOW && intDOWN == LOW) {
  // Проезд
  for (float p = -13.5; p < HEIGHT + 13.5; p += 0.8) {
    updateSnow(); drawFrame(p, true); delay(10);
  }
                                                            
   // Смена поворота для следующего раза
  rotationMode = (rotationMode + 1) % 4;
  // Пауза
  unsigned long ps = millis();
  while (millis() - ps < 1000) {
    if(intESC != LOW || intUP != LOW || intDOWN != LOW) {goto interr; break;}
    updateSnow(); drawFrame(0, false); delay(10);
  }                                                         }                                                        
  break; 
  ///////////////////////////////////////////////////////////////
  case 4:
  colorWipe(strip.Color(0,  0,  0), 0); 
  strip.setBrightness(10);
  colo = strip.Color(255, 0, 255); 
  STA = 1;
  //wi = 26;
  sme = -8; //HOR
  //sme1 = -8; //VERT

  while(intESC == LOW && intUP == LOW && intDOWN == LOW) {
      for(int i=0; i<235; i+=1) { 
    strip.setPixelColor(i, strip.Color(0, 0, 0)); // CLEAR BUFFER
                                }
    PressedButton(1); //NAV
    if(numButton0 == 3 || numButton0 == 4 || STA == 1) {
if(numButton0 == 4) {sme -= 1; if(sme < -9) {sme = -9;} numButton0 = -1;}
if(numButton0 == 3) {sme += 1; if(sme >  7) {sme =  7;} numButton0 = -1;}
  for (int i = 0; i < 9; i++) { // Проход по строкам (0, 1, 2)
      if((i+1)==1) {dob = wi*0;   napr =  1;} // row1
      if((i+1)==2) {dob = wi*2-1; napr = -1;} // row2
      if((i+1)==3) {dob = wi*2;   napr =  1;}
      if((i+1)==4) {dob = wi*4-1; napr = -1;}
      if((i+1)==5) {dob = wi*4;   napr =  1;}
      if((i+1)==6) {dob = wi*6-1; napr = -1;}
      if((i+1)==7) {dob = wi*6;   napr =  1;}
      if((i+1)==8) {dob = wi*8-1; napr = -1;}
      if((i+1)==9) {dob = wi*8;   napr =  1;}
    for (int s = 0; s < 26; s++) { // Проход по столбцам (0, 1)
      if(myMatrixq[i][s] == 0) {
      strip.setPixelColor(dob + ((s+sme)*napr), colo); //strip.show();
                               }                               
                                 }
                              } strip.show(); 
                                                      } STA = 2;
                                                        }
  colorWipe(strip.Color(0,  0,  0), 0);
  break;             
                 
  case 5:
  colorWipe(strip.Color(0,  0,  0), 0); 
  strip.setBrightness(15);
///
  while(intESC == LOW && intUP == LOW && intDOWN == LOW) {
  float sunX = WIDTH / 2.0;
  float sunY = 5.8;          
  float sunRadius = 4.5;     
  int waterLine = 6;         
  
  static float t = 0;
  static float cloudOffset = 0;
  t += 0.03; 
  cloudOffset += 0.018; 

  for (int y = 0; y < HEIGHT; y++) {
    for (int x = 0; x < WIDTH; x++) {
      int r = 0, g = 0, b = 0;

      if (y < waterLine) {
        // --- 1. НЕБО, ЗВЕЗДЫ И СОЛНЦЕ ---
        r = map(y, 0, waterLine, 5, 30);
        g = 0;
        b = map(y, 0, waterLine, 20, 5);

        uint32_t seed = x * 13 + y * 29; 
        if ((seed % 35 == 0) && (y < waterLine - 2)) {
          float starPulse = (sin(t * 1.5 + seed) + 1.0) / 2.0;
          int lum = 10 + (int)(30 * starPulse); 
          r = max(r, lum); g = max(g, lum); b = max(b, lum); 
        }

        float dx = x - sunX;
        float dy = y - sunY;
        float dist = sqrt(dx * dx + dy * dy);

        if (dist < sunRadius) {
          r = 140; g = 30; b = 0; 
        } else if (dist < sunRadius + 1.2) {
          float halo = 1.0 - ((dist - sunRadius) / 1.2);
          r = max(r, (int)(60 * halo));
          g = max(g, (int)(10 * halo));
        }

        // ОБЛАКА (ВЕРХНИЕ 3 СТРОКИ)
        if (y < 3) {
          float cloudNoise = sin(x * 0.35 + cloudOffset) * cos(y * 0.6 + cloudOffset * 0.5);
          if (cloudNoise > 0.25) { 
            float opacity = (cloudNoise - 0.25) * 2.0;
            if (opacity > 0.8) opacity = 0.8; 
            int cloudR = 30; int cloudG = 30; int cloudB = 50; 
            r = (int)(r * (1.0 - opacity) + cloudR * opacity);
            g = (int)(g * (1.0 - opacity) + cloudG * opacity);
            b = (int)(b * (1.0 - opacity) + cloudB * opacity);
          }
        }
      } 
      else {
        // --- 2. ВОДА: РАСШИРЕННАЯ ДОРОЖКА ---
        r = 0; g = 1; b = 10; 

        float distToSunAxis = abs(x - sunX);
        
        // ШИРИНА УВЕЛИЧЕНА (радиус 4.5 пикселя + расширение)
        float pathWidth = 4.5 + (y - waterLine) * 0.8;
        
        float wave = sin(x * 1.6 - t * 2.2) * cos(y * 0.9 + t * 1.2);
        float ripple = (wave + 1.0) / 2.0;

        if (distToSunAxis < pathWidth) {
          // ОРАНЖЕВАЯ ДОРОЖКА (Плотная, но с мягкими краями)
          float edgeFade = 1.0;
          if (distToSunAxis > pathWidth - 2.0) {
             edgeFade = 1.0 - (distToSunAxis - (pathWidth - 2.0)) / 2.0;
          }
          r = max(r, (int)(110 * ripple * edgeFade)); 
          g = max(g, (int)(40 * ripple * edgeFade));
        } 
        
        // ГОЛУБАЯ РЯБЬ (по всей поверхности)
        int rippleIntensity = (int)(28 * ripple); 
        r = max(r, rippleIntensity / 3); 
        g = max(g, rippleIntensity / 3);
        b = max(b, rippleIntensity + 5); 
      }

      strip.setPixelColor(getIndex(x, y), strip.Color(r, g, b));
    }
  }
  strip.show();
  delay(50);
}
colorWipe(strip.Color(0,  0,  0), 0); 
  break;
  
  case 6:
  colorWipe(strip.Color(0,  0,  0), 0);
  strip.setBrightness(10);

  while(intESC == LOW && intUP == LOW && intDOWN == LOW && intENTER == LOW) {
    strip.clear();
  float currentX = offset;
  
  for (int i = 0; i < text.length(); i++) {
    int idx = getCharIndex(text[i]);
    uint32_t charColor = Wheel((hueOffset + i * 15) & 255);
    
    if (idx != -1) {
      for (int row = 0; row < 9; row++) {
        uint8_t rowData = font[idx][row];
        for (int col = 0; col < 5; col++) {
          if (rowData & (0x10 >> col)) {
            // Теперь рисуем от 0 до 8 строки (высота 9)
            drawSoftPixel(currentX + col, row, charColor);
          }
        }
      }
    }
    currentX += 7; // Ширина буквы 5 + пробел 2
  }
  strip.show();
  offset -= 0.32; 
  hueOffset += 1;
  
  if (offset < -(int)text.length() * 7) offset = WIDTH;
  delay(3);
  }
  colorWipe(strip.Color(0,  0,  0), 0);
  break;
   }
///////////////////////////////////////////////
///////////////////////////////////////////////
 interr:
       //PressedButton(1);
       if(intDOWN == HIGH)  {intESC = LOW; intUP = LOW; intDOWN = LOW; intENTER = LOW; LEDpreset ++ ; if(LEDpreset > 6)  {LEDpreset = 6;}  colorWipe(strip.Color(0,  0,  0), 0); delay(170); goto newPRESET;} //NEXT = DOWN
       if(intUP   == HIGH)  {intESC = LOW; intUP = LOW; intDOWN = LOW; intENTER = LOW; LEDpreset -- ; if(LEDpreset < -3) {LEDpreset = -3;} colorWipe(strip.Color(0,  0,  0), 0); delay(170); goto newPRESET;} //PREV = UP
       if(intENTER == HIGH) {intESC = LOW; intUP = LOW; intDOWN = LOW; intENTER = LOW; colorWipe(strip.Color(0,  0,  0), 0); EDIT_STRING_LED(); delay(170); goto redrawAfterEdit; }
       if(intESC  == HIGH)  {intESC = LOW; intUP = LOW; intDOWN = LOW; intENTER = LOW;} //EXIT 
       else {intESC = LOW; intUP = LOW; intDOWN = LOW; intENTER = LOW; goto newPRESET;}
              
  detachInterrupt(digitalPinToInterrupt(interruptPinESC));
  detachInterrupt(digitalPinToInterrupt(interruptPinUP));
  detachInterrupt(digitalPinToInterrupt(interruptPinDOWN));
  detachInterrupt(digitalPinToInterrupt(interruptPinENTER));

  intESC = LOW; intUP = LOW; intDOWN = LOW; scaleX = 1; scaleY = 1; //
  colorWipe(strip.Color(0,  0,  0), 0); strip.show(); //MODULE
} //EXIT
///////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////////////////////////// 
void INTFESC()   {
intESC   = HIGH;
}
void INTFDOWN()  {
intDOWN  = HIGH;
}
void INTFUP()    {
intUP    = HIGH;
}
void INTFENTER() {
intENTER = HIGH;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////// 
///////////////////////////////////////////////////////////////////////////////////////////////////////////////                    
uint16_t color565( byte r, byte g, byte b ) {
  return ( ( r & 0xF8 ) << 8 ) | ( ( g & 0xFC ) << 3 ) | ( ( b & 0xF8 ) >> 3 );
                                            }
///////////////////////////////////////////////////////////////////////////////////////////////////////////////  





void chooseMenu() {
  if(selectMenuP == 2 && mod == 0)  {InMenu = 1; NOTE(1);}
  if(selectMenuP == 3 && mod == 1)  {InMenu = 1; MACRO_PAD();}
  if(selectMenuP == 2 && mod == 1)  {InMenu = 1; LEDMOD();}
  if(selectMenuP == 3 && mod == 0)  {InMenu = 1; NAV_GRAPH();}
  if(selectMenuP == 1 && mod == 1)  {InMenu = 1; INT_RADIO();}
  if(selectMenuP == 4 && mod == 0)  {InMenu = 1; VISUAL();}
  if(selectMenuP == 1 && mod == 0)  {InMenu = 1; WIFI_CONFIG();}
  if(selectMenuP == 4 && mod == 1)  {InMenu = 1; MICRO_SD();}
  if(selectMenuP == 7 && mod == 0)  {InMenu = 1; BATTERY_INFO();}
  if(selectMenuP == 5 && mod == 0)  {InMenu = 1; GAME();}
  // if(selectMenuP == 6)  {InMenu = 1; NOTE(1);}
  // if(selectMenuP == 7)  {InMenu = 1; NOTE(1);}
  // if(selectMenuP == 8)  {InMenu = 1; NOTE(1);}
  // if(selectMenuP == 9)  {InMenu = 1; NOTE(1);}
  // if(selectMenuP == 10) {InMenu = 1; NOTE(1);}
  // if(selectMenuP == 11) {} //GAMES //InMenu = 1; PLOT();
  // if(selectMenuP == 12) {} 
                  }

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
////////////////////////////////////////////////////////////////////////////////////////////


void event() {//PARSES THE STRING BY CHARACTER AND SENDS TO THE PRINT FUNCTION [ event() => chooseSymbol() => symbolDraw() ]
int charByteStart, charByteEnd, dobByte, strLen = MyText.length();
for (charByteStart=0; charByteStart<strLen+0; charByteStart+=dobByte) {
                        if(MyText.charAt(charByteStart) == '\320' ||
                           MyText.charAt(charByteStart) == '\321') {dobByte=2;}//+BYTE IF RUSSIAN   
                                                              else {dobByte=1;}    
                                                           charByteEnd=charByteStart+dobByte;        
substrSpecific = MyText.substring(charByteStart, charByteEnd);
//if(substrSpecific == "\40") {if(startX == 2) {continue;} startX+=14; continue;}//IF SPACE. CANCEL IF START STRING
                                                           chooseSymbol();
                                                                      }
             } 
///////////////////////////////////////////////////////////////////////////////
void symbolDraw(int shift){
  int row = 0, col = 0, buffidx=0; uint8_t colo; //int h = 27-1, w = 2506; 
  int symbolW = 14, symbolWidth = 1, shi = w - symbolW; shift = shift*symbolW; //shift*symbolW
                                    if(startX > (DispW-(symbolW*scaleX))) {startX = 2; startY = startY+(h*scaleY)+(-4);}//-X =BETWEEN ROWS
  for (col=startY; col<h*scaleY+startY; col+=scaleY) {  symbolWidth = 1;                                                 
  for (row=startX; row<w*scaleX+startX; row+=scaleX) { 
      colo = pgm_read_byte(NOTO_FONT_ALL + buffidx + shift); //shift*symbolW
                                                      symbolWidth++;
      if(colo != 1)  {
                      tft.fillRect(row,col,scaleX,scaleY,charColo); //WITH SCALE 
                      //tft.drawPixel(row,col,charColo); //WITHOUT SCALE
                     }
      buffidx++;
                      if(symbolWidth == 15) {buffidx = buffidx + shi; break;}                                 
                                                     }    
                                                     }
                                                      startX = row; 
                           }
///////////////////////////////////////////////////////////////////////////////  
void chooseSymbol() {
//if(substrSpecific == "\40") {startX+=15; return;}
if(substrSpecific == "а") {symbolDraw(0); return;}
if(substrSpecific == "б") {symbolDraw(1); return;}
if(substrSpecific == "в") {symbolDraw(2); return;}
if(substrSpecific == "г") {symbolDraw(3); return;}
if(substrSpecific == "д") {symbolDraw(4); return;}
if(substrSpecific == "е") {symbolDraw(5); return;}
if(substrSpecific == "ё") {symbolDraw(6); return;}
if(substrSpecific == "ж") {symbolDraw(7); return;}
if(substrSpecific == "з") {symbolDraw(8); return;}
if(substrSpecific == "и") {symbolDraw(9); return;}
if(substrSpecific == "й") {symbolDraw(10); return;}
if(substrSpecific == "к") {symbolDraw(11); return;}
if(substrSpecific == "л") {symbolDraw(12); return;}
if(substrSpecific == "м") {symbolDraw(13); return;}
if(substrSpecific == "н") {symbolDraw(14); return;}
if(substrSpecific == "о") {symbolDraw(15); return;}
if(substrSpecific == "п") {symbolDraw(16); return;}
if(substrSpecific == "р") {symbolDraw(17); return;}
if(substrSpecific == "с") {symbolDraw(18); return;}
if(substrSpecific == "т") {symbolDraw(19); return;}
if(substrSpecific == "у") {symbolDraw(20); return;}
if(substrSpecific == "ф") {symbolDraw(21); return;}
if(substrSpecific == "х") {symbolDraw(22); return;}
if(substrSpecific == "ц") {symbolDraw(23); return;}
if(substrSpecific == "ч") {symbolDraw(24); return;}
if(substrSpecific == "ш") {symbolDraw(25); return;}
if(substrSpecific == "щ") {symbolDraw(26); return;}
if(substrSpecific == "ъ") {symbolDraw(27); return;}
if(substrSpecific == "ы") {symbolDraw(28); return;}
if(substrSpecific == "ь") {symbolDraw(29); return;}
if(substrSpecific == "э") {symbolDraw(30); return;}
if(substrSpecific == "ю") {symbolDraw(31); return;}
if(substrSpecific == "я") {symbolDraw(32); return;}

if(substrSpecific == "a") {symbolDraw(35); return;}
if(substrSpecific == "b") {symbolDraw(36); return;}
if(substrSpecific == "c") {symbolDraw(37); return;}
if(substrSpecific == "d") {symbolDraw(38); return;}
if(substrSpecific == "e") {symbolDraw(39); return;}
if(substrSpecific == "f") {symbolDraw(40); return;}
if(substrSpecific == "g") {symbolDraw(41); return;}
if(substrSpecific == "h") {symbolDraw(42); return;}
if(substrSpecific == "i") {symbolDraw(43); return;}
if(substrSpecific == "j") {symbolDraw(44); return;}
if(substrSpecific == "k") {symbolDraw(45); return;}
if(substrSpecific == "l") {symbolDraw(46); return;}
if(substrSpecific == "m") {symbolDraw(47); return;}
if(substrSpecific == "n") {symbolDraw(48); return;}
if(substrSpecific == "o") {symbolDraw(49); return;}
if(substrSpecific == "p") {symbolDraw(50); return;}
if(substrSpecific == "q") {symbolDraw(51); return;}
if(substrSpecific == "r") {symbolDraw(52); return;}
if(substrSpecific == "s") {symbolDraw(53); return;}
if(substrSpecific == "t") {symbolDraw(54); return;}
if(substrSpecific == "u") {symbolDraw(55); return;}
if(substrSpecific == "v") {symbolDraw(56); return;}
if(substrSpecific == "w") {symbolDraw(57); return;}
if(substrSpecific == "x") {symbolDraw(58); return;}
if(substrSpecific == "y") {symbolDraw(59); return;}
if(substrSpecific == "z") {symbolDraw(60); return;}

if(substrSpecific == "А") {symbolDraw(63); return;}
if(substrSpecific == "Б") {symbolDraw(64); return;}
if(substrSpecific == "В") {symbolDraw(65); return;}
if(substrSpecific == "Г") {symbolDraw(66); return;}
if(substrSpecific == "Д") {symbolDraw(67); return;}
if(substrSpecific == "Е") {symbolDraw(68); return;}
if(substrSpecific == "Ё") {symbolDraw(69); return;}
if(substrSpecific == "Ж") {symbolDraw(70); return;}
if(substrSpecific == "З") {symbolDraw(71); return;}
if(substrSpecific == "И") {symbolDraw(72); return;}
if(substrSpecific == "Й") {symbolDraw(73); return;}
if(substrSpecific == "К") {symbolDraw(74); return;}
if(substrSpecific == "Л") {symbolDraw(75); return;}
if(substrSpecific == "М") {symbolDraw(76); return;}
if(substrSpecific == "Н") {symbolDraw(77); return;}
if(substrSpecific == "О") {symbolDraw(78); return;}
if(substrSpecific == "П") {symbolDraw(79); return;}
if(substrSpecific == "Р") {symbolDraw(80); return;}
if(substrSpecific == "С") {symbolDraw(81); return;}
if(substrSpecific == "Т") {symbolDraw(82); return;}
if(substrSpecific == "У") {symbolDraw(83); return;}
if(substrSpecific == "Ф") {symbolDraw(84); return;}
if(substrSpecific == "Х") {symbolDraw(85); return;}
if(substrSpecific == "Ц") {symbolDraw(86); return;}
if(substrSpecific == "Ч") {symbolDraw(87); return;}
if(substrSpecific == "Ш") {symbolDraw(88); return;}
if(substrSpecific == "Щ") {symbolDraw(89); return;}
if(substrSpecific == "Ъ") {symbolDraw(90); return;}
if(substrSpecific == "Ы") {symbolDraw(91); return;}
if(substrSpecific == "Ь") {symbolDraw(92); return;}
if(substrSpecific == "Э") {symbolDraw(93); return;}
if(substrSpecific == "Ю") {symbolDraw(94); return;}
if(substrSpecific == "Я") {symbolDraw(95); return;}

if(substrSpecific == "A") {symbolDraw(98); return;}
if(substrSpecific == "B") {symbolDraw(99); return;}
if(substrSpecific == "C") {symbolDraw(100); return;}
if(substrSpecific == "D") {symbolDraw(101); return;}
if(substrSpecific == "E") {symbolDraw(102); return;}
if(substrSpecific == "F") {symbolDraw(103); return;}
if(substrSpecific == "G") {symbolDraw(104); return;}
if(substrSpecific == "H") {symbolDraw(105); return;}
if(substrSpecific == "I") {symbolDraw(106); return;}
if(substrSpecific == "J") {symbolDraw(107); return;}
if(substrSpecific == "K") {symbolDraw(108); return;}
if(substrSpecific == "L") {symbolDraw(109); return;}
if(substrSpecific == "M") {symbolDraw(110); return;}
if(substrSpecific == "N") {symbolDraw(111); return;}
if(substrSpecific == "O") {symbolDraw(112); return;}
if(substrSpecific == "P") {symbolDraw(113); return;}
if(substrSpecific == "Q") {symbolDraw(114); return;}
if(substrSpecific == "R") {symbolDraw(115); return;}
if(substrSpecific == "S") {symbolDraw(116); return;}
if(substrSpecific == "T") {symbolDraw(117); return;}
if(substrSpecific == "U") {symbolDraw(118); return;}
if(substrSpecific == "V") {symbolDraw(119); return;}
if(substrSpecific == "W") {symbolDraw(120); return;}
if(substrSpecific == "X") {symbolDraw(121); return;}
if(substrSpecific == "Y") {symbolDraw(122); return;}
if(substrSpecific == "Z") {symbolDraw(123); return;}

if(substrSpecific == "1") {symbolDraw(126); return;}
if(substrSpecific == "2") {symbolDraw(127); return;}
if(substrSpecific == "3") {symbolDraw(128); return;}
if(substrSpecific == "4") {symbolDraw(129); return;}
if(substrSpecific == "5") {symbolDraw(130); return;}
if(substrSpecific == "6") {symbolDraw(131); return;}
if(substrSpecific == "7") {symbolDraw(132); return;}
if(substrSpecific == "8") {symbolDraw(133); return;}
if(substrSpecific == "9") {symbolDraw(134); return;}
if(substrSpecific == "0") {symbolDraw(135); return;}

if(substrSpecific == ".") {symbolDraw(138); return;}
if(substrSpecific == ":") {symbolDraw(139); return;}
if(substrSpecific == ",") {symbolDraw(140); return;}
if(substrSpecific == ";") {symbolDraw(141); return;}
if(substrSpecific == " ") {symbolDraw(142); return;}
if(substrSpecific == "'") {symbolDraw(143); return;}
if(substrSpecific == "\42") {symbolDraw(144); return;}// "
if(substrSpecific == "(") {symbolDraw(145); return;}
if(substrSpecific == "!") {symbolDraw(146); return;}
if(substrSpecific == "?") {symbolDraw(147); return;}
if(substrSpecific == ")") {symbolDraw(148); return;}
if(substrSpecific == "+") {symbolDraw(149); return;}
if(substrSpecific == "-") {symbolDraw(150); return;}
if(substrSpecific == "*") {symbolDraw(151); return;}
if(substrSpecific == "/") {symbolDraw(152); return;}
if(substrSpecific == "=") {symbolDraw(153); return;}
if(substrSpecific == "@") {symbolDraw(154); return;}
if(substrSpecific == "#") {symbolDraw(155); return;}
if(substrSpecific == "|") {symbolDraw(156); return;}
if(substrSpecific == "<") {symbolDraw(157); return;}
if(substrSpecific == ">") {symbolDraw(158); return;}
if(substrSpecific == "[") {symbolDraw(159); return;}
if(substrSpecific == "]") {symbolDraw(160); return;}
if(substrSpecific == "{") {symbolDraw(161); return;}
if(substrSpecific == "}") {symbolDraw(162); return;}
if(substrSpecific == "&") {symbolDraw(163); return;}
if(substrSpecific == "%") {symbolDraw(164); return;}
if(substrSpecific == "\134") {symbolDraw(165); return;}
//166 t* | 167 LEFT | 168 RIGHT | 169 UP | 170 DOWN | 171 SMART_HOME | 172 HUMIDITY
if(substrSpecific == "_") {symbolDraw(173); return;}
if(substrSpecific == "`") {symbolDraw(174); return;}
if(substrSpecific == "№") {symbolDraw(175); return;} //№
if(substrSpecific == "^") {symbolDraw(176); return;}
if(substrSpecific == "$") {symbolDraw(177); return;}
if(substrSpecific == "~") {symbolDraw(178); return;}

return;
                    }
//////////////////////////////////////////////////////////////////////////////////////////////////////////

//#include <Arduino.h>
#include <ESP_I2S.h>

#define I2S_BCLK 9
#define I2S_LRC  3
#define I2S_DOUT 8
int station = 0; //int activeStation;

//const char* radio_url = "http://listen.radio.tomsk.ru:8000/jazz";
//http://sknt.ru
//http://stream.live.vc.bbcmedia.co.uk/bbc_radio_one
//http://microit.n340.com:9000/VgMv0WV17ZVx1uuo_20_sport_128_reg_1
  //audio.connecttohost("0n-80s.radionetz.de:8000/0n-70s.mp3");
  //audio.connecttohost("http://ice1.somafm.com/gsclassic-128-mp3"); 
  //audio.connecttohost("http://radiorecord.hostingradio.ru/symph96.aacp");
  //audio.connecttohost("http://pub0301.101.ru:8443/stream/air/mp3/256/100");

void INT_RADIO() { 
  //if(f == 2) {goto from_edit;}
  int vol = 17; //0-21
  double timeVol;
  timeVol = millis();
strip.setBrightness(100);
colorWipe(strip.Color(0,  0,  0), 0); //MODULE
strip.setPixelColor(0, strip.Color(255,  0,  0)); //PIXEL 1 LEFT-BOTTOM
strip.setPixelColor(1, strip.Color(255,  0,  0)); //PIXEL 2 LEFT-TOP
strip.setPixelColor(2, strip.Color(255,  0,  0)); //PIXEL 3 RIGHT-TOP
strip.setPixelColor(3, strip.Color(255,  0,  0)); //PIXEL 4 RIGHT-BOTTOM
                                                  strip.show();
  tft.fillScreen(BackColor); 

  Audio audio;
  delay(100);
  audio.setPinout(I2S_BCLK, I2S_LRC, I2S_DOUT);
  audio.setVolume(vol);


        String stringSSID = EEPROM.readString(400);
        String stringPASS = EEPROM.readString(450); 
        String stringStation; //
        // if(station == 0) {stringStation = EEPROM.readString(500);}
        // if(station == 1) {stringStation = EEPROM.readString(600);}
        // if(station == 2) {stringStation = EEPROM.readString(700);}
        // if(station == 3) {stringStation = EEPROM.readString(800);}
        charColo = color565(255,255,255);         
        startX = 2; startY = 2;  MyText = "Connecting to WiFi"; event(); 
        //startX = 2; startY = 32; MyText = stringSSID; event();  

const char* ssid =      stringSSID.c_str();//"";
const char* password =  stringPASS.c_str();//""; 
const char* radio_url;// = stringStation.c_str();//"";
/////////////////////////////////////////////////
if (WiFi.status() != WL_CONNECTED) {WiFi.begin(ssid, password);}
  int dots = 0; startX = 2; startY = 32;
  while (WiFi.status() != WL_CONNECTED) {
      delay(2000);
      if(dots < 7) {MyText =  "."; event();} dots++; if(dots > 4) {break;}
                                        }
                                        //startY = 32;
   if(WiFi.status() == WL_CONNECTED) {   
  MyText = "OK!"; event();
  startX = 2; startY = 62;
  MyText = WiFi.localIP().toString(); event();
  //tft.drawBitmap(214, 0,  NET_PIC, 25, 21, WHITE);
                                     } else {
                                             MyText = "ERROR"; event(); WiFi.disconnect();
                                              while(numButton1 != 13 && numButton0 != 5) {  PressedButton(1); PressedButton(2);
                                              if(digitalRead(0) == 0 && (millis() - timeColorT) > 200) {CHANGE_COLOR_TOP();}
                                              if(numButton1 == 15 && (millis() - timeLayout) > 200) {LAYOUT_IND();}
                                              } goto EXI;
                                            }
/////////////////////////////////////////////////  

        //tft.fillScreen(BackColor); 
from_edit:
  //activeStation = station;
  charColo = BackColor;     
  tft.fillRoundRect(5,122,   50,50,10,TFT_WHITE);
  startX = 7; startY = 124;  MyText = "1"; event();
    tft.drawRoundRect(0+(station*60),117,   60,60,12,color565(255,0,0));
    tft.drawRoundRect(1+(station*60),118,   58,58,12,color565(255,0,0)); 
    tft.drawRoundRect(2+(station*60),119,   56,56,12,color565(255,0,0)); 
  tft.fillRoundRect(65,122,  50,50,10,TFT_WHITE);
  startX = 67; startY = 124;  MyText = "2"; event();
  tft.fillRoundRect(125,122, 50,50,10,TFT_WHITE);
  startX = 127; startY = 124;  MyText = "3"; event();
  tft.fillRoundRect(185,122, 50,50,10,TFT_WHITE);
  startX = 187; startY = 124;  MyText = "4"; event();

  startX = 21; startY = 179;  MyText = "Ex = ред. адрес"; charColo = color565(85,85,185); event();
  startX = 21; startY = 201;  MyText = "Откл. зарядное!"; charColo = color565(85,85,185); event();
  

  tft.drawWideLine(21+(station*60),104, 30+(station*60), 111, 2,color565(255,255,255)); //V
  tft.drawWideLine(30+(station*60), 111,39+(station*60), 104, 2,color565(255,255,255));
///////////////////////////////////////////////////////////////////////////////////////

for(int a=0; a<22; a++ ) {
tft.drawFastHLine(0,317-a*4, 240, tft.color888(155, 155, 155));
                         } 
tft.fillRect( 0,318-4*vol,240,2,tft.color888(255, 0, 0)); //BAR VOLUME

        if(station == 0) {stringStation = EEPROM.readString(500);}
        if(station == 1) {stringStation = EEPROM.readString(600);}
        if(station == 2) {stringStation = EEPROM.readString(700);}
        if(station == 3) {stringStation = EEPROM.readString(800);}
        radio_url = stringStation.c_str();
  audio.connecttohost(radio_url); 
//////////////////////////////////////////////////////////////////////////////////// 
////////////////////////////////////////////////////////////////////////////////////
while(numButton1 != 13 && numButton0 != 5) {  PressedButton(1); PressedButton(2); //
  if(numButton0 == 2 && (millis() - timeVol) > 100) { vol++; if(vol > 21) {vol = 21;} audio.setVolume(vol); timeVol = millis(); 
                                                      tft.fillRect( 0,318-4*(vol-1),240,2,BackColor);
                                                      tft.fillRect( 0,318-4*vol,240,2,tft.color888(255, 0, 0));
   }
  if(numButton0 == 1 && (millis() - timeVol) > 100) { vol--; if(vol < 0)  {vol = 0;}  audio.setVolume(vol); timeVol = millis(); 
                                                      tft.fillRect( 0,318-4*(vol+1),240,2,BackColor);
                                                      tft.fillRect( 0,318-4*vol,240,2,tft.color888(255, 0, 0));
   }
audio.loop();

if(numButton0 == 3 && (millis() - timeVol) > 150) {
  tft.fillRect( 17+(station*60),100,27,16,BackColor);
   station++ ; if(station > 3) {station = 3;}
  tft.drawWideLine(21+(station*60),104, 30+(station*60), 111, 2,color565(255,255,255)); //V
  tft.drawWideLine(30+(station*60), 111,39+(station*60), 104, 2,color565(255,255,255)); timeVol = millis();
}
if(numButton0 == 4 && (millis() - timeVol) > 150) {
  tft.fillRect( 17+(station*60),100,27,16,BackColor);
   station-- ; if(station < 0) {station = 0;}
  tft.drawWideLine(21+(station*60),104, 30+(station*60), 111, 2,color565(255,255,255)); //V
  tft.drawWideLine(30+(station*60), 111,39+(station*60), 104, 2,color565(255,255,255)); timeVol = millis();
}
if(numButton0 == 6 && (millis() - timeVol) > 300) { // IF ENTER
    tft.drawRoundRect(0+(0*60),117,   60,60,12,BackColor);
    tft.drawRoundRect(1+(0*60),118,   58,58,12,BackColor); 
    tft.drawRoundRect(2+(0*60),119,   56,56,12,BackColor);
    tft.drawRoundRect(0+(1*60),117,   60,60,12,BackColor);
    tft.drawRoundRect(1+(1*60),118,   58,58,12,BackColor); 
    tft.drawRoundRect(2+(1*60),119,   56,56,12,BackColor);
    tft.drawRoundRect(0+(2*60),117,   60,60,12,BackColor);
    tft.drawRoundRect(1+(2*60),118,   58,58,12,BackColor); 
    tft.drawRoundRect(2+(2*60),119,   56,56,12,BackColor);
    tft.drawRoundRect(0+(3*60),117,   60,60,12,BackColor);
    tft.drawRoundRect(1+(3*60),118,   58,58,12,BackColor); 
    tft.drawRoundRect(2+(3*60),119,   56,56,12,BackColor);

    tft.drawRoundRect(0+(station*60),117,   60,60,12,color565(255,0,0)); //activeStation = station;
    tft.drawRoundRect(1+(station*60),118,   58,58,12,color565(255,0,0)); 
    tft.drawRoundRect(2+(station*60),119,   56,56,12,color565(255,0,0));
        if(station == 0) {stringStation = EEPROM.readString(500);}
        if(station == 1) {stringStation = EEPROM.readString(600);}
        if(station == 2) {stringStation = EEPROM.readString(700);}
        if(station == 3) {stringStation = EEPROM.readString(800);}
        radio_url = stringStation.c_str();
    audio.connecttohost(radio_url); PressedButton(1); PressedButton(2);
      timeVol = millis();
}

if(digitalRead(47) == 1 && (millis() - timeColorT) > 200) {STATION_EDIT(station); delay(300); PressedButton(1); PressedButton(2); goto from_edit;} //EX

if(digitalRead(0) == 0 && (millis() - timeColorT) > 200) {CHANGE_COLOR_TOP();}
if(numButton1 == 15 && (millis() - timeLayout) > 200)    {LAYOUT_IND();}
if(numButton3 == 12 && (millis() - timeColor) > 200)     {CHANGE_COLOR_MODULE();}
}
  //tft.fillScreen(BackColor);
  WiFi.disconnect(); 
  //if(WiFi.status() != WL_CONNECTED) {MyText = "disconnect OK"; scaleX = 1; scaleY = 1; startX = 32; startY = 105; event();}
  //else {MyText = "ERROR"; scaleX = 1; scaleY = 1; startX = 82; startY = 105; event();}
  EXI:
colorWipe(strip.Color(0,  0,  0), 0); //MODULE 

}
/////////////////////////////////////////////////////////////////////////////////
// Обязательные колбэки для вывода информации
void audio_showstation(const char *info){
    //Serial.print("Станция: "); Serial.println(info);
}
void audio_showstreamtitle(const char *info){
    //Serial.print("Трек: "); Serial.println(info);
}
// Дополнительный колбэк для отладки ошибок сети
void audio_error(const char *info){
    //Serial.print("Ошибка аудио: "); Serial.println(info);
}
////////////////////////////////////



// void INT_RADIO() {
// strip.setBrightness(100);
// colorWipe(strip.Color(0,  0,  0), 0); //MODULE
// strip.setPixelColor(0, strip.Color(255,  0,255)); //PIXEL 1 LEFT-BOTTOM
// strip.setPixelColor(1, strip.Color(255,  0,255)); //PIXEL 2 LEFT-TOP
// strip.setPixelColor(2, strip.Color(255,  0,255)); //PIXEL 3 RIGHT-TOP
// strip.setPixelColor(3, strip.Color(255,  0,255)); //PIXEL 4 RIGHT-BOTTOM
//                                                   strip.show();
// //Перед прошивкой обязательно установите библиотеку ESP32-audioI2S
// // #include "Arduino.h"
// // #include "WiFi.h"
// // #include "Audio.h"

// // Настройки Wi-Fi
// //const char* ssid     = "";
// //const char* password = "";

// // Пины для подключения MAX98357A к ESP32-S3
// #define I2S_LRC       37
// #define I2S_BCLK      36
// #define I2S_DOUT      35

// Audio audio;

// //void setup() {
//     //Serial.begin(115200);
    
//     // Подключение к Wi-Fi
//     WiFi.disconnect();
//     WiFi.mode(WIFI_STA);
//     WiFi.begin(ssid, password);
    
//     //Serial.print("Connecting to WiFi");
//     while (WiFi.status() != WL_CONNECTED) {
//         delay(500);
//         //Serial.print(".");
//     }
//     //Serial.println("\nConnected to WiFi network!");

//     // Настройка I2S интерфейса для аудио
//     audio.setPinout(I2S_BCLK, I2S_LRC, I2S_DOUT);
    
//     // Установка громкости (от 0 до 21)
//     audio.setVolume(7); 

//     // Ссылка на MP3/AAC поток радиостанции (пример: )
//     audio.connecttohost("http://ice1.somafm.com/gsclassic-128-mp3");
// //}

// while(true) { //void loop() {
//     // Поддержание работы аудио-потока (обязательно вызывать без задержек delay)
//     audio.loop();
// }
// colorWipe(strip.Color(0,  0,  0), 0); //MODULE  
// //EXIT
// }
// // Необязательные функции для вывода информации о треке в консоль
// //void audio_showstation(const char *info){
//     //Serial.print("Station: "); Serial.println(info);
// //}
// //void audio_showstreamtitle(const char *info){
//     //Serial.print("Now Playing: "); Serial.println(info);
// //}
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

void VISUAL() {
strip1.setBrightness(255);
double timVisual;
 int rndR; int rndG; int rndB; 
 int colorR = 128; 
 int colorG = 188; 
 int colorB = 128; 
 int x; int y;
 rndR = random(3); if(rndR == 0) {colorR = x+7;} if(rndR == 1) {colorR = (x+y)/9;} if(rndR == 2) {colorR = 255-(y+7)/1.38;}
 rndG = random(3); if(rndG == 0) {colorG = x+7;} if(rndG == 1) {colorG = (x+y)/9;} if(rndG == 2) {colorG = 255-(y+7)/1.38;}
 rndB = random(3); if(rndB == 0) {colorB = x+7;} if(rndB == 1) {colorB = (x+y)/9;} if(rndB == 2) {colorB = 255-(y+7)/1.38;}

  tft.startWrite();
  tft.setAddrWindow(0, 0, 240, 320); 
  for (int y = 0; y < 320; ++y) {
    for (int x = 0; x < 240; ++x) {
      tft.writeColor(tft.color888(x+7,(x+y)/9,255-(y+7)/1.38), 1);
    }
  }
  tft.endWrite();

 while(true) { 
  // Цикл смещения цвета для создания эффекта движения
  for (long firstPixelHue = 0; firstPixelHue < 5 * 65536; firstPixelHue += 256) { 
   //waitQ:
   PressedButton(1); PressedButton(2); if(numButton1 == 13 || numButton0 == 5) {goto back;}
    //if(millis() - timVisual < 10) {goto waitQ;} 
///////////////////////////////////////////////DISPLAY///////////////////////////////////////////////
  more:







  if((millis() - timVisual) > 9) {goto later;} else {goto more;} // Скорость движения (меньше — быстрее)    
  later:  
/////////////////////////////////////////////////////////////////////////////////////////////////////
    timVisual = millis(); 
    for (int i = 0; i < strip1.numPixels(); i++) {
      // Вычисляем цвет для каждого пикселя
      int pixelHue = firstPixelHue + (i * 65536 / strip1.numPixels());
      strip1.setPixelColor(i, strip1.gamma32(strip1.ColorHSV(pixelHue)));
    }
    strip1.show();                     
  }
  }
  back:
}

//void DISP_VISUAL() {
// int rndR; int rndG; int rndB; int colorR; int colorG; int colorB; int x; int y;
//  rndR = random(2); //if(rndR == 0) {colorR = x;} if(rndR == 1) {colorR = y/1.26;}
//  rndG = random(2); //if(rndG == 0) {colorG = x;} if(rndG == 1) {colorG = y/1.26;}
//  rndB = random(2); //if(rndB == 0) {colorB = x;} if(rndB == 1) {colorB = y/1.26;}
//   tft.startWrite();
//   tft.setAddrWindow(0, 0, 240, 320);
//   for (y = 0; y < 320; y++) {for (x = 0; x < 240; x++) {
//  if(rndR == 0) {colorR = x;} if(rndR == 1) {colorR = y/1.26;}
//  if(rndG == 0) {colorG = x;} if(rndG == 1) {colorG = y/1.26;}
//  if(rndB == 0) {colorB = x;} if(rndB == 1) {colorB = y/1.26;}
//   tft.writeColor(tft.color888(colorR, colorG, colorB), 1);}}
//   tft.endWrite();
//}
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
#include "FS.h"
#include "SD.h"
//#include "SPI.h"

// Пины подключения для ESP32-S3
#define SDSPI_MOSI 5
#define SDSPI_MISO 6
#define SDSPI_CLK  4
#define SDSPI_CS   7

SPIClass sdSPI(HSPI); 

// Функция для чтения и вывода структуры файлов и папок
// void listDir(fs::FS &fs, const char * dirname, uint8_t levels) {
//   Serial.printf("Каталог: %s\n", dirname);

//   File root = fs.open(dirname);
//   if (!root) {
//     Serial.println("Не удалось открыть каталог");
//     return;
//   }
//   if (!root.isDirectory()) {
//     Serial.println("Это не каталог");
//     return;
//   }

//   File file = root.openNextFile();
//   while (file) {
//     if (file.isDirectory()) {
//       Serial.print("  [ПАПКА] ");
//       Serial.println(file.name());
//       // Если заданы уровни вложенности, заходим внутрь папки
//       if (levels) {
//         listDir(fs, file.path(), levels - 1);
//       }
//     } else {
//       Serial.print("  [ФАЙЛ]  ");
//       Serial.print(file.name());
//       Serial.print("\tРазмер: ");
//       Serial.print(file.size()); // Исправлено на .print()
//       Serial.println(" байт");
//     }
//     file = root.openNextFile();
//   }
// }

void MICRO_SD() {
 uint16_t wallcol = color565(0,55,115); tft.fillScreen(wallcol);
 uint64_t totalBytes;
 uint64_t usedBytes;
  startX = 2;  startY = 2; scaleX = 1; scaleY = 1; charColo = color565(255,255,255); MyText = "Инициализация:::"; event();
  sdSPI.begin(SDSPI_CLK, SDSPI_MISO, SDSPI_MOSI, SDSPI_CS);

  if (!SD.begin(SDSPI_CS, sdSPI)) {
    startX = 2;  startY = 22; charColo = color565(255,255,255); MyText = "microSD не найдена"; event();
    goto fromError; 
  }
  // Выводим общую информацию о карте
  totalBytes = SD.totalBytes();
  usedBytes = SD.usedBytes();

  //startX = 2;  startY = 42; charColo = color565(255,255,255); MyText = "Информация:"; event();
  startX = 2;  startY = 62; charColo = color565(255,255,255); MyText = "Всего:"; event();
       startX = 40;  startY = 82; charColo = color565(255,255,255); MyText = String(totalBytes / (1024*1024)) + " МБ"; event();
  startX = 2;  startY = 102; charColo = color565(255,255,255); MyText = "Занято:"; event();
       startX = 40;  startY = 122; charColo = color565(255,255,255); MyText = String(usedBytes / (1024*1024)) + " МБ"; event();
  startX = 2;  startY = 142; charColo = color565(255,255,255); MyText = "Свободно:"; event();
       startX = 40;  startY = 162; charColo = color565(255,255,255); MyText = String((totalBytes - usedBytes) / (1024*1024)) + " МБ"; event();

  // Вызываем функцию чтения содержимого корневого каталога "/"
  // Цифра 2 означает глубину поиска во вложенных папках
  //Serial.println("=== Список файлов и папок ===");
  //listDir(SD, "/", 2);
 fromError:
while(numButton1 != 13 && numButton0 != 5) { PressedButton(1); PressedButton(2); }

SD.end();
// 2. Отключаем аппаратную шину SPI
sdSPI.end();
// 3. Переводим пины в безопасное нейтральное состояние
pinMode(SDSPI_CLK, OUTPUT);
digitalWrite(SDSPI_CLK, 0);
pinMode(SDSPI_MISO, OUTPUT);
digitalWrite(SDSPI_MISO, 0);
pinMode(SDSPI_MOSI, OUTPUT);
digitalWrite(SDSPI_MOSI, 0);
pinMode(SDSPI_CS, OUTPUT);
digitalWrite(SDSPI_CS, 0);
} 


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




void GAME() { 
 double timD; int r = 50; //TOP START DOTS Y 
 int b = 320; //BOTTOM DOTS Y 
 uint16_t BCol = color565(255,255,255);
 uint16_t LCol = color565(155,155,255);
 uint16_t ro = color565(255,147,  0); //ORANGE
 double timPos; 
 double step = 1.1;
 double timLL; int timLR = 2;
 double ylef = 55; double yrig = 55; double ycen = 55; //start L
 int limL = 320; int limC = 320; int limR = 320;
 int curPos = 2; 
 int posL, posR, posC;
 tft.fillScreen(BCol);
 tft.pushImage(0, 0, 240, 51, sky);
 tft.fillTriangle(130, 50, 240, 50, 240, 190, color565(30,79,134));
 tft.fillTriangle(110, 50, 0, 50, 0, 190, color565(34,52,84));
 tft.pushImage(42, 190, im_width_cen, im_height_cen, car_image_center);

while(analogRead(12) < 2000) {

     if((millis() - timD) > 20) { timD = millis(); //timLL += 20; if(timLL > 3400) {timLL = 0; } 

 if(timLR == 1) {posL=1;
   if(curPos == 1) {limL = 186;} else {limL = 320;} //без наложения
           tft.fillRect(135-(ylef/2.05),ylef, 2+ylef/8,1+ylef/20,BCol);
           ylef = (ylef+0)*1.03; if(ylef > limL) {ylef = 55; posL=0; timLR = random(1, 4); goto pr;}
           tft.fillRect(135-(ylef/2.05),ylef, 2+ylef/8,1+ylef/20,LCol); pr: }
 if(timLR == 3) {posR=1;
   if(curPos == 3) {limR = 186;} else {limR = 320;} //без наложения
           tft.fillRect(105+(yrig/2.55),yrig, 2+yrig/8,1+yrig/20,BCol);
           yrig = (yrig+0)*1.03; if(yrig > limR) {yrig = 55; posR=0; timLR = random(1, 4); goto prq;}
           tft.fillRect(105+(yrig/2.55),yrig, 2+yrig/8,1+yrig/20,LCol); prq:}
 if(timLR == 2) {posC=1;   
   if(curPos == 2) {limC = 180;} else {limC = 320;} //без наложения
           tft.fillRect(117-(ycen/60),ycen, 2+ycen/8,1+ycen/20,BCol);
           ycen = (ycen+0)*1.03; if(ycen > limC) {ycen = 55; posC=0; timLR = random(1, 4); goto prqw;}
           tft.fillRect(117-(ycen/60),ycen, 2+ycen/8,1+ycen/20,LCol); prqw:}


           for (int l=r; l < b; l= (l+1)*step) {
                                                 if(curPos == 1 && l > 186) {goto q;}
                                                 tft.fillRect(145-(l/1.5),l+0, 2+l/90,1+l/50,BCol); q:
                                                 if(curPos == 3 && l > 186) {goto qw;}
                                                 tft.fillRect(95+(l/1.5),l+0, 2+l/90,1+l/50,BCol); qw: //DOTS   
                                                 if(curPos == 2 && l > 186) {continue;}
                                                 tft.fillRect(130-(l/4),l+0, 2+l/90,1+l/50,BCol); 
                                                 tft.fillRect(110+(l/4),l+0, 2+l/90,1+l/50,BCol);}                                                 
                                                 r += 1; if(r > 60) {r = 50;}
           for (int l=r; l < b; l= (l+1)*step) {
                                                 if(curPos == 1 && l > 186) {goto a;}
                                                 tft.fillRect(145-(l/1.5),l+0, 2+l/90,1+l/50,ro); a: 
                                                 if(curPos == 3 && l > 186) {goto aw;}
                                                 tft.fillRect(95+(l/1.5),l+0, 2+l/90,1+l/50,ro); aw: 
                                                 if(curPos == 2 && l > 186) {continue;}
                                                 tft.fillRect(130-(l/4),l+0, 2+l/90,1+l/50,ro); 
                                                 tft.fillRect(110+(l/4),l+0, 2+l/90,1+l/50,ro);}
     }
  if(millis() - timPos > 150) {
     if(analogRead(13) > 500 && curPos == 2) { //TO RIGHT
      tft.fillRect(0,190, 70,130,TFT_WHITE); //LEFT
      tft.fillRect(42,190, 156,130,TFT_WHITE); //CENTER
      tft.pushImage(170, 190, im_width, im_height, car_image_right); curPos = 3;}
    if(analogRead(2) > 500 && curPos == 2) { //TO LEFT
      tft.fillRect(170,190, 70,130,TFT_WHITE); //RIGHT
      tft.fillRect(42,190, 156,130,TFT_WHITE); //CENTER
      tft.pushImage(0, 190, im_width, im_height, car_image_left); curPos = 1;}
    if((analogRead(13) > 500 && curPos == 1) || (analogRead(2) > 500 && curPos == 3)) { //TO CENTER
      tft.fillRect(0,190, 70,130,TFT_WHITE); //LEFT
      tft.fillRect(170,190, 70,130,TFT_WHITE); //RIGHT
      tft.pushImage(42, 190, im_width_cen, im_height_cen, car_image_center); curPos = 2;}
      timPos = millis();
  }
 }
 }












 


                   

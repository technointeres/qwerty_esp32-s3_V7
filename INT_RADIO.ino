
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

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





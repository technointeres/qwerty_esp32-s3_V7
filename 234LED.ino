
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


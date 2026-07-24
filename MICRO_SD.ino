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





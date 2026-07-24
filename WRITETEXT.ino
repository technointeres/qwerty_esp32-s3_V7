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

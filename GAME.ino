     
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


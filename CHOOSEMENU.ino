




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
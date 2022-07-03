boolean loadingFlag = true;
int effectsc = 50;
int effectsp = 1;

void effect_tick() {
  if (brightnessls != 0 && !sunlightfl && (millis() - timer > 50 || (currentMode>=2 && currentMode<=5))) {
    timer = millis();
    switch (currentMode) {
      case 0:
        break;
//      case 1: rainbow();
//        break;
      case 2: lightmusic(0);
        break;
      case 3: lightmusic(1);
        break;
      case 4: lightmusic(2);
        break;
      case 5: lightmusic(3);
        break;
      case 6: solid();
        break;
      //              case 4: romantic();
      //        break;
//      case 7: rnd();
//        break;
    }
    //lightmusic(2);
    //    FastLED.show();
  } else if (brightnessls == 0) FastLED.setBrightness(0);
}

void solid() {
  for (int i = 0; i < 30; i++) {
    leds[i] = CRGB(r, g, b);
  }
  //    fill_solid(leds, brightnessls, CRGB(r, g, b));
}


void rainbow() {
  for (int i = 0; i < 5; i++ ) {         // от 0 до первой трети
    for (int j = 0; j < 6; j++ ) {
      leds[6 * i + j] = CHSV(counter + i * 15, 255, 255); // HSV. Увеличивать HUE (цвет)
      // умножение i уменьшает шаг радуги
    }
  }
  //  for (int i = 0; i < 30; i++ ) {         // от 0 до первой трети
  //    leds[i] = CHSV(counter + i * 15, 255, 255); // HSV. Увеличивать HUE (цвет)
  //    // умножение i уменьшает шаг радуги
  //  }
  counter += effectsp;
  if (counter > 255) counter = 0;
}


//#define SPARKLES 1        // вылетающие угольки вкл выкл
//unsigned char line[5];
//int pcnt = 0;
//
////these values are substracetd from the generated values to give a shape to the animation
//const unsigned char valueMask[8][16] PROGMEM = {
//  {0    , 2    , 0    , 0    , 2},
//  {7    , 5    , 9    , 0    , 5},
//  {42   , 23   , 45   , 26   , 50},
//  {90   , 60   , 100  , 50   , 100},
//  {130  , 170  , 160  , 200  , 180},
//  {230  , 255  , 200  , 245  , 255}
//};
//
////these are the hues for the fire,
////should be between 0 (red) to about 25 (yellow)
//const unsigned char hueMask[8][16] PROGMEM = {
//  {20 , 11, 25, 12, 25},
//  {14 , 8 , 19, 7, 19},
//  {10 , 5 , 13, 5, 13},
//  {7 , 5 , 11, 4, 11},
//  {4 , 1 , 5 , 3 , 8},
//  {2 , 0 , 1 , 2 , 5},
//  {0 , 0 , 0 , 1 , 1}
//};



void fire() {
  //
  //  if (loadingFlag) {
  //    loadingFlag = false;
  //    generateLine();
  //  }
  //  if (pcnt >= 100) {
  //    shiftUp();
  //    generateLine();
  //    pcnt = 0;
  //  }
  //  drawFrame(pcnt);
  //  pcnt += 30;
  //}
  //
  //// Randomly generate the next line (matrix row)
  //
  //void generateLine() {
  //  for (uint8_t x = 0; x < 5; x++) {
  //    line[x] = random(64, 255);
  //  }
  //}
  //
  //void shiftUp() {
  //  for (uint8_t y = 5; y > 0; y--) {
  //    for (uint8_t x = 0; x < 5; x++) {
  //      uint8_t newX = x;
  //      if (x > 6) newX = x - 6;
  //      if (y > 5) continue;
  //      matrixValue[y][newX] = matrixValue[y - 1][newX];
  //    }
  //  }
  //
  //  for (uint8_t x = 0; x < 5; x++) {
  //    uint8_t newX = x;
  //    if (x > 6) newX = x - 6;
  //    matrixValue[0][newX] = line[newX];
  //  }
  //}
  //
  //// draw a frame, interpolating between 2 "key frames"
  //// @param pcnt percentage of interpolation
  //
  //void drawFrame(int pcnt) {
  //  int nextv;
  //
  //  //each row interpolates with the one before it
  //  for (unsigned char y = 5; y > 0; y--) {
  //    for (unsigned char x = 0; x < 5; x++) {
  //      uint8_t newX = x;
  //      if (x > 6) newX = x - 6;
  //      if (y < 5) {
  //        nextv = (((100.0 - pcnt) * matrixValue[y][newX] + pcnt * matrixValue[y - 1][newX]) / 100.0) - pgm_read_byte(&(valueMask[y][newX]));
  //
  //        CRGB color = CHSV(
  //                       pgm_read_byte(&(hueMask[y][newX])), // H
  //                       255, // S
  //                       (uint8_t)max(0, nextv) // V
  //                     );
  //
  //        leds[getPixelNumber(x, y)] = color;
  //      } else if (y == 5 && SPARKLES) {
  //        if (random(0, 20) == 0 && getPixColorXY(x, y - 1) != 0) drawPixelXY(x, y, getPixColorXY(x, y - 1));
  //        else drawPixelXY(x, y, 0);
  //      } else if (SPARKLES) {
  //
  //        // старая версия для яркости
  //        if (getPixColorXY(x, y - 1) > 0)
  //          drawPixelXY(x, y, getPixColorXY(x, y - 1));
  //        else drawPixelXY(x, y, 0);
  //
  //      }
  //    }
  //  }
  //
  //  //first row interpolates with the "next" line
  //  for (unsigned char x = 0; x < 5; x++) {
  //    uint8_t newX = x;
  //    if (x > 6) newX = x - 6;
  //    CRGB color = CHSV(
  //                   pgm_read_byte(&(hueMask[0][newX])), // H
  //                   255,           // S
  //                   (uint8_t)(((100.0 - pcnt) * matrixValue[0][newX] + pcnt * line[newX]) / 100.0) // V
  //                 );
  //    leds[getPixelNumber(newX, 0)] = color;
  //  }
}
//
//
//void romantic() {
//
//  if (counter > 100) {
//    fl = true;
//    counter = 99;
//  }
//  if (counter < 1) {
//    fl = false;
//    counter = 1;
//  }
//  if (millis() - timer > 100) {
//    timer = millis();
//    for (int i = 0; i < 5; i++ ) {         // от 0 до первой трети
//      for (int j = 0; j < 6; j++ ) {
//
//        leds[6 * i + j] = CHSV(700 - counter - i * 2, 255, 255); // HSV. Увеличивать HUE (цвет)
//        // умножение i уменьшает шаг радуги
//      }
//    }
//    if (fl) {
//      counter -= 10;
//    } else {
//      counter += 10;
//    }
//
//  }
//}
//
//
void rnd() {
  leds[random(29)] = CRGB(random(255), random(255), random(255));
}

byte minv = 255;
byte maxv = 0;
byte minv2 = 0;
byte maxv2 = 0;
byte count = 0;
byte countcolor = 0;
int value = 0;
int value2 = 0;
int percentvalue = 0;

void lightmusic(int modem) {
  if (volume == 0) currentMode++; else {
    if (millis() % 20 == 0) {
      value2 = analogRead(A0);
      if (abs(value - value2) > 1)
        value = value2;
      if (minv > value) {
        minv = value;
      }
      if (maxv < value) {
        maxv = (minv == value) ? value + 1 : value;
      }

      if (minv2 > value) {
        minv2 = value;
      }
      if (maxv2 < value) {
        maxv2 = (minv2 == value) ? value + 1 : value;
      }
      count++;
      countcolor++;
      if (count > 25) {
        count = 0;
        maxv = maxv2;
        minv = minv2;
        maxv2 = 0;
        minv2 = 255;
      }

      percentvalue = (((value - minv) * 2 * brightnessls) / (maxv - minv) + percentvalue) / 3;
      //      Serial.println(percentvalue);
      switch (modem) {
        case 0:
          for (int i = 0; i < 30; i++) {
            leds[i] = CRGB(r, g, b);
            FastLED.setBrightness(percentvalue);
          }
          break;
        case 1:
          for (int i = 0; i < 30; i++) {
            leds[i] = CHSV(percentvalue * 400/brightnessls, 255, 150);
            FastLED.setBrightness(percentvalue);
          }
          break;
        case 2:
          for (int j = 0; j < 5; j++)
            for (int i = 0; i < 6; i++) {
              leds[j * 6 + i] = CHSV(100 - j * 20, 255, percentvalue > j * (brightnessls / 5) || j == 0 ? 100 : 0);
              FastLED.setBrightness(brightnessls);
            }
          break;
        case 3:
          for (int i = 0; i < 30; i++) {
            leds[i] = CHSV(countcolor * 2, 255, 100);
            FastLED.setBrightness(percentvalue);
          }
          break;
      }
      FastLED.show();
    }
  }
}

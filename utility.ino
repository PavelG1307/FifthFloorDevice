////// служебные функции






////
////// залить все
////void fillAll(CRGB color) {
////  for (int i = 0; i < NUM_LEDS; i++) {
////    leds[i] = color;
////  }
////}
////
////// функция отрисовки точки по координатам X Y
//void drawPixelXY(int8_t x, int8_t y, CRGB color) {
//  if (x < 0 || x > 4 || y < 0 || y > 5) return;
//  int thisPixel = getPixelNumber(x, y) * 1;
//  for (byte i = 0; i < 1; i++) {
//    leds[thisPixel + i] = color;
//  }
//}
////
////// функция получения цвета пикселя по его номеру
//uint32_t getPixColor(int thisSegm) {
//  int thisPixel = thisSegm;
//  if (thisPixel < 0 || thisPixel > NUM_LEDS - 1) return 0;
//  return (((uint32_t)leds[thisPixel].r << 16) | ((long)leds[thisPixel].g << 8 ) | (long)leds[thisPixel].b);
//}
////
////// функция получения цвета пикселя в матрице по его координатам
//uint32_t getPixColorXY(int8_t x, int8_t y) {
//  return getPixColor(getPixelNumber(x, y));
//}
////
////// **************** НАСТРОЙКА МАТРИЦЫ ****************
////#if (CONNECTION_ANGLE == 0 && STRIP_DIRECTION == 0)
////#define _WIDTH WIDTH
////#define THIS_X x
////#define THIS_Y y
////
////#elif (CONNECTION_ANGLE == 0 && STRIP_DIRECTION == 1)
////#define _WIDTH HEIGHT
////#define THIS_X y
////#define THIS_Y x
////
////#elif (CONNECTION_ANGLE == 1 && STRIP_DIRECTION == 0)
////#define _WIDTH WIDTH
////#define THIS_X x
////#define THIS_Y (HEIGHT - y - 1)
////
////#elif (CONNECTION_ANGLE == 1 && STRIP_DIRECTION == 3)
////#define _WIDTH HEIGHT
////#define THIS_X (HEIGHT - y - 1)
////#define THIS_Y x
////
////#elif (CONNECTION_ANGLE == 2 && STRIP_DIRECTION == 2)
////#define _WIDTH WIDTH
////#define THIS_X (WIDTH - x - 1)
////#define THIS_Y (HEIGHT - y - 1)
////
////#elif (CONNECTION_ANGLE == 2 && STRIP_DIRECTION == 3)
////#define _WIDTH HEIGHT
////#define THIS_X (HEIGHT - y - 1)
////#define THIS_Y (WIDTH - x - 1)
////
////#elif (CONNECTION_ANGLE == 3 && STRIP_DIRECTION == 2)
////#define _WIDTH WIDTH
////#define THIS_X (WIDTH - x - 1)
////#define THIS_Y y
////
////#elif (CONNECTION_ANGLE == 3 && STRIP_DIRECTION == 1)
////#define _WIDTH HEIGHT
////#define THIS_X y
////#define THIS_Y (WIDTH - x - 1)
////
////#else
////#define _WIDTH WIDTH
////#define THIS_X x
////#define THIS_Y y
////#pragma message "Wrong matrix parameters! Set to default"
////
////#endif
////
////// получить номер пикселя в ленте по координатам
//uint16_t getPixelNumber(int8_t x, int8_t y) {
//  if ((y % 2 == 0)) {               // если чётная строка
//    return (y * 5 + x);
//  } else {                                              // если нечётная строка
//    return (y * 5 + 6 - x - 1);
//  }
//}
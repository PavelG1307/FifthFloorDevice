int timer3 = 0;
int timer4 = 0;
int alm;
CHSV dawnColor;
boolean sunlightfl = false;
boolean manualoffring = false;

void ring_ticker() {
  if ((millis() % 1000)) {
    for (int i = 0; i < 5; i++) {
      if (alarm[i].time*60 - timevalue < DAWNTIME*60 && alarm[i].time*60 - timevalue > 0 && alarm[i].act && alarm[i].sinerise && !sunlightfl) {
        sunlightfl = true;
        manualoffring = false;
        Serial.println("Dawn true!");
        alm = i;
      }
      if (alarm[i].time == (int) timevalue/60 && alarm[i].act) {
        ringstart(i);
      }
    }
  }
  if (sunlightfl && !manualoffring && (millis() % 1000)) {
    if (abs(timevalue - alarm[alm].time*60) < DAWNTIME*60) {
      sunlight();
      fill_solid(leds, NUM_LEDS, dawnColor);
      //      fillString(timeStr, CRGB::Black, false);
      delay(1);
      ESP.wdtFeed();   // пнуть собаку
      yield();  // ещё раз пнуть собаку
      FastLED.show();
    } else {
      sunlightfl = false;
      brightnessls = 0;
      FastLED.setBrightness(brightnessls);
      FastLED.show();
    }
  }

}


void ringstart(int i) {
  Serial.println("Ring!");
  Serial.println("Ring!");
  Serial.println("Ring!");
  Serial.println("Ring!");
  alarm[i].act = false;
}



void sunlight() {

  //  Serial.println("SUN");
  if (!manualoffring) {
    // величина рассвета 0-255
    int dawnPosition = (float) 255 * ((float)((float)(timevalue / 60) - (alarm[alm].time - DAWNTIME)) / DAWNTIME);
    dawnPosition = constrain(dawnPosition, 0, 255);
    dawnColor = CHSV(map(dawnPosition, 0, 255, 10, 35),
                     map(dawnPosition, 0, 255, 255, 170),
                     map(dawnPosition, 0, 255, 10, DAWNBRIGHT));
    FastLED.setBrightness(255);
  } else {
    if (sunlightfl) {
      sunlightfl = false;
      manualoffring = false;
      brightnessls = 0;
      FastLED.setBrightness(brightnessls);
      FastLED.clear();
      FastLED.show();
    }
  }
}

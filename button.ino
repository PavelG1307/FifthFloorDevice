int timer_btn = 0;
int timer_btn_hold = 0;
boolean flagbtn1 = false;
boolean flagbtn2 = false;
boolean flagbtn3 = false;
boolean flagbtn1hold = false;
boolean flagbtn2hold = false;
boolean flagbtn3hold = false;
void button_tick() {
  if (digitalRead(BTN1_PIN)) {
    if (!flagbtn1) {
      flagbtn1 = true;
      timer_btn = millis();
      if (!flagbtn3 && !flagbtn2) {
        brightnessls = brightnessls <= 10 ? 0 : brightnessls - 10;
        Serial.print("Bright: ");
        Serial.println(brightnessls);
      }

      if (flagbtn3 && flagbtn2) {
        currentMode=currentMode>0?currentMode-1:0;
        flagbtn3 = false;
        flagbtn2 = false;
        Serial.print("Mode: ");
        Serial.println(currentMode);

      }
    }
  }

  if (digitalRead(BTN2_PIN)) {
    if (!flagbtn2) {
      flagbtn2 = true;
      timer_btn_hold = millis();

    }
    if (millis() - timer_btn_hold > 500 && !flagbtn2hold) {
      flagbtn2hold = true;
      speaker=!speaker;
      Serial.print("Volume: ");
      Serial.println(volume);
    }
  }

  if (digitalRead(BTN3_PIN)) {
    if (!flagbtn3) {
      flagbtn3 = true;
      timer_btn = millis();
      if (!flagbtn1 && !flagbtn2) {
        brightnessls = brightnessls > 246 ? 155 : brightnessls + 10;
        Serial.print("Bright: ");
        Serial.println(brightnessls);
      }

      if (flagbtn1 && flagbtn2) {
        currentMode=currentMode<10?currentMode+1:10;;
        flagbtn1 = false;
        flagbtn2 = false;
        Serial.print("Mode: ");
        Serial.println(currentMode);
      }
    }
  }

  if (!digitalRead(BTN1_PIN) && flagbtn1 && millis() - timer_btn > 1000) {
    flagbtn1 = false;
  }
  if (!digitalRead(BTN2_PIN) && flagbtn2 && millis() - timer_btn > 1000) {
    if (!flagbtn1 && !flagbtn3 && !flagbtn2hold) {
      brightnessls = brightnessls == 0 ? 50 : 0;
      Serial.print("Bright: ");
      Serial.println(brightnessls);
    }
    flagbtn2hold = false;
    flagbtn2 = false;
  }
  if (!digitalRead(BTN3_PIN) && flagbtn3 && millis() - timer_btn > 1000) {
    flagbtn3 = false;
  }
}

  //
  //void enc_rotate(int direct) {
  //  switch (enc_state) {
  //    case 0:
  //      if ((brightnessls < 245 || direct < 0) && (brightnessls > 0 || direct > 0)) {
  //        brightnessls += direct * 10;
  //        if (brightnessls < 0) brightnessls = 0;
  //        Serial.print("brightness: ");
  //        Serial.println(brightnessls);
  //        FastLED.setBrightness(brightnessls);
  //        FastLED.show();
  //      }
  //      break;
  //    case 1:
  //      if ((currentMode < 5 || direct < 0) && (currentMode > 0 || direct > 0)) {
  //        currentMode += direct;
  //        counter=0;
  //        effectsp = 1;
  //      }
  //      Serial.print("Mode: ");
  //      Serial.println(currentMode);
  //      break;
  //    case 2:
  //      if (effectsc > 5 || direct > 0) {
  //        effectsc += direct * 3;
  //        if (effectsc < 1) effectsc = 1;
  //      }
  //    case 3:
  //      if (effectsp > 0 || direct > 0) {
  //        effectsp += direct;
  //        if (effectsp < 0) effectsp = 0;
  //      }
  //  }
  //}

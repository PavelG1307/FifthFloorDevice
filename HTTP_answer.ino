void handleRoot() {
  if (server.argName(0) == "active") {
    server.send(200, "text/plain", "true");
  }
  if (server.argName(0) == "ssid") {
    if (MODEWIFI == 0) {
      server.send(200, "text/plain", "connecting");
      server.arg(0).toCharArray(ssid, server.arg(0).length() + 1);
      server.arg(1).toCharArray(pass, server.arg(1).length() + 1);
      for (int j = server.arg(0).length() + 1; j < 16; j++) {
        ssid[j] = '\0';
      }
      for (int j = server.arg(1).length() + 1; j < 16; j++) {
        ssid[j + 15] = '\0';
      }
      for (byte i = 2; i < 17; i++) {
        Serial.println((char)ssid[i - 1]);
        delay(100);
        EEPROM.write(i, ssid[i - 2]);
        delay(100);
        EEPROM.write(i + 15, pass[i - 2]);
        delay(100);
      }
      EEPROM.write(0, 1);
      if (EEPROM.commit()) {
        delay(500);
        Serial.println("EEPROM commited!");
      }
      delay(100);
      EEPROM.end();
      resetFunc();
    } else {
      server.send(200, "text/plain", "Error!");
    }
  }

  if (server.argName(0) == "RST") {
    server.send(200, "text/plain", "default settings");
    rstf();
  }
  if (server.argName(0) == "STT") {
    server.send(200, "text/plain", STT());
  }

  if (server.argName(0) == "BRT") {
    brt(server.arg(0));

  }

  if (server.argName(0) == "NGH") {
    if (server.arg(0) == 0) {
      nghtlight = 0;
    } else {
      nghtlight = 1;
      timeonhrs = (int) (server.arg(1)[0] + server.arg(1)[1]);
      timeonmnts = (int) (server.arg(1)[2] + server.arg(1)[3]);
      timeonhrs = (int) (server.arg(2)[0] + server.arg(2)[1]);
      timeonmnts = (int) (server.arg(2)[2] + server.arg(2)[3]);
      //вызвать еепром
    }
  }
//  if (server.argName(0) == "SPQ") {
//    if (server.arg(0) == "1") {
//      speaker = 1;
//      digitalWrite(SPQ_PIN, HIGH);
//    } else {
//      speaker = 0;
//      digitalWrite(SPQ_PIN, LOW);
//    }
//    server.send(200, "text/plain", (String) speaker);
//  }

  if (server.argName(0) == "RNG") {
    server.send(200, "text/plain", "1");
    int count = server.arg(0).toInt();
    for (int k = 0; k < 5; k++) {
      alarm[k].act = false;
    }
    if (count != 0) {
      for (int i = 0; i < count; i++) {
        int j = server.arg(1 + i * 5).toInt();
        alarm[j].music = server.arg(4 + i * 5).toInt();
        if (server.arg(5) == "1") {
          alarm[j].sinerise = true;
        }
        else {
          alarm[j].sinerise = false;
        }
        alarm[j].act = true;
        alarm[j].time = 0;

        if (alarm[j].act) {
          Serial.print("Set ring number: ");
          Serial.println(j);
          Serial.print("On: ");
          Serial.println(time_form(alarm[j].time));
          Serial.print("music:");
          Serial.println(alarm[j].music);
          Serial.print("sunlight:");
          Serial.println(alarm[j].sinerise);
          Serial.print("До будильника:");
          Serial.println(alarm[j].time - (int) timevalue/60);
        }
      }
    }
  }

  if (server.argName(0) == "MD") {
    currentMode = server.arg(0).toInt();
    if (currentMode == 1) {
      r = server.arg(1).toInt();
      g = server.arg(2).toInt();
      b = server.arg(3).toInt();
      FastLED.setBrightness(30);
      Serial.println(r);
      Serial.println(g);
      Serial.println(b);
    }
    brightnessls = 30;
    counter = 0;
  }
}

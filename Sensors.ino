int ValueSens[] = {0, 0, 0, 0, 0};
int timerSens = 0;
byte data[12];
String dataS;




int valuesens = 0;
String topicname = "";
void sensor_tick() {

  if (Serial.available() > 0) {
    dataS = Serial.readString();
    if (dataS.indexOf("?") >= 0) {
      Serial.print("Список: ");
      for (int i = 0; i < CountSens; i++) {
        Serial.println();
        Serial.print("Сенсор: ");
        Serial.println(i);
        Serial.print("ID: ");
        Serial.println(sens[i].id);
        Serial.print("Значение: ");
        Serial.println(sens[i].value);
        Serial.println();
      }
    } else {
      flsens = false;
      idS = dataS.substring(0, 4).toInt();
      for (int i = 0; i < CountSens; i++) {
        if (sens[i].id == idS) {
          sens[i].value = dataS.substring(10, 17).toInt();
          if (sens[i].type > 10 && sens[i].value == 1) alarms((String) sens[i].id + ":" + sens[i].type);
          sens[i].timereq = timevalue;
          flsens = true;
          Serial.print("Сенсор: ");
          Serial.println(i);
          Serial.print("ID: ");
          Serial.println(sens[i].id);
          Serial.print("Значение: ");
          Serial.println(sens[i].value);

        }
      }
      if (!flsens) {
        if (CountSens - 1 < MAXSENS) {
          CountSens++;
          sens[CountSens - 1].id = (int) idS;
          sens[CountSens - 1].value = dataS.substring(10, 17).toInt();
          sens[CountSens - 1].type = dataS.substring(4, 6).toInt();
          sens[CountSens - 1].timereq = timevalue;
          Serial.print("Новый сенсор: ");
          Serial.println(CountSens - 1);
          Serial.print("ID: ");
          Serial.println(sens[CountSens - 1].id);
          Serial.print("Тип: ");
          Serial.println(sens[CountSens - 1].type);
          Serial.print("Значение: ");
          Serial.println(sens[CountSens - 1].value);
        } else {
          Serial.println("Достигнуто макс. кол-во датчиков!");
        }
      }
    }
  }

  if (millis() - timerSens > 10000) {
    timerSens = millis();
    dataS = (String) id + " " + key() + " ";
    for (int i = 0; i < CountSens; i++) {
      dataS += sens[i].id;
      dataS += " ";
      dataS += sens[i].type;
      dataS += " ";
      //      if (timevalue - sens[i].timereq < 600 || sens[i].type > 10) {
      dataS += sens[i].value;
      dataS += " ";
      dataS += (String) (((int) timevalue/60)-sens[i].timereq);
      dataS += " ";
      //      } else {
      //        dataS += ":-1 ";
      //        }
    }
    client.publish("torsh/sens", dataS);
  }
}

String key() {
  int k = random(10, 99);
  k = k + ((k + id) * 4 - 7) * 100;
  return (String) k;
}

void alarms(String s) {
  client.publish("torsh/alarm", (String) id + " " + key() + " " + s);
}

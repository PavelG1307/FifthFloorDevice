int ValueSens[] = { 0, 0, 0, 0, 0 };
int timerSens = 0;
byte data[12];
String dataS;

void alarms(String s) {
  client.publish("torsh/alarm", (String)id + " 123 " + s);
}

void sendSens() {
  dataS = "123 ";
  for (int i = 0; i < CountSens; i++) {
    dataS += sens[i].id;
    dataS += " ";
    dataS += sens[i].type;
    dataS += " ";
    //      if (timevalue - sens[i].timereq < 600 || sens[i].type > 10) {
    dataS += sens[i].value;
    dataS += " ";
    dataS += (String)(((int)timevalue / 60) - sens[i].timereq);
    dataS += " ";
    //      } else {
    //        dataS += ":-1 ";
    //        }
  }
  client.publish(ID_B_S + "/sens", dataS);
}

int valuesens = 0;
String topicname = "";
void sensor_tick() {
  if (rx.gotData()) {
    flsens = false;
    idS = (int)(rx.buffer[0] << 8 | rx.buffer[1]);
    for (int i = 0; i < CountSens; i++) {
      if (sens[i].id == rx.buffer[0]) {
        sens[i].value = rx.buffer[4];
        if (sens[i].type > 10 && sens[i].value > 0) alarms((String)sens[i].id + ":" + sens[i].type);
        sens[i].timereq = timevalue;
        checkRules(idS, sens[i].value);
        flsens = true;
      }
    }
    if (!flsens && CountSens - 1 < MAXSENS) {
      sens[CountSens].id = (int)idS;
      sens[CountSens].key = rx.buffer[2];
      sens[CountSens].type = rx.buffer[3];
      sens[CountSens].value = rx.buffer[4];
      sens[CountSens].timereq = timevalue;
      CountSens++;
    }
    sendSens();
  }

  if (millis() - timerSens > 10000) {
    timerSens = millis();
    sendSens();
  }
}


String key() {
  int k = random(10, 99);
  k = k + ((k + id) * 4 - 7) * 100;
  return (String) k;
}
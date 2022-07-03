int timertime = 0;
int countupd = 0;
void time_tick() {
  if (millis() - timertime >= 1000) {
    timertime = millis();
    timevalue++;
    if (timevalue>=86400) {
      timevalue=0;
      timeupd();
      }
    countupd++;
    if (countupd == 3600) {
      timeupd();
    }
  }
}

void timeupd() {
  timeClient.update();
  timevalue = (timeClient.getHours() * 60 + timeClient.getMinutes()) * 60 + timeClient.getSeconds();
}

String time_form(int t) {
  String tf = "";
  t = (int) t / 60;
  int h = (int) t / 60;
  int m = t - h * 60;
  if (h < 10 && h != 0) {
    tf += "0";
  }
  tf += h;
  tf += ",";
  if (m < 10) {
    tf += "0";
  }
  tf += m;
  return tf;
}


void defRules() {
  for (int i = 0; i <= MAXSENS; i++) {
    rules[2 * i].id = sens[i].id;
    rules[2 * i + 1].id = sens[i].id;
    rules[2 * i].more = true;
    rules[2 * i + 1].more = false;
  }
}

void setRule(int id, bool more, int value, String data) {
  Serial.println("Правило датчика: " + (String) id);
  String cond = more ? "больше " : "меньше ";
  Serial.println("Если значение " + cond + (String) value);
  Serial.println("Отправлю: " + data);
  for (int i = 0; i <= MAXRULES; i++) {
    if (rules[i].id == id && rules[i].more == more) {
      rules[i].value = value;
      rules[i].data = data;
      Serial.println("Успешно установлено");
    }
  }
}

void checkRules(int id, int value) {
  for (int i = 0; i <= MAXSENS; i++) {
    if  (sens[i].id == id) {
      if (rules[2*i].value > value) {
        sendData(rules[2*i].data);
      } else if (rules[2*i+1].value < value) {
        sendData(rules[2*i+1].data);
      }
    }
  }
}
void sendData(String data) {
  Serial.println(data);
}

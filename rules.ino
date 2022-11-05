
void defRules() {
  for (int i = 0; i <= MAXSENS; i++) {
    rules[2 * i].id = sens[i].id;
    rules[2 * i + 1].id = sens[i].id;
    rules[2 * i].more = true;
    rules[2 * i + 1].more = false;
    rules[2 * i].value = 254;
  }
}

void setRule(int id, bool more, int value, String data) {

  for (int i = 0; i <= MAXSENS; i++) {
    if (sens[i].id == id) {
      if (more) {
        rules[2 * i].value = value;
        rules[2 * i].data = data;
      } else {
        rules[2 * i + 1].value = value;
        rules[2 * i + 1].data = data;
      }
        Serial.println("Правило датчика: " + (String) id);
      String cond = more ? "больше " : "меньше ";
      Serial.println("Если значение " + cond + (String) value);
      Serial.println("Отправлю: " + data);
      Serial.println("Успешно установлено");
      break;
    }
  }
}

void checkRules(int id, int value) {
  for (int i = 0; i <= MAXSENS; i++) {
    if  (sens[i].id == id) {
      Serial.println(rules[2*i+1].value);
      Serial.println();
      if (value > rules[2*i].value) {
        sendData(rules[2*i].data);
      } else if (value < rules[2*i+1].value) {
        sendData(rules[2*i+1].data);
      }
      break;
    }
  }
}

void sendData(String data) {
  Serial.print("Отправлю в сеть: ");
  Serial.println(data);
}

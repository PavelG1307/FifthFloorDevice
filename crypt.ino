String crypt(String data) {
  int key = random(10, 99);
  String output = "";
  for (int i = 0; i <= data.length(); i++) {
    output += (String) (key ^ data[i]) + ".";
  }
  output += (String) key;
  return output;
}


// String decrypt(String data) {
//   String buffer = "";
//   String output = "";
//   for (int i = 0; i <= data.length(); i++) {
//     if (data[i] == ".") {
//       output += (char)(buffer.toInt());
//       buffer = "";
//     } else {
//       buffer += data[i];
//     }
//   }
// }
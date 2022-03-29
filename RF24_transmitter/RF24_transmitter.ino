#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

RF24 radio(9, 10); // CE, CSN

const byte address[6] = "00001";
int i = 0;

void setup() {
  radio.begin();
  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_MIN);  //công suất DBm (W), tùy khoảng cách, mức cao cần dùng tụ
  radio.stopListening();
}

void loop() {
  //const char text[] = "Hello World";
  //radio.write(&text, sizeof(text));
  ++i;
  radio.write(&i, sizeof(i));
  delay(100);
}

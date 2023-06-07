
#include "HX711.h"



HX711 scale;

void setup() {
  Serial.begin(9600);
  scale.begin(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN);
}

void loop() {
  //scale.read();
  Serial.println(scale.read());
  //Serial.println(scale.read_average(10));
  delay(200);
}
#include <Arduino.h>
#include "Conexion.h"

Conexion con;

void setup() {
  Serial.begin(115200);
  con.ConnectWiFi_STA();
}

void loop() {
  // put your main code here, to run repeatedly:
}
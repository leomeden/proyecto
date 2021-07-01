#include <Arduino.h>
#include "Conexion.h"
#include "Hora.h"

Conexion con;
Hora tiempo;
String hora;
long unixTime;

void setup() {
  Serial.begin(115200);
  con.ConnectWiFi_STA(); //conecta wifi en modo Station
  tiempo.Iniciar_Hora();
}

void loop() {
  // put your main code here, to run repeatedly:
  tiempo.Actualizar_Hora();
  unixTime = tiempo.Traer_Hora_Unix();
  hora = tiempo.Traer_Hora();
  Serial.print("Hora: ");
  Serial.println(hora);
  delay(5000);

}
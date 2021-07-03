#include <Arduino.h>
#include <Ticker.h> // libreria para interrupciones temporizadas

#include "Conexion.h"
#include "Hora.h"
#include "Api.h"

Ticker interrupt_1;

Conexion con;
Hora tiempo;
Api api;
String hora;
long unixTime;
volatile boolean bandera = false;
int randNumber1, randNumber2;

void funcInterr() {
  bandera = true;
}

void setup() {
  Serial.begin(115200);
  con.ConnectWiFi_STA(); //conecta wifi en modo Station
  tiempo.Iniciar_Hora();
  tiempo.Actualizar_Hora();

  interrupt_1.attach(10, funcInterr);
}

void loop() {
  
  if (bandera) {
    tiempo.Actualizar_Hora();
    hora = tiempo.Traer_Hora();
    randNumber1 = random(218, 223); //aca poner la funcion de lectura de tension
    randNumber2 = random(3, 8); //aca poner la funcion de lectura de corriente
    bandera = false;
    unixTime = tiempo.Traer_Hora_Unix();

    api.Create(randNumber1, hora , unixTime);

    Serial.print("Hora: ");
    Serial.print(hora);
    Serial.print(" / ");
    Serial.print("V: ");
    Serial.print(randNumber1);
    Serial.print(" / ");
    Serial.print("I: ");
    Serial.println(randNumber2);
    Serial.println("");
  }

}
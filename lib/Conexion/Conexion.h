#ifndef __CONEXION_H__
#define __CONEXION_H__

#include <Arduino.h>
#include <ESP8266WiFi.h>

class Conexion  {  
    private:
        // Credenciales del Wifi
        String ssid     = "Internet2";
        String password = "Vicente2016";
        //static char* ssid     = "WiFiGuest";
        //static char* password = "@estacion";
  
    public:
        // Para conectar en modo Estación
        void ConnectWiFi_STA();
                   
};

#endif // __CONEXION_H__
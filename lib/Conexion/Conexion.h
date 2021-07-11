#ifndef __CONEXION_H__
#define __CONEXION_H__

#include <Arduino.h>
#include <ESP8266WiFi.h>

//needed for library
#include <DNSServer.h>
#include <ESP8266WebServer.h>
#include <WiFiManager.h>          //https://github.com/tzapu/WiFiManager



class Conexion  {  
    private:
        // Credenciales del Wifi
        String ssid     = "Internet";
        String password = "Vicente2016";
        WiFiManager wifiManager;
        //static char* ssid     = "WiFiGuest";
        //static char* password = "@estacion";
  
    public:
        // Para conectar en modo Estación
        void ConnectWiFi_STA();
        void ConManager();
                   
};

#endif // __CONEXION_H__
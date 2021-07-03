#ifndef __API_H__
#define __API_H__

#include <Arduino.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>
#include <ArduinoJson.h>

class Api  {  
    private:

        WiFiClient client;
        HTTPClient http;
        
        String ApiHost = "http://192.168.1.8:3000";
        //String ApiHost = "http://raspberrypi.local:3000";
        //String ApiHost = "http://10.103.79.156:3000";

        void processResponse(int, HTTPClient&, String, String);
          
    public:
        void Create(int valor, String hora, long unixTime);
        //void Reenvio(String message, String dayStamp);
        
                   
};

#endif // __API_H__
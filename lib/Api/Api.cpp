#include "Api.h"

void Api::processResponse(int httpCode, HTTPClient& http, String message, String dayStamp)
{
  if (httpCode > 0) {
      
    if (httpCode == HTTP_CODE_CREATED) {
      String payload = http.getString();
      Serial.println("Response code fue 201");
      Serial.println(payload);
    }
  }
  else {
    Serial.printf("Request failed, error: %s\n", http.errorToString(httpCode).c_str());
    Serial.println("");
    Serial.printf("Request failed, error: %i\n", httpCode);

    Fs.Guardar_FS(message, dayStamp);
  }
  http.end();
}

void Api::Create(int valor, String hora, long unixTime)
{
  Serial.println("Entre al create");
  //WiFiClient client;
  //HTTPClient http;

  http.setTimeout(500);
  http.begin(client, ApiHost + "/api/sensor");
  http.addHeader("Content-Type", "application/json");

  Serial.print("Ultima hora: ");
  Serial.println(hora);  
  
  
  String message = "";
  StaticJsonDocument<300> jsonDoc;
  jsonDoc["valor"] = valor;
  jsonDoc["hora"] = hora;
  jsonDoc["unixTime"] = unixTime;
  
  serializeJson(jsonDoc, message);

  //Verifica largo del mensaje
  int contentLength = message.length();
  //Serial.printf("largo del mensaje: %d\n", contentLength);
  String largo = String(contentLength);
  http.addHeader("Content-Length", largo);
  
  int httpCode = http.POST(message);
 
  int splitT = hora.indexOf("T");
  String dayStamp = hora.substring(0, splitT);
  processResponse(httpCode, http, message, dayStamp);

}

/*void Api::Reenvio(String message, String dayStamp)
{
  //HTTPClient http;
  http.setTimeout(500);
  http.begin(ApiHost + "/api/sensor");
  http.addHeader("Content-Type", "application/json");

  //Verifica largo del mensaje
  int contentLength = message.length();
  Serial.printf("largo del mensaje: %d\n", contentLength);
  String largo = String(contentLength);
  http.addHeader("Content-Length", largo);
  
  int httpCode = http.POST(message);

  processResponse(httpCode, http, message, dayStamp);
 
  //int splitT = hora.indexOf("T");
  //String dayStamp = hora.substring(0, splitT);
  //processResponse(httpCode, http, message, dayStamp);
  
}*/
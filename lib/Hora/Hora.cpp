#include "Hora.h"

WiFiUDP ntpUDP;

long utcOffsetInSeconds = -10800;
long updateInterval = 60*60*1000;

NTPClient timeClient(ntpUDP,"pool.ntp.org", utcOffsetInSeconds, updateInterval);

void Hora::Iniciar_Hora(){
  timeClient.begin();
}

void Hora::Actualizar_Hora(){
   timeClient.update();
}
String Hora::Traer_Hora(){
    return ( timeClient.getFormattedDate() );
}

long Hora::Traer_Hora_Unix(){
    return ( timeClient.getEpochTime() );
}
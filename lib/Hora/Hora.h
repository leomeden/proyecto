#ifndef __HORA_H__
#define __HORA_H__

#include <Arduino.h>
#include <NTPClient.h>
#include <WiFiUdp.h>

class Hora  {  
    private:
        // Parametros 
          
    public:
        void Iniciar_Hora();
        void Actualizar_Hora();
        String Traer_Hora();
        long Traer_Hora_Unix();
                   
};

#endif // __HORA_H__
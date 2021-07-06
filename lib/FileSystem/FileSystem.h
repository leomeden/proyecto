#ifndef __FILESYSTEM_H__
#define __FILESYSTEM_H__

#include <Arduino.h>
#include "FS.h" 
//#include "Api.h"

class FileSystem {

    private: 

        //Api _api;

    public:

        void Format_FS();
        void Abrir_FS();
        void Guardar_FS(String message, String dayStamp);
        void Enviar_FS();

};

#endif // __FILESYSTEM_H__
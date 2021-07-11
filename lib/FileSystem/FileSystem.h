#ifndef __FILESYSTEM_H__
#define __FILESYSTEM_H__

#include <Arduino.h>
#include "LittleFS.h" 


class FileSystem {

    private: 
        bool result;
        File f;
        Dir dir;
        String lastFileName;
        String nomArchivo;
        int contadorLineas;
        int contadorArchivos;
        String carpetaFecha;
        String line;
        String lastDir;
        String message ="";
        String arrayDatos[10];
        int i;
        int j;
        String suma;
        
    public:

        void Format_FS();
        void Abrir_FS();
        void Guardar_FS(String message, String dayStamp);
        String Enviar_FS();

};

#endif // __FILESYSTEM_H__
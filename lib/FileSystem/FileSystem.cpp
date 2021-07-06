#include "FileSystem.h"


void FileSystem::Format_FS()
{
   // Siempre usa esto para "montar" el sistema de archivos
  bool result = SPIFFS.format();
  Serial.print("SPIFFS formateado: ");
  Serial.println(result);
}



void FileSystem::Abrir_FS()
{
   // Siempre usa esto para "montar" el sistema de archivos
  bool result = SPIFFS.begin();
  Serial.print("SPIFFS abierto: ");
  Serial.println(result);
}


void FileSystem::Guardar_FS(String message, String dayStamp)
{
      File f;
      String lastFileName;
      int contadorLineas;
      int contadorArchivos;
      String carpetaFecha;

      carpetaFecha = "/"+dayStamp;
      
      Dir dir = SPIFFS.openDir(carpetaFecha);

        //verifica si hay carpeta con la fecha de hoy y
        //crea la carpeta si no existe
        if (!dir.next()){
            Serial.println("No Hay Archivos!!!!!"); 
            Serial.println("");
            Serial.print("Creando Archivo: "); 
            Serial.print(carpetaFecha);
            Serial.println("/1");
            String nomArchivo = carpetaFecha+"/1";
            f = SPIFFS.open(nomArchivo, "w");
            f.println(message);
            f.close();   
        } else {
              contadorArchivos = 1;
              lastFileName = dir.fileName();
              while(dir.next()){ 
                  ++contadorArchivos;
                  lastFileName = dir.fileName();   
              }

              f = SPIFFS.open(lastFileName, "r");
              contadorLineas=0;
         
              while(f.available()) {
                // Permite leer línea por línea desde el archivo
                ++contadorLineas;
                String line = f.readStringUntil('\n');
                //Serial.println(line);
              }
              f.close();
              //Serial.print("Cantidad de líneas: ");
              //Serial.println(contadorLineas);
              if (contadorLineas <10){
                  Serial.print("Cantidad de archivos: ");
                  Serial.println(contadorArchivos);
                  f = SPIFFS.open(lastFileName, "a");
                  f.println(message);
                  f.close();
                  //Serial.println("Ultimo agregado: ");
                  //Serial.println(message);
                  
                  f = SPIFFS.open(lastFileName, "r");
                  Serial.println("Contenido del archivo con el agregado: ");
                  while(f.available()) {
                      // Permite leer línea por línea desde el archivo
                      String line = f.readStringUntil('\n');
                      Serial.println(line);
                  }
                  f.close();
              } else {
                  ++contadorArchivos;
                  Serial.print("Cantidad de archivos: ");
                  Serial.println(contadorArchivos);
                  lastFileName = carpetaFecha + "/" + contadorArchivos;
                  f = SPIFFS.open(lastFileName, "w");
                  f.println(message);
                  f.close();
                  f = SPIFFS.open(lastFileName, "r");
                  Serial.println("Contenido del archivo con el agregado: ");
                  while(f.available()) {
                      // Permite leer línea por línea desde el archivo
                      String line = f.readStringUntil('\n');
                      Serial.println(line);
                  }
                  f.close();
                  Serial.println("Ultimo agregado: ");
                  Serial.println(message);
              }
        }
        
}

void FileSystem::Enviar_FS()
{
      File f;
      String lastFileName;
      String message;
      int contadorLineas;
      int contadorArchivos = 0;
      String arrayDatos[10];
      int i;
      int j;
      //String carpetaFecha;
      Serial.println("Rutina de reenvio");
      
      //carpetaFecha = "/"+dayStamp;
      
      //Dir dir = SPIFFS.openDir(carpetaFecha);
      Dir dir = SPIFFS.openDir("/");
      
        //Serial.println("Carpetas creadas: ");  

        if (!dir.next()){
            Serial.println("No Hay Nada Acumulado Para Mandar!!!!!");   
        } else {
              contadorArchivos = 1;
              lastFileName = dir.fileName();
              Serial.print("Nombre de Archivo: "); 
                  Serial.println(lastFileName);
                  Serial.println("");
                  
        }

              
              while(dir.next()){ 
                  ++contadorArchivos;
                  lastFileName = dir.fileName();  
                  Serial.print("Nombre de Archivo: "); 
                  Serial.println(lastFileName);
                  Serial.println("");
                  /*f = SPIFFS.open(lastFileName, "r");
                  contadorLineas=0;
                  Serial.println("Contenido del archivo: ");
                  while(f.available()) {
                      // Permite leer línea por línea desde el archivo
                    ++contadorLineas;
                     String line = f.readStringUntil('\n');
                    Serial.println(line);
                  }
                  f.close();
                  Serial.print("Cantidad de líneas: ");
                  Serial.println(contadorLineas);*/
                  }
              
              Serial.print("Ultimo archivo creado: "); 
              Serial.println(lastFileName);
              Serial.print("Cantidad de Archivos: ");
              Serial.println(contadorArchivos);
                  
                  //Creo el array para enviarlo
                  contadorLineas = 0;
                  f = SPIFFS.open(lastFileName, "r");
                  while(f.available()) {
                      // Permite leer línea por línea desde el archivo
                     String line = f.readStringUntil('\n');
                    arrayDatos[contadorLineas] = line;
                    ++contadorLineas;
                  }
                  f.close();
                  Serial.println("Array: ");
                  for (i=0; i<contadorLineas; i++) {
                    
                      Serial.println(arrayDatos[i]);
                  }  

                  if (contadorLineas<1) {
                          SPIFFS.remove(lastFileName);
                  } else {
                            
                            message=arrayDatos[(contadorLineas-1)];
                            
                            Serial.println("ultimo dato: ");
                            Serial.println(message);
                            Serial.println("array con el ultimo dato afuera: ");
                            f = SPIFFS.open(lastFileName, "w");
                            for (j=0; j<(contadorLineas-1); j++) {
                                     
                              f.println(arrayDatos[j]);
                              Serial.println(arrayDatos[j]);
                              
                            }
                            f.close();

                            int splitT = lastFileName.indexOf("/", 2);
                            String dayStamp = lastFileName.substring(1, splitT);

                            //_api.Reenvio(message, dayStamp);
                                                     
                      }
                    
                  }
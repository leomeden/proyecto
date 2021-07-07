#include "FileSystem.h"


void FileSystem::Format_FS()
{
   // Siempre usa esto para "montar" el sistema de archivos
  result = LittleFS.format();
  Serial.print("SPIFFS formateado: ");
  Serial.println(result);
}



void FileSystem::Abrir_FS()
{
   // Siempre usa esto para "montar" el sistema de archivos
  result = LittleFS.begin();
  Serial.print("SPIFFS abierto: ");
  Serial.println(result);
}


void FileSystem::Guardar_FS(String message, String dayStamp)
{
      carpetaFecha = "/"+dayStamp;
      
      dir = LittleFS.openDir(carpetaFecha);

        //verifica si hay carpeta con la fecha de hoy y
        //crea la carpeta si no existe
        if (!dir.next()){
            Serial.println("No Hay Archivos!!!!!"); 
            Serial.println("");
            Serial.print("Creando Archivo: "); 
            Serial.print(carpetaFecha);
            Serial.println("/1");
            nomArchivo = carpetaFecha+"/1";
            f = LittleFS.open(nomArchivo, "w");
            f.println(message);
            f.close();   
            //prueba de imprimir al crear primer archivo
            //Serial.println("###################");
            //Serial.println("Prueba al crear");
            //f = LittleFS.open(nomArchivo, "r");
            //  while(f.available()) {
            //    String line = f.readStringUntil('\n');
            //    Serial.println(line);
            //  }
            //  f.close();
            //Serial.println("Fin Prueba al crear");
            //Serial.println("###################");

        } else {
              contadorArchivos = 1;
              lastFileName = dir.fileName();
              //Serial.println("###################");
              //Serial.println("Prueba 2!!!!!!");
              Serial.print("Archivo: ");
              Serial.println(carpetaFecha+"/"+lastFileName);
            
              while(dir.next()){ 
                  ++contadorArchivos;
                  lastFileName = dir.fileName();   
                  Serial.print("Archivo: ");
                  Serial.println(carpetaFecha+"/"+lastFileName);
              }

              f = LittleFS.open(carpetaFecha+"/"+lastFileName, "r");
              contadorLineas=1;
              line = f.readStringUntil('\n');
              //Serial.println(line);
         
              while(f.available()) {
                // Permite leer línea por línea desde el archivo
                ++contadorLineas;
                line = f.readStringUntil('\n');
                //Serial.println(line);
              }
              f.close();
              //Serial.print("Cantidad de líneas: ");
              //Serial.println(contadorLineas);
              if (contadorLineas <10){
                  Serial.print("Cantidad de archivos: ");
                  Serial.println(contadorArchivos);
                  f = LittleFS.open(carpetaFecha+"/"+lastFileName, "a");
                  f.println(message);
                  f.close();
                  //Serial.println("Ultimo agregado: ");
                  //Serial.println(message);
                  
                  f = LittleFS.open(carpetaFecha+"/"+lastFileName, "r");
                  Serial.println("Contenido del archivo con el agregado: ");
                  while(f.available()) {
                      // Permite leer línea por línea desde el archivo
                      line = f.readStringUntil('\n');
                      Serial.println(line);
                  }
                  f.close();
              } else {
                  ++contadorArchivos;
                  Serial.print("Cantidad de archivos: ");
                  Serial.println(contadorArchivos);
                  lastFileName = carpetaFecha + "/" + contadorArchivos;
                  f = LittleFS.open(lastFileName, "w");
                  f.println(message);
                  f.close();
                  f = LittleFS.open(lastFileName, "r");
                  Serial.println("Contenido del archivo con el agregado: ");
                  while(f.available()) {
                      // Permite leer línea por línea desde el archivo
                      line = f.readStringUntil('\n');
                      Serial.println(line);
                  }
                  f.close();
                  //Serial.println("Ultimo agregado: ");
                  //Serial.println(message);
              }
        }
        
}

String FileSystem::Enviar_FS()
{
      contadorArchivos = 0;
      
      //String carpetaFecha;
      Serial.println("#######################");
      Serial.println("Rutina de reenvio");
      
      //carpetaFecha = "/"+dayStamp;
      
      //Dir dir = SPIFFS.openDir(carpetaFecha);
      dir = LittleFS.openDir("/");
      
        //Serial.println("Carpetas creadas: ");  

        if (!dir.next()){
            Serial.println("No Hay Nada Acumulado Para Mandar!!!!!");   
        } else {
              //contadorArchivos = 1;
              lastDir = dir.fileName();
              Serial.print("Nombre de Carpetas DIAS: "); 
              Serial.println(lastDir);
              Serial.println("");        
        }

        while (dir.next()){
            lastDir = dir.fileName();
            Serial.print("Nombre de Carpetas DIAS: "); 
            Serial.println(lastDir);
            Serial.println("");        
        }
        dir = LittleFS.openDir("/"+lastDir+"/");
              
              contadorArchivos = 0;
              while(dir.next()){ 
                  ++contadorArchivos;
                  lastFileName = dir.fileName();  
                  Serial.print("Nombre de Archivo: "); 
                  Serial.println(lastDir+"/"+lastFileName);
                  Serial.println("");
                  }
              
              Serial.print("Ultimo archivo creado: "); 
              Serial.println(lastDir+"/"+lastFileName);
              Serial.print("Cantidad de Archivos: ");
              Serial.println(contadorArchivos);
                  
                  //Creo el array para enviarlo
                  contadorLineas = 0;
                  f = LittleFS.open(lastDir+"/"+lastFileName, "r");
                  while(f.available()) {
                      // Permite leer línea por línea desde el archivo
                    line = f.readStringUntil('\n');
                    arrayDatos[contadorLineas] = line;
                    ++contadorLineas;
                  }
                  f.close();
                  Serial.println("Array: ");
                  for (i=0; i<contadorLineas; i++) {
                    
                      Serial.println(arrayDatos[i]);
                  }  

                  if (contadorLineas<1) {

                        LittleFS.remove(lastDir+"/"+lastFileName);
                        message ="";

                  } else {
                            
                            message=arrayDatos[(contadorLineas-1)];
                            
                            Serial.println("ultimo dato: ");
                            Serial.println(message);
                            Serial.println("array con el ultimo dato afuera: ");
                            f = LittleFS.open(lastDir+"/"+lastFileName, "w");
                            for (j=0; j<(contadorLineas-1); j++) {
                                     
                              f.println(arrayDatos[j]);
                              Serial.println(arrayDatos[j]);
                              
                            }
                            f.close();

                            Serial.print("Dato a Enviar: ");
                            Serial.println(message);

                            

                            //int splitT = lastFileName.indexOf("/", 2);
                            //String dayStamp = lastFileName.substring(1, splitT);

                            //_api.Reenvio(message, dayStamp);
                                                     
                      }

                      return message;
                    
                  }
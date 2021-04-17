                      #include <MD_MAX72xx.h>
#include <SPI.h>
#include <Servo.h>



String mensaje;
int recibe=2;
int baud=9600;
Servo servoMotor;
int pinDIN = 2;
int pinCS = 3;
int pinCLK = 4;
//Inicializamos la pantalla de leds MAX7219 en modo generico, en el pin CS indicado y el numero de pantallas 
MD_MAX72XX pLED = MD_MAX72XX(MD_MAX72XX::DR0CR0RR1_HW, pinDIN,pinCLK,pinCS, 1);


//Funciones y movimientos

void setupLeds(){  

   pLED.control(MD_MAX72XX::TEST, true);
   delay(100);
   pLED.control(MD_MAX72XX::TEST, false);
   delay(100);
  
   pLED.control(MD_MAX72XX::INTENSITY,5);
   delay(250);

   // Recorrido de prueba por todos los leds
   int i=0,val=0;
   for(i=0;i<8;i++){
    int power=1;
    for(val=0;val<8;val++)
    {
      pLED.setColumn(i,power);
      power*=2;
      delay(5);
      
    }    
    pLED.setColumn(i,0);
    
   }

   // Mensaje de inicio
   // mostach1B0t
  pLED.setChar(5,'m');
  delay(100);
  pLED.clear();
  pLED.setChar(5,'o');
  delay(100);
  pLED.clear();
  pLED.setChar(5,'s');
  delay(100);
  pLED.clear();
  pLED.setChar(5,'t');
  delay(100);  
  pLED.clear();
  pLED.setChar(5,'a');
  delay(100);
  pLED.clear();
  pLED.setChar(5,'c');
  delay(100);
  pLED.clear();
  pLED.setChar(5,'h');
  delay(100);
  pLED.clear();
  pLED.setChar(5,'1');
  delay(100);
  pLED.clear();
  pLED.setChar(5,'B');
  delay(100);
  pLED.clear();
  pLED.setChar(5,'0');
  delay(100);
  pLED.clear();
  pLED.setChar(5,'t');
  delay(2000);
  pLED.clear();
  // v0.1
  pLED.setColumn(0,0);
  pLED.setColumn(6,B00011000);
  pLED.setColumn(5,B00100100);
  pLED.setColumn(4,B00011000);
  pLED.setColumn(3,B00100000);
  pLED.setColumn(2,B00001000);
  pLED.setColumn(1,B00111100);
  pLED.setColumn(7,0);
  delay(2000);
  pLED.clear();
}

void estrella(){
  pLED.setColumn(7,B11101100);
  pLED.setColumn(6,B10010100);
  pLED.setColumn(5,B10000110);
  pLED.setColumn(4,B01000001);
  pLED.setColumn(3,B01000001);
  pLED.setColumn(2,B10000110);
  pLED.setColumn(1,B10010100);
  pLED.setColumn(0,B11101100);
  delay(100);
}

void setup() {
  //Inicializamos el puerto serie a determinada velocidad  
  Serial.begin(baud);
  pLED.begin();
  setupLeds();

   //Realizamos breve test de comprobación de los leds
   
 
   
 
}

void loop() {
  // put your main code here, to run repeatedly:
 

  if(Serial.available()>0)
  {
  
       
    mensaje = Serial.readString();
    if(mensaje == "encender"){ 
     estrella();
    }
    if(mensaje == "apagar")
    {
     pLED.clear();
    }
    
    
    
  }
}

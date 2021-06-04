  #include <Servo.h>
  #include <MD_MAX72xx.h>

Servo piernaI, caderaI, brazoI, piernaD, caderaD, brazoD;
#define pinDIN 2
#define pinCLK 4
#define pinCS 3
 
 //Inicializamos la pantalla de leds MAX7219 en modo generico, en el pin CS indicado y el numero de pantallas 
MD_MAX72XX pLED = MD_MAX72XX(MD_MAX72XX::DR0CR0RR1_HW, pinDIN,pinCLK,pinCS, 1);

void bracitos() {

// Colocamos cada servo en su pin de entrada
  piernaI.attach(11);
  caderaI.attach(10);
  brazoI.attach(9);
  brazoD.attach(8);
  caderaD.attach(7);
  piernaD.attach(6);

// Escribimos la posicion inicial
 piernaI.write(90);
 caderaI.write(90);
 brazoI.write(0); // Brazo abajo
 brazoD.write(180); // Brazo abajo
 caderaD.write(90);
 piernaD.write(90);

 
}

void holaMostachi() {
   pLED.begin();
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
  pLED.setColumn(3,B01111010);
  pLED.setColumn(2,B00101010);
  pLED.setColumn(1,B00100110);
  pLED.setColumn(7,0);
  delay(2000);
  pLED.clear();
}

void setup() {

  bracitos();
  holaMostachi();

 
}

void loop() {
  // put your main code here, to run repeatedly:


  
}



#include <Wire.h>
#include <splash.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_GrayOLED.h>
#include <Adafruit_SPITFT.h>
#include <Adafruit_SPITFT_Macros.h>
#include <gfxfont.h>
#include <MD_MAX72xx.h>
#include <SPI.h>
#include <Servo.h>

#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
 #include <avr/power.h> // Required for 16 MHz Adafruit Trinket
#endif

#define NUMPIXELS 12
#define PINIZQ 6
#define PINDER 7


Adafruit_SSD1306 oled(128,64,&Wire,4);
Adafruit_NeoPixel ojoizq(NUMPIXELS, PINIZQ, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel ojoder(NUMPIXELS, PINDER, NEO_GRB + NEO_KHZ800);



/* PROTOCOLO COMUNICACION */



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
  mensaje="";
}



void setup() {
  //Inicializamos el puerto serie a determinada velocidad  
  Serial.begin(baud);
  ojoizq.begin();
  ojoder.begin();
  pLED.begin();
  setupLeds();
  Wire.begin();
  oled.begin(SSD1306_SWITCHCAPVCC,0x3C);
  ojoizq.fill(ojoizq.Color(20,20,20,2),0,12);
  ojoder.fill(ojoder.Color(50,50,50,50),0,12);
  ojoizq.show();
  ojoder.show();
  
 
 
   
 
}

void loop() {
  // put your main code here, to run repeatedly:
  oled.clearDisplay();
  oled.setTextColor(WHITE);
  oled.setCursor(40,0);
  oled.setTextSize(7);
  oled.print("w");
  oled.display();

  if(Serial.available()>0)
  {
  
       
    mensaje = Serial.readString();
    
    if(mensaje == "encender\n"){ 
      
     estrella();
     Serial.println("Retro calvo <3");     
    
    }
    if(mensaje == "apagar")
    {
     pLED.clear();
    }
    
    
    
  }
  else
  {

    // Si no hay mensaje en el serial, estamos en IDLE

    for (int i=20;i<100;i++)
    {      
    ojoizq.fill(ojoizq.Color(i,i,i,i),0,12);
    ojoder.fill(ojoder.Color(i,i,i,i),0,12);
    delay(6);
    ojoizq.show();
    ojoder.show();
    }
  
    for (int i=100;i>20;i--)
    {      
    ojoizq.fill(ojoizq.Color(i,i,i,i),0,12);
    ojoder.fill(ojoder.Color(i,i,i,i),0,12);
    delay(6);
    ojoizq.show();
    ojoder.show();
    }

  
  
    
  }
  
  }

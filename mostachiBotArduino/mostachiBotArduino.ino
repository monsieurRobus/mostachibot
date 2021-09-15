// Asistente Mostachi Bot v0.1
//DEFINICION PINES DE LA TIRA DE LEDS ESTÁTICA

#define ROJO 9
#define AZUL 11
#define VERDE 10
#define DIRECCIONABLE 8
#define DIRECCIONABLE2 7
#define tiempoDELAY 10


// ELEMENTOS DE ADAFRUIT NEOPIXEL STRAND (LEDS DIRECCIONABLES)

#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
 #include <avr/power.h> // Required for 16 MHz Adafruit Trinket
#endif
#define LED_COUNT 70

Adafruit_NeoPixel strip(LED_COUNT, DIRECCIONABLE, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel strip2(LED_COUNT, DIRECCIONABLE2, NEO_GRB + NEO_KHZ800);


int colorRojo=50;
int colorVerde=50;
int colorAzul=50;
String colorNuevo = "";
char caracterSerial ="";

enum eventos{mensajeDestacado,sub,bits,follow} eventoRealizado;
String leeString; //string capturada
String evento; //evento 
String arg1; 
String arg2; 
String arg3; 
String arg4;
String arg5;

int dato1; 
int dato2;
int dato3;
int dato4;
int dato5;
int dato6;

// Funcion tipoEvento que devuelve el tipo ENUM del evento llamado desde el chat de twitch
eventos tipoEvento(String eventoDetectado){
  if(eventoDetectado =="sub") return sub;
  if(eventoDetectado =="mensajeDestacado") return mensajeDestacado;
}

// STRIP FUNCITIONS 
// Funcion RAINBOW extraida del ejemplo STRIP

// Rainbow cycle along whole strip. Pass delay time (in ms) between frames.
void rainbow(int wait) {
  // Hue of first pixel runs 5 complete loops through the color wheel.
  // Color wheel has a range of 65536 but it's OK if we roll over, so
  // just count from 0 to 5*65536. Adding 256 to firstPixelHue each time
  // means we'll make 5*65536/256 = 1280 passes through this outer loop:
  for(long firstPixelHue = 0; firstPixelHue < 2*65536; firstPixelHue += 256) {
    for(int i=0; i<strip.numPixels(); i++) { // For each pixel in strip...
      // Offset pixel hue by an amount to make one full revolution of the
      // color wheel (range of 65536) along the length of the strip
      // (strip.numPixels() steps):
      int pixelHue = firstPixelHue + (i * 65536L / strip.numPixels());
      // strip.ColorHSV() can take 1 or 3 arguments: a hue (0 to 65535) or
      // optionally add saturation and value (brightness) (each 0 to 255).
      // Here we're using just the single-argument hue variant. The result
      // is passed through strip.gamma32() to provide 'truer' colors
      // before assigning to each pixel:
      strip.setPixelColor(i, strip.gamma32(strip.ColorHSV(pixelHue)));
    }
    strip.show(); // Update strip with new contents
    delay(wait);  // Pause for a moment
  }
}
// FUNCION THEARHERCHASE extraida de ejemplo STRIP

void theaterChase(uint32_t color, int wait) {
  for(int a=0; a<10; a++) {  // Repeat 10 times...
    for(int b=0; b<3; b++) { //  'b' counts from 0 to 2...
      strip.clear();         //   Set all pixels in RAM to 0 (off)
      // 'c' counts up from 'b' to end of strip in steps of 3...
      for(int c=b; c<strip.numPixels(); c += 3) {
        strip.setPixelColor(c, color); // Set pixel 'c' to value 'color'
      }
      strip.show(); // Update strip with new contents
      delay(wait);  // Pause for a moment
    }
  }
}

// Funcion cambiaColorDinamico que hace FADE progresivo a acada pixel y restaura cada pixel a un color concreto

//REVISAR!!!!!! hacer algo similar a cambiarColor
void cambiaColorDinamico(uint32_t color){

  bool restaura = false;
  uint32_t colorActual = 0;
  do 
  {
    restaura=true;
    for (int i=0;i<LED_COUNT+1;i++)
    {
      colorActual = strip.getPixelColor(i);
      if(colorActual>color) {
        colorActual--;
        restaura=false;
      }
                            
      if(colorActual<color) 
      {
        colorActual++;
        restaura=false;
      }
     strip.setPixelColor(i,colorActual);
     }
    strip.show();
    
  } while (!restaura);
  
}


// Funcion cambiarColor que hace un FADE progresivo con TIEMPODELAY 
// LEDS ESTATICOS
void cambiarColor(int newR, int newA, int newV) {
  int deltaR = 1;
  int deltaA = 1;
  int deltaV = 1;
  if (newR>colorRojo)
    {
      deltaR=1;    
    }
  
  else
    {
      deltaR=-1;
    }

  if (newA>colorAzul)
    {
      deltaA=1;    
    }
  
  else
    {
      deltaA=-1;
    }
  
  if (newV>colorVerde)
    {
      deltaV=1;    
    }
  
  else
    {
      deltaV=-1;
    }

  //CAMBIO ROJO

  for(int i=colorRojo;i!=newR;i+=deltaR)
  {
    analogWrite(ROJO,i);
    delay(tiempoDELAY);
  
  }

    for(int i=colorVerde;i!=newV;i+=deltaV)
  {
    analogWrite(VERDE,i);
    delay(tiempoDELAY);  
  }

  
    for(int i=colorAzul;i!=newA;i+=deltaA)
  {
    analogWrite(AZUL,i);
    delay(tiempoDELAY);  
  }

  colorRojo = newR;
  colorAzul = newA;
  colorVerde = newV;
    
}


void setup() {

    // INICIAMOS EL SERIAL
  Serial.begin(9600);  
  Serial.println("Probamos el serial"); // Testeo de serial
  Serial.print("Color inicial: Blanco intensidad media");

analogWrite(ROJO,0);

analogWrite(VERDE,0);

analogWrite(AZUL,0);

delay(1000);



analogWrite(ROJO,255);

analogWrite(VERDE,0);

analogWrite(AZUL,10);

  Serial.println("...hecho");

delay(1000);


#if defined(__AVR_ATtiny85__) && (F_CPU == 16000000)
  clock_prescale_set(clock_div_1);
#endif
  // END of Trinket-specific code.

  strip.begin();           // INITIALIZE NeoPixel strip object (REQUIRED)
  strip.fill(strip.Color(155,154,155),0,100);
  strip.show();            // Turn OFF all pixels ASAP
  strip.setBrightness(255); // Set BRIGHTNESS to about 1/5 (max = 255)
  
  strip2.begin();           // INITIALIZE NeoPixel strip object (REQUIRED)
  strip2.fill(strip.Color(255,10,0),0,100);
  strip2.show();            // Turn OFF all pixels ASAP
  strip2.setBrightness(200); // Set BRIGHTNESS to about 1/5 (max = 255)
  strip2.fill(strip.Color(150,150,255),23,100);
  strip2.show();            // Turn OFF all pixels ASAP
  strip2.setBrightness(200); // Set BRIGHTNESS to about 1/5 (max = 255)
 

}


void loop() {

  //esperamos un string de la forma dato1/dato2/dato3/dato4$
  

  if (Serial.available())  {
    char c = Serial.read();  //captura un caracter del serial
    if (c == '$') {
      //do stuff
      
      Serial.println();
      Serial.print("string capturada es: "); 
      Serial.println(leeString); //muestra la string capturada
      
      dato1 = leeString.indexOf('/'); 
      evento = leeString.substring(0, dato1);   //captura el primer dato
      dato2 = leeString.indexOf('/', dato1+1 );   
      arg1 = leeString.substring(dato1+1, dato2);   //captura el dato dato
      dato3 = leeString.indexOf('/', dato2+1 );
      arg2 = leeString.substring(dato2+1, dato3); //captura el tercer dato
      dato4 = leeString.indexOf('/', dato3+1 );
      arg3 = leeString.substring(dato3+1); //captura el cuartol dato
      dato5 = leeString.indexOf('/', dato4+1 );
      arg4 = leeString.substring(dato3+1); //captura el cuartol dato
      dato6 = leeString.indexOf('/', dato5+1 );
      arg5 = leeString.substring(dato3+1); //captura el cuartol dato

      Serial.print("evento = ");
      Serial.println(evento); 
      Serial.print("argumento1 = ");
      Serial.println(arg1);
      Serial.print("argumento2 = ");
      Serial.println(arg2);
      Serial.print("argumento3 = ");
      Serial.println(arg3);
      Serial.print("argumento4 = ");
      Serial.println(arg4);
      Serial.print("argumento5 = ");
      Serial.println(arg5);
      Serial.println();
      Serial.println();

      eventoRealizado = tipoEvento(evento);
      
      
      leeString=""; //limpia la string almacenada para recibir más datos
      evento="";
      arg1="";
      arg2="";
      arg3="";
      arg4="";
      arg5="";

      // Realiza una accion en funcion del evento
    
      switch(eventoRealizado){
        case 1:
        Serial.println(eventoRealizado);
          cambiarColor(100,0,0);
          strip.fill(strip.Color(155,155,155),0,100);
          strip.show();
          delay(1000);
          rainbow(1);
          strip.fill(strip.Color(155,155,155),0,100);
          strip.show();
          cambiarColor(155,155,155);
          
          
        
        break;
        }
    
    }  
    else {     
      leeString += c; //makes the string leeString
    }
  }

}

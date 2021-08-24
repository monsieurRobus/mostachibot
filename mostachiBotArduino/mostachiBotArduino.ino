// Asistente Mostachi Bot v0.1
//DEFINICION PINES DE LA TIRA DE LEDS ESTÁTICA

#define ROJO 9
#define AZUL 11
#define VERDE 10
#define DIRECCIONABLE 8
#define tiempoDELAY 10


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

// Funcion cambiarColor que hace un FADE progresivo con TIEMPODELAY
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


analogWrite(ROJO,50);

analogWrite(VERDE,50);

analogWrite(AZUL,50);

  Serial.println("...hecho");

delay(1000);

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
          delay(1000);
          cambiarColor(155,155,155);
        
        break;
        }
    
    }  
    else {     
      leeString += c; //makes the string leeString
    }
  }

}

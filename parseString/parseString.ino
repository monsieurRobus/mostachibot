

// Carlos Díaz aka soyMonsieur 2021 
// parseString v0.1 Serial Twitch
// Usando separadores / y finalizador $
// El programa lee el serial en busca de una string 
// y al encontrar $ saca información de la string almacenada

String leeString; //string capturada
String evento; //evento 
String usuario; //usuario que lo realiza
String bits; //bits aportados (0 en caso de ser sin bits)
String mensaje; //mensaje de la recompensa

int dato1; 
int dato2;
int dato3;
int dato4;

void setup() {
  Serial.begin(9600);
  Serial.println("Probamos el serial"); // Testeo de serial
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
      usuario = leeString.substring(dato1+1, dato2);   //captura el dato dato
      dato3 = leeString.indexOf('/', dato2+1 );
      bits = leeString.substring(dato2+1, dato3); //captura el tercer dato
      dato4 = leeString.indexOf('/', dato3+1 );
      mensaje = leeString.substring(dato3+1); //captura el cuartol dato

      Serial.print("evento = ");
      Serial.println(evento); 
      Serial.print("usuario = ");
      Serial.println(usuario);
      Serial.print("bits = ");
      Serial.println(bits);
      Serial.print("mensaje = ");
      Serial.println(mensaje);
      Serial.println();
      Serial.println();
      
      leeString=""; //limpia la string almacenada para recibir más datos
      evento="";
      usuario="";
      bits="";
      mensaje="";
    }  
    else {     
      leeString += c; //makes the string leeString
    }
  }
}

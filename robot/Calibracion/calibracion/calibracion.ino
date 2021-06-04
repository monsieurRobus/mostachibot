#include <Servo.h>

Servo prueba,prueba2,prueba3;
void setup() {
  // put your setup code here, to run once:
  prueba.attach(9);
  prueba2.attach(10);
  prueba3.attach(11);
  prueba.write(180);
  prueba2.write(180);
  prueba3.write(180);
}

void loop() {
  // put your main code here, to run repeatedly:
  

}

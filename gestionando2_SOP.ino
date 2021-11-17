#include <Ticker.h>

#define POT1 A6
#define POT2 A5
#define LED1 4
#define LED2 5
#define Btn1 6
#define Btn2 7

int valor_led1 = 0;
int valor_led2 = 0;
int valor_pot = -1;
int valor_pot1;
int valor_pot2;
int valor_Btn1;
int valor_Btn2;

void fnLectura()
{
  int potenciometro1;
  int potenciometro2;
  int estadoBtn1 = digitalRead(Btn1);
  int estadoBtn2 = digitalRead(Btn2);
  potenciometro1 = analogRead(POT1);
  potenciometro2 = analogRead(POT2);
  valor_pot1 = potenciometro1;
  valor_pot2 = potenciometro2;
  valor_Btn1 = estadoBtn1;
  valor_Btn2 = estadoBtn2;
  
  Serial.println(String(valor_pot1) + "," + String(valor_pot2)+ "," + String(valor_Btn1)+ "," + String(valor_Btn2));
}
Ticker ticLectura(fnLectura,500);//la funcion fnPotenc se ejecuta cada 500 mS

void fnActuadores(String cadena)
{
  int pos;
  String etiqueta, valor;
  cadena.trim(); //se quitan espacios en blanco
  cadena.toLowerCase(); //convertir todas las letras a minusculas
  pos = cadena.indexOf(':'); //Se encuentra la posición de los puntos
  etiqueta = cadena.substring(0,pos);//se obtiene la etiqueta
  valor = cadena.substring(pos+1);//se obtiene el valor
  
  if (etiqueta.equals("led1")) //compara la etiqueta para saber si el LED1 es el que se debe encender
  {
    if(valor_led1 != valor.toInt())
    {
      valor_led1 = valor.toInt();  
      digitalWrite(LED1,valor_led1); 
    }
  }
  
  else if (etiqueta.equals("led2")) //compara la etiqueta para saber si el LED1 es el que se debe encender
  {
    if(valor_led2 != valor.toInt())
    {
      valor_led2 = valor.toInt();  
      digitalWrite(LED2,valor_led2); 
    }
  }
}

void setup() 
{
  Serial.begin(9600);
  delay(30);
  // config pines

  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(Btn1, INPUT_PULLUP);
  pinMode(Btn2, INPUT_PULLUP);

  //Valores iniciales
  digitalWrite(LED1,valor_led1);
  digitalWrite(LED2,valor_led2);

  ticLectura.start();
}

void loop() 
{
  ticLectura.update();
  //Lectura puerto serial
  if(Serial.available())
  {
    fnActuadores(Serial.readString());
  }
}

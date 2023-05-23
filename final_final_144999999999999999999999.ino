#include <Wire.h>//se llama la libreria Wire que nos ayudara a comunicarnos con el dispositivos de I2C
#include <LiquidCrystal_I2C.h>//se instala la libreria LiquidCrystal_I2C para trabajar con el i2c del lcd junto con el MÃ³dulo serial I2C
#include <Keypad.h>//se crea la libreria para iniciar el teclado matricial
#include <RTClib.h>//se instala y llama la libreria RTClib para poder utilizar el modulo RTC
#include <Servo.h>//se instala esta libreria para el servo motor

#define lcdAddress 0x27  //se indica la direcciÃ³n que toma el modulo i2c
#define filas 2//se indica que numero de filas que tiene el lcd que son dos para despues utilizarlo
#define columnas 16//se indica el numero de columnas que tiene el lcd que son 16 

const int pul1 = 2;//se indica que el pulador 1 ira al pin 2
const int cau = 4;//se indica que el pulador 2 ira al pin 4
int ser;//nos ayudara a poder ver el estado de los pulsadores
int lou;//nos ayudara a ver el estado de los pulsadores
int RS=10;//nos ayudara a la contabilización de los parqueos 
int ZK;//nos ayudara a la contabilización de los parqueos

LiquidCrystal_I2C pantallalcd(lcdAddress, columnas, filas);//se llama la libreria LiquidCrystal_I2C se le indica el nombre de pantallalcd se le indica la direcciÃ³n del lcd,la variable columnas y filas

Servo dota;//SE CREA LA VARIABLE PARA EL SERVO MOTOR
Servo jota;//SE CREA OTRA  VARIABLE PARA EL SERVO MOTOR}
RTC_DS3231 THC;//crea objeto del tipo RTC_DS3231

#define Epul_1() pinMode(pul1,INPUT);//se indica que Epul_1 va a cambiar al pinMode del pul1 que es entrada
#define Epul_2() pinMode(cau,INPUT); //se indica que Epul_2 va a cambiar al pinMode del pul2 que es entrada 

const int foto=6;//NO AYUDARA AL CONTROL DE PARQUEOS
const int led=7;//NO AYUDARA AL CONTROL DE PARQUEOS
int valor;
#define entrada()  pinMode(foto,INPUT);
#define salida() pinMode(led,OUTPUT);
void setup() {
  Epul_1();//solo se inicializa la función 
  Epul_2();//solo se inicializa la función 
  Serial.begin(9600);//se inicializa el monitor serial
 pantallalcd.init();//se indica que la pantallalcd que en eso se iniciara
 pantallalcd.backlight();//se indica que la pantallalcd para su iluminaciÃ³n
 THC.begin();//se inicializa el THC
 THC.adjust(DateTime(__DATE__, __TIME__));//funcion que permite establecer fecha y horario 
 dota.attach(3);//se indica en que pin se coloca
 jota.attach(5);//se indica en que pin se coloca
 entrada();
 salida();
}
void loop() {
  pantallalcd.setCursor(2,0);//que que fila va estar y que columna
  pantallalcd.print("PARQUEO THC");//que imprima el mensaje
  pantallalcd.setCursor(0,1);//que que fila va estar y que columna
  pantallalcd.print("DIS:");//que imprima el mensaje
  pantallalcd.print(RS);//que imprima el valor que este tenga
  pantallalcd.setCursor(9,1);//que que fila va estar y que columna
  pantallalcd.print("OCU:");//que imprima el mensaje
  pantallalcd.print(ZK);//que imprima el valor que este tenga
  dota.write(0);// que el servo simpre inice en 0  grados
  DateTime fecha = THC.now();//funcion que devuelve fecha y horario en formato
  ser = digitalRead(pul1);// que ser sea lo mismo que digitalRead(pul1)
  if(ser==HIGH && RS>0){//se se cumple nuestra condición que haga todo lo siguiente
    pantallalcd.clear();//que limpie todo lo escrito
    RS--;//que reste cada vez a esta variable
    ZK++;//que le sume cada vez a esta variable
    pantallalcd.setCursor(3,0);//que que fila va estar y que columna
    pantallalcd.print("BIENVENIDO");
    pantallalcd.setCursor(0,1);//se dise que en la columna 0 se imprima lo siguiente y que se coloque en la fila 0
    pantallalcd.print("ENTRADA:");
    pantallalcd.print(fecha.hour() );//funcion que obtiene la hora de la fecha completa
    pantallalcd.print(":");//caracter dos puntos como separador
    pantallalcd.print(fecha.minute());//funcion que obtiene los minutos de la fecha completa
    pantallalcd.print(":");//caracter dos puntos como separador
    pantallalcd.print(fecha.second());//funcion que obtiene los segundos de la fecha completa
    dota.write(90);//se indica los grados a moverse el servo motor
    delay(3000);//que se tome una pausa de 3 segundos
    dota.write(0);//que el servo regrese a 0
    pantallalcd.clear();//que limpie todo lo escrito
    Serial.print("ENTRADA:");//qie imprima el mensaje
    Serial.print(fecha.hour() );//funcion que obtiene la hora de la fecha completa
    Serial.print(":");//caracter dos puntos como separador
    Serial.print(fecha.minute());//funcion que obtiene los minutos de la fecha completa
    Serial.print(":");//caracter dos puntos como separador
    Serial.println(fecha.second());//funcion que obtiene los segundos de la fecha completa

  }else{
    if(ser==HIGH && RS==0){//se se cumple nuestra condición que haga todo lo siguiente
     pantallalcd.clear();//que limpie todo lo escrito
     pantallalcd.setCursor(2,0);//que que fila va estar y que columna
     pantallalcd.print("LO SENTIMOS");//que imprima el mensaje
     pantallalcd.setCursor(1,1);//que que fila va estar y que columna
     pantallalcd.print("ESTAMOS LLENOS");//que imprima el mensaje
     delay(2000);//que tome una pausa de 2 segundos
     pantallalcd.clear();//que limpie todo lo escrito
    
    }
  }
  
  lou=digitalRead(cau);//que lau sea lo mismo que digitalRead(cau)
  jota.write(0);//que inice simpre el servo en  grados
  if(lou==HIGH && RS<10){//se se cumple nuestra condición que haga todo lo siguiente
    RS++;//que le sume cada vez a esta variable
    ZK--;//que reste cada vez a esta variable
    pantallalcd.clear();//que limpie todo lo escrito
    pantallalcd.setCursor(2,0);//que que fila va estar y que columna
    pantallalcd.print("FELIZ VIAJE");//se imprime el mensaje
    pantallalcd.setCursor(0,1);//que que fila va estar y que columna
    pantallalcd.print("SALIDA:");//se imprime la salida
    pantallalcd.print( fecha.hour());//funcion que obtiene la hora de la fecha completa
    pantallalcd.print(":");//caracter dos puntos como separador
    pantallalcd.print(fecha.minute());//funcion que obtiene los minutos de la fecha completa
    pantallalcd.print(":");//caracter dos puntos como separador
    pantallalcd.print(fecha.second());//funcion que obtiene los segundos de la fecha completa
    jota.write(90);//se indica los grados a moverse el servo motor
    delay(3000);//se toma una pausa 
    jota.write(0);//los grados a lo que va el servo
    pantallalcd.clear();//que limpie todo lo escrito
    Serial.print("SALIDA:");//que imprima la salida
    Serial.print(fecha.hour() );//funcion que obtiene la hora de la fecha completa
    Serial.print(":");//caracter dos puntos como separador
    Serial.print(fecha.minute());//funcion que obtiene los minutos de la fecha completa
    Serial.print(":");//caracter dos puntos como separador
    Serial.println(fecha.second());//funcion que obtiene los segundos de la fecha completa
  }else{}

  valor=digitalRead(foto);//indicamos que valor va a hacer lo mismo que el digitalRead
  if(valor==LOW){//si cumple la condición va a realizar lo siguiente
    digitalWrite(led,HIGH);//se se cumple esto la led se encendera
    delay(100);//se tome un tiempo 
  }else{//si no hace esto 
    digitalWrite(led,LOW);//el led estara apagdo 
    delay(100);//se tome un tiempo

  }
}



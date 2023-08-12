/*PROJETO DE CONTROLE DE UM MOTOR E SUAS RESPECTIVAS SINALIZAÇÕES,
DE ACORDO COM A DISTÂNCIA DE RETORNO DO SENSOR ULTRASSÔNICO HC-SR04 APRESENTADA NO DISPLAY LCD
*/

#include "Ultrasonic.h" //INCLUSÃO DA BIBLIOTECA DO SENSOR HC-SR04
#include <LiquidCrystal.h> //INCLUSÃO DA BIBLIOTECA DO LCD

//DEFINIÇÃO DOS PINOS DOS PERIFÉRICOS
#define ledvd 40
#define ledam 41
#define ledvm 46
#define K1 51

const int echoPin = 31; //PINO DIGITAL UTILIZADO PELO HC-SR04 ECHO(RECEBE)
const int trigPin = 30; //PINO DIGITAL UTILIZADO PELO HC-SR04 TRIG(ENVIA)
int sinal; //VARIÁVEL DE 16 BITS

Ultrasonic ultrasonic(trigPin, echoPin); //INICIALIZANDO OS PINOS DO ARDUINO EM QUE O ECHO E TRIG ESTÃO CONCTADOS
LiquidCrystal lcd (8, 9, 4, 5, 6, 7);//MAPEAMENTO/PINAGEM DO LCD

int distancia; //VARIÁVEL DE 16 BITS
String result; //VARIÁVEL DO TIPO STRING
int resultadoLed; //VARIÁVEL DE 16 BITS



//MÉTODO RESPONSÁVEL POR CALCULAR A DISTÂNCIA
void hcsr04() {
  digitalWrite(trigPin, 0); 
  delayMicroseconds(2); 
  digitalWrite(trigPin, 1); 
  delayMicroseconds(10); 
  digitalWrite(trigPin, 0); 
  distancia = (ultrasonic.Ranging(CM));
  result = String(distancia); 
}


//FUNÇÃO DE INICIALIZAÇÃO DO SISTEMA
void setup() {
  pinMode(echoPin, INPUT); //DEFINE O PINO COMO ENTRADA (RECEBE)
  pinMode(K1, OUTPUT);
  pinMode(trigPin, OUTPUT); //DEFINE O PINO COMO SAIDA (ENVIA)
  pinMode(ledvd, OUTPUT);
  pinMode(ledam, OUTPUT);
  pinMode(ledvm, OUTPUT);
  lcd.begin(16, 2);
  Serial.begin(9600); //INICIALIZA A PORTA SERIAL
}

//Função de repetição acoplada com o controle de motores e suas respectivas sinalizações
void loop()
{
  hcsr04(); 
  Serial.print("Distancia "); 
  Serial.print(result); 
  Serial.println("cm"); 
  lcd.setCursor(0, 0);
  lcd.print("Distancia: ");
  lcd.print(result);
  lcd.print("cm");
  delay(500);
  lcd.clear();
  resultadoLed = result.toInt();

  if (resultadoLed == 0 || resultadoLed <= 100) {
    digitalWrite(ledvd, 1);
    digitalWrite(ledam, 0);
    digitalWrite(ledvm, 0);
    digitalWrite(K1, 0);
  }

  else  if (resultadoLed > 100 || resultadoLed <= 300) {
    digitalWrite(ledvd, 0);
    digitalWrite(ledam, 1);
    digitalWrite(ledvm, 0);
    digitalWrite(K1, 1);
  }

  if (resultadoLed > 300) {
    digitalWrite(ledvd, 0);
    digitalWrite(ledam, 0);
    digitalWrite(ledvm, 1);
    digitalWrite(K1, 1);
  }
}

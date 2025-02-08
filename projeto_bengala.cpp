//Carrega a biblioteca do sensor ultrassonico
#include < ultrasonic.h>
 
#define INTERVALO_LEITURA 250 //(ms)
 
//definição dos PINOS que utilizaremos para os LEDS e o BUZZER
#define PIN_BLUE_LED    16
#define PIN_GREEN_LED   17
#define PIN_YELLOW_LED  18
#define PIN_RED_LED     19
#define PIN_BUZZER      21
 
//variável responsável por armazenar a distância lida pelo sensor ultrassônico
unsigned int distancia = 0;

//conexão dos pinos para o sensor ultrasonico
#define PIN_TRIGGER   4
#define PIN_ECHO      5
 
//Inicializa o sensor nos pinos definidos acima
Ultrasonic ultrasonic(PIN_TRIGGER, PIN_ECHO);
 
// Module connection pins (Digital Pins)
#define CLK 14
#define DIO 13

void setup()
{
  Serial.begin(9600);
 
  configurarPinos();
   
  Serial.println("Setup...");
}

/*
  CONFIGURA O MODOS DE CADA UM DOS PINOS QUE UTILIZAREMOS COMO SAIDA
*/
void configurarPinos()
{
  pinMode(PIN_BLUE_LED,   OUTPUT);
  pinMode(PIN_GREEN_LED,  OUTPUT);
  pinMode(PIN_YELLOW_LED, OUTPUT);
  pinMode(PIN_RED_LED,    OUTPUT);
  pinMode(PIN_BUZZER,     OUTPUT);  
}

void loop()
{
  verificarDistancia();
  delay(INTERVALO_LEITURA);
}

/*
  FAZ A LEITURA DA DISTANCIA ATUAL CALCULADA PELO SENSOR
*/
int getDistance()
{
    //faz a leitura das informacoes do sensor (em cm)
    int distanciaCM;
    long microsec = ultrasonic.timing();
    // pode ser um float ex: 20,42 cm se declarar a var float
    distanciaCM = ultrasonic.convert(microsec, Ultrasonic::CM);
 
    return distanciaCM;
}

/*
  VERIFICA A DISTANCIA ATUAL QUE O SENSOR ULTRASONIC ESTA LENDO
  E EM SEGUIDA, IMPRIME O VALOR NO DISPLAY, E ACENDE O LED CORRESPONDENTE
*/
void verificarDistancia()
{
 
    //recupera a distância atual lida pelo sensor
    distancia = getDistance();
 
 
//esse FOR tem como objetivo apagar todos os LEDS que estejam acesos.
  for(int i=PIN_BLUE_LED; i<=PIN_RED_LED; i++)
  {
    digitalWrite(i, LOW);    
  }
 
  //desliga o BUZZER
  digitalWrite(PIN_BUZZER, LOW);
 
 
//caso a distancia lida seja menor ou igual a 5, tomaremos como uma distância de perigo
  //então acenderemos o LED VERMELHO e ligaremos o BUZZER
  if( distancia <= 5 )
  {
    digitalWrite(PIN_RED_LED, HIGH);
    digitalWrite(PIN_BUZZER, HIGH);
  }
  //caso a distancia seja maior que 5 e menor ou igual a 20,
  //tomaremos como uma distância de atenção, e ligaremos o LED AMARELO
  else if(distancia <=20)
  {
    digitalWrite(PIN_YELLOW_LED, HIGH);
  }
  //caso a distancia seja maior que 20 e menor ou igual a 40,
  //tomaremos como uma distância segura, e ligaremos o LED VERDE
  else if(distancia <= 40)
  {
    digitalWrite(PIN_GREEN_LED, HIGH);
  }
  //para distâncias maiores que 40, tomaremos como uma distância sem perigo
  //acenderemos o LED AZUL para indicar
  else
  {
    digitalWrite(PIN_BLUE_LED, HIGH);
  }
}  
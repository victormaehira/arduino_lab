//Carrega a biblioteca do servo motor
#include <Servo.h>

//Carrega a biblioteca do sensor ultrassônico
#include <Ultrasonic.h>

// Define o pino para o servo (Porta PWM)
#define SERVO 6 

//Define os pinos para o trigger e echo
#define pino_trigger 4
#define pino_echo 5

//Inicializa o sensor nos pinos definidos acima
Ultrasonic ultrasonic(pino_trigger, pino_echo);
Servo servo;

//Le as informacoes do sensor, em cm e pol
float cmMsec;

byte contator = 0;

void setup () {
pinMode(13, OUTPUT);
Serial.begin(57600);
servo.attach(SERVO);
servo.write(90);
}

void loop()
{
  //Le as informacoes do sensor, em cm e pol
  cmMsec = ultrasonic.convert(ultrasonic.timing(), Ultrasonic::CM);
  
  if(cmMsec < 10.0) {
      contator = contator + 1;
    if (contator > 5){
      delay(300);
      
      servo.write(40);
      notificaLiberacao();
  
      delay(500);
      servo.write(90);
      
      delay(1000);
      contator = 0;
    }
  } else{
      contator = 0;
  }
  delay(100);
}

void notificaLiberacao() {
  Serial.println("{\"deviceUUID\":\"Sala-VictorSP\",\"model\":\"Bootcamp Fiap\",\"action\":\"Acionado\"}");
}
const int IN3 = 5 ; // Inpu t3 puente H c onec t ad a a l pin 7 Arduino
const int IN4 = 6 ; // Input4 puente H c onec t ad a a l pin 8 Arduino
const int EPinA = 2 ; // Am a rill o Encoder c onec t ad a a l pin 2 Arduino
const int EPinB = 3 ; // Verde Encoder c onec t ad a a l pin 3 Arduino
volatile int count=0 ;
volatile int ISRCounter = 0 ;

void setup ( ){
  SREG = (SREG & 0b01111111 ) ; // Desabilitar interrupciones
  TIMSK2 = TIMSK2 | 0b00000001 ; // Habilita interrupcion por desbordamiento
  TCCR2B = 0b00000011 ; // Configura preescala para que FT2 sea de 250KHz
  TCNT2 = 0b00000101 ; // pre−cargar valor inicial el registro contador
  SREG = (SREG & 0b01111111 ) | 0b10000000 ; // Habilitar−Desabilitar interrup
  pinMode ( IN3 , OUTPUT) ;
  pinMode ( IN4 , OUTPUT) ;
  pinMode (EPinA , INPUT_PULLUP) ;
  Serial.begin (115200) ;
  attachInterrupt (digitalPinToInterrupt (EPinA ) , doEncode , CHANGE) ;
}

void loop( ){
  
}

//−−−−−−−−RUTINA DE INTERRUPCIN POR TIMER−−−−−−−−−
//−−−−−−−−−−−−−−SE REALIZA CADA 1ms−−−−−−−−−−−−−−−−
ISR (TIMER2_OVF_vect ){
  TCNT2 = 13 ;
  if( count<6001 ) {
    count++;
    if( count%2==0 )
    Serial.println( ISRCounter );
  }
  if ( count>=0 && count<=2000 ) {
    digitalWrite(IN3 ,HIGH);
    digitalWrite(IN4 ,LOW);
  }
  else if(count>=2001 && count<=4000){
    digitalWrite(IN3 ,LOW);
    digitalWrite(IN4 ,LOW);
    ISRCounter=0;
  }
  else if ( count>=4001 && count<=6000 ) {
    digitalWrite(IN3 ,HIGH);
    digitalWrite(IN4 ,LOW);
  }
  else{
    digitalWrite(IN3 ,LOW);
    digitalWrite(IN4 ,LOW);
  }
}

//−−−−−−−−RUTINA DE INTERRUPCI N POR CAMBIO DE VALOR−−−−−−−−−
void doEncode (){
  if(digitalRead(EPinA)^ digitalRead(EPinB)) {
    ISRCounter++;
  }
  else{
    ISRCounter--;
  }
}
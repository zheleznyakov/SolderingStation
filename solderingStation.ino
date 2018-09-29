struct heater
{
  int portNumber;
  int dimming;
  bool endWork;
};
volatile bool zeroCross = 0;
unsigned long zeroTime = 0;
unsigned long currentTime = 0;
heater HEAT_UP = {8,128,0};
heater HEAT4 = {9,128,0};
heater HEAT3 = {10,128,0};
heater HEAT2 = {11,128,0};
heater HEAT1 = {12,128,0};

void setup()
{
  pinMode(HEAT_UP.portNumber, OUTPUT);
  pinMode(HEAT4.portNumber, OUTPUT);
  pinMode(HEAT3.portNumber, OUTPUT);
  pinMode(HEAT2.portNumber, OUTPUT);
  pinMode(HEAT1.portNumber, OUTPUT);
  setDimming(100,30,60,90,120);
  attachInterrupt(0, zero_crosss_int, RISING);
}
void zero_crosss_int()
{
  zeroCross = true;
}
void setDimming(int up,int heat4,int heat3, int heat2, int heat1)
{
  HEAT_UP.dimming = up;
  HEAT4.dimming = heat4;
  HEAT3.dimming = heat3;
  HEAT2.dimming = heat2;
  HEAT1.dimming = heat1;
}
void loop()
{
  int elapsedTime;
  currentTime = micros();
  if (zeroCross)
  {
    zeroTime = currentTime;
    HEAT_UP.endWork = false;
    HEAT4.endWork = false;
    HEAT3.endWork = false;
    HEAT2.endWork = false;
    HEAT1.endWork = false;
  }
  
  elapsedTime = currentTime - zeroTime;
  //снимим управляющий сигнал со всех отработавших семисторов
  if (HEAT_UP.dimming*75+10<=elapsedTime && HEAT_UP.endWork ==true){
      digitalWrite(HEAT_UP.portNumber,LOW);  
  }
  if (HEAT4.dimming*75+10<=elapsedTime && HEAT4.endWork == true){
      digitalWrite(HEAT4.portNumber,LOW);  
  }
  if (HEAT3.dimming*75+10<=elapsedTime && HEAT3.endWork == true){
      digitalWrite(HEAT3.portNumber,LOW);  
  }
  if (HEAT2.dimming*75+10<=elapsedTime && HEAT2.endWork == true){
      digitalWrite(HEAT2.portNumber,LOW);  
  }
  if (HEAT1.dimming*75+10<=elapsedTime && HEAT1.endWork == true){
      digitalWrite(HEAT1.portNumber,LOW);  
  }
  
  // включим симисторы, для которых подошло время включения
  if (HEAT_UP.dimming*75<=elapsedTime && HEAT_UP.endWork == false){
      digitalWrite(HEAT_UP.portNumber,HIGH);
      HEAT_UP.endWork = true;
  }
  if (HEAT4.dimming*75<=elapsedTime && HEAT4.endWork == false){
      digitalWrite(HEAT4.portNumber,HIGH);
      HEAT4.endWork = true;
  }
  if (HEAT3.dimming*75<=elapsedTime && HEAT3.endWork == false){
      digitalWrite(HEAT3.portNumber,HIGH);
      HEAT3.endWork = true;
  }
  if (HEAT2.dimming*75<=elapsedTime && HEAT2.endWork == false){
      digitalWrite(HEAT2.portNumber,HIGH);
      HEAT2.endWork = true;
  }
  if (HEAT1.dimming*75<=elapsedTime && HEAT1.endWork == false){
      digitalWrite(HEAT1.portNumber,HIGH);
      HEAT1.endWork = true;
  }  
}


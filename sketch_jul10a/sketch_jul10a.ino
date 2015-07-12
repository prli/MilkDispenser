#include <Valve.h>

Valve dc_valve(3, 2, 4);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  dc_valve.init();
}

char* readSerialLine(){
   static char buffer[256] = {0};
   int i = 0;
   int8_t temp = 0;
   
   while(!(Serial.available() > 0)){}
  
   temp = Serial.read();   
   while(temp != 0x0D){
       if(temp > 0){
           if (temp == 0x08 || temp == 0x7F){
              if(i != 0){
                 Serial.write(temp);
                 i --;
              }
           }else{
             if (i < 256){
                 buffer[i] = temp;
                 Serial.write(buffer[i]);
                 i ++;
             }else{
                 Serial.println("\r\nBuffer Overflow!");
                 return 0;
             }
          }
       }
       temp = Serial.read();
   }
   
   Serial.write("\r\n");
   buffer[i] = '\0';
   
   return buffer;
}

#define NEUTRAL   7

#define phTest1   4.3

void loop() {
  // put your main code here, to run repeatedly:
//  char* returnValue;
//  Serial.println("Enter valve state:");
//  returnValue = readSerialLine();

//  Serial.println("Enter to start:");
//  char* s = readSerialLine();
//  
//  bool state = atoi(s) == 1;
//  dc_valve.setRate(state);
//  unsigned long beginTime = micros();
//  
//  Serial.println("Enter to end:");
//  char* pHValue = readSerialLine();
//  dc_valve.setRate(state);
//  unsigned long endTime = micros();
//  Serial.println("time in micro:" +  endTime-beginTime);

  Serial.println("Enter target pH:");
  char* pHValue = readSerialLine();
  double pH = atof(pHValue);
  unsigned int delayTime = 0;
  if(pH == phTest1)
  {
    delayTime = 1000;
  }
  else if(pH >= 5.5 )
  {
    Serial.println("Sorry, pH too high to reach");
  }
  else if(pH >= 5.25 && pH < 5.5 )
  {
    delayTime = 10;
  }
  else if(pH >= 5 && pH < 5.25 )
  {
    delayTime = 40;
  }
  else if(pH >= 4.75 && pH < 5 )
  {
    delayTime = 100;
  }
  else if(pH >= 4.5 && pH < 4.75 )
  {
    delayTime = 400;
  }
  else if(pH >= 4.25 && pH < 4.5 )
  {
    delayTime = 1000;
  }
  else if(pH >= 4 && pH < 4.25 )
  {
    delayTime = 3000;
  }
  else if(pH >= 3.75 && pH < 4 )
  {
    delayTime = 6000;
  }
  else if(pH >= 3.5 && pH < 3.75 )
  {
    delayTime = 10000;
  }
  else if(pH >= 3.25 && pH < 3.5 )
  {
    delayTime = 40000;
  }
  else if(pH >= 3 && pH < 3.25 )
  {
    delayTime = 100000;
  }
  else
  {
    Serial.println("sorry, pH is too low to reach");
  }

  if(delayTime != 0)
  {
    dc_valve.setRate(1);
  //  delayMicroseconds(delayTime);
    delay(delayTime);
    dc_valve.setRate(0);
  }
}

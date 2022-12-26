/*        Your Name & E-mail: Shashwath Gunasekaran

*          Discussion Section: 021

 *         Assignment: Final Project

 *         Exercise Description: [optional - include for your own benefit]

 *        

 *         I acknowledge all content contained herein, excluding template or example code, is my own original work.

 *

 *         Demo Link 1: https://www.youtube.com/watch?v=JhG9Bn_G15k
           Demo Link 2: https://www.youtube.com/watch?v=HCMBpplHjoU

 */

#include <SoftwareSerial.h>  // Library Allowed by TA
#include <SPI.h>

SoftwareSerial bluetooth_mod(2,3);


int DC = 7;
int RST = 9;
int CE = A2;

int pin1 = 6;
int pin2 = 7;
int H;
int L;
int count = 0;
int count1 = 0;
int input_signal;
int recieve_signal;
int mode;

typedef struct task 
{
  int state;
  unsigned long period;
  unsigned long elapsedTime;
  int (*TickFct)(int);

} task;

int delay_gcd;
const unsigned short tasksNum = 3;
task tasks[tasksNum];

enum bluetooth_input_states {bluetooth_INIT, bluetooth_SAMPLE};
int bluetooth_input(int state1) 
{
  switch (state1) 
  { // State transitions
    case bluetooth_INIT:
      state1 = bluetooth_SAMPLE;
      break;

    case bluetooth_SAMPLE:
      if (bluetooth_mod.available())
      {
          input_signal = bluetooth_mod.read();
          Serial.println("DATA RECEIVED:");

          if(input_signal == '3')
          {
              recieve_signal = 3;
               
          }

          if(input_signal == '2')
          {
              recieve_signal = 2;
              
              
          }

          if(input_signal == '1')
          {
              recieve_signal = 1;
              
          }

          if(input_signal == '0')  // TURN OFF FAN
          {
             recieve_signal = 0;
            
             
          }

      }

      //state1 = SM1_SAMPLE;

      break;
  

  }
  switch (state1) 
  { // State Action
    case bluetooth_INIT:
      break;
    case bluetooth_SAMPLE:
      break;
  
  }

  return state1;
}

enum _States { SM2_INIT, SM2_SAMPLE, SM2_SPIN_MOTOR};
int SM2_Tick(int state2) {
  switch (state2) 
  { // State transitions
    case SM2_INIT:
      state2 = SM2_SAMPLE;
      break;

    case SM2_SAMPLE:
      if (recieve_signal == 3)
      {
          H = 90;
          L = 10;   
          mode = 3;
      }

      if (recieve_signal == 2)
      {
          H = 60;
          L = 40;
          mode = 2;
      }

      if (recieve_signal == 1)
      {
          H = 20;
          L = 80; 
          mode = 1;     
      }

      if (recieve_signal == 0)
      {
          H = 0;
          L = 100;
      }

      state2 = SM2_SPIN_MOTOR;
      break;

    case SM2_SPIN_MOTOR:

      state2 = SM2_SAMPLE;

      break;

  }
  switch (state2) 
  { // State Action
    case SM2_INIT:
      break;

    case SM2_SAMPLE:
      if (count <= H)
      {
        digitalWrite(pin1, HIGH);
        count++;
      }

      else if (count > H)
      {
        if (count1 <= L)
        {
          digitalWrite(pin1, LOW);
          count1++;
        }

        else if (count1 > L)
        {
          count = 0;
          count1 = 0;
          
        }
      }
      break;

  }

  return state2;
}

enum SM3_States { SM3_INIT, SM3_WRITE};
int SM3_Tick(int state3) 
{
  switch(state3)
  {
    case SM3_INIT:
      state3 = SM3_WRITE;
      break;

    case SM3_WRITE:
      if (mode == 1)
      {
          for (int i = 0; i < 504; i++)
          {
            digitalWrite(DC, 1);
            SPI.transfer(0x00);
          }

          digitalWrite(DC, 0);
          SPI.transfer(0x40);
          SPI.transfer(0x80);

          
          digitalWrite(DC, 1);
          SPI.transfer(0xFF);
          SPI.transfer(0xFF);

          SPI.transfer(0x80);
          SPI.transfer(0x80);
          SPI.transfer(0x80);
          SPI.transfer(0x80);
          SPI.transfer(0x80);
          SPI.transfer(0x80);
          SPI.transfer(0x00);
          SPI.transfer(0x00);
          SPI.transfer(0xFF);
          SPI.transfer(0xFF);
          SPI.transfer(0x81);
          SPI.transfer(0x81);
          SPI.transfer(0x81);
          SPI.transfer(0x81);
          SPI.transfer(0x81);
          SPI.transfer(0xFF);
          SPI.transfer(0xFF);
          SPI.transfer(0x00);
          SPI.transfer(0x00);
          SPI.transfer(0x00);
          SPI.transfer(0x01);
          SPI.transfer(0x02);
          SPI.transfer(0x04);
          SPI.transfer(0x08);
          SPI.transfer(0x10);
          SPI.transfer(0x20);
          SPI.transfer(0x40);
          SPI.transfer(0x20);
          SPI.transfer(0x10);
          SPI.transfer(0x20);
          SPI.transfer(0x40);
          SPI.transfer(0x20);
          SPI.transfer(0x10); 
          SPI.transfer(0x08);
          SPI.transfer(0x04);
          SPI.transfer(0x02);
          SPI.transfer(0x01);

      }

      

    if (mode == 2)
      {
         for (int i = 0; i < 504; i++)
          {
            digitalWrite(DC, 1);
            SPI.transfer(0x00);
          }
          

          digitalWrite(DC, 0);
          SPI.transfer(0x40);
          SPI.transfer(0x80);

          digitalWrite(DC, 1);
          SPI.transfer(0xFF);
          SPI.transfer(0x01);
          SPI.transfer(0x02);
          SPI.transfer(0x04);
          SPI.transfer(0x08);
          SPI.transfer(0x04);
          SPI.transfer(0x02);
          SPI.transfer(0x01);
          SPI.transfer(0xFF);
          SPI.transfer(0x00);
          SPI.transfer(0x00);

          SPI.transfer(0xFF);
          SPI.transfer(0x89);
          SPI.transfer(0x89);
          SPI.transfer(0x89);
          SPI.transfer(0x89);
          SPI.transfer(0x89);
          SPI.transfer(0x89);
          SPI.transfer(0x00);
          SPI.transfer(0x00);

          SPI.transfer(0xFF);
          //SPI.transfer(0xFF);
          SPI.transfer(0x81);
          SPI.transfer(0x42);
          SPI.transfer(0x24);
          SPI.transfer(0x18);

          SPI.transfer(0x00);
          SPI.transfer(0x00);

          SPI.transfer(0x81);
          SPI.transfer(0x81);
          SPI.transfer(0xFF);
          SPI.transfer(0x81);
          SPI.transfer(0x81);

          SPI.transfer(0x00);
          SPI.transfer(0x00);

          SPI.transfer(0xFF);
          SPI.transfer(0x80);
          SPI.transfer(0x80);
          SPI.transfer(0x80);
          SPI.transfer(0x80);
          SPI.transfer(0x80);
          SPI.transfer(0xFF);

          SPI.transfer(0x00);
          SPI.transfer(0x00);

          SPI.transfer(0xFF);
          SPI.transfer(0x01);
          SPI.transfer(0x02);
          SPI.transfer(0x04);
          SPI.transfer(0x08);
          SPI.transfer(0x04);
          SPI.transfer(0x02);
          SPI.transfer(0x01);
          SPI.transfer(0xFF);
          SPI.transfer(0x00);
          SPI.transfer(0x00);
          

          
      }

    if (mode == 3)
      {
  
          for (int i = 0; i < 504; i++)
          {
            digitalWrite(DC, 1);
            SPI.transfer(0x00);
          }
          

          digitalWrite(DC, 0);
          SPI.transfer(0x40);
          SPI.transfer(0x80);
          

          digitalWrite(DC, 1);
          SPI.transfer(0xFF);
          SPI.transfer(0x10);
          SPI.transfer(0x10);
          SPI.transfer(0x10);
          SPI.transfer(0x10);
          SPI.transfer(0x10);
          SPI.transfer(0xFF);

          SPI.transfer(0x00);
          SPI.transfer(0x00);
          SPI.transfer(0x81);
          SPI.transfer(0x81);
          SPI.transfer(0xFF);
          SPI.transfer(0x81);
          SPI.transfer(0x81);

          SPI.transfer(0x00);
          SPI.transfer(0x00);

          SPI.transfer(0xFF);
          SPI.transfer(0x81);
          SPI.transfer(0x91);
          SPI.transfer(0x91);
          SPI.transfer(0xF1);

          SPI.transfer(0x00);
          SPI.transfer(0x00);
          SPI.transfer(0xFF);
          SPI.transfer(0x10);
          SPI.transfer(0x10);
          SPI.transfer(0x10);
          SPI.transfer(0x10);
          SPI.transfer(0x10);
          SPI.transfer(0xFF);

      }


      state3 = SM3_WRITE;
      break;


  }

  return state3;
}




void setup() {
  // put your setup code here, to run once:
  pinMode(pin1, OUTPUT);
  pinMode(pin2, OUTPUT);

  Serial.begin(9600);
  bluetooth_mod.begin(9600);

  pinMode(RST, OUTPUT); //RST
  pinMode(DC, OUTPUT); //DC 
  pinMode(CE, OUTPUT); //CE
  SPI.begin();
  
  digitalWrite(CE, HIGH);
  delay(5);
  digitalWrite(RST, 0);
  delay(100);
  digitalWrite(RST, 1);

    
  digitalWrite(CE, LOW);
  digitalWrite(DC, 0); //DC
  SPI.transfer(0x21);
  delay(5);
  SPI.transfer(0x90);
  delay(5);
  SPI.transfer(0x20);
  delay(5);
  SPI.transfer(0x0C);
  delay(5);


  unsigned char i = 0;
  tasks[i].state = bluetooth_INIT;
  tasks[i].period = 1;
  tasks[i].elapsedTime = 0;
  tasks[i].TickFct = &bluetooth_input;
  i++;
  tasks[i].state = SM2_INIT;
  tasks[i].period = 1;
  tasks[i].elapsedTime = 0;
  tasks[i].TickFct = &SM2_Tick;

  i++;
  tasks[i].state = SM3_INIT;
  tasks[i].period = 100;
  tasks[i].elapsedTime = 0;
  tasks[i].TickFct = &SM3_Tick;
  
  

  delay_gcd = 1; // GCD
}

void loop() {
  unsigned char i;
  for (i = 0; i < tasksNum; ++i) {
    if ( (millis() - tasks[i].elapsedTime) >= tasks[i].period) {
      tasks[i].state = tasks[i].TickFct(tasks[i].state);
      tasks[i].elapsedTime = millis(); // Last time this task was ran
    }
  }
}

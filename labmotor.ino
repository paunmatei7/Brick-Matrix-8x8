#include "LedControl.h"
LedControl lc = LedControl(12,11,10,1); // 

 int stdValue = 55;
 int joyPin1 = 0; // slider variable connecetd to analog pin 0
 int joyPin2 = 1; // slider variable connecetd to analog pin 1
 int buttonPin = 6;
 int value1 = 0;// variable to read the value from the analog pin 0
 int value2 = 0;// variable to read the value from the analog pin 1
 byte Start = 0;
  int  row = 0, col = 4;
 int timpIntreLinii = 7000, previousScor = 0;
 unsigned long previousMillis2 = 0, previousMillisR = 0;
 
 unsigned long prevMillis = 0;
 byte state[10][10];
 byte waitSignal = 0;
 int numRows = 0, scor = 0, ok = 0;
 
void setup() { 
  pinMode(buttonPin, INPUT);
  lc.shutdown(0,false);// turn off power saving, enables display
  lc.setIntensity(0,8);// sets brightness (0~15 possible values)
  lc.clearDisplay(0);// clear screen
  Serial.begin(9600);
 }
 
 void loop() {
  if (waitSignal == 0)      
    mesajStart();
    else 
    if (waitSignal == 1 && Start == 1) {
        mesajStartOff();
        Serial.println("jocul a inceput!");
      }
      else
      if (waitSignal == 1) {
        cob();
        dif();    
        CheckAlive(); 
      }
      else {
        if(waitSignal == 3) {
          Serial.print("GAME OVER. scor final: ");
          Serial.println(scor);
          waitSignal = 0;
          scor = 0;
        }
      }
 
  command();       
  check();             
}

void mesajStart() {
  lc.clearDisplay(0);
  for (int i = 3; i <= 5; ++i) {
     lc.setLed(0, 1, i, true);
     lc.setLed(0, 3, i, true);
     lc.setLed(0, 5, i, true);
    }
  lc.setLed(0, 2, 4, true);
  Start = 1;
  delay(2000);
 }

 void mesajStartOff() {
  lc.clearDisplay(0);
  Start = 0;
 }
 void shoot(int coloana) {
  unsigned long currentMillis = millis();
  int contor = 0;
   for (int row1 = 1; row1 <= 7; ++row1) {
     if (state[coloana][row1] == 0) {
      lc.setLed(0, coloana, row1, true); // turns on LED at coloana, row
     }
   }

   for (int row1 = 1; row1 <= 7; ++row1) {
     if (state[coloana][row1] == 0) {
       lc.setLed(0,coloana,row1,false);
     }
   }
  
   state[coloana][8] = 1;
   for (int row1 = 1; row1 <= 8; ++row1) {
      if (state[coloana][row1] == 1) {
         lc.setLed(0, coloana, row1 - 1, true);
         state[coloana][row1 - 1] = 1;
         break;
        }
   }
}

int treatValue(int data) {
  return (data * 9 / 1024) + 48;
 }

void command() {   //interpretarea datelor primite de la joystick
  unsigned long currentMillis = millis();
  
   lc.setLed(0, col, row, true);
   state[col][row] = 1;
   value1 = analogRead(joyPin1);   
   if (millis() - previousMillisR >= 150) {
    value2 = analogRead(joyPin2); 
     previousMillisR = millis();

     if (treatValue(value1) != stdValue || treatValue(value2) != stdValue) {
      waitSignal = 1;
     }
     
       lc.setLed(0, col, row, false);
       state[col][row] = 0;
       if (treatValue(value1) > stdValue) {
         col++;  
       }
         else
         if (treatValue(value1) < stdValue) {
          col--; 
         }
     
       if (col == 8) {
           col = 7;
       }
       if (col == -1) {
           col = 0;
       }
    
   
     if (treatValue(value2) < stdValue) {
         shoot(col); 
     }
         
     lc.setLed(0, col, row, true);
     state[col][row] = 1;
     CheckAlive();      
    }
 }

void CheckAlive() {
  for(int i = 0; i <= 7; ++i) {
  if (state[i][1] == 1) {
      for(int j = 0; j <= 7; ++j) {
        for(int k = 0; k <= 7; ++k) {
          state[j][k] = 0;
        }
      }
      waitSignal = 3;
  }
  }
}

 void gen() {
   //generam un n intre 4 si 7
   int n = rand()%4;
   n += 4;
   int i = 0;
   while (i < n) {
        int j = rand()%8;
        lc.setLed(0, j, 7, true);
        state[j][7] = 1;
        i++;
       }
 numRows++;
}

void cob() {
 //dupa fiecare timpIntreLinii secunde, fiecare linie cade cu o pozitie
  unsigned long currentMillis = millis();
  int lastRow = 8 - numRows;

  if (currentMillis - previousMillis2 >= timpIntreLinii || ok == 2) { 
    for (int i = lastRow; i <= 7; ++i)
      for (int j = 0; j <= 7; j++) {
        state[j][i - 1] = state[j][i];
        lc.setLed(0, j, i, false);
        state[j][i] = 0;
        if (state[j][i - 1] == 1)
          lc.setLed(0, j, i - 1, true);
       }
   gen();
   previousMillis2 = currentMillis;
   }
 }

 void acoperaGol(int fullRow) {
  for (int x = fullRow; x >= 1; x--)
    for (int j = 0; j <= 7; j++)
        if (state[j][x] == 1) {
             lc.setLed(0,j,x,false);
             state[j][x] = 0;
            }
 }

 void check() {
  //daca toate ledurile unui rand sunt aprinse, sterge linia si numRows--. scor++
   for (int i = 1; i <= 7; ++i)
    {
     ok = 1;
     for (int j = 0; j <= 7; ++j) {
        if (state[j][i] == 0) {
          ok = 0;
        } 
     }
     if (ok == 1) {  //inseamna ca toate ledurile unui rand sund aprinse
        acoperaGol(i);
         numRows--;
         scor++;
         for (int k = 0; k <= 7; k++) {
           lc.setLed(0, k, i, false);
           state[k][i] = 0;
           }
         Serial.print("scor: ");
         Serial.println(scor);
         ok = 2;
        }
    }    
 }

 void dif() {
  unsigned long currentMillis = millis();
  if (scor - previousScor == 3) {
     previousScor = scor;
     timpIntreLinii -= 1000;
     Serial.println("next level!");
     }
  if (timpIntreLinii <= 0) {
      waitSignal = 3;
  }
 }

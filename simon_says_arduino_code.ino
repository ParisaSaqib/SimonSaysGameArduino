int ldAr[] = {11, 10, 5, 3};

  

int BNAr[] = {9, 12, 6, 7};

  

int PCt = 4; 
  

int BZZ = 8;  

  

   

  

int ledState = 0;  

  

int gameState = 0;  

  

   

  

#define NUMBERTOWIN 5
int gameValues[NUMBERTOWIN];  

  

int NMofRN = 0;  

  

   

  

unsigned long previousMillis = 0; 
unsigned long interval1 = 500;

void setLed(int ledNum);  

  

void displayClue(int NMofRN);  

  

boolean waitForInput(int buttonNum);  

  

   

  

void setup () {  

  

Serial.begin(9600);  

  

   

  

Serial.println("setup");  

  

   

  

  for(int Pin = 0; Pin < PCt; Pin++)
  {  



  pinMode(ldAr[Pin], OUTPUT);  

  

  }  

  

      

  

  for(int Pin = 0; Pin < PCt; Pin++)  

  

  {  

  pinMode(BNAr[Pin], INPUT_PULLUP);  

  

  }  
  

  

randomSeed(analogRead(0));  

  

}  


void loop () {  

  

    

  

  if (gameState == 0)  

  

  {  

  

     int button0 = digitalRead(BNAr[0]);  

  

     int button1 = digitalRead(BNAr[1]);    

  

     int button2 = digitalRead(BNAr[2]);   

  

     int button3 = digitalRead(BNAr[3]);   

  

       

  

  

    if (button0 && button1 && button2 && button3)  

  

    {  

  

      pre_game();  

  

    }  

  


    else  

  

    {  

  

      Serial.println("button Pressed");   

  


  

      setLed(-1);  

 

  

      NMofRN = 0;  

  

      delay (1000);  

    

  

      gameState = 1;  

  

    }  

  

  }  

  

   

  

  if (gameState == 1)  

  

  {  

  

    gamePlay();  

  

  }  

  

    

  

  if (gameState == 2)  

  

  {  

  



  

    delay(500);  

  

    winning_sound();  

  

    winDisplay();  

  

    winDisplay();  

  

    winDisplay();  

  

    loseDisplay();  

  

    Serial.println("winDisplay");  

 

  

    delay (1000);  


  

    gameState = 0;  

  

  }  

  

    

  

  if (gameState == 3)  

  

  {  

    delay(500);  

  

    losing_sound();  

  

    loseDisplay();  

  

    loseDisplay();  

  

    loseDisplay();  

  

    Serial.println("loseDisplay");   

  

    delay (1000);  


    gameState = 0;  

  

  }   

  

}  

  

   

  


void pre_game()  

  

{  


  

  unsigned long currentMillis = millis();  

  

  if (currentMillis - previousMillis > interval1)  

  

  {  

  if (ledState == 0)  

  

  {  

  

    Serial.println("pre green");  

  

    setLed(0);  

  

    ledState = 1;  

  

  }  

  

  else if (ledState == 1)  

  

  {  

  

    Serial.println("pre red");  

  

    setLed(1);  

  

    ledState = 2;  

  

  }  

  

  else if (ledState == 2)  

  

  {  

  

    Serial.println("pre yellow");  

  

    setLed(2);  

  

    ledState = 3;  

  

  }  

  

  else if (ledState == 3)  

  

  {  

  

    Serial.println("pre blue");  

  

    setLed(3);  

  

    ledState = 0;  

  

  }  

  

  previousMillis = currentMillis;  

  

  }  

  

}  

  

   

  


  

void gamePlay()  

  

{  

  

  Serial.println("gamePlay");  

  



  

  for ( int i=0; i<NUMBERTOWIN; i++)  

  

  {  

  

    gameValues[i] = floor(random(0,4));  

  

    Serial.println(gameValues[i], DEC);  

  

  }  

  

   

  

    

  

  Serial.print("Starting Round ");  

  

  Serial.println(NMofRN, DEC);  

  

  for (int r=0; r<NUMBERTOWIN; r++)  

  

  {  

  

    displayClue(NMofRN);  

  

    

  

    for (int i=0; i<=NMofRN; i++)  

  

    {        

  

      Serial.print("Wainting for input ");  

  

      Serial.print(i+1, DEC);  

  

      Serial.print(" of ");  

  

      Serial.print(NMofRN+1, DEC);  

  

      Serial.println("");  


  

      if (waitForInput(gameValues[i]))  

  

      {  

        if (i==NMofRN)  

  

        {  

  

          Serial.println("Correct");  

          if (NMofRN == NUMBERTOWIN-1)  

  

          {  

  

            Serial.println("You Win!");  

  

           gameState = 2;  

  

           return;  

  

          }  

  

          else   

  

          {  

  

            Serial.println("Continue");  

  

          }  

  

        }  

  

      }  

  

      else   

  

      {  

  



  

        Serial.println("You Lose!");  

  

   

  

  

        gameState = 3;  

  

        return;  

  

      }  

  

    }  
  

    NMofRN++;  


    delay(1000);  

  

  }  

  

}  

  

   

  

void setLed(int ledNum)  

  

{  


  

  if (ledNum<0)  

  

  {  

  

   for (int i = 0; i<PCt; i++)  

  

   {  

  

   digitalWrite(ldAr[i], LOW);  

  

   }  

  

  }  

  

  else  

  

  {  

   

    for (int i = 0; i<PCt; i++)  

  

    {  

  

      if (i == ledNum)  

  

      {  

  

        digitalWrite(ldAr[i], HIGH);  

  

      }  

  

      else   

  

      {  

  

        digitalWrite(ldAr[i], LOW);  

  

      }  

  

    }  

  

  }  

  

}  

  

   

  

   

  

void displayClue(int NMofRN)  

  

{  

  setLed(-1);  

  

  for (int i=0; i<=NMofRN; i++)  

  

  {  

    setLed(gameValues[i]);  

  

    delay(750);  

  

    setLed(-1);  

  

    delay(250);  

  

  }  

  

}  

  

   

  

boolean waitForInput(int buttonNum)  

  

{  


  while(true)   

  

  {  

  

   int button0 = digitalRead(BNAr[0]);  

  

   int button1 = digitalRead(BNAr[1]);    

  

   int button2 = digitalRead(BNAr[2]);   

  

   int button3 = digitalRead(BNAr[3]);    

  

   if (!button0 || !button1 || !button2 || !button3)  

  

   {  

      delay(250);  


      if (buttonNum == 0)  

  

      {  

  

        digitalWrite(ldAr[0], HIGH);  

  

        delay(250);  

  

        digitalWrite(ldAr[0], LOW);  

  

      }  

  

      else if (buttonNum == 1)  

  

      {  

  

        digitalWrite(ldAr[1], HIGH);  

  

        delay(250);  

  

        digitalWrite(ldAr[1], LOW);  

  

      }  

  

      else if (buttonNum == 2)  

  

      {  

  

        digitalWrite(ldAr[2], HIGH);  

  

        delay(250);  

  

        digitalWrite(ldAr[2], LOW);  

  

      }  

  

      else if (buttonNum == 3)  

  

      {  

  

        digitalWrite(ldAr[3], HIGH);  

  

        delay(250);  

  

        digitalWrite(ldAr[3], LOW);  

  

      }  


      if (buttonNum == 0 && button0 == 0)  

  

      {  

  

        Serial.println("0 Pressed");  

  

        return true;  

  

      }  

  

      else if (buttonNum == 1 && button1 == 0)  

  

      {  

  

        Serial.println("1 Pressed");  

  

        return true;  

  

      }  

  

      else if (buttonNum == 2 && button2 == 0)  

  

      {  

  

        Serial.println("2 Pressed");  

  

        return true;  

  

      }  

  

      else if (buttonNum == 3 && button3 == 0)  

  

      {  

  

        Serial.println("3 Pressed");  

  

        return true;  

  

      }  

  

      else  

  

      {  

  

        return false;  

  

      }  

  

    }  

  

  }  

  

}  


  

void winDisplay()  

  

{  

  

digitalWrite(ldAr[0], HIGH);  

  

delay(75);  

  

digitalWrite(ldAr[0], LOW);  

  

delay(75);  

  

digitalWrite(ldAr[1], HIGH);  

  

delay(75);  

  

digitalWrite(ldAr[1], LOW);  

  

delay(75);  

  

digitalWrite(ldAr[2], HIGH);  

  

delay(75);  

  

digitalWrite(ldAr[2], LOW);  

  

delay(75);  

  

digitalWrite(ldAr[3], HIGH);  

  

delay(75);  

  

digitalWrite(ldAr[3], LOW);  

  

delay(75);  

  

digitalWrite(ldAr[2], HIGH);  

  

delay(75);  

  

digitalWrite(ldAr[2], LOW);  

  

delay(75);  

  

digitalWrite(ldAr[1], HIGH);  

  

delay(75);  

  

digitalWrite(ldAr[1], LOW);  

  

delay(75);  

  

digitalWrite(ldAr[0], HIGH);  

  

delay(75);  

  

digitalWrite(ldAr[0], LOW);  

  

delay(75);  

  

}  

  

   

  

void winning_sound(void)  

  

{  

  


  

  Serial.println("BZZ1");  

  

  tone(BZZ, 294, 250);  

  

  delay(200);  

  

  tone(BZZ, 294, 250);  

  

  delay(200);  

  

  tone(BZZ, 294, 250);  

  

  delay(200);  

  

  tone(BZZ, 392, 500);  

  

  delay(500);  

  

  Serial.println("second 392");  

  

  tone(BZZ, 392, 250);  

  

  delay(200);  

  

  tone(BZZ, 440, 250);  

  

  delay(200);  

  

  tone(BZZ, 392, 250);  

  

  delay(200);  

  

  tone(BZZ, 440, 250);  

  

  delay(200);  

  

  tone(BZZ, 494, 500);  

  

}  

  

   

  

   

  

void loseDisplay()  

  

{  

  

  digitalWrite(ldAr[0], HIGH);  

  

  digitalWrite(ldAr[1], HIGH);  

  

  digitalWrite(ldAr[2], HIGH);  

  

  digitalWrite(ldAr[3], HIGH);  

  

  delay(200);  

  

  digitalWrite(ldAr[0], LOW);  

  

  digitalWrite(ldAr[1], LOW);  

  

  digitalWrite(ldAr[2], LOW);  

  

  digitalWrite(ldAr[3], LOW);  

  

  delay(200);  

  

}  

  

   

  

void losing_sound(void)  

  

{  

  

  Serial.println("losing_sound");  

  

  tone(BZZ, 98, 250);  

  

  delay(250);  

  

   tone(BZZ, 93, 250);  

  

  delay(250);  

  

   tone(BZZ, 87, 250);  

  

  delay(250);  

  

}  

 

 

#include <LiquidCrystal.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);



bool volba1 = false;              //false - automat
bool volba_potvrzeno = false;     //potvrzení výběru
bool volba_smer = false;          //false - <-
bool volba_otoc = false;          //false - NE
int rychlost = 0;

int obnova = 0; //obnova displaye


//motor
const int stepPin = 6;
const int dirPin = 7;

const int stepPinB = 10;
const int dirPinB = 11;

//koncovy spinac
#define spinacA 2
#define spinacB 3              

// joystick
#define pinX A6
#define pinY A7
#define clickPin 4
int joyX = 0;
int joyY = 0;
int aktX;
int aktY;
int nulaX;
int nulaY;

//potenciometr
#define potpin A0
int potProm = 0;


/////////////////////////////////////////////////////////////////////////////
void setup() {

 //joystick
pinMode(clickPin, INPUT_PULLUP);
pinMode(pinX,INPUT);
pinMode(pinY, INPUT);

int nulaX = analogRead(pinX);
int nulaY = analogRead(pinY);

//potenciometr
pinMode(potpin, INPUT);

//lcd
lcd.begin();
lcd.backlight();

Serial.begin(9600);

//motor 1
pinMode(6, OUTPUT);
pinMode(7,OUTPUT);
//motor2
pinMode(10, OUTPUT);
pinMode(11, OUTPUT);


  lcd.clear();
  lcd.setCursor ( 0, 0 );
  lcd.print("Joystick");
  lcd.setCursor ( 0, 1 );
  lcd.print("Automat");
  


//VOLBA1
while(digitalRead(clickPin) == HIGH | volba_potvrzeno == false){
  
    if (analogRead(pinX) < 400){
      lcd.clear();
      lcd.setCursor ( 0, 0 );
       lcd.print("Joystick <");
       lcd.setCursor ( 0, 1 );
       lcd.print("Automat");
       volba1 = true;
       volba_potvrzeno = true;
      }
     else if (analogRead(pinX)> 600){
              lcd.clear();
              lcd.setCursor ( 0, 0 );
              lcd.print("Joystick");
              lcd.setCursor ( 0, 1 );
              lcd.print("Automat <");
              volba1 = false;
              volba_potvrzeno = true;
            }
     
  
  delay(10);
  Serial.print(digitalRead(pinX));  
  }




volba_potvrzeno = false;
delay(1000);

if(volba1 == true){
 
  }



//automat

//VOLBA_SMER
if(volba1 == false){
  while(digitalRead(clickPin) == HIGH | volba_potvrzeno == false){

  if (analogRead(pinY) < 490){
    lcd.clear();
    lcd.setCursor( 0, 0 );
    lcd.print("      SMER      ");
    lcd.setCursor( 0, 1 );
    lcd.print("      --->    ");
       volba_smer = true;
       volba_potvrzeno = true;
       delay(10);
      }
      
     else if (analogRead(pinY)> 530){
              lcd.clear();
              lcd.setCursor( 0, 0 );
              lcd.print("      SMER      ");
              lcd.setCursor( 0, 1 );
              lcd.print("      <---    ");
                volba_smer = false;
                volba_potvrzeno = true;
                delay(10);
            }
            
     else if (volba_potvrzeno == false){
 lcd.clear();
  lcd.setCursor( 0, 0 );
  lcd.print("      SMER      ");
  lcd.setCursor( 0, 1 );
  }
delay(10);
Serial.println(analogRead(pinY));
 }
//konec volba_smer
delay(1000);







//zadání základní polohy otočení
if (volba_otoc == true){
  //nastavení základní polohy
  }







 delay(1000);
volba_potvrzeno = false;





//rychlost
while(digitalRead(clickPin) == HIGH){
  potProm = analogRead(potpin);
     lcd.clear();
     lcd.setCursor(0,0);
     lcd.print("Rychlost:");
     lcd.setCursor (0, 1);
     lcd.print(potProm);
     rychlost = analogRead(potpin);
     delay(80);
}
//konec rychlosti





delay(1000);
lcd.clear();
lcd.print("ZVOLENO:");
delay(1000);

//shrnutí
lcd.clear();
lcd.setCursor( 0, 0 );
if(volba1 == true){lcd.print("Joystick");}
else if(volba1 == false){lcd.print("Automat");}
delay(1000);

lcd.clear();
lcd.setCursor( 0, 0 );
if(volba_smer == true){lcd.print("->");}
else if(volba_smer == false){lcd.print("<-");}
delay(1000);


lcd.clear();
lcd.setCursor( 0, 0 );
lcd.print(potProm);
delay(1000);
}


//konec volba1



















//volba1
//volba_smer
//volba_otoc
//rychlost






if (volba1 == false){
        if(volba_smer == true){//nastavit otočení
            digitalWrite(dirPin, LOW);
          while (digitalRead(spinacA) == HIGH){
           digitalWrite(stepPin, HIGH);
           delayMicroseconds(500);
           digitalWrite(stepPin, LOW);
           delayMicroseconds(500);
 }
 
 digitalWrite(dirPin, HIGH);

 
 while (digitalRead(spinacB) == HIGH){                  
  digitalWrite(stepPin, HIGH);
  delayMicroseconds(rychlost*10);
  digitalWrite(stepPin, LOW);
  delayMicroseconds(rychlost*10);
  }
  
        }
        else if(volba_smer == false){ 
           digitalWrite(dirPin, HIGH);
          while (digitalRead(spinacB) == HIGH){
           digitalWrite(stepPin, HIGH);
           delayMicroseconds(500);
           digitalWrite(stepPin, LOW);
           delayMicroseconds(500);
 }
 
 digitalWrite(dirPin, LOW);

 
 while (digitalRead(spinacA) == HIGH){                  
  digitalWrite(stepPin, HIGH);
  delayMicroseconds(rychlost*10);
  digitalWrite(stepPin, LOW);
  delayMicroseconds(rychlost*10);
  }
        }
          
  }

}














void loop() {
 //pokud joystick - loop na ovládání motorů + senzory na zastavení
if (volba1 == true){

rychlost = analogRead(potpin);



if (analogRead(pinY) < 400 & digitalRead(spinacB) == HIGH){
  digitalWrite(dirPin, HIGH);
  digitalWrite(stepPin, HIGH);
  delayMicroseconds(rychlost*10);
  digitalWrite(stepPin, LOW);
  delayMicroseconds(rychlost*10);
  }
  
else if (analogRead(pinY) > 600 & digitalRead(spinacA) == HIGH){
  digitalWrite(dirPin, LOW);
  digitalWrite(stepPin, HIGH);
  delayMicroseconds(rychlost*10);
  digitalWrite(stepPin, LOW);
  delayMicroseconds(rychlost*10);
  }

if (analogRead(pinX) < 400 & obnova > 100){
  digitalWrite(dirPinB, HIGH);
  digitalWrite(stepPinB, HIGH);
  delayMicroseconds(20000);
  digitalWrite(stepPinB, LOW);
  delayMicroseconds(rychlost*10);
  obnova = 0;
  }
  else {obnova++;}
  
if (analogRead(pinX) > 600 & obnova > 100){
  digitalWrite(dirPinB, LOW);
  digitalWrite(stepPinB, HIGH);
  delayMicroseconds(rychlost*100);
  digitalWrite(stepPinB, LOW);
  delayMicroseconds(rychlost*100);
  obnova = 0;
  }
else {obnova++;}
}

  
  
}

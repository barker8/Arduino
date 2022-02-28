#include <LiquidCrystal.h>
LiquidCrystal lcd (11,10,5,4,3,2);
void setup()
{
  Serial.begin(9600);
  lcd.begin(16,2);
  pinMode(13,OUTPUT);
  pinMode(12,INPUT);
  lcd.print("Good luck"); //In the first game
  delay(1500);
}

void loop()
{
  lcd.clear();                    //Clear the screen before each game  
  float a=0,score = 0, clicks [4]={0,0,0,0};
  digitalWrite(13,HIGH);          //This is the flickering stage of the LED
  delay(400);
  digitalWrite(13,LOW);
  delay(300);
  digitalWrite(13,HIGH);
  delay(400);
  digitalWrite(13,LOW);
  delay(400);
  
  digitalWrite(13,HIGH);
  delay(200);
  digitalWrite(13,LOW);
  delay(200);
  digitalWrite(13,HIGH);
  delay(200);
  digitalWrite(13,LOW);
  delay(200);
  digitalWrite(13,HIGH);
  delay(400);
  digitalWrite(13,LOW);
  delay(500);
  
  
  char letters [4] = {'b', 'c', 'd', 'e'};  //This is where the click times will come in
  a =  (pulseIn(12,HIGH,5000000))/100;//400 // "a" alone because it has a different timeout
  lcd.print("a: ");                         //print on the LCD and serial monitor
  lcd.setCursor(2,0);
  lcd.print((int)a);
  Serial.print("a:");
  Serial.println((int)a);
  
  for(int i=0,x=0; i<4; i++)
  {		
    clicks [i] =  pulseIn(12,HIGH,500000)/100; // Saving every click in the array
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print(letters[i]);                     // //print on the LCD and serial monitor
    lcd.setCursor(1,0);
    lcd.print(": ");
    lcd.setCursor(2,0);
    x=(int)clicks [i];
    lcd.print((int)x);
    Serial.print(letters[i]);
    Serial.print(": ");
  	Serial.println(x);
  }   
  
  if (a>=400)                   //a   Beginning of the calculations of the final grade
    score = (400/a)*20;
  else
    score = (400/(400*2-a))*20;
  
  for (int i=0;i<4;i++)
  {
    if(i<2||i>3)
    {
      if (clicks [i]>=400)                   //b
         score = score +((400/clicks [i])*20);
      else
         score = score +(400/(400*2-clicks [i]))*20;
    }
    else
    {
     if (clicks [i]>=200)                   //c
        score = score +((200/clicks [i])*20);
     else
        score = score +(200/(200*2-clicks [i]))*20; 
    }
  }   
  delay(1000);
  lcd.clear();
  lcd.setCursor(0,0);
  Serial.print("The score is: ");
  Serial.println(score);
  lcd.print("The score is: ");
  lcd.setCursor(0,1);
  lcd.print(score);
  delay(2000);
  lcd.clear();
  if( score>80)
    lcd.print("Well done");
  else
    lcd.print("Try again");
  delay(2000);
  
    
}


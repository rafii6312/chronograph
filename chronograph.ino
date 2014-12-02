#include <LiquidCrystal.h>
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
float time = 0;
boolean wait = false;
int state = 0;

                   //Einzige zu ändernde Variable!
float dist = 0.15; //Entfernung zwichen den Schranken in meter

boolean lastA = false;
boolean lastB = false;

void setup()
{
  lcd.begin(16, 2);
  pinMode(6, INPUT);
  pinMode(7, INPUT);
  lcd.setCursor(0, 0);
  lcd.print("Warte auf Signal");
  lcd.setCursor(0, 1);
  lcd.print("                ");
  
}

void loop()
{
  if(wait == false)
  {
    if(isTriggerA() == true)
    {
      triggerA();
      state = 1;
    }

    if(isTriggerB() == true && state == 1)
    {
      triggerB();
      
      lcd.setCursor(0, 0);
      String res = "m/s: ";
      res.concat((1000/time) * dist);
      lcd.print(res);
      
      lcd.setCursor(0, 1);
      res = "f/s: ";
      res.concat((1000/time) * dist * 3.2808399);
      lcd.print(res);
      
      state = 2;
      resetTrigger();
    }
  }
  else
  {
    if(isTriggerC() == true && state == 2)
    {
      wait = false;
      state = 0;
      lcd.setCursor(0, 0);
      lcd.print("                ");
    }
  }

}

boolean isTriggerA()
{
  return (digitalRead(6) == HIGH);
}

boolean isTriggerB()
{
  return (digitalRead(7) == HIGH);
}

boolean isTriggerC()
{
  return (digitalRead(6) == HIGH);
}

void resetTrigger()
{
  time = 0;
  wait = true;
}

void triggerA()
{
  time = millis();
}

void triggerB()
{
  time = millis() - time;
}





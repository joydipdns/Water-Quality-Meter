#include <LiquidCrystal.h>

//--------------------------------------------initializations--------------------------------------------//
const int buttonPin = 7 ;
int buttonState = 0 ;
int lastButtonState = 0 ;
float S = 0.00, Tds = 0.00, Sal = 0.00;
int aval;
int counter = 0;
float a=0.0;
float temp=0.0;
int ch = 1 ;
boolean edge1 ;
boolean edge2 ;
boolean edge3 ;
boolean edge4 ;
LiquidCrystal lcd (12 , 11 , 5 , 4 , 3 , 2 ) ;

byte degree[8] = {              //custom character degree symbol
  B00110,
  B01001,
  B01001,
  B00110,
  B00000,
  B00000,
  B00000,
  B00000
};

//----------------------------------------------setup function--------------------------------------------//

void setup ( )
{
  pinMode ( buttonPin , INPUT) ;
  lcd.createChar(0, degree);
  lcd.begin (16, 2) ;
  lcd.print ( "TO BEGIN MEASURE" ) ;
  lcd.setCursor(0, 1) ;
  lcd.print( "USE CHANNEL ONE  " ) ;
  lcd.setCursor(0, 0) ;
  delay (4000) ;
  lcd.clear( ) ;
  lcd.setCursor (0, 0) ;
  lcd.print ( "  PRESS MEASURE   " ) ;
  lcd.setCursor ( 0, 1 ) ;
  lcd.print ( "BUTTON 2 MEASURE" ) ;
}

//---------------------------------------------------functions------------------------------------------------//

int trigger ( )                               //for sensing the external trigger by user
{
  buttonState = digitalRead ( buttonPin ) ;
  if ( buttonState != lastButtonState )
  {
    if ( buttonState == HIGH)
      return HIGH;
    else if ( buttonState == LOW)
      return LOW;
    delay ( 50 ) ;
  }
  lastButtonState = buttonState ;
}

void displayVol ( float v1 , float v2 )        //for displaying measured VOLTAGE
{
  lcd.clear ( ) ;
  lcd.print ( "V1=" ) ;
  lcd.print ( v1 , 3 ) ;    //LCD prints upto 3 decimal places
  lcd.print ( " " ) ;
  lcd.setCursor ( 0, 1 ) ;
  lcd.print ( "V2= " ) ;
  lcd.print ( v2 , 3 ) ;    //LCD prints upto 3 decimal places
  lcd.print ( " Volt" ) ;
  delay ( 3000 ) ;
  lcd.setCursor (0, 0) ;
}

void displayS ( float s )                   //for displaying CONDUCTIVITY
{
  lcd.clear( ) ;
  lcd.print ( "S= " ) ;
  lcd.print ( s , 3) ;      //LCD prints upto 3 decimal places
  lcd.print ( " uS/cm" ) ;
  delay ( 3000 ) ;
  lcd.setCursor (0, 0) ;
}

void displayTDS ( float tds )               //for displaying TDS
{
  lcd.clear( ) ;
  lcd.print ( "TDS= " ) ;
  lcd.print ( tds , 3) ;    //LCD prints upto 3 decimal places
  lcd.print ( " ppm" ) ;
  delay ( 3000 ) ;
  lcd.setCursor (0, 0) ;
}

void displaySal ( float sal )                //for displaying SALINITY
{
  lcd.clear( ) ;
  lcd.print ( "Sal= " ) ;
  lcd.print ( sal , 3) ;    //LCD prints upto 3 decimal places
  lcd.print ( " ppm" ) ;
  delay ( 3000 ) ;
  lcd.setCursor (0, 0) ;
}

float tempComp()                            //for sensing the solution temperature
{
  while (counter < 50)
  {
    aval = analogRead(A3);
    float mv = (aval / 1024.0) * 5000;
    float temp = (mv / 10) + 1.5;
    a = a + temp;
    counter++;
    delay(100);
  }
  while (counter == 50)
  {
    float avg_temp = a / 50.0;
    counter=0;
    a=0.0;
    return(avg_temp);
  }
}

//-------------------------------------------------loop function--------------------------------------------------//

void loop ( )
{
  float pi = 3.14159;
  switch ( ch )
  {
    case 1 :
      {
        edge1 = trigger ( ) ;
        if ( edge1 == HIGH )
        {
          int sensorValue1 = analogRead (A1 ) ;
          int sensorValue2 = analogRead (A2 ) ;
          float voltage1 = sensorValue1 * ( 5.0 / 1023.0 ) ;
          float voltage2 = sensorValue2 * ( 5.0 / 1023.0 ) ;
          float x = voltage1 / voltage2;
          if (voltage2 == 5.000)
          {
            S = 0.00;
            Tds = 0.00;
            Sal = 0.00;
          }
          else
          {
            S = (1.110 * x * x * x) - (11.70 * x * x) + (63.23 * x) - 19.38;
            Tds = 0.965 * S - 0.522;
            Sal = 0.829 * S + 9.899;
          }
          displayVol ( voltage1 , voltage2 ) ;
          delay ( 2000 ) ;
          displayS ( S ) ;
          delay ( 2000 ) ;
          displayTDS ( Tds ) ;
          delay ( 2000 ) ;
          displaySal ( Sal ) ;
          lcd.clear();
          lcd.print ( "TEMP= " ) ;
          lcd.print(tempComp(),3);
          lcd.print(" ");
          lcd.write(byte(0));
          lcd.print("C");
        }
      }
      break ;
  }
}


#include <LiquidCrystal.h>

const int buttonPin = 7 ;   
int buttonState = 0 ;      
int lastButtonState = 0 ;   
float S=0.00, Tds=0.00, Sal=0.00;
LiquidCrystal lcd (12 , 11 , 5 , 4 , 3 , 2 ) ;

void setup ( ) 
{
  Serial.begin(9600);
  pinMode ( buttonPin , INPUT) ;
  lcd.begin (16,2) ;
  lcd.print ( "TO BEGIN MEASURE" ) ;  
  lcd.setCursor(0,1) ;                
  lcd.print( "USE CHANNEL ONE  " ) ;
  lcd.setCursor(0,0) ;
  delay (5000) ;
  lcd.clear( ) ;
  lcd.setCursor (0,0) ;
  lcd.print ( "  PRESS MEASURE   " ) ;
  lcd.setCursor ( 0,1 ) ;
  lcd.print ( "BUTTON 2 MEASURE" ) ;
}

int ch = 1 ;         
boolean edge1 ;
boolean edge2 ;
boolean edge3 ;
boolean edge4 ;

void displayS (/* float theta , float z ,*/ double s )
{
  lcd.clear( ) ;
//  lcd.print ( "0=" ) ;
//  lcd.print ( theta ) ;
//  lcd.print ( " Z=" ) ;
//  lcd.print ( z ) ;
//  lcd.setCursor ( 0,1 ) ;
  lcd.print ( "S= " ) ;
  lcd.print ( s ,3) ;
  lcd.print ( " uS/cm" ) ;
  delay ( 3000 ) ;
  lcd.setCursor (0,0) ;
}

void displayTDS (/* float theta , float z ,*/ double s )
{
  lcd.clear( ) ;
//  lcd.print ( "0=" ) ;
//  lcd.print ( theta ) ;
//  lcd.print ( " Z=" ) ;
//  lcd.print ( z ) ;
//  lcd.setCursor ( 0,1 ) ;
  lcd.print ( "TDS= " ) ;
  lcd.print ( s ,3) ;
  lcd.print ( " ppm" ) ;
  delay ( 3000 ) ;
  lcd.setCursor (0,0) ;
}
void displaySal (/* float theta , float z ,*/ double s )
{
  lcd.clear( ) ;
//  lcd.print ( "0=" ) ;
//  lcd.print ( theta ) ;
//  lcd.print ( " Z=" ) ;
//  lcd.print ( z ) ;
//  lcd.setCursor ( 0,1 ) ;
  lcd.print ( "Salinity= " ) ;
  lcd.print ( s ,3) ;
  lcd.print ( " ppm" ) ;
  delay ( 3000 ) ;
  lcd.setCursor (0,0) ;
}

void displayvol (/* float theta , */float z ,double s )
{
  lcd.clear ( ) ;
//  lcd.print ( "V0=" ) ;
//  lcd.print ( theta , 3 ) ; //LCD prints upto 3 decimal places
//  lcd.print ( " " ) ;
  lcd.print ( "V1=" ) ;
  lcd.print ( z , 3 ) ;
  lcd.print ( " " ) ;
  lcd.setCursor ( 0,1 ) ;
  lcd.print ( "V2= " ) ;
  lcd.print ( s , 3 ) ;
  lcd.print ( " Volt" ) ;
  delay ( 3000 ) ;
  lcd.setCursor (0,0) ;
}

int measure ( ) 
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

void loop ( ) 
{
  float pi =3.14159;
  switch ( ch )
  {
    case 1 :
    {
//      float A = 40.17 ;     //fixed for the PCB
//      float B = 6.842 ;     //fixed for the PCB
//      float C = 14269.5 ;   //fixed for the PCB
//      float D = 724.8 ;     //fixed for the PCB
//      float E = 235619.778044682;
//      float F = -0.93817820930803;
      edge1 = measure ( ) ; 
      if ( edge1==HIGH)
      {
//        int sensorValue0 = analogRead (A0 ) ;
        int sensorValue1 = analogRead (A1 ) ;
        int sensorValue2 = analogRead (A2 ) ;
//        float voltage0 = sensorValue0 * ( 5.0/1023.0 ) ;
//          float theta = ( ( voltage0 *A)+B) ;
//        float rad = theta *( pi / 180 ) ;
        float voltage1 = sensorValue1 * ( 5.0/1023.0 ) ;
        float voltage2 = sensorValue2 * ( 5.0/1023.0 ) ;
//          float z = ( ( voltage2 / voltage1 )*C)+D;
        float x=voltage1/voltage2;
        if(voltage2==5.000)
        {
         S=0.00;
         Tds=0.00;
         Sal=0.00;
        }
        else
        {
         S= (1.110*x*x*x)-(11.70*x*x)+(63.23*x)-19.38;
         Tds= 0.965*S-0.522;
         Sal= 0.829*S+9.899;
        }
//          double cond = ( (E/ z ) * ( cos ( rad )))+F;
        displayvol ( /*voltage0 ,*/voltage1 , voltage2 ) ;
        Serial.println("--------");
//        Serial.println(voltage0);
        Serial.println(voltage1);
        Serial.println(voltage2);
        Serial.println("--------");
        delay ( 4000 ) ;
//        if ( z<= 1700.0 ) 
//        {
//          int tme=0;
//          again :
//          tme++;
//          while ( tme<=5)
//          {
//            lcd.clear ( ) ;
//            lcd.setCursor (0,0) ;
//            lcd.print ( "TURN TO CHNL TWO" ) ;
//            delay ( 1000 ) ;
//            goto again ;
//          }
//          lcd.setCursor (0,0) ;
//          if ( tme>5)
//          {
//            ch=2;
//            lcd.clear ( ) ;
//            lcd.print ( " CHANNEL 2 " ) ;
//            delay ( 3000 ) ; 
//          }
//        }
//        else 
{
          displayS ( /*theta , z , cond*/S ) ;
          delay ( 4000 ) ;
          displayTDS ( /*theta , z , cond*/Tds ) ;
          delay ( 4000 ) ;
          displaySal ( /*theta , z , cond*/Sal ) ;
        }
      }
    }
    break ;
  
  case 2 :
 {
//    float Ach2 = 40.17 ;     //fixed for the PCB
//    float B2 = 6.842 ;       //fixed for the PCB
//    float C2 = 1766.21 ;     //fixed for the PCB
//    float D2 = 89.71 ;       //fixed for the PCB
//    float E2 = 254560.03363755;
//    float F2 = -30.3225059027586;
//    edge2 = measure ( ) ;
//    if ( edge2==HIGH) 
//    {
//      int sensorValuech2 = analogRead (A0 ) ;
//      int sensorValue1ch2 = analogRead (A1 ) ;
//      int sensorValue2ch2 = analogRead (A2 );
//      float voltagech2 = sensorValuech2 * ( 5.0/1023.0 ) ;
//      float thetach2 = ( ( voltagech2 *Ach2)+B2 ) ;
//      float radch2 = thetach2 *( pi / 180 ) ;
//      float voltage1ch2 = sensorValue1ch2 * ( 5.0/1023.0 ) ;
//      float voltage2ch2 = sensorValue2ch2 * ( 5.0/1023.0 ) ;
//      float zch2 = ( ( voltage2ch2 / voltage1ch2 )*C2)+D2 ;
//      double condch2 = ( (E2/ zch2 ) * ( cos ( radch2 )))+F2 ;
//      displayvol ( voltagech2 , voltage1ch2 , voltage2ch2 ) ;
//      delay ( 4000 ) ;
//      if ( zch2 < 110.0 )
//      {
//        int tme=0;
//        again1 :
//        tme++;
//        while ( tme<=5)
//        {
//          lcd.clear ( ) ;
//          lcd.setCursor (0,0) ;
//          lcd.print ( "TURN TO CHNL 3" ) ;
//          delay ( 1000 ) ;
//          goto again1 ;
//        }
//        if ( tme>5)
//        {
//          ch=3;
//          lcd.clear ( ) ;
//          lcd.print ( " CHANNEL 3 " ) ;
//          delay ( 3000 ) ; 
//        }
//      }
//      else if ( condch2 <1500.0)
//      {
//        display ( thetach2 , zch2 , condch2 ) ;
//      }
//    }
  }
  break ;
  
  case 3 :
  {
//    float Ach3 = 40.17 ;  //fixed for the PCB
//    float B3 = 6.842 ;    //fixed for the PCB
//    float C3 = 401.625 ;  //fixed for the PCB
//    float D3 = 724.8 ;    //fixed for the PCB
//    float E3 = 317682.124066368;
//    float F3 = -902.453934875978;
//    edge3 = measure() ;
//    if ( edge3==HIGH)
//    {
//      int sensorValuech3 = analogRead (A0 ) ;
//      int sensorValue1ch3 = analogRead (A1 ) ;
//      int sensorValue2ch3 = analogRead (A2 ) ;
//      float voltagech3 = sensorValuech3 * ( 5.0/1023.0 ) ;
//      float thetach3 = ( ( voltagech3 *Ach3)+B3 ) ;
//      float radch3 = thetach3 *( pi / 180 ) ;
//      float voltage1ch3 = sensorValue1ch3 * ( 5.0/1023.0 ) ;
//      float voltage2ch3 = sensorValue2ch3 * ( 5.0/1023.0 ) ;
//      float zch3 = ( ( voltage2ch3 / voltage1ch3 )*C3)+D3 ;
//      double condch3 = (E3/ zch3)+F3 ;
//      displayvol ( voltagech3 , voltage1ch3 , voltage2ch3 ) ;
//      delay ( 4000 ) ;
//      display ( thetach3 , zch3 , condch3 ) ;
//      ch=1;
//    }
  }
  break ;
  }
}

#include <Grove_I2C_Motor_Driver.h>

/*
 * FM.h
 * A library for SeeedStudio Grove FM
 *
 * Copyright (c) 2012 seeed technology inc.
 * Website    : www.seeed.cc
 * Author     : Steve Chang
 * Create Time: JULY 2014
 * Change Log : Modified by loovee 2013-10-29  ,   Modified by jacob yan 2014-7-29
 
 * The MIT License (MIT)
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

#include <SoftwareSerial.h>   //Software Serial Port
#include <PWM.h>

#define RxD         6
#define TxD         7

#define LEDON()     digitalWrite(PINLED, HIGH)
#define LEDOFF()    digitalWrite(PINLED, LOW)

#define DEBUG_ENABLED  1

SoftwareSerial blueToothSerial(RxD,TxD);
 

// Motor Shield
//#define Input1      10
//#define Input2      9
//int frequencyOutputPin = 3;

// I2C Motor Driver
#define I2C_ADDRESS 0x0f

// PWM
long frq, width;

void setup()
{
    Serial.begin(9600);
    pinMode(RxD, INPUT);
    pinMode(TxD, OUTPUT);
   
    pinMode(LED_BUILTIN, OUTPUT);
    
//    digitalWrite(Input1, HIGH);   // turn the LED on (HIGH is the voltage level)
//    digitalWrite(Input2, LOW);   // turn the LED on (HIGH is the voltage level)

     //Frequency Output
    InitTimersSafe();
 
    // PWM default settings
//    frq = 222; //Hz
//    width = 0; //%
//    //Set Frequency
//    SetPinFrequency(frequencyOutputPin, frq);
//    //Set Width
//    pwmWrite(frequencyOutputPin, 50 * 2.55f);
      
    Motor.begin(I2C_ADDRESS);
    setupBlueToothConnection();
}

void loop()
{
    char recvChar;
    String inString = "";
    int i = 0;
    blink_fast();
    blink_slow();
    delay(2000);                       // wait for a second
    Serial.print("Hello Arduino here");
    while(1)
    {
//        delay(2000);                       // wait for a second
        //blink();
        if(Serial.available())
        {
          
            //Serial.print("Serial arrived");
            recvChar = Serial.read();
            //Serial.print(recvChar);
            inString += recvChar;
            if(recvChar == ' ')
            {
              recvChar = '\n';
              width = inString.toInt();
              if (width < 0 || width > 100) { error(1); break; }
              //pwmWrite(frequencyOutputPin, width * 2.55f);
              Motor.speed(MOTOR1 ,width);
              Serial.print("PWM: ");
              Serial.println(width);
              inString = "";
            }
        }
    }
}

// the loop function runs over and over again forever
void blink_fast() {
  digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(333);                       // wait for a second
  digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
  delay(333);                       // wait for a second
}

// the loop function runs over and over again forever
void blink_slow() {
  digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(1000);                       // wait for a second
  digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
  delay(1000);                       // wait for a second
}


/***************************************************************************
 * Function Name: setupBlueToothConnection
 * Description:  initilizing bluetooth connction
 * Parameters: 
 * Return: 
***************************************************************************/
void setupBlueToothConnection()
{	

	
	
	blueToothSerial.begin(9600);  
	
	blueToothSerial.print("AT");
	delay(400); 

	blueToothSerial.print("AT+DEFAULT");             // Restore all setup value to factory setup
	delay(2000); 
	
	blueToothSerial.print("AT+NAMESeeedBTSlave");    // set the bluetooth name as "SeeedBTSlave" ,the length of bluetooth name must less than 12 characters.
	delay(400);
	
    blueToothSerial.print("AT+PIN0000");             // set the pair code to connect 
	delay(400);
	
	blueToothSerial.print("AT+AUTH1");             //
    delay(400);    

    blueToothSerial.flush();

}

void error(int no) {
    Serial.print(F("Error: "));
    switch (no)
    {
    case 1:
        Serial.println(F("Width only in the range of 0 to 100."));
        break;
    case 2:
        Serial.println(F("Frequency only in the range of 0 to 1000000."));
        break;
    }
} //end error

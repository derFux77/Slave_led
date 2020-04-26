#include <SoftwareSerial.h>

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

#define RxD         6
#define TxD         7

// Motor
#define Input1      9
#define Input2      10

#define PINLED      5

#define LEDON()     digitalWrite(PINLED, HIGH)
#define LEDOFF()    digitalWrite(PINLED, LOW)

#define DEBUG_ENABLED  1

SoftwareSerial blueToothSerial(RxD,TxD);

void setup()
{
    Serial.begin(9600);
    pinMode(RxD, INPUT);
    pinMode(TxD, OUTPUT);
    pinMode(PINLED, OUTPUT);
   
    pinMode(LED_BUILTIN, OUTPUT);
      
    LEDOFF();
    
    setupBlueToothConnection();
   
}

void loop()
{
    char recvChar;
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
            Serial.print("Serial arrived");
            recvChar = Serial.read();
            Serial.print(recvChar);
            if(recvChar == '1')
            {
                  digitalWrite(Input1, HIGH);   // turn the LED on (HIGH is the voltage level)
                  digitalWrite(Input2, LOW);   // turn the LED on (HIGH is the voltage level)
                  blink_fast();
                  
            }
            else if(recvChar == '0')
            {
                  digitalWrite(Input1, LOW);   // turn the LED on (HIGH is the voltage level)
                  digitalWrite(Input2, HIGH);   // turn the LED on (HIGH is the voltage level)
                  blink_slow();
            }
        }
//        if(blueToothSerial.available())
//        {//check if there's any data sent from the remote bluetooth shield
//            Serial.print("Something arrived");
//            recvChar = blueToothSerial.read();
//            Serial.print(recvChar);
//            if(recvChar == '1')
//            {
////                LEDON();
//                  blink_fast();
//                  //digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
//            }
//            else if(recvChar == '0')
//            {
////                  digitalWrite(LED_BUILTIN, LOW);   // turn the LED on (HIGH is the voltage level)
//                  blink_fast();
////                  LEDOFF();
//            }
//        }
        else
        {
//          Serial.print("Nothing arrived");        
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

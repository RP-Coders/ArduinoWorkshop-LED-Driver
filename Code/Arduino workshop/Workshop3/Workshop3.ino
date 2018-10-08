// 4 Channel LED Driver v1.1.0 
// For LED Controller v1.1.0+ 
// Copyright (c) 2018 http://retro-commodore.eu 
// Author: Carsten Jensen aka Tomse 

#include <IRremote.h>

//#define auxpin1 A5 
//#define auxpin2 A4 


int keypin[] = {A2, A3, A0, A1}; 

unsigned long keylast[] = {0,0,0,0};

// Channel 1-6 using PWM pins 3,5,6,9,10,11 
int Channel[] = {5,6,9,10}; 

// Set initial power state for each channel
int ChannelState[] = {HIGH,LOW,HIGH,HIGH}; 
int ChannelValue[] = {255,128,64,32}; 

int key;


IRrecv irrecv(13);
decode_results results;
 
// Eizo remote
#define PowerCycle 560208103      //Power
#define IncreasePWM 560263183     //Volume +
#define DecreasePWM 560255023     //Volume -
#define NextLED 560204023         //PC
#define PreviousLED 560226973     //HDMI
#define Repeat 4294967295         //Any key hold down for a few sec
#define Quater 560260123          //Bright -
#define ThreeQuater 560243803     //Arrow up
#define Half 560227483            //Arrow down
#define Full 560207083            //Bright +
#define Effects 560244313         //Smart
#define TT 560257573              //EcoView
 
uint32_t LastCode = 0;
uint32_t CurrentCode = 0;
int SelectedLED = 0;
// 1 = on, 0 = off
int PowerCycleState = 1;


void setup() { 
 
  Serial.begin(9600);
  Serial.println("Hello world"); 

  // IR Receiver
  irrecv.enableIRIn();
  
  for (int a=0;a<4;a++){ 
    pinMode(Channel[a], OUTPUT); 
    analogWrite(Channel[a], ChannelValue[a]); 
    
    pinMode(keypin[a], INPUT_PULLUP);
  } 

}     

 
void loop() { 
  // Do nothing 
  for (int a=0;a<4;a++){
    key = digitalRead(keypin[a]);
    if(key == LOW) 
    { 
      keypress(a);
      Serial.print("Key ");
      Serial.println(a+1); 
    } 
  }
  

  // listen to IR receiver
  if (irrecv.decode(&results)) {
 
    if (results.value != Repeat)
    {
      LastCode = results.value;
    }
 
    Serial.print(LastCode, HEX);
    Serial.print(" -- ") ;
    Serial.println(LastCode, DEC);
 

    switch (LastCode) {
   
    case PowerCycle:
        Serial.println("pwr cycle") ;
        if (PowerCycleState == 0)
        {
          analogWrite(Channel[0], ChannelValue[0]);
          analogWrite(Channel[1], ChannelValue[1]);
          analogWrite(Channel[2], ChannelValue[2]);
          analogWrite(Channel[3], ChannelValue[3]);
          PowerCycleState = 1;
        }
        else
        {
          analogWrite(Channel[0], 0);
          analogWrite(Channel[1], 0);
          analogWrite(Channel[2], 0);
          analogWrite(Channel[3], 0);
          PowerCycleState = 0;
        }
        break;
    case IncreasePWM:
        Serial.println("pwn up") ;
        if (ChannelValue[SelectedLED] + 5 >= 255)
        {
          ChannelValue[SelectedLED] = 255;
        }
        else
        {
          ChannelValue[SelectedLED] = ChannelValue[SelectedLED] + 5;
        }
        analogWrite(Channel[SelectedLED], ChannelValue[SelectedLED]);
        break;
    case DecreasePWM:
        Serial.println("pwn down") ;
        if (ChannelValue[SelectedLED] - 5 <= 0)
        {
          ChannelValue[SelectedLED] = 0;
        }
        else
        {
          ChannelValue[SelectedLED] = ChannelValue[SelectedLED] - 5;
        }
        analogWrite(Channel[SelectedLED], ChannelValue[SelectedLED]);
        break;
    case NextLED:
        Serial.print("next LED = ") ;
        if (SelectedLED < 3)
        {
          SelectedLED++;
        }
        else
        {
          SelectedLED = 0;
        }
        Serial.println(SelectedLED);
        // indicate the selected LED
        BlinkFunction(SelectedLED);
        analogWrite(Channel[SelectedLED], ChannelValue[SelectedLED]);
        break;
    case PreviousLED:
        Serial.print("prev LED = ") ;
        if (SelectedLED > 0)
        {
          SelectedLED--;
        }
        else
        {
          SelectedLED = 3;
        }
        Serial.println(SelectedLED);
        // indicate the selected LED
        BlinkFunction(SelectedLED);
        analogWrite(Channel[SelectedLED], ChannelValue[SelectedLED]);
        break;
    case Quater:
        Serial.println("set 1/4") ;
        ChannelValue[SelectedLED] = 64;
        analogWrite(Channel[SelectedLED], ChannelValue[SelectedLED]);
        break;
    case ThreeQuater:
        Serial.println("set 3/4") ;
        ChannelValue[SelectedLED] =  196;
        analogWrite(Channel[SelectedLED], ChannelValue[SelectedLED]);
        break;
    case Half:
        Serial.println("set Half") ;
        ChannelValue[SelectedLED] = 128;
        analogWrite(Channel[SelectedLED], ChannelValue[SelectedLED]);
        break;
    case Full:
        Serial.println("set Full") ;
        ChannelValue[SelectedLED] = 255;
        analogWrite(Channel[SelectedLED], ChannelValue[SelectedLED]);
        break;
    case Effects:
        Serial.println(" -- now doing effects --") ;

        for(int a=0;a<255;a++){
          analogWrite(Channel[SelectedLED], a);
          delay(5);
        }
        
        for(int a=0;a<255;a++){
          analogWrite(Channel[SelectedLED], 255-a);
          delay(5);
        }
        
        analogWrite(Channel[SelectedLED], ChannelValue[SelectedLED]);
        // make your own      
        break;
    case TT:
        // noget smart her
        Serial.println("Noget smart her");
        break;
    default:
        break;  
    }

    delay(100);
    irrecv.resume(); // Continue receiving
  }

} 


void keypress(int key)
{
  Serial.println("IWH2");
  Serial.println(key);
  Serial.println(ChannelState[key]);
  Serial.println(ChannelValue[key]);
  Serial.println(keylast[key]);
       
  if (keylast[key] + 250 <= millis())
  {
    if (ChannelState[key] == HIGH)
    {
      analogWrite(Channel[key], 0);
      ChannelState[key] = LOW;
    }
    else
    {
      analogWrite(Channel[key], ChannelValue[key]);
      ChannelState[key] = HIGH;
    }
    keylast[key] = millis();
  }
}
 
void BlinkFunction(int pin){
  int de = 100;
  analogWrite(Channel[pin], 0);
  delay(de);
  analogWrite(Channel[pin], 128);
  delay(de);
  analogWrite(Channel[pin], 0);
  delay(de);
  analogWrite(Channel[pin], 128);
  delay(de);
}

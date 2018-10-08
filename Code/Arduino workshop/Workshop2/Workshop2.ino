    // 4 Channel LED Driver v1.1.0 
// For LED Controller v1.1.0+ 
// Copyright (c) 2018 http://retro-commodore.eu 
// Author: Carsten Jensen aka Tomse 
 
//#define auxpin1 A5 
//#define auxpin2 A4 
  
#define key1pin A2 
#define key2pin A3 
#define key3pin A0 
#define key4pin A1 

// Brugt til at tokle lyset
int blinktime = 250;

int keypin[] = {A2, A3, A0, A1}; 

unsigned long keylast[] = {0,0,0,0};

// Channel 1-6 using PWM pins 3,5,6,9,10,11 
int Channel[] = {5,6,9,10}; 

// Set initial power state for each channel
int ChannelState[] = {HIGH,LOW,HIGH,HIGH}; 
int ChannelValue[] = {32,32,32,32}; 

int key;

void setup() { 
 
  Serial.begin(9600);
  Serial.println("Hello world"); 
 
  // AUX Inputs 
  // pinMode(auxpin1, INPUT); 
  // pinMode(auxpin2, INPUT); 


  // Keypad
  /*
  pinMode(key1pin, INPUT_PULLUP); 
  pinMode(key2pin, INPUT_PULLUP); 
  pinMode(key3pin, INPUT_PULLUP); 
  pinMode(key4pin, INPUT_PULLUP); 
  */
/*
  // FETs 
  pinMode(Channel[0], OUTPUT); 
  pinMode(Channel[1], OUTPUT); 
  pinMode(Channel[2], OUTPUT); 
  pinMode(Channel[3], OUTPUT); 
    
  analogWrite(Channel[0], ChannelValue[0]); 
  analogWrite(Channel[1], ChannelValue[1]); 
  analogWrite(Channel[2], ChannelValue[2]); 
  analogWrite(Channel[3], ChannelValue[3]); 
*/
  
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
  

  //delay(100);
     
} 


void keypress(int key)
{
  //Serial.println("IWH2");
  //Serial.println(key);
  Serial.println(ChannelState[key]);
  Serial.println(ChannelValue[key]);
  //Serial.println(keylast[key]);
       
  if (keylast[key] + blinktime <= millis())
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

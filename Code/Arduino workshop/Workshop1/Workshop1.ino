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

// Channel 1-6 using PWM pins 3,5,6,9,10,11 
int Channel[] = {5,6,9,10}; 
int keypin[] = {A2,A3,A0,A1};

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
  pinMode(keypin[0], INPUT_PULLUP); 
  pinMode(key2pin, INPUT_PULLUP); 
  pinMode(key3pin, INPUT_PULLUP); 
  pinMode(key4pin, INPUT_PULLUP); 



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
  
  for (int a=0;a<4;a=a+1){ 
    pinMode(keypin[a], INPUT_PULLUP);
    pinMode(Channel[a], OUTPUT); 
    analogWrite(Channel[a], ChannelValue[a]); 
  } 
  

}     

 
void loop() { 
  // Do nothing 
  for (int a=0;a<4;a++){
    key = digitalRead(keypin[a]);
    if (key == LOW) 
    { 
      //Serial.println("Key " + String(a+1)); 

      Serial.print("Key ");
      Serial.println(a+1);
    } 
  }
 /* 
  key = digitalRead(key2pin);
  if (key == LOW) 
  { 
    Serial.println("Key 2"); 
  } 

  key = digitalRead(key3pin);
  if (key == LOW) 
  { 
    Serial.println("Key 3"); 
  } 
  
  key = digitalRead(key4pin);
  if (key == LOW) 
  { 
    Serial.println("Key 4"); 
  } 
*/
  delay(100 );
}

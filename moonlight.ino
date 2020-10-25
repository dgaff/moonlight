
// Wemos pin mapping

// #define A0 not sure  ADC0
#define D0 16 // WAKE
#define D1 5  // SCL
#define D2 4  // SDA
#define D3 0  // FLASH
#define D4 2  // Blue LED - lights on digital 0
#define D5 14 // SCLK
#define D6 12 // MISO
#define D7 13 // MOSI
#define D8 15 // CS
#define TX 1  // TX
#define RX 3  // RX

// Set all digital pins to output

void setup()
{
  pinMode(D0, OUTPUT); // Digital Output
  pinMode(D1, OUTPUT);
  pinMode(D2, OUTPUT);
  pinMode(D3, OUTPUT);
  pinMode(D4, OUTPUT);
  pinMode(D5, OUTPUT);
  pinMode(D6, OUTPUT);
  pinMode(D7, OUTPUT);
  pinMode(D8, OUTPUT);
}

// Sets the phase for each segment

void setPhase(int s1, int s2, int s3, int s4, int s5, int s6)
{
  if (s1) digitalWrite(D7, HIGH);   
  else digitalWrite(D7, LOW);    

  if (s2) digitalWrite(D6, HIGH);   
  else digitalWrite(D6, LOW);    

  if (s3) digitalWrite(D5, HIGH);   
  else digitalWrite(D5, LOW);    

  if (s4) digitalWrite(D3, HIGH);   
  else digitalWrite(D3, LOW);    

  if (s5) digitalWrite(D2, HIGH);   
  else digitalWrite(D2, LOW);    

  if (s6) digitalWrite(D1, HIGH);   
  else digitalWrite(D1, LOW);    
}

// Loop through the phases

void loop()
{
  setPhase(1, 0, 0, 0, 0, 0);  
  delay(500);              
  
  setPhase(1, 1, 0, 0, 0, 0);  
  delay(500);              
  
  setPhase(1, 1, 1, 0, 0, 0);  
  delay(500);              
  
  setPhase(1, 1, 1, 1, 0, 0);  
  delay(500);              
  
  setPhase(1, 1, 1, 1, 1, 0);  
  delay(500);              
  
  setPhase(1, 1, 1, 1, 1, 1);  
  delay(500);              
  
  setPhase(0, 1, 1, 1, 1, 1);  
  delay(500);              
  
  setPhase(0, 0, 1, 1, 1, 1);  
  delay(500);              
  
  setPhase(0, 0, 0, 1, 1, 1);  
  delay(500);              
  
  setPhase(0, 0, 0, 0, 1, 1);  
  delay(500);              
  
  setPhase(0, 0, 0, 0, 0, 1);  
  delay(500);              
  
  setPhase(0, 0, 0, 0, 0, 0);  
  delay(500);              

//  yield();
}

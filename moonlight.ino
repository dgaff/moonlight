#include "NTPClient.h"
#include "ESP8266WiFi.h"
#include "WiFiUdp.h"
#include "TimeLib.h"
#include "GDBStub.h"

#include "moonPhase.h"

// Don't save your wifi to GitHub! Put these two declarations in your wifisecrets.h file and replace with your SSID and PW.
// const char *ssid     = "SSID";
// const char *password = "WIFI Password";
#include "wifisecrets.h"

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

// Turn on serial output for debugging
//#define SERIAL

// Time info
//const long utcOffsetInSeconds = -18000; // EST
const long utcOffsetInSeconds = -14400; // EDT

char daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};

// Define NTP Client to get time
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "north-america.pool.ntp.org", utcOffsetInSeconds);

// For getting the moon phase
moonPhase moonPhaseV;                       

// VT100 Terminal Emulation
#define OFF         "\033[0m"
#define BOLD        "\033[1m"
#define LOWINTENS   "\033[2m"
#define UNDERLINE   "\033[4m"
#define BLINK       "\033[5m"
#define REVERSE     "\033[7m"
#define GOTOXY( x,y) "\033[x;yH"   // Esc[Line;ColumnH  <-- this doesn't seem to be expanding correclty
#define CLS          "\033[2J"

// Run once
void setup()
{
  // Serial port output. Note that GDB isn't working reliably yet.
#ifdef SERIAL  
  Serial.begin(115200);
//  gdbstub_init();
#endif

  // Set all pins to digital output
  pinMode(D0, OUTPUT); 
  pinMode(D1, OUTPUT);
  pinMode(D2, OUTPUT);
  pinMode(D3, OUTPUT);
  pinMode(D4, OUTPUT);
  pinMode(D5, OUTPUT);
  pinMode(D6, OUTPUT);
  pinMode(D7, OUTPUT);
  pinMode(D8, OUTPUT);

  // Connect to Wifi
  WiFi.begin(ssid, password);
  while ( WiFi.status() != WL_CONNECTED ) {
    delay ( 500 );
  }

  // Initialize NTP time
  timeClient.begin();

  // Cycle the phases once
  cyclePhases();
}

// Lights up different segments of the moon light.
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

// Test function to run through all phases.
void cyclePhases()
{
  setPhase(0, 0, 0, 0, 0, 0);  
  delay(500);    
  
  setPhase(0, 0, 0, 0, 0, 1);  
  delay(500);              
  
  setPhase(0, 0, 0, 0, 1, 1);  
  delay(500);              

  setPhase(0, 0, 0, 1, 1, 1);  
  delay(500);              
  
  setPhase(0, 0, 1, 1, 1, 1);  
  delay(500);              
  
  setPhase(0, 1, 1, 1, 1, 1);  
  delay(500);              
  
  setPhase(1, 1, 1, 1, 1, 1);  
  delay(500);              
  
  setPhase(1, 1, 1, 1, 1, 0);  
  delay(500);              
  
  setPhase(1, 1, 1, 1, 0, 0);  
  delay(500);              
  
  setPhase(1, 1, 1, 0, 0, 0);  
  delay(500);              

  setPhase(1, 1, 0, 0, 0, 0);  
  delay(500);              
  
  setPhase(1, 0, 0, 0, 0, 0);  
  delay(500);               
}

// Set approximate phase angle.
// Credit: https://blogs.jccc.edu/astronomy/lab-manual/experiment-two-lunar-phases/
void setMoonPhase(int angle)
{
  if (angle >= 0 && angle < 15)
    setPhase(0, 0, 0, 0, 0, 0); // New Moon
  else if (angle >= 15 && angle < 45)
    setPhase(0, 0, 0, 0, 0, 1); // Waxing Crescent
  else if (angle >= 45 && angle < 75)
    setPhase(0, 0, 0, 0, 1, 1); // Waxing Crescent
  else if (angle >= 75 && angle < 105)
    setPhase(0, 0, 0, 1, 1, 1); // 1st Quarter (half moon)
  else if (angle >= 105 && angle < 135)
    setPhase(0, 0, 1, 1, 1, 1); // Waxing Gibbous
  else if (angle >= 135 && angle < 165)
    setPhase(0, 1, 1, 1, 1, 1); // Waxing Gibbous
  else if (angle >= 165 && angle < 195)
    setPhase(1, 1, 1, 1, 1, 1); // Full Moon
  else if (angle >= 195 && angle < 225)
    setPhase(1, 1, 1, 1, 1, 0); // Waning Gibbous
  else if (angle >= 225 && angle < 255)
    setPhase(1, 1, 1, 1, 0, 0); // Waning Gibbous
  else if (angle >= 255 && angle < 285)
    setPhase(1, 1, 1, 0, 0, 0); // 3rd Quarter (half moon)
  else if (angle >= 285 && angle < 315)
    setPhase(1, 1, 0, 0, 0, 0); // Waning Crescent
  else if (angle >= 315 && angle < 345)
    setPhase(1, 0, 0, 0, 0, 0); // Waning Crescent
  else // 345 to 360
    setPhase(0, 0, 0, 0, 0, 0); // New Moon
}

// Main Loop

bool nightModeOn = true;
int nightHour = 21; // time to shut off
int dayHour = 8;    // time to turn on
bool isNight = false;
bool bSetPhase = true; // default to setting the phase on startup

void loop()
{
  // Read the time
  timeClient.update();
  time_t time = timeClient.getEpochTime();

  // Calculate the moon phase
  moonData_t moon;              
  moon = moonPhaseV.getPhase(time-utcOffsetInSeconds);

  // Check for night mode and toggle on or off based on time. This doesn't take into account if you
  // plug the light in for the first time at night.
  if (nightModeOn)
  {
    int hour = numberOfHours(time);
    int minute = numberOfMinutes(time);
    int seconds = numberOfSeconds(time);

    // Turn on for daytime
    if (hour == dayHour && minute == 0 && seconds == 0)
    {
      bSetPhase = true;
      isNight = false;
    }
    // Turn off for nightime
    else if (hour == nightHour && minute == 0 && seconds == 0)
    {
      setMoonPhase(0); // angle 0 is new moon
      bSetPhase = false;
      isNight = true;
    }
  }

  // Don't set the phase if it's night. We don't need to set the phase very often, since it doesn't change much. 
  if (!isNight && time % 3600 == 0) bSetPhase = true;

  // Set the phase if necessary
  if (bSetPhase) 
  {
    setMoonPhase(moon.angle);
    bSetPhase = false;
  }

#ifdef SERIAL
  char timestr[10];
  Serial.print("\033[0;0H"); // terminal emulation to go to top
  sprintf(timestr, "%02d:%02d:%02d", timeClient.getHours(), timeClient.getMinutes(), timeClient.getSeconds());
  Serial.print(daysOfTheWeek[timeClient.getDay()]);
  Serial.print(", ");
  Serial.print(day(time));
  Serial.print(" ");
  Serial.print(month(time));
  Serial.print(" ");
  Serial.print(year(time));
  Serial.print(" ");
  Serial.print(", ");
  Serial.print(timestr);
  Serial.println("");
  //Serial.println(timeClient.getFormattedTime());

  // Print moon info
  Serial.print( "Moon phase angle: " );
  Serial.print( moon.angle );             // angle is a integer between 0-360
  Serial.println( " degrees." );
  Serial.print( "Moon surface lit: " );
  Serial.print( moon.percentLit * 100 );  // percentLit is a real between 0-1
  Serial.println( " %" );
#endif  

  yield();
}

#include <ArduinoOSCWiFi.h>
#include <U8g2lib.h>
#include <Wire.h>

//OLED setup
U8G2_SH1106_128X64_NONAME_F_HW_I2C oled(U8G2_R0, /* reset=*/U8X8_PIN_NONE);
// WiFi stuff change it to whatever matches your network
const char* ssid = "Khan_Hotspot";
const char* pwd = "Connection";


// for ArduinoOSC
///IP address of your computer
const char* sendIPaddress = "192.168.137.1";
//this is message address that is used by unity 
const char* arduinoMessageTag = "/arduino2";
//port specified in the OSC in variable in Unity
const int mySendPort = 8000;
//this is message address that is SENT from unity 
const char* unityMessageTag = "/unity2";
//port specified int eh OSC out variable in Unity
const int myReceivePort = 9000;

IPAddress ip;
String cnvIP;

//values from Unity, 
float paddleY;

//Motor pin values
const int motorOnePwn = 2;
const int motorOneForward = 3;
const int motorOneBackwards = 4;
const int motorTwoPwn = 5;
const int motorTwoForward = 6;
const int motorTwoBackwards = 7;
const int LEDpin1 = 8;
const int LEDpin2 = 9;

///function called when data is received from Unity
void unityOSCdata(const OscMessage& unityMessage) 
{

//read the 2 float values from Unity
paddleY = unityMessage.arg<float>(0);

if (paddleY>0){
  analogWrite(motorOnePwn, 255);
  digitalWrite(motorOneForward, HIGH);
  digitalWrite(motorOneBackwards, LOW);
  analogWrite(motorTwoPwn, 255);
  digitalWrite(motorTwoForward, HIGH);
  digitalWrite(motorTwoBackwards, LOW);
  digitalWrite(LEDpin1, HIGH);
  digitalWrite(LEDpin2, LOW);
}

else if (paddleY<0){
  analogWrite(motorOnePwn, 255);
  digitalWrite(motorOneForward, LOW);
  digitalWrite(motorOneBackwards, HIGH);
  analogWrite(motorTwoPwn, 255);
  digitalWrite(motorTwoForward, LOW);
  digitalWrite(motorTwoBackwards, HIGH);
  digitalWrite(LEDpin1, LOW);
  digitalWrite(LEDpin2, HIGH);

}

else{
  analogWrite(motorOnePwn,255);
  digitalWrite(motorOneForward, LOW);
  digitalWrite(motorOneBackwards, LOW);
  analogWrite(motorTwoPwn,255);
  digitalWrite(motorTwoForward, LOW);
  digitalWrite(motorTwoBackwards, LOW);
  digitalWrite(LEDpin1, LOW);
  digitalWrite(LEDpin2, LOW);
}

//Serial.print(paddleY);
//Serial.println();

}

void setup() 
{
  pinMode(motorOnePwn, INPUT);
  pinMode(motorOneForward, INPUT);
  pinMode(motorOneBackwards, INPUT);
  pinMode(motorTwoPwn, INPUT);
  pinMode(motorTwoForward, INPUT);
  pinMode(motorTwoBackwards, INPUT);
  pinMode(LEDpin1, OUTPUT);
  pinMode(LEDpin2, OUTPUT);
//connect to WiFi
    WiFi.begin(ssid, pwd);

    //lets you know it is connecting
    while (WiFi.status() != WL_CONNECTED) 
    {
    Serial.print(" .connecting.");
    delay(500);
    }

    ip = WiFi.localIP();
    cnvIP = "IP: "+IpAddress2String(ip);

    Serial.print("WiFi connected, IP = ");
    Serial.println(ip);

    //turns on the built in LED to show it conneted
    pinMode(LED_BUILTIN,OUTPUT);
    digitalWrite(LED_BUILTIN,HIGH);
 
    //////******THE OUTPUTS*********//////
    //This binds the incoming data to a callback function (just like how it is set up on the unity side)
    OscWiFi.subscribe(myReceivePort, unityMessageTag, unityOSCdata);

}

void loop() 
{
    
    //OscWiFi.update();  // should be called to receive + send osc
    // or do that separately
    OscWiFi.parse(); // to receive osc
    // OscWiFi.post(); // to publish osc
   

}


//helper function to convert the IP address to a string
String IpAddress2String(const IPAddress& address)
{
  return String() + address[0] + "." + address[1] + "." + address[2] + "." + address[3];
}
#include "FirebaseESP8266.h"
#include <ESP8266WiFi.h>
#include <Servo.h>

#define FIREBASE_HOST "rainwaterpr-default-rtdb.firebaseio.com"  //Database link
#define FIREBASE_AUTH "MAoY66aPoJW45E338qgWOnfIdYfschDpmiQoq1nJ"  //Database secrate

#define WIFI_SSID "RainWater"      //Router name
#define WIFI_PASSWORD "11111111"  //Router password


Servo myservo;
FirebaseData firebaseData,loadData;
FirebaseJson json;

int wait=10;




void setVal(String path, String v){
  Firebase.setString(firebaseData,"/Data/"+path,v);
}


String getVal(String path){
 if (Firebase.getString(loadData, "/Data/"+path)){
    return loadData.stringData();
  }
}


int LED=D0;
void setup() {
  pinMode(D6,INPUT);
  pinMode(LED,OUTPUT);
  pinMode(D4,OUTPUT);
  myservo.attach(D3);

   Serial.begin(9600);

  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to Wi-Fi");
  
  while (WiFi.status() != WL_CONNECTED)
  {
    digitalWrite(D4,0);
    Serial.print(".");
    delay(200);
    digitalWrite(D4,1);
    Serial.print(".");
    delay(200);
    
  }
  
  Serial.println();
  Serial.print("Connected with IP: ");
  Serial.println(WiFi.localIP());
  Serial.println();

  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  Firebase.reconnectWiFi(true);

  Firebase.setString(firebaseData,"/Testing","OK!");;

}

String up="-1";
String manual="0";

void loop() {

  if(getVal("Manual")=="1"){
    myservo.write(90);
    return;
  }
  delay(200);
  
  
  
 if(!val()){
    digitalWrite(D4,0);
    if(up!="0"){
      setVal("Mode","0");
      up="0";
      dis("No rain is"," detected!");
      myservo.write(0);
    }
    return;
  }


digitalWrite(D4,1);


 
  for(int i=0; val() &&  i<wait;i++){

    if(up!="1"){
      setVal("Mode","1");
      up="1";
    }
    digitalWrite(LED,1);
    dis("Raining! Please","wait for "+String(wait-i)+" sec");
    delay(500);
    digitalWrite(LED,0);
     if(!val()) return;
    delay(500);
   
  }


  while(val()){
    if(up!="2"){
      setVal("Mode","2");
      up="2";
    }

    digitalWrite(LED,1);
    delay(100);
    digitalWrite(LED,0);
    delay(100);
    digitalWrite(LED,1);
    delay(100);
    digitalWrite(LED,0);
    delay(2000);
       

    
    myservo.write(90);
    dis("Pure water","is  filling!");
  
    
  }

}

bool val(){
  return !digitalRead(D6);
}



void dis(String a, String b){
  Serial.println(a+" "+b);
}

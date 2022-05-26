#include <SoftwareSerial.h>
#include <Servo.h>

SoftwareSerial serialimiz(0, 1);// RX, TX
Servo motor;

#define kamelya 2
                                                                            
#define havuz 3
#define kapi 7 
#define cit 4
#define k_led 5
#define y_led 6
#define m_led 8

#define echoPin 9
#define trigPin 10
#define buzzerPin 11


int salter = 0, kapidurum = 0, evsalter = 0, sure = 100, alarmacik = 0, hhh = 0;

void setup()
{ 
  Serial.begin(9600);
  serialimiz.begin(9600);
  pinMode(k_led,OUTPUT);
  pinMode(y_led,OUTPUT);
  pinMode(m_led,OUTPUT);
  pinMode(cit,OUTPUT);
  pinMode(havuz,OUTPUT);
  pinMode(kapi,OUTPUT);
  pinMode(kamelya,OUTPUT);
  
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(buzzerPin, OUTPUT);
  
  motor.attach(kapi);//servonun bağlı olduğu pini ayarladık
  kapikapat();

  Serial.println("Akıllı Ev uygulamasi");
  digitalWrite(k_led, HIGH);
  digitalWrite(y_led, HIGH);
  digitalWrite(m_led, HIGH);
}
void loop()
{
  
  char deger = serialimiz.read();

  if(deger == 'x')
  {
    alarmacik = (alarmacik + 1)%2;
    Serial.println(alarmacik);
  }
  if(alarmacik == 1)
  {
    int olcum = mesafe();
    if(olcum <= 15 && olcum > 0)
    {
      tone(buzzerPin, 1023);
serialimiz.print("alarm alarm kalk hirsiz var");
      
     
    }
    else
    {
      noTone(buzzerPin);
      digitalWrite(cit, LOW);
    }
    serialimiz.println(olcum);
  }//alarm acık == 1

  if (deger == '1') 
  {
    if(salter == 0)
      salter = 1;
    else
    {
      salter = 0;
    digitalWrite(kamelya, LOW);
    digitalWrite(cit, LOW);
    digitalWrite(havuz, LOW);
    }
  }
  else if (deger == '2' && salter == 1) 
  {
    Serial.println("kamelya yan");
    digitalWrite(kamelya, !digitalRead(kamelya));
  }
  else if (deger == '3' && salter == 1) 
  {
    Serial.println("havuz yan");
    digitalWrite(havuz, !digitalRead(havuz));
  }
  else if (deger == '4' && salter == 1) 
  {
    Serial.println("cit yan");
    digitalWrite(cit, !digitalRead(cit));
  }
  else if (deger == '5') 
  {
    Serial.println("kapiackapa");
    if(kapidurum == 0)
    {
      kapiac();
    }
    else if(kapidurum == 1)
    {
      kapikapat();
    }
  }
  else if (deger == '6') 
  {
      Serial.println("evsalter");
      evsalter = (evsalter + 1) % 2;
      if(evsalter == 1)
      {
        beyaz();
      }else
      {
        digitalWrite(k_led, HIGH);
        digitalWrite(y_led, HIGH);
        digitalWrite(m_led, HIGH);
      }
     hhh = 0;
  }
  else if (deger == '7' && evsalter == 1) 
  {
     Serial.println("yesil yan");
     yesil();
     hhh = 0;
  }
  else if (deger == '8' && evsalter == 1) 
  {
    Serial.println("kirmizi yan");
     kirmizi();
     hhh = 0;
  }
  else if (deger == '9' && evsalter == 1) 
  {
    Serial.println("mavi yan");
     mavi();
     hhh = 0;
  }
  else if (deger == 'a' && evsalter == 1) 
  {
    Serial.println("sari yan");
     sari();
     hhh = 0;
  }
  else if (deger == 'b' && evsalter == 1) 
  {
    Serial.println("turkuaz yan");
     turkuaz();
     hhh = 0;
  }
  else if (deger == 'c' && evsalter == 1) 
  {
    Serial.println("mor yan");
     mor();
     hhh = 0;
  }
  else if (deger == 'h' && evsalter == 1) 
  {
    Serial.println("hepsi");
    hhh = (hhh + 1)%2;
  }
  if(evsalter == 1 && hhh == 1) 
  {
    Serial.println("sirayla yan");
    beyaz();delay(sure);
    sari();delay(sure);
    mavi();delay(sure);
    yesil();delay(sure);
    kirmizi();delay(sure);
    mor();delay(sure);
    turkuaz();delay(sure);
  }

}

void kapiac()
{
  kapidurum = 1;
  motor.write(100);
}
void kapikapat()
{
  kapidurum = 0;
  motor.write(1);
}
void kirmizi(){
digitalWrite(k_led,LOW);
digitalWrite(y_led,HIGH);
digitalWrite(m_led,HIGH);
}

void yesil(){
digitalWrite(k_led,HIGH);
digitalWrite(y_led,LOW);
digitalWrite(m_led,HIGH);
}
void mavi(){
digitalWrite(k_led,HIGH);
digitalWrite(y_led,HIGH);
digitalWrite(m_led,LOW);
}

void sari(){
digitalWrite(k_led,LOW);
digitalWrite(y_led,LOW);
digitalWrite(m_led,HIGH);
}
void mor(){
digitalWrite(k_led,LOW);
digitalWrite(y_led,HIGH);
digitalWrite(m_led,LOW);
}
void turkuaz()
{
digitalWrite(k_led,HIGH);
digitalWrite(y_led,LOW);
digitalWrite(m_led,LOW);
}
void beyaz()
{
  digitalWrite(k_led,LOW);
  digitalWrite(y_led,LOW);
  digitalWrite(m_led,LOW);
}
int mesafe()
{
  long duration, distance;

  digitalWrite(trigPin,LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);
  distance = duration / 58.2;
  delay(50);
  if(distance >20)
    distance = 21;
  else if(distance <=0)
  distance = 21;

  return distance;
}

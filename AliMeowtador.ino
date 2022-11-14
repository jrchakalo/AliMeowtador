#include <Servo.h>
#include <DS3231.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#define pinServo A1
#define led 7
#define butao 11
#define rele 9
#define butao2 12

LiquidCrystal_I2C lcd(0x27,2,1,0,4,5,6,7,3, POSITIVE);
Servo servo1;
DS3231 rtc(SDA, SCL);
Time t;

int estadobutao=0, angulo=0, estadobutao2=0, guardaestado=0; 
int hrAtual, mnAtual;
int hrAlim1, mnAlim1, hrAlim2, mnAlim2;
int demosCom1, demosCom2;

void setup() {
  Serial.begin(1200);
  rtc.begin();
  lcd.begin(16,2);

  servo1.attach(pinServo);
  lcd.setBacklight(HIGH);
  
  pinMode(led, OUTPUT);
  pinMode(butao, INPUT);
  pinMode(rele, OUTPUT);
  pinMode(butao2, INPUT);
  
  servo1.write(120);
  lcd.setCursor(0,0);
  lcd.print("  Bem Vindo Ao  ");
  lcd.setCursor(0,1);
  lcd.print(" AliMEOWtador!! ");
  delay(3500);
  lcd.clear();
  
  hrAlim1 = 15;
  mnAlim1 = 45;
  demosCom1 = 0;
  hrAlim2 = 15;
  mnAlim2 = 46;
  demosCom2 = 0;
  
  //rtc.setDate(29,2,2020);
  //rtc.setDOW(SATURDAY);
  //rtc.setTime(2,1,0);
}

void loop() {
  t = rtc.getTime();
  hrAtual = t.hour;
  mnAtual = t.min;

  lcd.setCursor(0,0);
  lcd.print(" Horario Atual: ");
  lcd.setCursor(0,1);
  lcd.print("    ");
  lcd.print(rtc.getTimeStr());
  lcd.print("    ");
  delay(2500);
  lcd.clear();
  if((demosCom1 == 0 && demosCom2 == 0) || (demosCom1 == 1 && demosCom2 == 1)){
    lcd.print("Prox Alimentacao");
    lcd.setCursor(0,1);
    lcd.print("   ");
    lcd.print(hrAlim1);
    lcd.print("hr ");
    lcd.print(mnAlim1);
    lcd.print("min");
    lcd.print("   ");
    delay(2500);
  }else if(demosCom1 == 1 && demosCom2 == 0){
    lcd.print("Prox Alimentacao");
    lcd.setCursor(0,1);
    lcd.print("   ");
    lcd.print(hrAlim2);
    lcd.print("hr ");
    lcd.print(mnAlim2);
    lcd.print("min");
    lcd.print("   ");
    delay(2500);
  }
  
  estadobutao2 = digitalRead(butao2);
  if (estadobutao2 == HIGH){
    guardaestado = !guardaestado;
    delay(300);
    if (guardaestado == HIGH){
      digitalWrite(rele, HIGH);
    }else{
      digitalWrite(rele, LOW);
    }
  } 

  estadobutao = digitalRead(butao);
  if((estadobutao == 1) || ((hrAtual == hrAlim1) && (mnAtual == mnAlim1) && (demosCom1 == 0))){
    if((hrAtual == hrAlim1) && (mnAtual == mnAlim1) && (demosCom1 == 0)){
      demosCom1 = 1;
    }
    angulo = 60;
    servo1.write(angulo);
    digitalWrite(led, HIGH);
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("                ");
    lcd.setCursor(0,1);
    lcd.print(" AliMEOWtando...");
    delay(5000);
    estadobutao=0;
  }else{
    angulo = 120;
    servo1.write(angulo);
    digitalWrite(led, LOW);
  }
  
  if((estadobutao == 1) || ((hrAtual == hrAlim2) && (mnAtual == mnAlim2) && (demosCom2 == 0))){
    if((hrAtual == hrAlim2) && (mnAtual == mnAlim2) && (demosCom2 == 0)){
      demosCom2 = 1;
    }
    angulo = 60;
    servo1.write(angulo);
    digitalWrite(led, HIGH);
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("                ");
    lcd.setCursor(0,1);
    lcd.print(" AliMEOWtando...");
    delay(5000);
    estadobutao=0;
  }else{
    angulo = 120;
    servo1.write(angulo);
    digitalWrite(led, LOW);
  }

  if(demosCom1 == 0 || demosCom1 == 1 && demosCom2 == 1){
    Serial.print("Horario Atual: ");
    Serial.println(rtc.getTimeStr());
    Serial.print("Proxima alimentacao: ");
    Serial.print(hrAlim1);
    Serial.print("h ");
    Serial.print(mnAlim1);
    Serial.println("min");
    Serial.println(" ");
  }

  if(demosCom1 == 1 && demosCom2 == 0){
    Serial.print("Horario atual: ");
    Serial.println(rtc.getTimeStr());
    Serial.print("Proxima alimentacao: ");
    Serial.print(hrAlim2);
    Serial.print("h ");
    Serial.print(mnAlim2);
    Serial.println("min");
    Serial.println(" ");
  }

  if(hrAtual == 0 && mnAtual == 0){
    demosCom1 = 0;
    demosCom2 = 0; 
  }
    
  delay(1000);
}

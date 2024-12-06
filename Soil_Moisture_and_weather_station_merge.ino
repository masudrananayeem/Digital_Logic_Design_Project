#include<Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2); 
byte degree_symbol[8] = 
              {
                0b00111,
                0b00101,
                0b00111,
                0b00000,
                0b00000,
                0b00000,
                0b00000,
                0b00000
              };
int gate=11; 
volatile unsigned long duration=0;
unsigned char i[5];
unsigned int j[40];
unsigned char value=0;
unsigned answer=0;
int z=0;
int b=1;
void setup(){

Serial.begin(9600);
lcd.init();
lcd.backlight();
lcd.clear();
pinMode(2, OUTPUT);
digitalWrite(2, HIGH);
delay(1000);
lcd.setCursor(0, 0);
lcd.print("IRRIGATION");
lcd.setCursor(0, 1);
lcd.print("SYSTEM IS ON ");
lcd.print("");
delay(3000);
lcd.clear();
lcd.setCursor(11,0);
 lcd.print("T=");
 lcd.setCursor(11,1);
 lcd.print("H=");
 lcd.createChar(1, degree_symbol);
 lcd.setCursor(14,0);
 lcd.write(1);
 lcd.print("C");
 lcd.setCursor(15,1);
 lcd.print("%");
}
void loop() {
delay(0);
 while(1)
 {
  int value = analogRead(A0);
  Serial.println(value);
  if (value > 850){
    digitalWrite(2, LOW);
    lcd.setCursor(0, 0);
    lcd.print("Pump : ON");
} 
else {
    digitalWrite(2, HIGH);
    lcd.setCursor(0, 0);
    lcd.print("Pump : OFF");
} 
if (value < 300) {
    lcd.setCursor(0, 1);
    lcd.print("Mois: HIGH");
} else if (value > 300 && value < 850) {
    lcd.setCursor(0, 1);
    lcd.print("Mois: MID");
} else if (value > 850) {
    lcd.setCursor(0, 1);
    lcd.print("Mois: LOW");
}

 
  delay(0);
  pinMode(gate,OUTPUT);
  digitalWrite(gate,LOW);
  delay(20);
  digitalWrite(gate,HIGH);
  pinMode(gate,INPUT_PULLUP);//by default it will become high due to internal pull up
 // delayMicroseconds(40);

  
  duration=pulseIn(gate, LOW);
  if(duration <= 84 && duration >= 72)
  {
      while(1)
      {
        duration=pulseIn(gate, HIGH);
        
        if(duration <= 26 && duration >= 20){
        value=0;}
        
        else if(duration <= 74 && duration >= 65){
        value=1;}
        
        else if(z==40){
        break;}
        
        i[z/8]|=value<<(7- (z%8));
        j[z]=value;
        z++;
      }
    }
answer=i[0]+i[1]+i[2]+i[3];

if(answer==i[4] && answer!=0)
{
lcd.setCursor(13,0);
lcd.print(i[2]);
lcd.setCursor(13,1);
lcd.print(i[0]);
}

z=0;
i[0]=i[1]=i[2]=i[3]=i[4]=0;
 }
}
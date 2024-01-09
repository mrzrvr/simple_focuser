/*
 * Versione 1.0 dello sketch per simple focuser. Usa un display led ssd 1306 un modulo a 4 pulsanti e un easydriver
 * con questa configurazione il motore compie un giro in 1600 (micro)passi
 * testato ok su breadboard - 11/01/2024
 */
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define BUTTON_UP 5
#define BUTTON_DOWN 6
#define BUTTON_VP 7
#define BUTTON_VM 8
#define STEP_PIN                9
#define DIRECTION_PIN           4

int pos = 0;
int vel = 0;//indice velocità
int up;
int down;
int velp;
int velm;
int t_delay = 50;
int speedness[] = {1,10,50,100,200,400};

#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
 
void setup() {
  Serial.begin(115200);
  pinMode(BUTTON_UP, INPUT);
  pinMode(BUTTON_DOWN, INPUT);
  pinMode(BUTTON_VP, INPUT);
  pinMode(BUTTON_VM, INPUT);
  pinMode(STEP_PIN,OUTPUT);
  pinMode(DIRECTION_PIN,OUTPUT);

  delay(2000);
  Serial.println(F("Starting!"));
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }
  Serial.println(F("Initialized!"));
  display.display();
  delay(2000);
  show_display();
}
 
void loop() {
  up = digitalRead(BUTTON_UP);
  if (up==0)moveup (speedness[vel]);
  delay(t_delay);
  down = digitalRead(BUTTON_DOWN);
  if (down==0)movedown (speedness[vel]);
   delay(t_delay);
  velp = digitalRead(BUTTON_VP);
  if (velp==0)velup ();
   delay(t_delay);
   velm = digitalRead(BUTTON_VM);
  if (velm==0)veldown ();
   delay(t_delay);
}

void moveup(int steps){
 pos = pos + steps;
 digitalWrite(DIRECTION_PIN,HIGH);
 motor_move(steps);
  show_display();
}

void movedown(int steps){
 pos = pos - steps;
 digitalWrite(DIRECTION_PIN,LOW);
 motor_move(steps);
 show_display();
}

void motor_move(int distance){
  for(int i=0;i<=distance;i++){
    digitalWrite(STEP_PIN, HIGH);
    delay(1);
    digitalWrite(STEP_PIN, LOW);
    delay(1);
  }
}
void velup(){
 vel++;;
 if(vel>5) vel=5;
  show_display();
}

void veldown(){
 vel--;;
 if(vel<0) vel=0;
  show_display();
}
void show_display(){
  display.clearDisplay();
  display.display();
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(10, 10);
  display.setTextSize(2);
  display.print(F("POS"));
   display.setCursor(60, 10);
  display.print(pos);
  display.setCursor(10, 50);
  display.setTextSize(1);
  display.print(F("VEL"));
   display.setCursor(60, 50);
  display.print(speedness[vel]);
  display.display();
}

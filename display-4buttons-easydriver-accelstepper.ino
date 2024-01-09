#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <AccelStepper.h>
 
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define BUTTON_UP 5
#define BUTTON_DOWN 6
#define BUTTON_VP 7
#define BUTTON_VM 8



int incremento = 10;
int pos = 200;
int pos0 = 200;
int vel = 0;//indice velocità
int up;
int down;
int velp;
int velm;
int reset;
int t_delay = 50;
int speedness[] = {1,10,50,100,200,400};
// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

//AccelStepper stepper(AccelStepper::DRIVER, step_pin, dir_pin)
AccelStepper stepper(AccelStepper::DRIVER, 16, 14);
 
void setup() {
  Serial.begin(115200);
  pinMode(BUTTON_UP, INPUT);
  pinMode(BUTTON_DOWN, INPUT);
  pinMode(BUTTON_VP, INPUT);
  pinMode(BUTTON_VM, INPUT);


  delay(2000);
  Serial.println(F("Starting!"));
 
  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }
  Serial.println(F("Initialized!"));
 
  
  display.display();
  delay(2000); // Pause for 2 seconds
  show_display();
  stepper.setMaxSpeed(1000);
  //stepper.setAcceleration(1000);
  stepper.setSpeed(500);
}
 
void loop() {
  stepper.runSpeed();
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

void set_reset(){
  pos = pos0;
  show_display();
}
void moveup(int steps){
 pos = pos + steps;
 stepper.move(steps);
  show_display();
}

void movedown(int steps){
 pos = pos - steps;
 stepper.move(-steps);
  show_display();
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
  // Clear the buffer
  display.clearDisplay();
  // Refresh (apply command)
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
  // Refresh (apply command)
  display.print(speedness[vel]);
  display.display();
}

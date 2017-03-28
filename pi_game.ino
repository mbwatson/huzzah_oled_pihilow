#include <Arduino.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <string>

char pi[] = "3.1415926535897932384626433832795028841971693993751058209749445923078164062862089986280348253421170679821480865132823066470938446095505822317253594081284811174502841027019385211055596446229489549303819644288109756659334461284756482337867831652712019091456485669234603486104543266482133936072602491412737245870066063155881748815209209628292540917153643678925903600113305305488204665213841469519415116094330572703657595919530921861173819326117931051185480744623799627495673518857527248912279381830119491298336733624406566430860213949463952247371907021798609437027705392171762931767523846748184676694051320005681271452635608277857713427577896091736371787214684409012249534301465495853710507922796892589235420199561121290219608640344181598136297747713099605187072113499999983729780499510597317328160963185950244594553469083026425223082533446850352619311881710100031378387528865875332083814206171776691473035982534904287554687311595628638823537875937519577818577805321712268066130019278766111959092164201989";

const int buttonA = 0;
const int buttonB = 16;
const int buttonC = 2;

const int digits_num = 10;

unsigned long processTime;
int a_state = 0;
int b_state = 0;
int c_state = 0;
int last_a_state = a_state;
int last_b_state = b_state;
int last_c_state = c_state;

int counter = 4;
int score = 0;
bool first_time = 1;

Adafruit_SSD1306 display = Adafruit_SSD1306();

void setup() {
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C); 
  pinMode(buttonA, INPUT_PULLUP);
  pinMode(buttonB, INPUT_PULLUP);
  pinMode(buttonC, INPUT_PULLUP);
}

void loop() {
  last_a_state = a_state;
  last_b_state = b_state;
  last_c_state = c_state;
  
  a_state = digitalRead(buttonA);
  b_state = digitalRead(buttonB);
  c_state = digitalRead(buttonC);
  
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.clearDisplay();
  
  // show position
  display.setCursor(0,0);
  display.print("DIGITS: ");
  display.print(counter - 1);
  display.setCursor(0,10);
  display.print("SCORE: ");
  display.print(score);
  
  if ((a_state != HIGH) and (a_state != last_a_state)) {
    if (pi[counter] > pi[counter - 1]) {
      counter += 1;
      if (first_time) { score += 1; }
      first_time = 1;
    } else {
      first_time = 0;
      score -= 1;
    }
  }
  if ((b_state != HIGH) and (b_state != last_b_state)) {
    if (pi[counter] == pi[counter - 1]) {
      counter += 1;
      if (first_time) { score += 1; }
      first_time = 1;
    } else {
      first_time = 0;
      score -= 1;
    }
  }
  if ((c_state != HIGH) and (c_state != last_c_state)) {
    if (pi[counter] < pi[counter - 1]) {
      counter += 1;
      if (first_time) { score += 1; }
      first_time = 1;
    } else {
      first_time = 0;
      score -= 1;
    }
  }

  // show digits
  display.setTextSize(2);
  display.setCursor(60,16);
  for (int i = -4; i < 0; i++) {
    display.print(pi[counter + i]);
  }
  display.display();
  delay(10);
}

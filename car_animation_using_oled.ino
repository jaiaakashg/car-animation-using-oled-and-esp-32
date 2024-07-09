#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Wire.h>
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
#define BUTTON_LEFT 14
#define BUTTON_RIGHT 27

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
int carX = SCREEN_WIDTH / 2 - 7;
const int carY = SCREEN_HEIGHT - 20;

// Score variable
int score = 0;

// Function prototypes
void drawRoad(int offset);
void drawBackground(int offset);
void drawCar(int x, int y);
void drawObstacle(int x, int y);
void handleButtons();

void setup() {
  Serial.begin(115200);
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;);
  }

  display.clearDisplay();
  pinMode(BUTTON_LEFT, INPUT_PULLUP);
  pinMode(BUTTON_RIGHT, INPUT_PULLUP);
}

void loop() {
  static int frame = 0;
  display.clearDisplay();
  handleButtons();
  drawRoad(frame);
  drawBackground(frame);
  drawCar(carX, carY);

  if (frame % 100 < 50) {
    drawObstacle(SCREEN_WIDTH / 2 - 7, SCREEN_HEIGHT - 40 - (frame % 100));
  }

  display.display();
  frame += 2;
  score++;
  display.setCursor(0, 0);
  display.setTextColor(SSD1306_WHITE);
  display.setTextSize(1);
  display.print("Score: ");
  display.print(score);

  delay(50);
}

void drawRoad(int offset) {
  display.drawLine(0, SCREEN_HEIGHT - 1, SCREEN_WIDTH, SCREEN_HEIGHT - 1, SSD1306_WHITE);
}

void drawBackground(int offset) {
  for (int x = 0; x < SCREEN_WIDTH; x += 40) {
    int adjustedX = (x - offset) % SCREEN_WIDTH;
    drawTree(adjustedX, 10);
    drawBuilding((adjustedX + 20) % SCREEN_WIDTH, 5);
  }
}

void drawTree(int x, int y) {
  display.drawRect(x + 2, y + 5, 4, 8, SSD1306_WHITE);
  display.fillTriangle(x - 2, y + 5, x + 4, y - 5, x + 10, y + 5, SSD1306_WHITE);
}

void drawBuilding(int x, int y) {
  display.drawRect(x, y, 10, 15, SSD1306_WHITE); 
  for (int i = 0; i < 3; i++) {
    display.drawLine(x, y + 5 * i, x + 10, y + 5 * i, SSD1306_WHITE); 
    display.drawLine(x + 5, y + 5 * i, x + 5, y + 5 * (i + 1), SSD1306_WHITE);
  }
}

void drawCar(int x, int y) {
  display.fillRect(x, y, 14, 8, SSD1306_WHITE); 
  display.fillRect(x + 3, y - 3, 8, 4, SSD1306_WHITE); 
  display.drawRect(x + 5, y - 2, 4, 2, SSD1306_BLACK);
  display.drawRect(x - 1, y, 2, 2, SSD1306_WHITE);
  display.drawRect(x + 13, y, 2, 2, SSD1306_WHITE);
  display.fillCircle(x + 3, y + 8, 3, SSD1306_WHITE); 
  display.fillCircle(x + 11, y + 8, 3, SSD1306_WHITE); 
  display.fillCircle(x + 3, y + 8, 1, SSD1306_BLACK);
  display.fillCircle(x + 11, y + 8, 1, SSD1306_BLACK);
  display.drawLine(x + 2, y + 2, x + 2, y + 6, SSD1306_BLACK);
  display.drawLine(x + 12, y + 2, x + 12, y + 6, SSD1306_BLACK); 
  display.drawLine(x + 1, y + 4, x + 13, y + 4, SSD1306_BLACK); 
}

void drawObstacle(int x, int y) {
  display.fillTriangle(x, y, x + 5, y - 10, x + 10, y, SSD1306_WHITE); 
}

void handleButtons() {
  if (digitalRead(BUTTON_LEFT) == LOW && carX > 0) {
    carX -= 2;
  }
  if (digitalRead(BUTTON_RIGHT) == LOW && carX < SCREEN_WIDTH - 14) {
    carX += 2;
  }
}


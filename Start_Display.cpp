#include <TFT_eSPI.h>
#include "Start_Display.h"
//#include "spaceship.h"

TFT_eSPI tft = TFT_eSPI();   // uses User_Setup.h config

// Cursor variables
int cursorX = 160;  // Start in middle of screen (adjust to your LCD size)
int cursorY = 120;
int cursorRadius = 5; // Cursor size
int stepSize = 3;    // movement step size

//click start function
int startBtnX = 80;
int startBtnY = 160;
int startBtnW = 160;
int startBtnH = 40;
bool start=false;

unsigned long lastBlink = 0;
bool showSubtitle = true;

Meteor meteors[MAX_METEORS];


// Number of stars
const int NUM_STARS = 20;
int starX[NUM_STARS];
int starY[NUM_STARS];

void Initmeteor()
{
  for(int i=0; i<MAX_METEORS; i++) 
  {
    meteors[i].x = random(0, SCREEN_W);
    meteors[i].y = 0; // start at top
    meteors[i].dx = 1 + random(1,6); // speed x
    meteors[i].dy = 1 + random(1,6); // speed y
    meteors[i].radius = random(1, 4); // random(min, max) → min inclusive, max exclusive
    meteors[i].active = true;
    for(int j=0; j<TAIL_LENGTH; j++){
      meteors[i].tailX[j] = -10;
      meteors[i].tailY[j] = -10;
    }
  }
}

void updateMeteor(Meteor &m)
{
  if(!m.active) return;

  // erase oldest tail
  tft.fillCircle(m.tailX[TAIL_LENGTH-1], m.tailY[TAIL_LENGTH-1], m.radius, BLACK);

  // shift tail
  for(int i=TAIL_LENGTH-1; i>0; i--){
    m.tailX[i] = m.tailX[i-1];
    m.tailY[i] = m.tailY[i-1];
  }

  // add new head
  m.tailX[0] = m.x;
  m.tailY[0] = m.y;

  // draw tail
  for(int i=0; i<TAIL_LENGTH; i++){
    uint16_t color = tft.color565(255-i*40, 255-i*40, 255); // fading white
    tft.fillCircle(m.tailX[i], m.tailY[i], m.radius, color);
  }

  // move head
  m.x += m.dx;
  m.y += m.dy;

  // disappear offscreen
  if(m.x - m.radius > SCREEN_W || m.y - m.radius > SCREEN_H){
    m.active = false; // optional: deactivate
  }
}

void meteor()
{
  for(int i=0; i<MAX_METEORS; i++)
  {
    if(meteors[i].active) 
    {
        updateMeteor(meteors[i]);

        // Check if meteor went off screen and erase tail immediately
        if (meteors[i].y - meteors[i].radius > SCREEN_H || meteors[i].x - meteors[i].radius > SCREEN_W) 
        {
            // erase tail
            for(int t = 0; t < TAIL_LENGTH; t++)
            {
                tft.fillCircle(meteors[i].tailX[t], meteors[i].tailY[t], meteors[i].radius, BLACK);
            }
            meteors[i].active = false;
        }
    }
    else
    {
      // RANDOM chance to respawn meteor
        if(random(0,100) > 97)  // tweak probability to control frequency
        {
            meteors[i].x = random(0, SCREEN_W);
            meteors[i].y = 0;
            meteors[i].dx = 1 + random(1,6);
            meteors[i].dy = 1 + random(1,6);
            meteors[i].radius = random(1,4);
            meteors[i].active = true;
            for(int j=0;j<TAIL_LENGTH;j++)
            {
                meteors[i].tailX[j] = -10;
                meteors[i].tailY[j] = -10;
            } 
        }   
    }
  }
}

void Moving_Stars_Init()
{
  // Initialize random stars
  randomSeed(analogRead(0));
  for (int i = 0; i < NUM_STARS; i++) 
  {
    starX[i] = random(0, tft.width());
    starY[i] = random(0, tft.height());
  }
}

void Moving_Stars()
{
    for (int i = 0; i < NUM_STARS; i++) 
    {
    // Erase old star
    tft.drawPixel(starX[i], starY[i], BLACK);

    // Update position
    starY[i]++;

    // Reset if out of screen
    if (starY[i] >= tft.height()) 
    {
      starY[i] = 0;
      starX[i] = random(0, tft.width());
    }

    // Draw new star
    tft.drawPixel(starX[i], starY[i], WHITE);
  }
}

void Title()
{

  tft.setTextColor(TFT_CYAN, TFT_BLACK);
  tft.setFreeFont(&FreeSerif24pt7b);
  tft.setCursor(20, 80);
  tft.println("GALAXAME");

  tft.fillRoundRect(80, 160, 160, 40, 10, TFT_BLUE);
  tft.setTextColor(TFT_WHITE, TFT_BLUE);
  tft.setFreeFont(&FreeSans12pt7b); // or FreeSerif24pt7b
  tft.setCursor(120, 185);
  tft.println("START");

  unsigned long now = millis();

  // Blink subtitle every 500ms
  if (now - lastBlink > 500) 
  {
    lastBlink = now;
    showSubtitle = !showSubtitle;

    const char* subtitle = "Press START to play";
    tft.setFreeFont(&FreeSans12pt7b);

    int w = tft.textWidth(subtitle);
    int h = tft.fontHeight();

    int x = 40;   // left
    int y = 120;  // baseline

    // Erase rectangle with some extra padding
    tft.fillRect(x, y - h, w, h + 10, TFT_BLACK);

    if (showSubtitle) 
    {
      tft.setTextColor(TFT_YELLOW, TFT_BLACK);
      tft.setCursor(x, y);
      tft.println(subtitle);
    }
  }
}

void Joystick_Init()
{
  pinMode(JOY_SW, INPUT_PULLUP); // Joystick button

  // Draw initial cursor
  tft.fillCircle(cursorX, cursorY, cursorRadius, TFT_RED);
}

void Joystick()
{

  static int oldX = cursorX;
  static int oldY = cursorY;

  int xVal = analogRead(JOY_X);
  int yVal = analogRead(JOY_Y);

  // Update position
  if (xVal < 1500 && cursorX > 0) cursorX -= stepSize;
  if (xVal > 3000 && cursorX < tft.width() - 1) cursorX += stepSize;
  if (yVal < 1500 && cursorY > 0) cursorY -= stepSize;
  if (yVal > 3000 && cursorY < tft.height() - 1) cursorY += stepSize;

  // Erase old cursor
  tft.fillCircle(oldX, oldY, 3, TFT_BLACK);

  // Draw new cursor
  tft.fillCircle(cursorX, cursorY, 3, BLUE);

  // Save current position as old for next frame
  oldX = cursorX;
  oldY = cursorY;
}

bool Click_Start()
{
  // Check joystick press
  if (cursorX > startBtnX && cursorX < startBtnX + startBtnW && cursorY > startBtnY && cursorY < startBtnY + startBtnH) 
  {

    // Draw new cursor
    tft.fillCircle(cursorX, cursorY, 3, YELLOW);

    if (digitalRead(JOY_SW) == LOW) 
    {

      // Action when pressing inside START button
      tft.fillScreen(BLACK);
      tft.setTextColor(TFT_GREEN, TFT_BLACK);
      tft.setFreeFont(&FreeSans12pt7b);
      tft.setCursor(100, 120);
      tft.println("Game Starting...");
      delay(1500);
      start=true;
      return true;
    }
    
  }
    return false;
}

bool Continue()
{

  static bool lastState = HIGH; // assume not pressed at start
  bool currentState = digitalRead(JOY_SW);

  if (lastState == HIGH && currentState == LOW) {
    // Button was just pressed
    lastState = currentState;
    return true;
  }

  lastState = currentState;
  return false;
}

void Crash()
{
  tft.fillScreen(BLACK);

  tft.setFreeFont(&FreeSansBold18pt7b); // not too big
  tft.setTextColor(TFT_YELLOW, TFT_BLACK);

  // Calculate position roughly centered
  int textX = 100;  // adjust by trial
  int textY = 120; // vertical position near robot
  tft.setCursor(textX, textY);
  tft.println("CRASH!");
}

// Hotspot coordinates
int hotspotX = 200;
int hotspotY = 20;
int hotspotW = 100;
int hotspotH = 100;

// Function to handle selection
bool galaxyClick() 
{
    // Update joystick and cursor position
    Joystick(); // moves cursorX and cursorY

    // Check if joystick button is pressed
    if (digitalRead(JOY_SW) == LOW) 
    { // button pressed
        // Check if cursor is inside hotspot
        if (cursorX >= hotspotX && cursorX <= hotspotX + hotspotW &&
            cursorY >= hotspotY && cursorY <= hotspotY + hotspotH) 
        {
          return true; // hotspot selected
        }
    }
    return false; // not selected
}

// Draw a flickering star with limited random size
void drawFlickeringStar(int x, int y, int baseRadius, uint16_t color) 
{
  int flicker = random(-1, 2); // random offset: -1, 0, or +1
  int r = baseRadius + flicker;

  if (r < 1) r = 1;  // avoid disappearing
  if (r > baseRadius + 1) r = baseRadius + 1; // limit max size

  // Draw glowing star effect
  for (int i = r; i > 0; i--) 
  {
    int brightness = map(i, 0, r, 30, 255); 
    uint16_t flickerColor = tft.color565(brightness, brightness, brightness); 
    tft.fillCircle(x, y, i, flickerColor);
  }
}

#define BTN_IGNORE_X 40
#define BTN_IGNORE_Y 160
#define BTN_WIDTH    100
#define BTN_HEIGHT   40

#define BTN_INVEST_X 180
#define BTN_INVEST_Y 160

int ShowChoice()
{

   int choice = -1;

  while (choice == -1)
  {
    // 1. Draw background animation
    Moving_Stars();
    Joystick();

    // 2. Redraw buttons every frame
    tft.fillRect(BTN_IGNORE_X, BTN_IGNORE_Y, BTN_WIDTH, BTN_HEIGHT, TFT_DARKGREY);
    tft.drawRect(BTN_IGNORE_X, BTN_IGNORE_Y, BTN_WIDTH, BTN_HEIGHT, TFT_WHITE);
    tft.setTextColor(TFT_WHITE, TFT_DARKGREY);
    tft.drawString("Ignore it", BTN_IGNORE_X + 10, BTN_IGNORE_Y + 12, 2);

    tft.fillRect(BTN_INVEST_X, BTN_INVEST_Y, BTN_WIDTH, BTN_HEIGHT, TFT_DARKGREY);
    tft.drawRect(BTN_INVEST_X, BTN_INVEST_Y, BTN_WIDTH, BTN_HEIGHT, TFT_WHITE);
    tft.setTextColor(TFT_WHITE, TFT_DARKGREY);
    tft.drawString("Investigate", BTN_INVEST_X + 5, BTN_INVEST_Y + 12, 2);

    // 3. Highlight logic + input
    if (cursorX > BTN_IGNORE_X && cursorX < BTN_IGNORE_X + BTN_WIDTH &&
        cursorY > BTN_IGNORE_Y && cursorY < BTN_IGNORE_Y + BTN_HEIGHT)
    {
      tft.drawRect(BTN_IGNORE_X, BTN_IGNORE_Y, BTN_WIDTH, BTN_HEIGHT, TFT_RED);
      if (digitalRead(JOY_SW) == LOW)
      {
        choice = 0;
        while (digitalRead(JOY_SW) == LOW) delay(10); // wait for release
      }
    }
    else if (cursorX > BTN_INVEST_X && cursorX < BTN_INVEST_X + BTN_WIDTH &&
             cursorY > BTN_INVEST_Y && cursorY < BTN_INVEST_Y + BTN_HEIGHT)
    {
      tft.drawRect(BTN_INVEST_X, BTN_INVEST_Y, BTN_WIDTH, BTN_HEIGHT, TFT_RED);
      if (digitalRead(JOY_SW) == LOW)
      {
        choice = 1;
        while (digitalRead(JOY_SW) == LOW) delay(10); // wait for release
      }
    }

    delay(20);
  }

  delay(150); // small debounce before returning
  return choice;


  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}

int Yes_or_No()
{

   int choice = -1;

  while (choice == -1)
  {
    // 1. Draw background animation
    Moving_Stars();
    Joystick();

    // 2. Redraw buttons every frame
    tft.fillRect(BTN_IGNORE_X, BTN_IGNORE_Y, BTN_WIDTH, BTN_HEIGHT, TFT_DARKGREY);
    tft.drawRect(BTN_IGNORE_X, BTN_IGNORE_Y, BTN_WIDTH, BTN_HEIGHT, TFT_WHITE);
    tft.setTextColor(TFT_WHITE, TFT_DARKGREY);
    tft.drawString("No", BTN_IGNORE_X + 10, BTN_IGNORE_Y + 12, 2);

    tft.fillRect(BTN_INVEST_X, BTN_INVEST_Y, BTN_WIDTH, BTN_HEIGHT, TFT_DARKGREY);
    tft.drawRect(BTN_INVEST_X, BTN_INVEST_Y, BTN_WIDTH, BTN_HEIGHT, TFT_WHITE);
    tft.setTextColor(TFT_WHITE, TFT_DARKGREY);
    tft.drawString("Yes", BTN_INVEST_X + 5, BTN_INVEST_Y + 12, 2);

    // 3. Highlight logic + input
    if (cursorX > BTN_IGNORE_X && cursorX < BTN_IGNORE_X + BTN_WIDTH &&
        cursorY > BTN_IGNORE_Y && cursorY < BTN_IGNORE_Y + BTN_HEIGHT)
    {
      tft.drawRect(BTN_IGNORE_X, BTN_IGNORE_Y, BTN_WIDTH, BTN_HEIGHT, TFT_RED);
      if (digitalRead(JOY_SW) == LOW)
      {
        choice = 0;
        while (digitalRead(JOY_SW) == LOW) delay(10); // wait for release
      }
    }
    else if (cursorX > BTN_INVEST_X && cursorX < BTN_INVEST_X + BTN_WIDTH &&
             cursorY > BTN_INVEST_Y && cursorY < BTN_INVEST_Y + BTN_HEIGHT)
    {
      tft.drawRect(BTN_INVEST_X, BTN_INVEST_Y, BTN_WIDTH, BTN_HEIGHT, TFT_RED);
      if (digitalRead(JOY_SW) == LOW)
      {
        choice = 1;
        while (digitalRead(JOY_SW) == LOW) delay(10); // wait for release
      }
    }

    delay(20);
  }

  delay(150); // small debounce before returning
  return choice;
}

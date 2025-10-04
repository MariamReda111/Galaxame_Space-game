#ifndef START_DISPLAY_H
#define START_DISPLAY_H

extern TFT_eSPI tft;

#define TFT_WIDTH  320   // adjust to your screen
#define TFT_HEIGHT 240

#define BLACK   0x0000
#define WHITE   0xFFFF
#define RED     0xF800
#define GREEN   0x07E0
#define BLUE    0x001F
#define MAGENTA 0xF81F
#define CYAN    0x07FF
#define YELLOW  0xFFE0


#define MAX_METEORS 3
#define TAIL_LENGTH 5
#define SCREEN_W 320
#define SCREEN_H 240

// Joystick pins
#define JOY_X 34   // VRx -> GPIO34 (ADC)
#define JOY_Y 35   // VRy -> GPIO35 (ADC)
#define JOY_SW 19  // SW -> GPIO19 (button)

struct Meteor {
  int x, y;
  int dx, dy;
  int radius;
  int tailX[TAIL_LENGTH];
  int tailY[TAIL_LENGTH];
  bool active;
};

void Initmeteor();
void meteor();
void updateMeteor(Meteor &m);

void Moving_Stars_Init();
void Moving_Stars();

void Title();

void Joystick_Init();
void Joystick();

bool Click_Start();

bool Continue();

void Crash();

void flySpaceshipAway();

bool galaxyClick();

void drawFlickeringStar(int x, int y, int baseRadius, uint16_t color);

int ShowChoice();
int Yes_or_No();

#endif
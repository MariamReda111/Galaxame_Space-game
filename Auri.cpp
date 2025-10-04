#include <TFT_eSPI.h>
#include "Auri.h"
#include "Start_Display.h"
#include "text_box.h"
#include "robotAI.h"

extern TFT_eSPI tft;

// int auriW = 180;   // width of box, fits screen
// int auriH = 150;    // height of box
// int auriX = 130
// int auriY = 20


void Auri(const char* auri)
{
  tft.pushImage(20,120,96,96,robot);
  // int auriX = (tft.width() - auriW) / 2;   // should now be positive
  // int auriY = (tft.height() - auriH) / 2;  // bottom of screen with 10 px margin

  // Draw box background + border
  tft.fillRoundRect(auriX, auriY, auriW, auriH, 8, TFT_BLACK);
  tft.drawRoundRect(auriX, auriY, auriW, auriH, 8, TFT_WHITE);

  // Text settings
  int margin = 10;
  int cursorX = auriX + margin;
  int cursorY = auriY + margin;
  int maxWidth = auriW - 2 * margin;

  tft.setTextColor(TFT_WHITE, TFT_BLACK);
  tft.setTextFont(2);   // readable medium font
  tft.setTextSize(1);

  // Word wrapping
  String line = "";
  for (int i = 0; i < strlen(auri); i++) {
    line += auri[i];
    int w = tft.textWidth(line);
    if (w > maxWidth || auri[i] == '\n') {
      tft.setCursor(cursorX, cursorY);
      tft.println(line);
      line = "";
      cursorY += tft.fontHeight(2); // move to next line
    }
  }
  if (line.length() > 0) {
    tft.setCursor(cursorX, cursorY);
    tft.println(line);
  }
}

void Auri_Init()
{
  tft.pushImage(20,120,96,96,robot);
  Auri("Hello...");
  while(!Continue()){}
  clearText();
  Auri("Are you... human?");
  while(!Continue()){}
  clearText();
  Auri("Oh thank the stars!");
  while(!Continue()){}
  clearText();
  Auri("I’ve been searching forsomeone who can help me.");
  while(!Continue()){}

  // while(1)
  // {
  //   // Moving_Stars();
  //   // Joystick();
  //   Auri("I’ve been searching for someone who can help me.");
  //   delay(20);
  //   if(Continue())
  //   {
  //     break;
  //   }
  // }
  // clearText();
  // while(1)
  // {
  //   tft.pushImage(20,120,96,96,robot);
  //   // Moving_Stars();
  //   // Joystick();
  //   textbox("Nice to meet you");
  //   delay(20);
  //   if(Continue())
  //   {
  //     break;
  //   }
  // }
  // clearText();
  // while(1)
  // {
  //   tft.pushImage(20,120,96,96,robot);
  //   // Moving_Stars();
  //   // Joystick();
  //   textbox("Let's play.");
  //   delay(20);
  //   if(Continue())
  //   {
  //     break;
  //   }
  // }  
  // clearText();
  // while(1)
  // {
  //   tft.pushImage(20,120,96,96,robot);
  //   // Moving_Stars();
  //   // Joystick();
  //   textbox("Are you ready?");
  //   delay(20);
  //   if(Continue())
  //   {
  //     break;
  //   }
  // } 
}
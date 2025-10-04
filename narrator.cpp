#include <TFT_eSPI.h>
#include "narrator.h"

extern TFT_eSPI tft;

// Box size (big enough for multiple lines)
int narratorW = 300;   // fits on screen with some margin
int narratorH = 100;    // enough for 2–3 lines


void narrator(const char* subtitle)
{

  int narratorX = (tft.width() - narratorW) / 2;   // should now be positive
  int narratorY = (tft.height() - narratorH) / 2;  // bottom of screen with 10 px margin

  // Draw box background + border
  tft.fillRoundRect(narratorX, narratorY, narratorW, narratorH, 8, TFT_BLACK);
  tft.drawRoundRect(narratorX, narratorY, narratorW, narratorH, 8, TFT_WHITE);

  // Text settings
  int margin = 10;
  int cursorX = narratorX + margin;
  int cursorY = narratorY + margin;
  int maxWidth = narratorW - 2 * margin;

  tft.setTextColor(TFT_WHITE, TFT_BLACK);
  tft.setTextFont(2);   // readable medium font
  tft.setTextSize(1);

  // Word wrapping
  String line = "";
  for (int i = 0; i < strlen(subtitle); i++) {
    line += subtitle[i];
    int w = tft.textWidth(line);
    if (w > maxWidth || subtitle[i] == '\n') {
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

  void clearnar()
{
  int narratorX = (tft.width() - narratorW) / 2;   // should now be positive
  int narratorY = (tft.height() - narratorH) / 2;  // bottom of screen with 10 px margin
  tft.fillRoundRect(narratorX, narratorY, narratorW, narratorH, 8, BLACK);  // overwrite with background color
  tft.drawRoundRect(narratorX, narratorY, narratorW, narratorH, 8, WHITE);  // redraw textbox border
}
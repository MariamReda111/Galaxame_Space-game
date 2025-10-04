#include <TFT_eSPI.h>
#include "text_box.h"

extern TFT_eSPI tft;


//String text;
//const char* subtitle;

void textbox(String text)
{
  tft.drawRoundRect(textboxX, textboXY, textboxW, textboxH, 5, WHITE);
  tft.drawRoundRect(textboxX-2, textboXY-2, textboxW-2, textboxH-2, 3, BLACK);

  // Set text properties
  tft.setTextColor(WHITE, BLACK); // white text on blue background
  tft.setTextDatum(MC_DATUM); // center text
  tft.drawString(text, textboxX + textboxW/2, textboXY + textboxH/2);
}

void clearText()
{
  tft.fillRoundRect(textboxX, textboXY, textboxW, textboxH, 5, BLACK);  // overwrite with background color
  tft.drawRoundRect(textboxX, textboXY, textboxW, textboxH, 5, WHITE);  // redraw textbox border
}

void subtitles(const char* subtitle)
{
  tft.drawRoundRect(subX, subY, subW, subH, 8, WHITE);

   int margin = 10; // inner padding
  int cursorX = subX + margin;
  int cursorY = subY + margin;

  // Draw subtitle box background
  //tft.fillRect(subX, subY, subW, subH, TFT_BLACK);

  // Set text style
  tft.setTextColor(TFT_WHITE, TFT_BLACK);
  tft.setTextFont(2); // built-in small font
  tft.setTextSize(1); // keep scale = 1

  tft.setTextWrap(true);

  // Limit text inside box width
  tft.setCursor(cursorX, cursorY);
  int maxWidth = subW - 2*margin;

  // Simple wrapping
  String word, line;
  for (int i = 0; i < strlen(subtitle); i++) {
    if (subtitle[i] == ' ' || subtitle[i] == '\0') {
      if (tft.textWidth(line + word) > maxWidth) {
        tft.println(line);
        line = word + " ";
      } else {
        line += word + " ";
      }
      word = "";
    } else {
      word += subtitle[i];
    }
  }
  tft.println(line + word);
}

void clearSub()
{
  tft.fillRoundRect(subX, subY, subW, subH, 5, BLACK);  // overwrite with background color
  tft.drawRoundRect(subX, subY, subW, subH, 5, WHITE);  // redraw textbox border
}

// void printWrapped(const char* msg) {
//   // Clear the box first
//   tft.fillRect(textboxX, textboXY, textboxW, textboxH, TFT_BLACK);

//   int16_t x1, y1;
//   uint16_t w, h;
//   int cursorX = textboxX + 5;   // padding
//   int cursorY = textboXY + 20;  // start line inside box
//   int lineHeight = 20;      // adjust with text size/font

//   String word = "";
//   String line = "";

//   for (int i = 0; i <= strlen(msg); i++) {
//     char c = msg[i];
//     if (c == ' ' || c == '\0') {
//       // Measure line + word
//       String testLine = line + word + " ";
//       tft.getTextBounds(testLine.c_str(), cursorX, cursorY, &x1, &y1, &w, &h);

//       if (w > textboxW - 10) { 
//         // Print current line, go to next
//         tft.setCursor(cursorX, cursorY);
//         tft.setTextColor(TFT_WHITE, TFT_BLACK);
//         tft.println(line);
//         line = word + " ";  // start new line with word
//         cursorY += lineHeight;
//       } else {
//         line = testLine;
//       }
//       word = "";
//     } else {
//       word += c; // keep building word
//     }
//   }

//   // Print last line
//   if (line.length() > 0) {
//     tft.setCursor(cursorX, cursorY);
//     tft.setTextColor(TFT_WHITE, TFT_BLACK);
//     tft.println(line);
//   }
// }

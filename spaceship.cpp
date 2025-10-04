#include <TFT_eSPI.h>
//#include "spaceship.h"

extern TFT_eSPI tft;

// void flySpaceshipAway() 
// {
//   int shipW = 100;   // width of spaceship image (adjust to your image)
//   int shipH = 100;   // height of spaceship image (adjust to your image)

//   // Start in the middle of the screen
//   int x = (tft.width() - shipW) / 2;
//   int y = (tft.height() - shipH) / 2;

//   // Clear screen first
//   tft.fillScreen(TFT_BLACK);

//   // Animate upward
//   while (y + shipH > 0) 
//   {
//     // Clear previous frame
//     tft.fillRect(x, y, shipW, shipH, TFT_BLACK);

//     // Draw spaceship at new position
//     tft.pushImage(x, y, shipW, shipH, spaceship);

//     // Move upward
//     y -= 4; // speed (lower = slower, higher = faster)

//     delay(30); // controls smoothness of animation
//   }
// }
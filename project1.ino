#include <TFT_eSPI.h>
#include "Start_Display.h"
#include "robotAI.h"
#include "text_box.h"
#include "Auri.h"
#include "spaceship.h"
#include "narrator.h"
#include "galaxy.h"


// Create TFT object
//TFT_eSPI tft = TFT_eSPI();   // uses User_Setup.h config


extern bool start;
int count=0;
// int galaxyX=,galaxyY=,galaxyW=,galaxyH=100;




void setup() 
{
  tft.init();
  tft.setRotation(1);  // Landscape
  tft.setSwapBytes(true);
  tft.fillScreen(BLACK);


  Moving_Stars_Init();
  Initmeteor();
  Joystick_Init();
  while(1)
  {
    Moving_Stars();
    meteor();
    Title();
    Joystick();
    Click_Start();
    delay(20);
    if(start)
    {
      break;
    }
  }



  tft.fillScreen(BLACK);

  while(1)
  {
    Moving_Stars();
    meteor();
    subtitles("Wow! Look at those shiny things in the sky!");
    delay(20);
    if(Continue())
    {
      break;
    }
  }
  clearSub();
  while(1)
  {
    Moving_Stars();
    meteor();
    subtitles("I wonder… are they all stars?");
    delay(20);
    if(Continue())
    {
      break;
    }
  }
  clearSub();
  while(1)
  {
    Moving_Stars();
    meteor();
    subtitles("Or maybe planets? ");
    delay(20);
    if(Continue())
    {
      break;
    }
  }
  clearSub();
  while(1)
  {
    Moving_Stars();
    meteor();
    subtitles("Hmmm...");
    delay(20);
    if(Continue())
    {
      break;
    }
  }  

  Crash();

  while(!Continue()){}
  tft.fillScreen(BLACK);
      

  
  subtitles("What was that sound?!");
  while(!Continue()){}
  clearSub();
  
  subtitles("Did it come from our backyard?...");
  while(!Continue()){}
  clearSub();

  tft.pushImage(120,60,100,100,spaceship);
  subtitles("Wha—?! A spaceship?! In my backyard?!");
  while(!Continue()){}
  tft.fillScreen(BLACK);
  narrator("You slowly walk outside and approache the   spaceship...");
  while(!Continue()){}
  clearnar();
  narrator("The door opens with a hiss, and out steps a small, friendly-looking AI robot with glowing eyes.");
  while(!Continue()){}

  tft.fillScreen(BLACK);
  Auri_Init();

  tft.fillScreen(BLACK);
  subtitles("Help you?");
  while(!Continue()){}
  clearSub();
  subtitles("Who... who are you?");
  while(!Continue()){}
  tft.fillScreen(BLACK);
  tft.pushImage(20,120,96,96,robot);
  Auri("My name is Auri. I came  from far away… but… I’ve lost my way home.");
  while(!Continue()){}
  clearText();
  Auri("My memory says my mother planet is out there, but I don’t know which shiny thing is a real planet… and which one isn’t.");
  while(!Continue()){}
  clearText();
  tft.fillScreen(BLACK);
  subtitles("So… you need to figure out what’s a          planet and what’s not?");
  while(!Continue()){}
  tft.fillScreen(BLACK);
  tft.pushImage(20,120,96,96,robot);
  Auri("Exactly! Without knowing   that, I may never find my way back. Will you come with me?");
  while(!Continue()){}
  tft.fillScreen(BLACK);
  narrator("Auri extends a robotic hand. You look  up at the sky, then back at the spaceship, your    curiosity growing.");
  while(!Continue()){}
  tft.fillScreen(BLACK);
  subtitles("Well… I’ve always wanted an adventure.      Let’s go find your home, Auri!");
  while(!Continue()){}
  tft.fillScreen(BLACK);
  narrator("The two enter the spaceship together. The    lights glow, and with a roar, the spaceship launches into the stars.");
  while(!Continue()){}
  tft.fillScreen(BLACK);
  flySpaceshipAway();

  tft.fillScreen(BLACK);

  while(!Continue())
  {
    Moving_Stars();
    narrator("After a long journey through empty space,    Auri finally sees… a glowing galaxy ahead!");
    delay(20);
  }
  clearnar();
  while(!Continue())
  {
    Moving_Stars();
    narrator("Inside this galaxy, AI helps explorers like Auri discover hidden worlds around distant stars.");
    delay(20);
  }
  clearnar();
  while(!Continue())
  {
    Moving_Stars();
    narrator("Let’s begin Auri’s quest to find a new   home planet.");
    delay(20);
  }
  
  tft.fillScreen(BLACK);



  tft.pushImage(200,20,100,100,galaxy);
  flystop();
  tft.fillRect(40, 60, 100, 200, BLACK);

  while(!Continue())
  {
    tft.pushImage(200,20,100,100,galaxy);
    tft.pushImage(40, 60, 100, 100,spaceship);
    Moving_Stars();
    subtitles("Look! That huge glowing cluster... it must be    a galaxy!");
    delay(20);
  }
  clearSub();
  while(!Continue())
  {
    tft.pushImage(200,20,100,100,galaxy);
    tft.pushImage(40, 60, 100, 100,spaceship);
    Moving_Stars();
    subtitles("Auri: Wow... I've never seen anything like       this. Do you think we should enter?");
    delay(20);
  }
  clearSub();
  while(!Continue())
  {
    tft.pushImage(200,20,100,100,galaxy);
    tft.pushImage(40, 60, 100, 100,spaceship);
    Moving_Stars();
    subtitles("It looks beautiful... but also... unknown.        Are we ready?");
    delay(20);
  }
  clearSub();
  while(!Continue())
  {
    tft.pushImage(200,20,100,100,galaxy);
    tft.pushImage(40, 60, 100, 100,spaceship);
    Moving_Stars();
    subtitles("Auri: I need to find my planet. This galaxy      could be our next clue.");
    delay(20);
  }
  clearSub();
  // while(!Continue())
  // {
  //   tft.pushImage(200,20,100,100,galaxy);
  //   tft.pushImage(40, 60, 100, 100,spaceship);
  //   Moving_Stars();
  //   subtitles("Alright… let's venture in, but stay alert.");
  //   delay(20);
  // }

  while(1)
  {
    subtitles("Alright... let's venture in, but stay alert.");
    tft.pushImage(200,20,100,100,galaxy);
    tft.pushImage(40, 60, 100, 100,spaceship);
    Moving_Stars();
    Joystick();
    if(galaxyClick())
    {
      break;
    }
    delay(20);
  }

  //tft.fillScreen(BLACK);
  label1:
  tft.fillScreen(BLACK);
  while(!Continue())
  {
    narrator("Auri notices a star flickering strangely...    Could this mean a planet?");
    Moving_Stars();
    Joystick();
    delay(20);
  }
  tft.fillScreen(BLACK);

  while(!Continue())
  {
    drawFlickeringStar(100, 80, 3, WHITE);
    Moving_Stars();
    Joystick();
    subtitles("Auri: Hey, look at that! The star’s light is     dipping in and out… what do you think      we should do?");
    delay(20);
  }
  tft.fillScreen(BLACK);

  //int explore=ShowChoice();
  tft.fillScreen(BLACK);
    // Player makes a choice
  int explore = ShowChoice();  

  // === If player chooses to explore ===
  if (explore == 1) 
  {   // (assuming 1 = Explore, 0 = Ignore)
    tft.fillScreen(BLACK);
    while(!Continue())
    {
      narrator("You decide to investigate the flickering star.");
      Moving_Stars();
      Joystick();
      delay(20);
    }
    tft.fillScreen(BLACK);

    while(!Continue())
    {
      drawFlickeringStar(100, 80, 3, WHITE);
      Moving_Stars();
      Joystick();
      subtitles("Auri: Look closer... the brightness dips in a    pattern. That’s a sign of a planet          crossing in front!");
      delay(20);
    }
    tft.fillScreen(BLACK);

    while(!Continue())
    {
      narrator("Congratulations! You discovered your first   planet using the **transit method**.");
      Moving_Stars();
      Joystick();
      delay(20);
    }
    //clearnar();
    label2:
     tft.fillScreen(BLACK);
    while(!Continue())
    {
      Moving_Stars();
      Auri("Hey! Look at that star    flickering...");
      Joystick();
      delay(20);
    }
    clearText();
    while(!Continue())
    {
      Moving_Stars();
      Auri("Do you think it’s just a star blinking?");
      Joystick();
      delay(20);
    }
    tft.fillScreen(BLACK);

    int answer= Yes_or_No();
    tft.fillScreen(BLACK);
    if (answer == 1) 
    {   // (assuming 1 = Explore, 0 = Ignore)
      while(!Continue())
      {
      Moving_Stars();
      Auri("Hmm… maybe... but stars usually shine steadily.");
      Joystick();
      delay(20);
      }
      clearText();
      while(!Continue())
      {
      Moving_Stars();
      Auri("Lets think about it again!");
      Joystick();
      delay(20);
      }
      goto label2;
    
    }
    else if(answer == 0)
    {
      while(!Continue())
      {
        Moving_Stars();
        Auri("That’s right! Stars      don’t usually blink like  that.");
        Joystick();
        delay(20);
      }
      clearText();
      while(!Continue())
      {
        Moving_Stars();
        Auri("What if something passed in front of it?");
        Joystick();
        delay(20);
      }
      clearText();
      while(!Continue())
      {
        Moving_Stars();
        Auri("What could it be?");
        Joystick();
        delay(20);
      }
      tft.fillScreen(BLACK);
    //   answer=
    //   if
    }
  }
    

  // === If player chooses to ignore ===
  else 
  {
    tft.fillScreen(BLACK);
    while(!Continue())
    {
      narrator("You decide to ignore the strange flicker and continue flying.");
      Moving_Stars();
      Joystick();
      delay(20);
    }
    clearnar();

    while(!Continue())
    {
      narrator("But something feels off... what if you missed a clue?");
      Moving_Stars();
      Joystick();
      delay(20);
    }
    tft.fillScreen(BLACK);
      while(!Continue())
  {
    subtitles("Auri: Hmmm… maybe we should take another    look...");
    Moving_Stars();
    delay(20);
  }
  clearSub();

  // Go back to the flickering star scene again
  goto label1;

    // Send them to another encounter (maybe a harder challenge later)
    // Level3();   // next level if they skipped

  // tft.fillScreen(BLACK);
  // while(!Continue())
  // {
  //   Moving_Stars();
  //   Auri("Hey! Look at that star flickering...");
  //   Joystick();
  //   delay(20);
  // }
  // clearText();

  
  //   }
}
  

}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



void loop() 
{

  while(1); // stop at end

}

void flySpaceshipAway() 
{
  int shipW = 100;   // width of spaceship image (adjust to your image)
  int shipH = 100;   // height of spaceship image (adjust to your image)

  // Start in the middle of the screen
  int x = (tft.width() - shipW) / 2;
  int y = (tft.height() - shipH) / 2;

  // Clear screen first
  tft.fillScreen(TFT_BLACK);

  // Animate upward
  while (y + shipH > 0) 
  {
    Moving_Stars();
    // Clear previous frame
    tft.fillRect(x, y, shipW, shipH, TFT_BLACK);

    // Draw spaceship at new position
    tft.pushImage(x, y, shipW, shipH, spaceship);

    // Move upward
    y -= 4; // speed (lower = slower, higher = faster)

    delay(50); // controls smoothness of animation
  }
}

void flystop()
{
  
  int shipW = 100;   // width of spaceship image (adjust to your image)
  int shipH = 100;   // height of spaceship image (adjust to your image)

  int x = 40;
  int y = 300;  // starting y position (bottom of screen)

  // Animate upward until y reaches 150
  while (y > 60) 
  {
    tft.pushImage(200,20,100,100,galaxy);

    Moving_Stars();
    // Clear previous frame
    tft.fillRect(x, y, shipW, shipH, TFT_BLACK);

    // Draw spaceship at new position
    tft.pushImage(x, y, shipW, shipH, spaceship);

    // Move upward
    y -= 4; // speed

    delay(50); // controls smoothness
  }

  // At this point, y = 150, spaceship stops

}






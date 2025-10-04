#define textboxX 130
#define textboXY 20
#define textboxW 180
#define textboxH 150

#define subX 10      // Left margin
#define subY 172     // Vertical position (bottom part of screen)
#define subW 300     // Width (almost full width, leaving small margins)
#define subH 60      // Height (enough for 2 lines of text)


#define BLACK   0x0000
#define WHITE   0xFFFF
#define RED     0xF800
#define GREEN   0x07E0
#define BLUE    0x001F
#define MAGENTA 0xF81F
#define CYAN    0x07FF
#define YELLOW  0xFFE0

//void textbox_Init();
void textbox(String text);
void clearText();
void subtitles(const char* subtitle);
void clearSub();
//void printWrapped(const char* msg);


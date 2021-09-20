
#define WIDTH 128
#define HEIGHT 64
typedef enum { false, true } bool;

int initSSD1306();
void drawGary();
void SSD1306_command(int command);
void SSD1306_data(int data);
void togglePixel(int x, int y);
void setPointer(int x, int y);
void setX(int x);
void setY(int y);

void writeSmallChar(char c, int line, int col);
void writeString(char* str, int line, int col);
void writeInt(int num, int line, int x);


void writeSpeed(float speed, bool dl);
void writeDownload(float dl);
void writeUpload(float ul);
void writeUnit(bool kBps, bool dl);

void drawPadding(int x);

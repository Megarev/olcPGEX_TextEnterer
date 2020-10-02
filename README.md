# olcPGEX_TextEnterer
A olc::PixelGameEngine Extension for writing text to the window in olc::PGE
At the moment it has support only for Windows

Here is a basic program that allows you to write text
```cpp
#define OLC_PGE_APPLICATION
#include "olcPixelGameEngine.h"
#include "olcPGEX_TextInput.h"

class TextApp : public olc::PixelGameEngine {
private:
  std::string text;
public:
  TextApp() {
    sAppName = "Title";
  }
  
  bool OnUserCreate() override {
    
    return true;
  }
  
  bool OnUserUpdate(float fElapsedTime) override {
    
    char c = olc::TextInput::Get().EnterText();
    if (c != '\0') text += c;
    
    DrawString(0, 0, text);
    
    return true;
  }
};
```
But this only allows you enter text in a line
It also doesn't allow you to add a new line and also backspace

For this there is another class **Text Area**

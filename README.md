# olcPGEX_TextEnterer
To use the extension you've to first download the [olc::PixelGameEngine](https://github.com/OneLoneCoder/olcPixelGameEngine).

A olc::PixelGameEngine Extension for writing text to the window in olc::PGE.
At the moment it has support only for Windows.
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
But this only allows you enter text in a line.
For more functionality there is **Text Area** class.
```cpp
#define OLC_PGE_APPLICATION
#include "olcPixelGameEngine.h"

class TextApp : public olc::PixelGameEngine {
private:
  olc::TextArea area;
public:
  TextApp() {
    sAppName = "Title";
  }
  
  bool OnUserCreate() pverride {
  
    area = olc::TextArea({ 0, 0 }); // The parameter takes the position of the starting point
    return true;
  }
  
  bool OnUserUpdate(float fElapsedTime) override {
  
    area.Input(this);
    area.Draw(this, olc::WHITE);
  
    return true;
  }
}
```
**Text Area** however doesn't allow you to copy-paste and select text at the moment.

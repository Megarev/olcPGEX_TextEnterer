# olcPGEX_TextEnterer
To use the extension you've to first download the [olc::PixelGameEngine](https://github.com/OneLoneCoder/olcPixelGameEngine).

People who've contributed to this project
-----------------------------------------
- **scripticuk** - for doing the key map bindings
- **Iornz** - for testing and making necessary changes for Linux
And me :)

At the moment, it contains two classes
* Text Area - For writing text in the entire window (you can set bounds too)
* Teat Box - For writing text in a box (it also has an added feature that allows you to move it with the mouse)

A olc::PixelGameEngine Extension for writing text to the window in olc::PGE.
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
    
    char c = olc::TextInput::Get().EnterText(this);
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
#include "olcPGEX_TextInput.h"

class TextApp : public olc::PixelGameEngine {
private:
  olc::TextArea area;
public:
  TextApp() {
    sAppName = "Title";
  }
  
  bool OnUserCreate() override {
  
    area = olc::TextArea({ 0, 0 }); // The parameter takes the position of the starting point
    return true;
  }
  
  bool OnUserUpdate(float fElapsedTime) override {
  
    area.Input(this);
    Clear(olc::BLACK);
    area.Draw(this, olc::WHITE);
  
    return true;
  }
}
```
**Text Area** however doesn't allow you to copy-paste and select text at the moment.

There is also **Text Box**
```cpp
#define OLC_PGE_APPLICATION
#include "olcPixelGameEngine.h"
#include "olcPGEX_TextInput.h"

class TextApp : public olc::PixelGameEngine {
private:
	olc::TextBox box;
public:
	TextApp() {
		sAppName = "Title";
	}

	bool OnUserCreate() override {

		box.Initialize(10, 10, 100, 25, olc::BLUE, 2, 6); //Parameters are (pos_x, pos_y, size_x, size_y, box_color, text_scale, characters_limit)

		return true;
	}

	bool OnUserUpdate(float dt) override {

		box.Input(this);

		Clear(olc::BLACK);
		box.Draw(this, olc::YELLOW);

		return true;
	}
};
```
You can also manually move the text boxes using the mouse, enable is_mouse_move flag in OnUserCreate()
```cpp
box.SetMouseMovement(true);
```

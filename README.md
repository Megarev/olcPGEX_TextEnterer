# olcPGEX_TextEnterer
A olc::PixelGameEngine Extension for writing text to the window in olc::PGE.
To use the extension you've to first download the [olc::PixelGameEngine](https://github.com/OneLoneCoder/olcPixelGameEngine).

People who've contributed to this project
-----------------------------------------
- **scripticuk** - for doing the key map bindings
- **Lorsanta** - for testing and making necessary changes for Linux
- And me too

At the moment, it contains two classes
* Text Area - For writing text in the entire window (you can set bounds too)
* Teat Box - For writing text in a box (it also has an added feature that allows you to move it with the mouse)

**To use this extension you've to add _#include OLC_PGEX_TEXTINPUT_ at the top of your main source file**

To write text, you use EnterText function 
```cpp
std::string text;
text += olc::TextInput::Get().EnterText(); // Returns a string
```
But this only allows you enter text in a line.
For more functionality there is **Text Area** class.
```cpp
#define OLC_PGE_APPLICATION
#define OLC_PGEX_TEXTINPUT
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
  
    area.Initialize({ 0, 0 }, 1, { -1, -1 });
    /*
    	Parameters are starting position, text scale and characters_limit (-1 for no character_limit)
    */
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
#define OLC_PGEX_TEXTINPUT
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
You can also manually move the text boxes using the mouse, just add this function in OnUserCreate
```cpp
box.SetMouseMovement(true);
```

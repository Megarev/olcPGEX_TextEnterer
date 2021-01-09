/*
    License (OLC-3)
    ~~~~~~~~~~~~~~~
	
    Copyright 2018 - 2020 OneLoneCoder.com
	Redistribution and use in source and binary forms, with or without modification,
	are permitted provided that the following conditions are met:
	1. Redistributions or derivations of source code must retain the above copyright
	notice, this list of conditions and the following disclaimer.
	2. Redistributions or derivative works in binary form must reproduce the above
	copyright notice. This list of conditions and the following	disclaimer must be
	reproduced in the documentation and/or other materials provided with the distribution.
	3. Neither the name of the copyright holder nor the names of its contributors may
	be used to endorse or promote products derived from this software without specific
	prior written permission.
    
	THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS	"AS IS" AND ANY
	EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
	OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT
	SHALL THE COPYRIGHT	HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
	INCIDENTAL,	SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED
	TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR
	BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
	CONTRACT, STRICT LIABILITY, OR TORT	(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
	ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
	SUCH DAMAGE.
*/

#pragma once
#include "olcPixelGameEngine.h"
#include <string>

#define max(a, b)  (((a) > (b)) ? (a) : (b)) 
#define min(a, b)  (((a) < (b)) ? (a) : (b))

#if __linux__
#undef None // None defined in /usr/include/X11/X.h
#endif

/*
    +Macro implementation is added for multiple file support
     Add #define OLC_PGEX_TEXTINPUT at the top of the main source file
    +Added sprinting in text
*/

enum TextKey {
    None = -1,
    A = 0, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q, R, S, T, U, V, W, X, Y, Z,
    Num0, Num1, Num2, Num3, Num4, Num5, Num6, Num7, Num8, Num9,
    LBracket, RBracket, Semicolon, Comma, Period, Quote, ForwardSlash, BackwardSlash,
    Tilda, Equal, Hyphen, Space
};

namespace olc {

    class TextInput {
    private:
        int n_TextKeys;
        std::string text_noshift = "abcdefghijklmnopqrstuvwxyz0123456789[];,.'/\\`=- ";
        std::string text_shift = "ABCDEFGHIJKLMNOPQRSTUVWXYZ)!@#$%^&*({}:<>\"?|~+_ ";
        TextInput() {
            n_TextKeys = 48;
        }

        bool IsTextKeyPressed(PixelGameEngine* pge, const TextKey& text_key);
        int GetAnyTextKey(PixelGameEngine* pge);
    public:
        static TextInput& Get() {
            static TextInput text_enterer;
            return text_enterer;
        }

        std::string EnterText(PixelGameEngine* pge);
    };

    class TextArea {
    private:
        std::ostringstream text_stream;
        std::vector<std::string> lines = { "" };
        vi2d position, cursor_pos;
        uint32_t scale = 1, index = 0;

        // Is text area selected
        bool is_selected = true;
        /*
           The maximum amount of characters each line in text area can hold
           text_max_length = -1 -> no limit to string length (for both x and y)
        */
        vi2d text_max_length = { -1, -1 };
    public:
        TextArea() {}
        TextArea(const vi2d& start_pos, uint32_t text_scale = 1, vi2d max_length = vi2d(-1, -1))
            : position(start_pos), cursor_pos(start_pos), scale(text_scale), text_max_length(max_length) {}

        void Initialize(const vi2d& start_pos, uint32_t text_scale = 1, vi2d max_length = vi2d(-1, -1));
        void Initialize(int x, int y, uint32_t text_scale = 1, int max_length_x = -1, int max_length_y = -1);

        void Input(PixelGameEngine* pge);
        // Color is the color of text
        void Draw(PixelGameEngine* pge, Pixel color = WHITE, bool showBorder = false, Pixel borderColor = WHITE);

        vi2d GetPosition() const { return position; }
        std::vector<std::string> GetStrings() const { return lines; }
        vi2d GetCursorPosition() const { return cursor_pos; }
    };

    class TextBox {
    private:
        vi2d position, size;
        int text_max_length = -1;

        // Show a part of text in text box
        int show_text_pos = 0;

        std::ostringstream text_stream;

        Pixel text_box_color = WHITE;
        int cursor_pos;
        uint32_t scale = 1;

        bool is_selected = false;

        bool is_mouse_move = false, is_pressed = false;
        vi2d offset;
        int offset_cursor;
    public:
        enum class TextMode { NORMAL, CENTER } mode;

        TextBox() {}
        TextBox(const vi2d& pos, const vi2d& box_size, Pixel box_color = WHITE, uint32_t text_scale = 1, int max_length = -1)
            : position(pos), size(box_size), text_max_length(max_length), text_box_color(box_color), scale(text_scale) {
            cursor_pos = position.x;
        }

        void Initialize(const vi2d& pos, const vi2d& box_size, Pixel box_color = WHITE, uint32_t text_scale = 1, int max_length = -1);
        void Initialize(int pos_x, int pos_y, int size_x, int size_y, Pixel box_color = WHITE, uint32_t text_scale = 1, int max_length = -1);

        void SetMouseMovement(bool state) { is_mouse_move = state; }

        bool IsPointInBounds(const vi2d& point);

        void Input(PixelGameEngine* pge);
        void Draw(PixelGameEngine* pge, Pixel text_color = WHITE, bool is_fill = false);
        void Draw(PixelGameEngine* pge, Pixel text_color = WHITE, Pixel box_color = BLACK, bool is_fill = false);

        void SetTextMode(TextMode _mode) { mode = _mode; }
        std::string GetText() const { return text_stream.str(); }
        uint32_t GetScale() const { return scale; }
        vi2d GetPos() const { return position; }
    };
}

#ifdef OLC_PGEX_TEXTINPUT
#undef OLC_PGEX_TEXTINPUT

namespace olc {
    // Definitions of functions in classes
    // TextInput
    bool TextInput::IsTextKeyPressed(PixelGameEngine* pge, const TextKey& text_key) {
        int vTextKey = 0;
        switch (text_key)
        {
        default:                        vTextKey = NONE;        break;
        case TextKey::A:                vTextKey = A;           break;
        case TextKey::B:                vTextKey = B;           break;
        case TextKey::C:                vTextKey = C;           break;
        case TextKey::D:                vTextKey = D;           break;
        case TextKey::E:                vTextKey = E;           break;
        case TextKey::F:                vTextKey = F;           break;
        case TextKey::G:                vTextKey = G;           break;
        case TextKey::H:                vTextKey = H;           break;
        case TextKey::I:                vTextKey = I;           break;
        case TextKey::J:                vTextKey = J;           break;
        case TextKey::K:                vTextKey = K;           break;
        case TextKey::L:                vTextKey = L;           break;
        case TextKey::M:                vTextKey = M;           break;
        case TextKey::N:                vTextKey = N;           break;
        case TextKey::O:                vTextKey = O;           break;
        case TextKey::P:                vTextKey = P;           break;
        case TextKey::Q:                vTextKey = Q;           break;
        case TextKey::R:                vTextKey = R;           break;
        case TextKey::S:                vTextKey = S;           break;
        case TextKey::T:                vTextKey = T;           break;
        case TextKey::U:                vTextKey = U;           break;
        case TextKey::V:                vTextKey = V;           break;
        case TextKey::W:                vTextKey = W;           break;
        case TextKey::X:                vTextKey = X;           break;
        case TextKey::Y:                vTextKey = Y;           break;
        case TextKey::Z:                vTextKey = Z;           break;
        case TextKey::Num0:             vTextKey = K0;          break;
        case TextKey::Num1:             vTextKey = K1;          break;
        case TextKey::Num2:             vTextKey = K2;          break;
        case TextKey::Num3:             vTextKey = K3;          break;
        case TextKey::Num4:             vTextKey = K4;          break;
        case TextKey::Num5:             vTextKey = K5;          break;
        case TextKey::Num6:             vTextKey = K6;          break;
        case TextKey::Num7:             vTextKey = K7;          break;
        case TextKey::Num8:             vTextKey = K8;          break;
        case TextKey::Num9:             vTextKey = K9;          break;

        case TextKey::LBracket:         vTextKey = OEM_4;       break;
        case TextKey::RBracket:         vTextKey = OEM_6;       break;
        case TextKey::Semicolon:        vTextKey = OEM_1;       break;
        case TextKey::Comma:            vTextKey = COMMA;       break;
        case TextKey::Period:           vTextKey = PERIOD;      break;
        case TextKey::Quote:            vTextKey = OEM_7;       break;
        case TextKey::ForwardSlash:     vTextKey = OEM_2;       break;
        case TextKey::BackwardSlash:    vTextKey = OEM_5;       break;
        case TextKey::Tilda:            vTextKey = OEM_3;       break;
        case TextKey::Equal:            vTextKey = EQUALS;      break;
        case TextKey::Hyphen:           vTextKey = MINUS;       break;

        case TextKey::Space:            vTextKey = SPACE;       break;
        }

        return pge->GetKey((Key)vTextKey).bPressed;
    }

    int TextInput::GetAnyTextKey(PixelGameEngine* pge) {
        for (int i = 0; i < n_TextKeys; i++) {
            if (IsTextKeyPressed(pge, (TextKey)i)) {
                return i;
            }
        }
        return None;
    }

    std::string TextInput::EnterText(PixelGameEngine* pge) {
        int index = GetAnyTextKey(pge);
        if (index == None) return "";

        if (pge->GetKey(SHIFT).bHeld) {
            return std::string(1, text_shift[index]);
        }

        return std::string(1, text_noshift[index]);
    }

    // TextArea
    void TextArea::Initialize(const vi2d& start_pos, uint32_t text_scale, vi2d max_length) {
        position = { (start_pos.x / 8) * 8, (start_pos.y / 8) * 8 };
        cursor_pos = { (start_pos.x / 8) * 8, (start_pos.y / 8) * 8 };
        scale = text_scale;
        text_max_length = max_length;
    }

    void TextArea::Initialize(int x, int y, uint32_t text_scale, int max_length_x, int max_length_y) {
        position = { (x / 8) * 8, (y / 8) * 8 };
        cursor_pos = { (x / 8) * 8, (y / 8) * 8 };
        if (x == 0) { 
            position.x = 0; 
            cursor_pos.x = 0; 
        }
        if (y == 0) {
            position.y = 0;
            cursor_pos.y = 0;
        }

        scale = text_scale;
        text_max_length = { max_length_x, max_length_y };
    }

    // For user input
    void TextArea::Input(PixelGameEngine* pge) {

        auto IsPointInBounds = [&](const olc::vi2d& pos) {

            if (text_max_length.x < 0 && text_max_length.y < 0) return true;

            const olc::vi2d& size = {
                 (text_max_length.x < 0) ? pge->ScreenWidth() : 8 * (int)scale * text_max_length.x,
                 (text_max_length.y < 0) ? pge->ScreenHeight() : 8 * (int)scale * text_max_length.y
            };

            return (pos.x > position.x && pos.x < position.x + size.x &&
                    pos.y > position.y && pos.y < position.y + size.y);
        };

        if (pge->GetMouse(0).bPressed) {
            is_selected = IsPointInBounds(olc::vi2d(pge->GetMouseX(), pge->GetMouseY()));
        }

        if (!is_selected) return;

        auto FindPos = [&](std::string& str, int offset = 0) {
            int pos = (cursor_pos.x - position.x) / (8 * (int)scale) - offset;
            std::string::iterator it = str.begin();
            int n = 0;
            while (pos > 0 && n != pos) {
                it++;
                n++;
            }

            return it;
        };

        auto FindPosFromVector = [&](int offset = 0) {
            std::vector<std::string>::iterator it = lines.begin();
            unsigned int n = 0;
            while (n != index + offset) {
                it++;
                n++;
            }

            return it;
        };

        auto InputText = [&]() {
            std::string c = TextInput::Get().EnterText(pge);
            if (c != "") {
                std::string str = text_stream.str();

                if (text_max_length.x < 0 || (text_max_length.x > 0 && (int)str.size() < text_max_length.x)) {

                    // Add it into the string
                    str.insert(FindPos(str), c[0]);
                    text_stream.str("");
                    text_stream << str;
                    lines[index] = text_stream.str();

                    // Increase position
                    cursor_pos.x += 8 * (int)scale;
                }
            }
        };

        auto ClearText = [&]() {
            if (lines[index].size() > 0 && cursor_pos.x != position.x) {

                // If string length is not 0 and the cursor_pos is not the start_pos of the text area

                // As string has size > 0
                std::string original_str = text_stream.str();

                // If string is exactly one char in size

                if (original_str.size() == 1) {
                    lines[index].pop_back();
                    cursor_pos.x -= 8 * scale;
                    text_stream.str("");
                }
                else {
                    // Find the string by calculating the index at which the cursor_pos is
                    // It works for mono-spaced fonts only
                    int pos = (cursor_pos.x - position.x) / (8 * (int)scale) - 1;

                    // Check if pos >= 0 to avoid out of bounds
                    if (pos >= 0) {
                        original_str.erase(FindPos(original_str, 1));

                        // Set string and string at index to the original string
                        text_stream.str("");
                        text_stream << original_str;
                        lines[index] = text_stream.str();

                        // Move the cursor back, but not so as to make it go out of screen
                        cursor_pos.x -= 8 * scale;
                    }
                }
            }
            else {
                // If cursor position isn't the first line and there are more than 1 lines
                if (lines.size() > 1 && index > 0) {

                    // Current Line is the line which is currently in the active line
                    std::string current_line = lines[index];

                    lines.erase(FindPosFromVector());
                    index--;

                    // Set the string in the previous line by adding the string from current_line
                    lines[index] += current_line;
                    text_stream.str("");
                    text_stream << lines[index];
                    cursor_pos.x = lines[index].size() * 8 * scale;
                }
            }
        };

        InputText();

        if (pge->GetKey(ENTER).bPressed) {
            if (text_max_length.y < 0 || (int)lines.size() < text_max_length.y) {
                int pos = (cursor_pos.x - position.x) / (8 * (int)scale);
                std::string line_string_original = lines[index].substr(0, pos); // Sub-string from 0 to pos
                std::string line_string = lines[index].substr(pos); // Sub-string from pos to string_size
                
                // Set original string (the line from which new line was done)
                lines[index] = std::move(line_string_original);
                // Insert a new string with the sub-string from pos to string_size
                lines.insert(FindPosFromVector(1), line_string);
                text_stream.str("");
                text_stream << line_string;
                index++; // Add to index variable
            }
        }
        
        if (pge->GetKey(UP).bPressed) {
            index = max((int)index - 1, 0); // Move the index up
            std::string line = lines[index]; // Set string to new index

            text_stream.str("");
            text_stream << line;
        }
        else if (pge->GetKey(DOWN).bPressed) {
            index = min(index + 1, lines.size() - 1); // Move the index down
            std::string line = lines[index]; // Set string to new index

            text_stream.str("");
            text_stream << line;
        }

        bool is_ctrl_pressed = pge->GetKey(CTRL).bHeld;

        auto CheckNoWhiteSpace = [&](char ch) {
            return (bool)(isalpha(ch) || isdigit(ch));
        };

        auto JumpToNextText = [&](int direction) {
            int init_pos = (cursor_pos.x - position.x) / (8 * scale);

            // Move cursor towards left, if it finds alphabets, then set this boolean flag to true
            bool is_cursor_read_letters = false;

            while (true) { 
                if ((direction > 0 && init_pos > (int)lines[index].size() - 1) ||
                    (direction < 0 && init_pos <= (int)(position.x / (8 * scale))) ||
                    (lines[index][init_pos] == ' ' && is_cursor_read_letters)) break;
                is_cursor_read_letters |= CheckNoWhiteSpace(lines[index][init_pos]);
                init_pos += direction;
            }
            cursor_pos.x = 8 * scale * init_pos;
        };

        if (pge->GetKey(LEFT).bPressed) {
            if (is_ctrl_pressed) JumpToNextText(-1);
            else cursor_pos.x -= 8 * scale;
        }
        else if (pge->GetKey(RIGHT).bPressed) {
            if (is_ctrl_pressed) JumpToNextText(1);
            else cursor_pos.x += 8 * scale;
        }

        if (pge->GetKey(BACK).bPressed) {
            if (is_ctrl_pressed) {
                int init_pos = (cursor_pos.x - position.x) / (8 * scale);
                
                // Move cursor towards left, if it finds alphabets, then set this boolean flag to true
                bool is_cursor_read_letters = false;

                while (init_pos != position.x / (8 * scale)) { 
                    is_cursor_read_letters |= CheckNoWhiteSpace(lines[index][init_pos - 1]);
                    if (lines[index][init_pos - 1] == ' ' && is_cursor_read_letters) break;
                    ClearText(); 
                    init_pos--; 
                }
                cursor_pos.x = 8 * scale * init_pos;
            }
            ClearText();
        }

        // Clamp the cursor in bounds
        if (cursor_pos.x < position.x) cursor_pos.x = position.x;
        if (cursor_pos.x > position.x + (int)lines[index].size() * 8 * (int)scale)
            cursor_pos.x = position.x + (int)lines[index].size() * 8 * (int)scale;
    }

    // Draw text to the window (color is white by default)
    void TextArea::Draw(PixelGameEngine* pge, Pixel color, bool showBorder, Pixel borderColor) {

        if (showBorder) {
            olc::vi2d size;
            if (text_max_length.x == -1) size = olc::vi2d(pge->ScreenWidth(), pge->ScreenHeight()) - position;
            else size = text_max_length * 8 * scale - olc::vi2d(1, 1);
            pge->DrawRect(position, size, borderColor);
        }

        int start_pos = position.y;
        unsigned index_pos = 0;

        for (const std::string& str : lines) {

            pge->DrawString(position.x, start_pos, str, color, scale);

            if (index_pos == index && is_selected) {
                pge->FillRect({ cursor_pos.x, start_pos + 8 * (int)scale - 2 }, { (int)scale * 8, (int)scale * 4 }, color);
            }

            start_pos += scale * 8;
            index_pos++;
        }
    }

    // TextBox
    void TextBox::Initialize(const vi2d& pos, const vi2d& box_size, Pixel box_color, uint32_t text_scale, int max_length) {
        position = pos;
        size = box_size;
        scale = text_scale;
        text_box_color = box_color;
        text_max_length = max_length;
        if (size.x < text_max_length * 8 * (int)scale) {
            size.x = text_max_length * 8 * (int)scale;
        }

        cursor_pos = position.x;
    }

    void TextBox::Initialize(int pos_x, int pos_y, int size_x, int size_y, Pixel box_color, uint32_t text_scale, int max_length) {
        position = { pos_x, pos_y };
        size = { size_x, size_y };
        scale = text_scale;
        text_box_color = box_color;
        text_max_length = max_length;
        if (size.x < text_max_length * 8 * (int)scale) {
            size.x = text_max_length * 8 * (int)scale;
        }

        cursor_pos = position.x;
    }

    bool TextBox::IsPointInBounds(const vi2d& point) {
        return (point.x > position.x && point.x < position.x + size.x &&
            point.y > position.y && point.y < position.y + size.y);
    }

    // For user input
    void TextBox::Input(PixelGameEngine* pge) {

        // For toggling is_selected booleans
        const vi2d& mouse_pos = vi2d(pge->GetMouseX(), pge->GetMouseY());

        if (pge->GetMouse(0).bPressed) {
            is_selected = IsPointInBounds(mouse_pos);
        }

        if (pge->GetMouse(0).bHeld) {
            if (IsPointInBounds(mouse_pos)) {
                if (is_mouse_move) {
                    offset = mouse_pos - position;
                    offset_cursor = mouse_pos.x - cursor_pos;
                    is_pressed = true;
                }
            }
            if (is_mouse_move && is_pressed) {
                cursor_pos = mouse_pos.x - offset_cursor;
                position = mouse_pos - offset;
            }
        }

        if (pge->GetMouse(0).bReleased) is_pressed = false;
        if (!is_selected) return;

        auto FindPos = [&](const std::string& str, int offset = 0) {
            int pos = (cursor_pos - position.x) / (8 * (int)scale) - offset + show_text_pos;
            std::string::const_iterator it = str.begin();
            int n = 0;
            while (pos > 0 && n != pos) {
                it++;
                n++;
            }

            return it;
        };

        auto InputText = [&]() {
            std::string c = TextInput::Get().EnterText(pge);
            if (c != "") {
                std::string str = text_stream.str();

                if (text_max_length < 0 || (int)str.size() < text_max_length) {

                    // Add it into the string
                    str.insert(FindPos(str), c[0]);
                    text_stream.str("");
                    text_stream << str;

                    // Increase position
                    if (text_stream.str().size() > size.x / (8 * scale)) show_text_pos++;
                    else cursor_pos += 8 * (int)scale;
                }
            }
        };

        auto ClearText = [&]() {
           int pos = (cursor_pos - position.x) / (8 * (int)scale) + show_text_pos;
           std::string original_str = text_stream.str();

           // Check if pos >= 0 to avoid out of bounds
           if (pos >= 0) {
               original_str.erase(FindPos(original_str, 1));

               // Set string and string at index to the original string
               text_stream.str("");
               text_stream << original_str;

               // Move the cursor back, but not so as to make it go out of screen
               if (show_text_pos > 0) show_text_pos--;
               else cursor_pos -= 8 * scale;
           }
        };

        InputText();

        bool is_ctrl_pressed = pge->GetKey(CTRL).bHeld;

        auto CheckNoWhiteSpace = [&](char ch) {
            return (bool)(isalpha(ch) || isdigit(ch));
        };

        auto JumpToNextText = [&](int direction) {
            
            // Jump distance is the amount of characters to jump in direction
            int init_pos = (cursor_pos - position.x) / (8 * scale) + show_text_pos;

            // Move cursor towards left, if it finds alphabets, then set this boolean flag to true
            bool is_cursor_read_letters = false;
            const std::string& str = text_stream.str();

            while (true) {
                if ((direction > 0 && init_pos > (int)str.size() - 1) ||
                    (direction < 0 && init_pos <= 0) ||
                    (str[init_pos] == ' ' && is_cursor_read_letters)) break;
                is_cursor_read_letters |= CheckNoWhiteSpace(str[init_pos]);
                init_pos += direction;
            
                if (direction < 0) {
                    if (show_text_pos > 0) show_text_pos--;
                    else cursor_pos -= 8 * scale;
                }
                else {
                    int pos = (cursor_pos - position.x) / (8 * scale);
                    if (pos + show_text_pos < text_stream.str().size()) {
                        if (pos == (int)(size.x / (8 * scale))) show_text_pos++;
                        else cursor_pos += 8 * scale;
                    }
                }
            }
        };

        if (pge->GetKey(LEFT).bPressed) {
            if (is_ctrl_pressed) JumpToNextText(-1);
            else {
                if (show_text_pos > 0) show_text_pos--;
                else cursor_pos -= 8 * scale;
            }
        }
        else if (pge->GetKey(RIGHT).bPressed) {
            if (is_ctrl_pressed) JumpToNextText(1);
            else {
                int pos = (cursor_pos - position.x) / (8 * scale);
                if (pos + show_text_pos < text_stream.str().size()) {
                    if (pos == (int)(size.x / (8 * scale))) show_text_pos++;
                    else cursor_pos += 8 * scale;
                }
            }
        }

        if (pge->GetKey(BACK).bPressed) {
            if (is_ctrl_pressed) {
                int init_pos = (cursor_pos - position.x) / (8 * scale) + show_text_pos;
                int cursor_pos_cache = cursor_pos;

                // Move cursor towards left, if it finds alphabets, then set this boolean flag to true
                bool is_cursor_read_letters = false;

                while (init_pos > 0) {
                    is_cursor_read_letters |= CheckNoWhiteSpace(text_stream.str()[init_pos-1]);
                    if (text_stream.str()[init_pos-1] == ' ' && is_cursor_read_letters) break;
                    ClearText();
                    init_pos--;
                
                    if (show_text_pos == 0) cursor_pos_cache -= 8 * scale;
                }
                //int n = init_pos_cache - init_pos;
                //cursor_pos = position.x + 8 * scale * init_pos;
                cursor_pos = cursor_pos_cache;
            }
            else { ClearText(); }
        }

        if (cursor_pos < position.x) cursor_pos = position.x;
        else if (cursor_pos > position.x + 8 * (int)scale * (int)text_stream.str().size())
            cursor_pos = position.x + 8 * (int)scale * (int)text_stream.str().size();
    }

    // For drawing text to the window (color is white by default)
    void TextBox::Draw(PixelGameEngine* pge, Pixel text_color, bool is_fill) {

        int spacing = (int)(std::fabs((float)size.y - 8 * scale) / 2); // change std::fabsf to std::fabs because of https://gcc.gnu.org/bugzilla/show_bug.cgi?id=79700
        spacing = max(spacing, 1);

        if (is_fill) pge->FillRect(position, size, text_box_color);
        else pge->DrawRect(position, size, text_box_color);

        std::string show_text = text_stream.str().substr(show_text_pos, size.x / (8*scale));
        pge->DrawString(position.x + 2, position.y + spacing, show_text, text_color, scale);

        if (is_selected) pge->FillRect({ cursor_pos, position.y + 8 * (int)scale - 2 }, { (int)scale * 8, (int)scale * 4 }, text_color);
    }

    void TextBox::Draw(PixelGameEngine* pge, Pixel text_color, Pixel box_color, bool is_fill) {
        const olc::Pixel& init_color = text_box_color;
        text_box_color = box_color;
        Draw(pge, text_color, is_fill);
        text_box_color = init_color;
    }
}
#endif
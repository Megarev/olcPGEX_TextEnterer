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

#if __linux__

#undef None // None defined in /usr/include/X11/X.h

#define max(a, b)  (((a) > (b)) ? (a) : (b)) 
#define min(a, b)  (((a) < (b)) ? (a) : (b)) 
#endif

enum TextKey {
    None = -1,
    A = 0, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q, R, S, T, U, V, W, X, Y, Z,
    Num0, Num1, Num2, Num3, Num4, Num5, Num6, Num7, Num8, Num9,
    LBracket, RBracket, Semicolon, Comma, Period, Quote, ForwardSlash, BackwardSlash,
    Tilda, Equal, Hyphen, Space
};

namespace olc {

    Sprite* font_sprite = nullptr;
    Decal* font_decal = nullptr;

    void DrawRotatedString(PixelGameEngine* pge, int32_t x, int32_t y, const std::string& sText, float angle, Pixel col = WHITE, uint32_t scale = 1);
    void DrawRotatedString(PixelGameEngine* pge, int32_t x, int32_t y, const std::string& sText, float angle, vi2d origin = { 0, 0 }, Pixel col = WHITE, uint32_t scale = 1);
    void DrawRotatedStringDecal(PixelGameEngine* pge, float x, float y, const std::string& sText, float angle, Pixel col = WHITE, vf2d scale = { 1.0f, 1.0f });
    void DrawRotatedStringDecal(PixelGameEngine* pge, float x, float y, const std::string& sText, float angle, vf2d origin = { 0.0f, 0.0f }, Pixel col = WHITE, vf2d scale = { 1.0f, 1.0f });

    // For clearing memory allocated for font_sprite and font_decal
    void Clear() {
        if (font_decal != nullptr) delete font_decal;
        if (font_sprite != nullptr) delete font_sprite;
    }

    // Construct Font Sheet (only for rotated strings)
    // As font sprite isn't a public member in the original header file, another font sheet has to be made (Use in OnUserCreate)
    void ConstructFontSheet()
    {
        std::string data;
        data += "?Q`0001oOch0o01o@F40o0<AGD4090LAGD<090@A7ch0?00O7Q`0600>00000000";
        data += "O000000nOT0063Qo4d8>?7a14Gno94AA4gno94AaOT0>o3`oO400o7QN00000400";
        data += "Of80001oOg<7O7moBGT7O7lABET024@aBEd714AiOdl717a_=TH013Q>00000000";
        data += "720D000V?V5oB3Q_HdUoE7a9@DdDE4A9@DmoE4A;Hg]oM4Aj8S4D84@`00000000";
        data += "OaPT1000Oa`^13P1@AI[?g`1@A=[OdAoHgljA4Ao?WlBA7l1710007l100000000";
        data += "ObM6000oOfMV?3QoBDD`O7a0BDDH@5A0BDD<@5A0BGeVO5ao@CQR?5Po00000000";
        data += "Oc``000?Ogij70PO2D]??0Ph2DUM@7i`2DTg@7lh2GUj?0TO0C1870T?00000000";
        data += "70<4001o?P<7?1QoHg43O;`h@GT0@:@LB@d0>:@hN@L0@?aoN@<0O7ao0000?000";
        data += "OcH0001SOglLA7mg24TnK7ln24US>0PL24U140PnOgl0>7QgOcH0K71S0000A000";
        data += "00H00000@Dm1S007@DUSg00?OdTnH7YhOfTL<7Yh@Cl0700?@Ah0300700000000";
        data += "<008001QL00ZA41a@6HnI<1i@FHLM81M@@0LG81?O`0nC?Y7?`0ZA7Y300080000";
        data += "O`082000Oh0827mo6>Hn?Wmo?6HnMb11MP08@C11H`08@FP0@@0004@000000000";
        data += "00P00001Oab00003OcKP0006@6=PMgl<@440MglH@000000`@000001P00000000";
        data += "Ob@8@@00Ob@8@Ga13R@8Mga172@8?PAo3R@827QoOb@820@0O`0007`0000007P0";
        data += "O`000P08Od400g`<3V=P0G`673IP0`@3>1`00P@6O`P00g`<O`000GP800000000";
        data += "?P9PL020O`<`N3R0@E4HC7b0@ET<ATB0@@l6C4B0O`H3N7b0?P01L3R000000020";

        font_sprite = new Sprite(128, 48);
        int px = 0, py = 0;
        for (size_t b = 0; b < 1024; b += 4)
        {
            uint32_t sym1 = (uint32_t)data[b + 0] - 48;
            uint32_t sym2 = (uint32_t)data[b + 1] - 48;
            uint32_t sym3 = (uint32_t)data[b + 2] - 48;
            uint32_t sym4 = (uint32_t)data[b + 3] - 48;
            uint32_t r = sym1 << 18 | sym2 << 12 | sym3 << 6 | sym4;

            for (int i = 0; i < 24; i++)
            {
                int k = r & (1 << i) ? 255 : 0;
                font_sprite->SetPixel(px, py, Pixel(k, k, k, k));
                if (++py == 48) { px++; py = 0; }
            }
        }

        font_decal = new Decal(font_sprite);
    }

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

        char EnterText(PixelGameEngine* pge);
    };

    class TextArea {
    private:
        std::ostringstream text_stream;
        std::vector<std::string> lines = { "" };
        vi2d position, cursor_pos;
        uint32_t scale = 1, index = 0;
        vi2d text_max_length = { -1, -1 };
        /*
           The maximum amount of characters each line in text area can hold
           text_max_length = -1 -> no limit to string length (for both x and y)
        */
    public:
        TextArea() {}
        TextArea(const vi2d& start_pos, uint32_t text_scale = 1, vi2d max_length = vi2d(-1, -1))
            : position(start_pos), cursor_pos(start_pos), scale(text_scale), text_max_length(max_length) {}

        void Initialize(const vi2d& start_pos, uint32_t text_scale = 1, vi2d max_length = vi2d(-1, -1));
        void Initialize(int x, int y, uint32_t text_scale = 1, int max_length_x = -1, int max_length_y = -1);

        void Input(PixelGameEngine* pge);
        void Draw(PixelGameEngine* pge, Pixel color = WHITE);

        vi2d GetPosition() const { return position; }
        std::vector<std::string> GetStrings() const { return lines; }
        vi2d GetCursorPosition() const { return cursor_pos; }
    };

    class TextBox {
    private:
        vi2d position, size;
        int text_max_length = -1;

        std::ostringstream text_stream;

        Pixel text_box_color = WHITE;
        int cursor_pos;
        uint32_t scale = 1;

        bool is_selected = false;

        bool is_mouse_move = false, is_pressed = false;
        vi2d offset;
        int offset_cursor;
    public:
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

        std::string GetText() const { return text_stream.str(); }
        uint32_t GetScale() const { return scale; }
        vi2d GetPos() const { return position; }
    };

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

    char TextInput::EnterText(PixelGameEngine* pge) {
        int index = GetAnyTextKey(pge);
        if (index == None) return '\0';

        if (pge->GetKey(SHIFT).bHeld) {
            return text_shift[index];
        }

        return text_noshift[index];
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

        char c = TextInput::Get().EnterText(pge);
        if (c != '\0') {
            std::string str = text_stream.str();

            if (text_max_length.x < 0 || (text_max_length.x > 0 && (int)str.size() < text_max_length.x)) {

                // Add it into the string
                str.insert(FindPos(str), c);
                text_stream.str("");
                text_stream << str;
                lines[index] = text_stream.str();

                // Increase position
                cursor_pos.x += 8 * (int)scale;
            }
        }

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
            index = max(index - 1, 0); // Move the index up
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

        if (pge->GetKey(LEFT).bPressed) {
            cursor_pos.x -= 8 * scale;
        }
        else if (pge->GetKey(RIGHT).bPressed) {
            cursor_pos.x += 8 * scale;
        }

        if (pge->GetKey(BACK).bPressed) {
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
        }

        // Clamp the cursor in bounds
        if (cursor_pos.x < position.x) cursor_pos.x = position.x;
        if (cursor_pos.x > position.x + (int)lines[index].size() * 8 * (int)scale)
            cursor_pos.x = position.x + (int)lines[index].size() * 8 * (int)scale;
    }

    // Draw text to the window (color is white by default)
    void TextArea::Draw(PixelGameEngine* pge, Pixel color) {

        int start_pos = position.y;
        unsigned index_pos = 0;

        for (const std::string& str : lines) {

            pge->DrawString(position.x, start_pos, str, color, scale);

            if (index_pos == index) {
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

        char c = TextInput::Get().EnterText(pge);
        auto FindPos = [&](std::string& str, int offset = 0) {
            int pos = (cursor_pos - position.x) / (8 * (int)scale) - offset;
            std::string::iterator it = str.begin();
            int n = 0;
            while (pos > 0 && n != pos) {
                it++;
                n++;
            }

            return it;
        };

        if (c != '\0') {
            std::string str = text_stream.str();

            if (text_max_length < 0 || (int)str.size() < text_max_length) {

                // Add it into the string
                str.insert(FindPos(str), c);
                text_stream.str("");
                text_stream << str;

                // Increase position
                cursor_pos += 8 * (int)scale;
            }
        }

        if (pge->GetKey(BACK).bPressed) {
            int pos = (cursor_pos - position.x) / (8 * (int)scale) - 1;
            std::string original_str = text_stream.str();

            // Check if pos >= 0 to avoid out of bounds
            if (pos >= 0) {
                original_str.erase(FindPos(original_str, 1));

                // Set string and string at index to the original string
                text_stream.str("");
                text_stream << original_str;

                // Move the cursor back, but not so as to make it go out of screen
                cursor_pos -= 8 * scale;
            }
        }

        if (pge->GetKey(LEFT).bPressed) cursor_pos -= 8 * (int)scale;
        else if (pge->GetKey(RIGHT).bPressed) cursor_pos += 8 * (int)scale;

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
        pge->DrawString(position.x + 2, position.y + spacing, text_stream.str(), text_color, scale);

        if (is_selected) pge->FillRect({ cursor_pos, position.y + 8 * (int)scale - 2 }, { (int)scale * 8, (int)scale * 4 }, text_color);
    }

    // For Drawing Rotated Strings
    void DrawRotatedString(PixelGameEngine* pge, int32_t x, int32_t y, const std::string& sText, float angle, Pixel col, uint32_t scale) {
        int32_t sx = 0;
        int32_t sy = 0;
        Pixel::Mode m = pge->GetPixelMode();
        int32_t text_length = (int32_t)sText.size();
        if (col.a != 255)		pge->SetPixelMode(Pixel::ALPHA);
        else					pge->SetPixelMode(Pixel::MASK);
        for (auto c : sText) {
            if (c == '\n') {
                sx = 0; sy += 8 * scale;
            }
            else {
                int32_t ox = (c - 32) % 16;
                int32_t oy = (c - 32) / 16;

                if (scale > 1) {
                    for (uint32_t i = 0; i < 8; i++)
                        for (uint32_t j = 0; j < 8; j++) {
                            if (font_sprite->GetPixel(i + ox * 8, j + oy * 8).r > 0) {
                                for (uint32_t is = 0; is < scale; is++)
                                    for (uint32_t js = 0; js < scale; js++) {

                                        vf2d points = {
                                           x + (sx + i * scale + 8) * cosf(angle) - (sy + j * scale + 8) * sinf(angle),
                                           y + (sx + i * scale + 8) * sinf(angle) + (sy + j * scale + 8) * cosf(angle)
                                        };
                                        pge->Draw((vi2d)points, col);
                                    }
                            }
                        }
                }
                else
                {
                    for (uint32_t i = 0; i < 8; i++)
                        for (uint32_t j = 0; j < 8; j++)
                            if (font_sprite->GetPixel(i + ox * 8, j + oy * 8).r > 0) {
                                vf2d points = {
                                           x + (sx + i + 8) * cosf(angle) - (sy + j + 8) * sinf(angle),
                                           y + (sx + i + 8) * sinf(angle) + (sy + j + 8) * cosf(angle)
                                };
                                pge->Draw((vi2d)points, col);
                            }
                }
                sx += 8 * scale;
            }
        }
        pge->SetPixelMode(m);
    }

    void DrawRotatedString(PixelGameEngine* pge, int32_t x, int32_t y, const std::string& sText, float angle, vi2d origin, Pixel col, uint32_t scale) {
        int32_t sx = 0;
        int32_t sy = 0;
        Pixel::Mode m = pge->GetPixelMode();
        int32_t text_length = (int32_t)sText.size();
        if (col.a != 255)		pge->SetPixelMode(Pixel::ALPHA);
        else					pge->SetPixelMode(Pixel::MASK);
        for (auto c : sText) {
            if (c == '\n') {
                sx = 0; sy += 8 * scale;
            }
            else {
                int32_t ox = (c - 32) % 16;
                int32_t oy = (c - 32) / 16;

                if (scale > 1) {
                    for (uint32_t i = 0; i < 8; i++)
                        for (uint32_t j = 0; j < 8; j++) {
                            if (font_sprite->GetPixel(i + ox * 8, j + oy * 8).r > 0) {
                                for (uint32_t is = 0; is < scale; is++)
                                    for (uint32_t js = 0; js < scale; js++) {

                                        vf2d points = {
                                           x + (sx + i * scale + 8 - origin.x) * cosf(angle) - (sy + j * scale + 8 - origin.y) * sinf(angle),
                                           y + (sx + i * scale + 8 - origin.x) * sinf(angle) + (sy + j * scale + 8 - origin.y) * cosf(angle)
                                        };
                                        pge->Draw((vi2d)points, col);
                                    }
                            }
                        }
                }
                else
                {
                    for (uint32_t i = 0; i < 8; i++)
                        for (uint32_t j = 0; j < 8; j++)
                            if (font_sprite->GetPixel(i + ox * 8, j + oy * 8).r > 0) {
                                vf2d points = {
                                           x + (sx + i + 8 - origin.x) * cosf(angle) - (sy + j + 8 - origin.y) * sinf(angle),
                                           y + (sx + i + 8 - origin.x) * sinf(angle) + (sy + j + 8 - origin.y) * cosf(angle)
                                };
                                pge->Draw((vi2d)points, col);
                            }
                }
                sx += 8 * scale;
            }
        }
        pge->SetPixelMode(m);
    }

    void DrawRotatedStringDecal(PixelGameEngine* pge, float x, float y, const std::string& sText, float angle, Pixel col, vf2d scale) {
        vf2d spos = { 0.0f, 0.0f };
        for (auto c : sText) {
            if (c == '\n') {
                spos.x = 0; spos.y += 8.0f * scale.y;
            }
            else {
                int32_t ox = (c - 32) % 16;
                int32_t oy = (c - 32) / 16;

                vf2d points = {
                      x + (spos.x + 8) * cosf(angle) - (spos.y + 8) * sinf(angle),
                      y + (spos.x + 8) * sinf(angle) + (spos.y + 8) * cosf(angle)
                };

                pge->DrawPartialDecal(points, font_decal, { float(ox) * 8.0f, float(oy) * 8.0f }, { 8.0f, 8.0f }, scale, col);
                spos.x += 8.0f * scale.x;
            }
        }
    }

    void DrawRotatedStringDecal(PixelGameEngine* pge, float x, float y, const std::string& sText, float angle, vf2d origin, Pixel col, vf2d scale) {
        vf2d spos = { 0.0f, 0.0f };
        for (auto c : sText) {
            if (c == '\n') {
                spos.x = 0; spos.y += 8.0f * scale.y;
            }
            else {
                int32_t ox = (c - 32) % 16;
                int32_t oy = (c - 32) / 16;

                vf2d points = {
                      x + (spos.x + 8 - origin.x) * cosf(angle) - (spos.y + 8 - origin.y) * sinf(angle),
                      y + (spos.x + 8 - origin.x) * sinf(angle) + (spos.y + 8 - origin.y) * cosf(angle)
                };

                pge->DrawPartialDecal(points, font_decal, { float(ox) * 8.0f, float(oy) * 8.0f }, { 8.0f, 8.0f }, scale, col);
                spos.x += 8.0f * scale.x;
            }
        }
    }
}

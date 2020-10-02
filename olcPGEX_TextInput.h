/*
License (OLC-3)
Copyright 2018-2020 OneLoneCoder.com

Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:

Redistributions or derivations of source code must retain the above copyright notice, this list of conditions and the following disclaimer.

Redistributions or derivative works in binary form must reproduce the above copyright notice. This list of conditions and the following disclaimer must be reproduced in the documentation and/or other materials provided with the distribution.

Neither the name of the copyright holder nor the names of its contributors may be used to endorse or promote products derived from this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#pragma once
#include "olcPixelGameEngine.h"
#include <Windows.h>
#include <string>

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
        bool on_press[256]{ 0 };
        int n_TextKeys;
        std::string text_noshift = "abcdefghijklmnopqrstuvwxyz0123456789[];,.'/\\`=- ";
        std::string text_shift = "ABCDEFGHIJKLMNOPQRSTUVWXYZ)!@#$%^&*({}:<>\"?|~+_ ";
        TextInput() {
            n_TextKeys = 48;
        }
    public:
        static TextInput& Get() {
            static TextInput text_enterer;
            return text_enterer;
        }

        bool ManageTextKeyPress(const TextKey& TextKey) {
            return IsTextKeyPressed(TextKey);
        }

        bool IsTextKeyPressed(const TextKey& TextKey) {
            int vTextKey = 0;
            switch (TextKey)
            {
            default:                        vTextKey = 0;             break;
            case TextKey::A:                vTextKey = 'A';           break;
            case TextKey::B:                vTextKey = 'B';           break;
            case TextKey::C:                vTextKey = 'C';           break;
            case TextKey::D:                vTextKey = 'D';           break;
            case TextKey::E:                vTextKey = 'E';           break;
            case TextKey::F:                vTextKey = 'F';           break;
            case TextKey::G:                vTextKey = 'G';           break;
            case TextKey::H:                vTextKey = 'H';           break;
            case TextKey::I:                vTextKey = 'I';           break;
            case TextKey::J:                vTextKey = 'J';           break;
            case TextKey::K:                vTextKey = 'K';           break;
            case TextKey::L:                vTextKey = 'L';           break;
            case TextKey::M:                vTextKey = 'M';           break;
            case TextKey::N:                vTextKey = 'N';           break;
            case TextKey::O:                vTextKey = 'O';           break;
            case TextKey::P:                vTextKey = 'P';           break;
            case TextKey::Q:                vTextKey = 'Q';           break;
            case TextKey::R:                vTextKey = 'R';           break;
            case TextKey::S:                vTextKey = 'S';           break;
            case TextKey::T:                vTextKey = 'T';           break;
            case TextKey::U:                vTextKey = 'U';           break;
            case TextKey::V:                vTextKey = 'V';           break;
            case TextKey::W:                vTextKey = 'W';           break;
            case TextKey::X:                vTextKey = 'X';           break;
            case TextKey::Y:                vTextKey = 'Y';           break;
            case TextKey::Z:                vTextKey = 'Z';           break;
            case TextKey::Num0:             vTextKey = '0';           break;
            case TextKey::Num1:             vTextKey = '1';           break;
            case TextKey::Num2:             vTextKey = '2';           break;
            case TextKey::Num3:             vTextKey = '3';           break;
            case TextKey::Num4:             vTextKey = '4';           break;
            case TextKey::Num5:             vTextKey = '5';           break;
            case TextKey::Num6:             vTextKey = '6';           break;
            case TextKey::Num7:             vTextKey = '7';           break;
            case TextKey::Num8:             vTextKey = '8';           break;
            case TextKey::Num9:             vTextKey = '9';           break;

            case TextKey::LBracket:         vTextKey = VK_OEM_4;      break;
            case TextKey::RBracket:         vTextKey = VK_OEM_6;      break;
            case TextKey::Semicolon:        vTextKey = VK_OEM_1;      break;
            case TextKey::Comma:            vTextKey = VK_OEM_COMMA;  break;
            case TextKey::Period:           vTextKey = VK_OEM_PERIOD; break;
            case TextKey::Quote:            vTextKey = VK_OEM_7;      break;
            case TextKey::ForwardSlash:     vTextKey = VK_OEM_2;      break;
            case TextKey::BackwardSlash:    vTextKey = VK_OEM_5;      break;
            case TextKey::Tilda:            vTextKey = VK_OEM_3;      break;
            case TextKey::Equal:            vTextKey = VK_OEM_PLUS;   break;
            case TextKey::Hyphen:           vTextKey = VK_OEM_MINUS;  break;

            case TextKey::Space:            vTextKey = VK_SPACE;      break;
            }

            if (GetAsyncKeyState(vTextKey) < 0 && !on_press[vTextKey]) {
                on_press[vTextKey] = true;

                return true;
            }
            if (GetAsyncKeyState(vTextKey) == 0 && on_press[vTextKey]) {
                on_press[vTextKey] = false;
            }

            return false;
        }

        int GetAnyTextKey() {
            bool is_press = false;
            for (int i = 0; i < n_TextKeys; i++) {
                if (IsTextKeyPressed((TextKey)i)) {
                    return i;
                }
            }
            return None;
        }

        char EnterText() {
            int index = GetAnyTextKey();
            if (index == None) return '\0';

            if (GetAsyncKeyState(VK_SHIFT)) {
                return text_shift[index];
            }

            return text_noshift[index];
        }
    };

    class TextArea {
    private:
        std::ostringstream text_stream;
        std::vector<std::string> lines = { "" };
        olc::vi2d position, cursor_pos;
        uint32_t scale = 1, index = 0;
    public:
        TextArea() {}
        TextArea(const olc::vi2d& start_pos, uint32_t text_scale = 1)
            : position(start_pos), cursor_pos(start_pos), scale(text_scale) {}

        void Input(olc::PixelGameEngine* pge) {

            if (!pge->IsFocused()) return;

            char c = TextInput::Get().EnterText();
            if (c != '\0') {
                std::string str = text_stream.str();
                
                // Calculate the index at which cursor is
                int pos = (cursor_pos.x - position.x) / (8 * (int)scale);
                
                // Find the position by iterator
                std::string::iterator it = str.begin();
                int n = 0;
                while (n != pos) {
                    it++;
                    n++;
                }
                // Add it into the string
                str.insert(it, c);
                text_stream.str("");
                text_stream << str;
                lines[index] = text_stream.str();

                // Increase position
                cursor_pos.x += 8 * (int)scale;
            }

            if (pge->GetKey(olc::ENTER).bPressed) {
                std::vector<std::string>::iterator it = lines.begin();

                int pos = (cursor_pos.x - position.x) / (8 * (int)scale);
                std::string line_string_original = lines[index].substr(0, pos); // Sub-string from 0 to pos
                std::string line_string = lines[index].substr(pos); // Sub-string from pos to string_size

                // Find the index at which new line was done
                int n = 0;
                while (n != index + 1) {
                    it++;
                    n++;
                }

                // Set original string (the line from which new line was done)
                lines[index] = std::move(line_string_original);
                // Insert a new string with the sub-string from pos to string_size
                lines.insert(it, line_string);
                text_stream.str("");
                text_stream << line_string;
                index++; // Add to index variable
            }

            if (pge->GetKey(olc::UP).bPressed) {
                index = max(index--, 0); // Move the index up
                std::string line = lines[index]; // Set string to new index

                text_stream.str("");
                text_stream << line;
            }
            else if (pge->GetKey(olc::DOWN).bPressed) {
                index = min(index++, lines.size() - 1); // Move the index down
                std::string line = lines[index]; // Set string to new index

                text_stream.str("");
                text_stream << line;
            }

            if (pge->GetKey(olc::LEFT).bPressed) {
                cursor_pos.x -= 8 * scale;
            }
            else if (pge->GetKey(olc::RIGHT).bPressed) {
                cursor_pos.x += 8 * scale;
            }

            if (pge->GetKey(olc::BACK).bPressed) {
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
                        std::string::iterator it = original_str.begin();
                        int n = 0;
                        int pos = (cursor_pos.x - position.x) / (8 * (int)scale) - 1;
                        
                        // Check if pos >= 0 to avoid out of bounds
                        if (pos >= 0) {
                            while (n != pos) {
                                it++;
                                n++;
                            }

                            original_str.erase(it);

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

                        // Take out the line from in between/back of the lines vector
                        int n = 0;
                        std::vector<std::string>::iterator it = lines.begin();
                        int pos = (cursor_pos.x - position.x) / (8 * (int)scale);
                        
                        while (n != index) {
                            n++;
                            it++;
                        }
                        
                        // Current Line is the line which is currently in the active line
                        std::string current_line = lines[index];
                        
                        lines.erase(it);
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
            if (cursor_pos.x > (int)lines[index].size() * 8 * scale) cursor_pos.x = (int)lines[index].size() * 8 * scale;
        }

        void Draw(olc::PixelGameEngine* pge, olc::Pixel color = olc::WHITE) {

            int start_pos = position.y;
            int index_pos = 0;

            for (const std::string& str : lines) {

                pge->DrawString(position.x, start_pos, str, color, scale);
                
                if (index_pos == index) {
                    pge->FillRect({ cursor_pos.x, start_pos + 8 * (int)scale - 2 }, { (int)scale * 8, (int)scale * 4 });
                }
                
                start_pos += scale * 8;
                index_pos++;
            }
        }

        olc::vi2d GetPosition() const { return position; }
        std::vector<std::string> GetStrings() const { return lines; }
        olc::vi2d GetCursorPosition() const { return cursor_pos; }
    };
}

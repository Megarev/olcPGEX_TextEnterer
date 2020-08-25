#include <iostream>
#include <Windows.h>

enum Key {
    None = -1,
    A = 0, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q, R, S, T, U, V, W, X, Y, Z,
    Num0, Num1, Num2, Num3, Num4, Num5, Num6, Num7, Num8, Num9,
    LBracket, RBracket, Semicolon, Comma, Period, Quote, ForwardSlash, BackwardSlash,
    Tilda, Equal, Hyphen, Space, LShift, RShift,
};

class TextEnterer {
private:
    bool on_press[256]{ 0 };
    int n_keys;
    std::string text_noshift = "abcdefghijklmnopqrstuvwxyz0123456789[];,.'\\/`=- ";
    std::string text_shift = "ABCDEFGHIJKLMNOPQRSTUVWXYZ)!@#$%^&*({}:<>'|?~+_ ";
    TextEnterer() {
        n_keys = 49;
    }
public:
    static TextEnterer& Get() {
        static TextEnterer text_enterer;
        return text_enterer;
    }

    bool ManageKeyPress(const Key& key) {
        return IsKeyPressed(key);
    }

    bool IsKeyPressed(const Key& key) {
        int vkey = 0;
        switch (key)
        {
        default:                    vkey = 0;             break;
        case Key::A:                vkey = 'A';           break;
        case Key::B:                vkey = 'B';           break;
        case Key::C:                vkey = 'C';           break;
        case Key::D:                vkey = 'D';           break;
        case Key::E:                vkey = 'E';           break;
        case Key::F:                vkey = 'F';           break;
        case Key::G:                vkey = 'G';           break;
        case Key::H:                vkey = 'H';           break;
        case Key::I:                vkey = 'I';           break;
        case Key::J:                vkey = 'J';           break;
        case Key::K:                vkey = 'K';           break;
        case Key::L:                vkey = 'L';           break;
        case Key::M:                vkey = 'M';           break;
        case Key::N:                vkey = 'N';           break;
        case Key::O:                vkey = 'O';           break;
        case Key::P:                vkey = 'P';           break;
        case Key::Q:                vkey = 'Q';           break;
        case Key::R:                vkey = 'R';           break;
        case Key::S:                vkey = 'S';           break;
        case Key::T:                vkey = 'T';           break;
        case Key::U:                vkey = 'U';           break;
        case Key::V:                vkey = 'V';           break;
        case Key::W:                vkey = 'W';           break;
        case Key::X:                vkey = 'X';           break;
        case Key::Y:                vkey = 'Y';           break;
        case Key::Z:                vkey = 'Z';           break;
        case Key::Num0:             vkey = '0';           break;
        case Key::Num1:             vkey = '1';           break;
        case Key::Num2:             vkey = '2';           break;
        case Key::Num3:             vkey = '3';           break;
        case Key::Num4:             vkey = '4';           break;
        case Key::Num5:             vkey = '5';           break;
        case Key::Num6:             vkey = '6';           break;
        case Key::Num7:             vkey = '7';           break;
        case Key::Num8:             vkey = '8';           break;
        case Key::Num9:             vkey = '9';           break;
        
        case Key::LBracket:         vkey = VK_OEM_4;      break;
        case Key::RBracket:         vkey = VK_OEM_6;      break;
        case Key::Semicolon:        vkey = VK_OEM_1;      break;
        case Key::Comma:            vkey = VK_OEM_COMMA;  break;
        case Key::Period:           vkey = VK_OEM_PERIOD; break;
        case Key::Quote:            vkey = VK_OEM_7;      break;
        case Key::ForwardSlash:     vkey = VK_OEM_2;      break;
        case Key::BackwardSlash:    vkey = VK_OEM_5;      break;
        case Key::Tilda:            vkey = VK_OEM_3;      break;
        case Key::Equal:            vkey = VK_OEM_PLUS;   break;
        case Key::Hyphen:           vkey = VK_OEM_MINUS;  break;
        
        case Key::Space:            vkey = VK_SPACE;      break;
        
        case Key::LShift:           vkey = VK_LSHIFT;     break;
        case Key::RShift:           vkey = VK_RSHIFT;     break;
        }
        
        // On Key Press
        if (GetAsyncKeyState(vkey) < 0 && !on_press[vkey]) {
            on_press[vkey] = true;
        
            return true;
        }
        
        // On Key Release
        if (GetAsyncKeyState(vkey) == 0 && on_press[vkey]) {
            on_press[vkey] = false;
        }

        return false;
    }

    int GetAnyKey() {
        bool is_press = false;
        for (int i = 0; i < n_keys - 2; i++) {
            if (IsKeyPressed((Key)i)) {
                return i;
            }
        }
        return None;
    }

    void EnterText() {
        int index = GetAnyKey();
        if (index == None) return;

        if (IsKeyPressed(Key::LShift) || IsKeyPressed(Key::RShift)) {
            std::cout << text_shift[index] << std::endl;
        }
        else {
            std::cout << text_noshift[index] << std::endl;
        }
    }
};

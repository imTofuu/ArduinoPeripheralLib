#pragma once

#include "LCDElement.h"
#include "TextLabel.h"

namespace APL {

    class TextButton : public LCDButtonElement, TextLabel {
        TextButton() : TextButton(nullptr) {};
        TextButton(void (*action)()) { setAction(action); }
    };

}
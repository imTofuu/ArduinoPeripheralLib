#pragma once

#include <Peripherals/LCDPeripheral.h>
#include <string>

namespace APL {

    class TextLabel : public LCDElement {
    public:

        UDim2 getSize(Arduino_GFX& display) override;

        void setText(const std::string& text) { thisFrame.text = text; }
        std::string getText() { return thisFrame.text; }

        void setTextColour(uint16_t colour) { thisFrame.textColour = colour; }
        uint16_t getTextColour() { return thisFrame.textColour; }

        void setTextSize(uint8_t size) { thisFrame.textSize = size; }
        uint8_t getTextSize() { return thisFrame.textSize; }

        void setTextPadding(UDim2 padding) { thisFrame.textPadding = padding; }
        UDim2 getTextPadding() { return thisFrame.textPadding; }

    protected:

        void draw(Arduino_GFX& display) override;

    private:

        struct FrameInfo {
            std::string text = "TextLabel";
            uint16_t textColour = 0xffff;
            uint8_t textSize = 3;
            UDim2 textPadding = UDim2();

            bool operator==(const FrameInfo& other) {
                return text == other.text &&
                    textColour == other.textColour &&
                    textSize == other.textSize;
            }
        };

        FrameInfo thisFrame;
        FrameInfo lastFrame;

    };

}
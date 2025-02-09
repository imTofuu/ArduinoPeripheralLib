#include <Peripherals/LCDElements/TextLabel.h>

namespace APL {

    void TextLabel::draw(Arduino_GFX& display) {

        if (thisFrame == lastFrame) return;

        display.setTextWrap(false);

        UI16Vector2 absoluteSize = getSize(display).absolute(display.width(), display.height());
        UI16Vector2 absolutePosition = getPosition().absolute(display.width(), display.height());
        UI16Vector2 absolutePadding = thisFrame.textPadding.absolute(absoluteSize.x, absoluteSize.y);

        if (!p_updated) {
            display.setCursor(absolutePosition.x + (absolutePadding.x / 2), absolutePosition.y + (absolutePadding.y / 2));

            display.setTextSize(lastFrame.textSize);
            display.setTextColor(getBackgroundColour());
            display.println(lastFrame.text.c_str());

        }

        display.setCursor(absolutePosition.x + (absolutePadding.x / 2), absolutePosition.y + (absolutePadding.y / 2));

        display.setTextSize(thisFrame.textSize);
        display.setTextColor(thisFrame.textColour);
        display.println(thisFrame.text.c_str());

        lastFrame = thisFrame;

    }

    UDim2 TextLabel::getSize(Arduino_GFX& display) {
        UI16Vector2 absolutePosition = getPosition().absolute(display.width(), display.height());

        int16_t x, y;
        uint16_t w, h;

        display.setTextSize(thisFrame.textSize);

        display.getTextBounds(thisFrame.text.c_str(), absolutePosition.x, absolutePosition.y, &x, &y, &w, &h);

        UI16Vector2 absolutePadding = thisFrame.textPadding.absolute(w, h);

        return { {0, 0}, {static_cast<uint16_t>(w + absolutePadding.x), static_cast<uint16_t>(h + absolutePadding.y)} };
    }

}
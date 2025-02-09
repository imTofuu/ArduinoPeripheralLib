#include <Peripherals/LCDPeripheral.h>

namespace APL {

    UI16Vector2 UDim2::absolute(uint16_t w, uint16_t h) {
        return {
            static_cast<uint16_t>((scale.x * w) + offset.x),
            static_cast<uint16_t>((scale.y * h) + offset.y)
        };
    }

    void LCDElement::predraw(Arduino_GFX& display) {
        thisFrame.size = getSize(display);

        UI16Vector2 lastFrameAbsolutePosition = lastFrame.position.absolute(display.width(), display.height());
        UI16Vector2 lastFrameAbsoluteSize = lastFrame.size.absolute(display.width(), display.height());

        UI16Vector2 thisFrameAbsolutePosition = thisFrame.position.absolute(display.width(), display.height());
        UI16Vector2 thisFrameAbsoluteSize = thisFrame.size.absolute(display.width(), display.height());

        if (!(thisFrame == lastFrame)) {
            p_updated = true;

            // Clear background and stroke
            display.fillRect(
                lastFrameAbsolutePosition.x - lastFrame.strokeSize,
                lastFrameAbsolutePosition.y - lastFrame.strokeSize,
                lastFrameAbsoluteSize.x + (lastFrame.strokeSize * 2),
                lastFrameAbsoluteSize.y + (lastFrame.strokeSize * 2),
                0x0
            );

            // Draw background
            display.fillRect(
                thisFrameAbsolutePosition.x,
                thisFrameAbsolutePosition.y,
                thisFrameAbsoluteSize.x,
                thisFrameAbsoluteSize.y,
                thisFrame.backgroundColour
            );

            // Draw stroke
            display.fillRect( // TL => TR
                thisFrameAbsolutePosition.x - thisFrame.strokeSize,
                thisFrameAbsolutePosition.y - thisFrame.strokeSize,
                thisFrameAbsoluteSize.x + (2 * thisFrame.strokeSize),
                thisFrame.strokeSize,
                thisFrame.strokeColour
            );
            display.fillRect( // BL => BR
                thisFrameAbsolutePosition.x - thisFrame.strokeSize,
                thisFrameAbsolutePosition.y + thisFrameAbsoluteSize.y,
                thisFrameAbsoluteSize.x + (2 * thisFrame.strokeSize),
                thisFrame.strokeSize,
                thisFrame.strokeColour
            );
            display.fillRect( // TL => BL
                thisFrameAbsolutePosition.x - thisFrame.strokeSize,
                thisFrameAbsolutePosition.y - thisFrame.strokeSize,
                thisFrame.strokeSize,
                thisFrameAbsoluteSize.y + (2 * thisFrame.strokeSize),
                thisFrame.strokeColour
            );
            display.fillRect( // TR => BR
                thisFrameAbsolutePosition.x + thisFrameAbsoluteSize.x,
                thisFrameAbsolutePosition.y - thisFrame.strokeSize,
                thisFrame.strokeSize,
                thisFrameAbsoluteSize.y + (2 * thisFrame.strokeSize),
                thisFrame.strokeColour
            );

            lastFrame = thisFrame;
        }

        display.setCursor(thisFrameAbsolutePosition.x, thisFrameAbsolutePosition.y);

        draw(display);

        p_updated = false;
    }

}
#include <Peripherals/LCDElements/MemoryImageLabel.h>

namespace APL {

    void MemoryImageLabel::draw(Arduino_GFX& display) {
        if (!p_updated) return;

        UI16Vector2 absolutePosition = getPosition().absolute(display.width(), display.height());

        display.draw16bitRGBBitmap(absolutePosition.x, absolutePosition.y, m_data, m_w, m_h);

    }

}
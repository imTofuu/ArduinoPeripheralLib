#pragma once

#include <Peripherals/LCDPeripheral.h>

namespace APL {

    class MemoryImageLabel : public LCDElement {
    public:

        MemoryImageLabel(uint16_t* data, uint8_t w, uint8_t h) : m_data(data), m_w(w), m_h(h) {}

        UDim2 getSize(Arduino_GFX& display) override { return { {0, 0}, {m_w, m_h} }; }

    protected:

        void draw(Arduino_GFX& display) override;

    private:

        uint16_t* m_data;
        uint8_t m_w, m_h;

    };

}
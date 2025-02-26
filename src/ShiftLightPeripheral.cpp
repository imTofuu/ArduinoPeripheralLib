#include <Peripherals/ShiftLightPeripheral.h>

#include <string>

namespace APL {

    void ShiftLightPeripheral::setLightColourRange(float start, float end, uint32_t colour) {
        size_t startLight = static_cast<size_t>(m_numLights * start);
        size_t endLight = static_cast<size_t>(m_numLights * end);

        for (int light = startLight; light < endLight; light++) {
            m_lightColours[light] = colour;
        }
    }

    void ShiftLightPeripheral::setNumLightsOn(size_t lightsOn) { this->m_lightsOn = lightsOn; }

    int ShiftLightPeripheral::start() {
        m_lights.begin();
        return 0;
    }

    void ShiftLightPeripheral::update() {
        m_lights.clear();

        for (int lightIndex = 0; lightIndex < m_lightsOn; lightIndex++) {
            m_lights.setPixelColor(lightIndex, m_lightColours[lightIndex]);
        }

        for (auto& [index, colour] : m_lightExceptions) {
            m_lights.setPixelColor(index, colour);
        }

        m_lights.show();
    }

}
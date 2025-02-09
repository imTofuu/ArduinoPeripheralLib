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
    void ShiftLightPeripheral::setNumLightsOnPointer(size_t* lightsOn) { this->m_lightsOnPointer = lightsOn; }

    int ShiftLightPeripheral::start() {
        m_lights.begin();
        return 0;
    }

    void ShiftLightPeripheral::update() {
        m_lights.clear();

        if (m_lightsOnPointer) m_lightsOn = *m_lightsOnPointer;

        for (int lightIndex = 0; lightIndex < m_lightsOn; lightIndex++) {
            m_lights.setPixelColor(lightIndex, m_lightColours[lightIndex]);
        }

        m_lights.show();
    }

}
#pragma once

#include <Peripheral.h>

#include <Adafruit_NeoPixel.h>
#include <unordered_map>

namespace APL {

    class ShiftLightPeripheral : public Peripheral {
    public:

        ShiftLightPeripheral(size_t numLights, uint8_t gpio)
            : m_lights(Adafruit_NeoPixel(numLights, gpio, NEO_GRB + NEO_KHZ800)),
            m_numLights(numLights),
            m_lightColours(new uint32_t[numLights] { 0 }) {}
        ~ShiftLightPeripheral() { delete[] m_lightColours; }

        void setLightColourRange(float start, float end, uint32_t colour);
        void setNumLightsOn(size_t lightsOn);

        void setLightException(size_t lightIndex, uint32_t colour) { m_lightExceptions[lightIndex] = colour; }
        void removeLightException(size_t lightIndex) { m_lightExceptions.erase(lightIndex); }

        size_t getNumLights() const { return m_numLights; }
        size_t getNumLightsOn() const { return m_lightsOn; }

        int start() override;
        void update() override;

    private:

        Adafruit_NeoPixel m_lights;

        std::unordered_map<size_t, uint32_t> m_lightExceptions;

        size_t m_numLights;
        size_t m_lightsOn = 0;

        uint32_t* m_lightColours;

    };

}
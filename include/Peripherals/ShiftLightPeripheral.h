#pragma once

#include <Peripheral.h>

#include <Adafruit_NeoPixel.h>

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
        void setNumLightsOnPointer(size_t* lightsOn);

        size_t getNumLights() const { return m_numLights; }
        size_t getNumLightsOn() const { return m_lightsOn; }

        int start() override;
        void update() override;

    private:

        Adafruit_NeoPixel m_lights;

        size_t m_numLights;

        size_t* m_lightsOnPointer = nullptr;
        size_t m_lightsOn = 0;

        uint32_t* m_lightColours;

    };

}
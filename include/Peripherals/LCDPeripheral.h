#pragma once

#include <Peripheral.h>

#include <Arduino_GFX_Library.h>
#include <vector>
#include <memory>

namespace APL {

    struct FVector2 {
        float x = 0, y = 0;
        bool operator==(const FVector2& other) {
            return x == other.x && y == other.y;
        }
    };

    struct UI16Vector2 {
        uint16_t x = 0, y = 0;

        bool operator==(const UI16Vector2& other) {
            return x == other.x && y == other.y;
        }
    };

    struct UDim2 {
        FVector2 scale;
        UI16Vector2 offset;
        enum class HorizontalAlignment {
            LEFT, CENTER, RIGHT
        } horizontalAlignment = HorizontalAlignment::LEFT;
        enum class VerticalAlignment {
            TOP, CENTER, BOTTOM
        } verticalAlignment = VerticalAlignment::TOP;

        UI16Vector2 absolute(uint16_t w, uint16_t h);
        UI16Vector2 absolute(uint16_t displayW, uint16_t displayH, uint16_t elementW, uint16_t elementH);

        bool operator==(const UDim2& other) {
            return scale == other.scale &&
                offset == other.offset &&
                horizontalAlignment == other.horizontalAlignment &&
                verticalAlignment == other.verticalAlignment;
        }
    };

    class LCDElement {
    public:

        LCDElement() = default;
        virtual ~LCDElement() = default;

        virtual UDim2 getSize(Arduino_GFX& display) = 0;

        void predraw(Arduino_GFX& display);

        void setPosition(UDim2 position) { thisFrame.position = position; }
        UDim2 getPosition() const { return thisFrame.position; }

        void setBackgroundColour(uint16_t colour) { thisFrame.backgroundColour = colour; }
        uint16_t getBackgroundColour() { return thisFrame.backgroundColour; }

        void setStrokeSize(int8_t size) { thisFrame.strokeSize = size; }
        int8_t getStrokeSize() { return thisFrame.strokeSize; }

        void setStrokeColour(uint16_t colour) { thisFrame.strokeColour = colour; }
        uint16_t getStrokeColour() { return thisFrame.strokeColour; }

    protected:

        virtual void draw(Arduino_GFX& display) {}

        bool p_updated = true;

    private:

        struct FrameInfo {
            UDim2 position;
            UDim2 size;

            uint16_t backgroundColour = 0;
            int8_t strokeSize = 0;
            uint16_t strokeColour = 0xffff;

            bool operator==(const FrameInfo& other) {
                return position == other.position &&
                    size == other.size &&
                    backgroundColour == other.backgroundColour &&
                    strokeSize == other.strokeSize &&
                    strokeColour == other.strokeColour;
            }
        };

        FrameInfo thisFrame;
        FrameInfo lastFrame;
    };

    using LCDPage = std::vector<std::shared_ptr<LCDElement>>;

    template<typename T>
    class LCDPeripheral : public Peripheral {
    public:

        template<typename... Args>
        LCDPeripheral(Args... args) : LCDPeripheral(static_cast<Arduino_DataBus*>(nullptr), args...) {}
        template<typename... Args>
        // Busses can be found at https://github.com/moononournation/Arduino_GFX/wiki/Data-Bus-Class
        LCDPeripheral(Arduino_DataBus* bus, Args... args);

        int start() override;
        void update() override;

        void setCurrentPage(const std::shared_ptr<LCDPage>& page) { m_currentPage = page; }

        T* getDisplay() { return m_display; }

    private:

        std::shared_ptr<LCDPage> m_currentPage;

        Arduino_DataBus* m_bus;
        T m_display;

    };

    template<typename T>
    template<typename... Args>
    LCDPeripheral<T>::LCDPeripheral(Arduino_DataBus* bus, Args... args)
        : m_bus(bus ? bus : create_default_Arduino_DataBus()), m_display(T(m_bus, args...)) {
        static_assert(std::is_base_of<Arduino_TFT, T>::value,
            "T must be a subclass of Arduino_TFT (see https://github.com/moononournation/Arduino_GFX/wiki/Display-Class)");
    }

    template<typename T>
    int LCDPeripheral<T>::start() {
        if (!m_display.begin()) {
            Serial.println("Failed to begin lcd");
            return -1;
        }
        m_display.fillRect(0, 0, m_display.width(), m_display.height(), 0x0);
        return 0;
    }

    template<typename T>
    void LCDPeripheral<T>::update() {
        m_display.setTextSize(5);

        for (auto& element : *m_currentPage) {
            element->predraw(m_display);
        }
    }
}
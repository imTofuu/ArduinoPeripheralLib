#pragma once

#include <cstdint>
#include <Arduino_GFX_Library.h>
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

        // Any overriders should still call this base function
        virtual void predraw(Arduino_GFX& display);

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

    class LCDButtonElement : public LCDElement {
    public:

        virtual ~LCDButtonElement() override = default;

        void predraw(Arduino_GFX& display) override;

        void setAction(void (*action)()) { m_action = action; }
        void (*getAction())() { return m_action; }

    protected:

        virtual void triggered() = 0;

    private:

        void (*m_action)() = nullptr;

        struct FrameInfo {
            bool selected = false;
            uint16_t selectedBackgroundColour = 0;
            uint16_t selectedStrokeColour = 0;


            bool operator==(const FrameInfo& other) {
                return selected == other.selected &&
                    selectedBackgroundColour == other.selectedBackgroundColour &&
                    selectedStrokeColour == other.selectedStrokeColour;
            }
        };

        FrameInfo thisFrame;
        FrameInfo lastFrame;

    };

    using LCDPage = std::vector<std::shared_ptr<LCDElement>>;

}
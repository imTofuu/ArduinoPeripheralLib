#pragma once

#include <Peripheral.h>

#include "LCDElements/LCDElement.h"

namespace APL {

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
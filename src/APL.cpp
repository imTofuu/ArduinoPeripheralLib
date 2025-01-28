#include <APL.h>

#include <Peripheral.h>

namespace APL {

    std::vector<Peripheral*> peripherals;

    void start() {
        for (Peripheral*& peripheral : peripherals) {
            peripheral->start();
        }
    }

    void update() {
        for (Peripheral*& peripheral : peripherals) {
            peripheral->update();
        }
    }

}
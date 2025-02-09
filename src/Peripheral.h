#pragma once

#include <Arduino.h>

namespace APL {

    class Peripheral {
    public:

        virtual ~Peripheral() {}

        // Called on APL::start
        virtual int start() { return 0; }
        // Called on APL::update
        virtual void update() {}
    };

}
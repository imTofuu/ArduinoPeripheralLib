#pragma once

#include <Arduino.h>

namespace APL {

    class Peripheral {
    public:

        virtual ~Peripheral() {}

        // Called on APL::start
        virtual void start() {}
        // Called on APL::update
        virtual void update() {}
    };

}
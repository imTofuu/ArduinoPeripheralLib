#pragma once

#include <vector>

namespace APL {

	class Peripheral;
	extern std::vector<Peripheral*> peripherals;

	// Can be called after peripherals have been added
	void start();
	void update();

	template <typename T, typename... InitArgs>
	T* addPeripheral(InitArgs... params);

}

// Template definitions

template <typename T, typename... InitArgs>
T* APL::addPeripheral(InitArgs... params) {
	static_assert(std::is_base_of<Peripheral, T>::value, "T must be a subclass of Peripheral (see include/Peripherals)");
	T* peripheral = new T(params...);
	peripherals.push_back(peripheral);
	return peripheral;
}
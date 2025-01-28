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
	T* existingPeripheral = getPeripheral<T>();
	if (existingPeripheral)
		return existingPeripheral;
	T* peripheral = new T(params...);
	peripherals.push_back(peripheral);
	return peripheral;
}
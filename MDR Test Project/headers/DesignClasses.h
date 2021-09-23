#pragma once

#include <string>

namespace MDR {
	class MetricID {
	public:
		// Default constructor
		MetricID(std::string name, size_t num);

		void set(std::string name, size_t num);
	};
}


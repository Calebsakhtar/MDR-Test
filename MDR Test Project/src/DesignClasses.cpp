#include <iostream>
#include <vector>
#include <string>

namespace MDR {

	// Note: I am using classes and not structs for readibility

	class MetricID {
		std::string m_name;
		size_t m_num = 0;

	public:
		// Default constructor
		MetricID() {};

		MetricID(const std::string name, const size_t num) {
			m_name = name;
			size_t m_num = num;
		}

		void set(const std::string name, const size_t num) {
			m_name = name;
			size_t m_num = num;
		}

		std::string get_name() {
			return m_name;
		}

		size_t get_num() {
			return m_num;
		}
	};

	class PerfMetric {
		MetricID m_id;
		double m_val = 0;

	public:
		// Default constructor
		PerfMetric() {}

		PerfMetric(MetricID id, const double val) {
			m_id.set(id.get_name(), id.get_num());
			m_val = val;
		}

		void set(MetricID id, const double val) {
			m_id.set(id.get_name(), id.get_num());
			m_val = val;
		}

		void set_id(MetricID id) {
			m_id.set(id.get_name(), id.get_num());
		}

		void set_val(const double val) {
			m_val = val;
		}

		std::string get_metric_name() {
			return m_id.get_name();
		}

		size_t get_metric_id_num() {
			return m_id.get_num();
		}


	};
}

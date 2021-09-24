#include <iostream>
#include <vector>
#include <string>

namespace MDR {

	// Note: I am using classes and not structs for readibility

	class MetricID {
		std::string m_name;
		size_t m_num = 0;

	public:
		// Default constructor (constructs an empty object)
		MetricID() {};

		// Intended constructor
		MetricID(const std::string& name, const size_t& num) {
			m_name = name;
			size_t m_num = num;
		}

		void set(const std::string& name, const size_t& num) {
			m_name = name;
			size_t m_num = num;
		}

		std::string get_name() const {
			return m_name;
		}

		size_t get_num() const {
			return m_num;
		}
	};

	class PerfMetric {
		MetricID m_metric_id;
		double m_val = 0;
		bool m_minimize = true;

	public:
		// Default constructor (constructs an empty object)
		PerfMetric() {}

		// Intended constructor
		PerfMetric(const MetricID& id, const double& val, const bool& minimize) {
			m_metric_id.set(id.get_name(), id.get_num());
			m_val = val;
			m_minimize = minimize;
		}

		void set(const MetricID& id, const double& val, const bool& minimize) {
			m_metric_id.set(id.get_name(), id.get_num());
			m_val = val;
			m_minimize = minimize;
		}

		void set_id(const MetricID& id) {
			m_metric_id.set(id.get_name(), id.get_num());
		}

		void set_val(const double& val) {
			m_val = val;
		}

		void set_minimize(const double& minimize) {
			/* Set the minimize bool. If true, the dominance relation will choose the
			design with the minimum value of the performance metric. */
			m_minimize = minimize;
		}

		std::string get_metric_name() const {
			return m_metric_id.get_name();
		}

		size_t get_metric_id() const {
			return m_metric_id.get_num();
		}

		bool get_metric_minimize() const {
			/* Set the minimize bool. If true, the dominance relation is choosing the
			design with the minimum value of the performance metric. */
			return m_minimize;
		}
	};

	class Design {
		std::vector<PerfMetric> m_perf_vector;
		size_t m_design_id = 0;

	public:
		// Default constructor (constructs an empty object)
		Design() {}

		// Constructor to be used for copying
		Design(const std::vector<PerfMetric>& perf_vect, const size_t& design_id) {
			m_perf_vector = perf_vect;
			m_design_id = design_id;
		}

		// Constructor for normal use
		Design(const size_t& design_id) {
			m_design_id = design_id;
		}


		void add_perf_metric(const PerfMetric& perf_metric) {
			// Add a performance metric to the existing metric vector
			m_perf_vector.push_back(perf_metric);
		}

		void set_perf_vector(const std::vector<PerfMetric>& perf_vector) {
			// Replace the existing metric vector with a specified performance metric vector
			m_perf_vector = perf_vector;
		}

		size_t get_design_id() const {
			return m_design_id;
		}

		std::vector<PerfMetric> get_perf_vector() const {
			return m_perf_vector;
		}

	};
}

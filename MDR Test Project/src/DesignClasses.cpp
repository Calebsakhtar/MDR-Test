#include <iostream>
#include <vector>
#include <string>
#include "../headers/DesignClasses.h"

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

		double get_metric_val() const {
			// Return the value of this particular performance metric.
			return m_val;
		}
	};

	class Design {
		std::vector<PerfMetric> m_perf_vector;
		size_t m_design_id = 0;
		size_t m_active_perf_id_1 = 0; // Using std::sort for dominance requires two 
												// inputs. Hence, need to store which metrics
												// we are using within the Design object itself.
		size_t m_active_perf_id_2 = 0;

	public:
		// Default constructor (constructs an empty object)
		Design() {}

		// Constructor to be used for copying
		Design(const std::vector<PerfMetric>& perf_vect, const size_t& design_id,
			const size_t& active_perf_id_1, const size_t& active_perf_id_2) {
			m_perf_vector = perf_vect;
			m_design_id = design_id;
			m_active_perf_id_1 = active_perf_id_1;
			m_active_perf_id_2 = active_perf_id_2;
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

		void set_active_perf_metrics(const size_t& active_perf_id_1, const size_t&
			active_perf_id_2) {
			// Set the metrics which MDR will use to determine dominance relations
			m_active_perf_id_1 = active_perf_id_1;
			m_active_perf_id_2 = active_perf_id_2;
		}

		size_t get_design_id() const {
			return m_design_id;
		}

		std::vector<PerfMetric> get_perf_vector() const {
			return m_perf_vector;
		}

		std::vector<size_t> get_active_perf_metric_ids() const {
			std::vector<size_t> active_perf_metric_ids;
			active_perf_metric_ids.push_back(m_active_perf_id_1);
			active_perf_metric_ids.push_back(m_active_perf_id_2);
			return active_perf_metric_ids;
		}

		bool get_perf_val(const size_t& metric_id, double& perf_val) const {
			// Given a metric id number, give the value of that performance metric. Please note that
			// the output (perf_val) is an argument of this function. This function will return true
			// if the operation is successful.

			for (size_t i = 0; i < m_perf_vector.size(); i++) {
				if (m_perf_vector[i].get_metric_id() == metric_id) {
					perf_val = m_perf_vector[i].get_metric_val();
					return true;
				}
			}
			return false;
		}

		bool get_perf_minimize(const size_t& metric_id, bool& minimize) const {
			// Given a metric id number, say whether the metric is to be minimized. Please note that
			// the output (minimize) is an argument of this function. This function will return true
			// if the operation is successful.

			for (size_t i = 0; i < m_perf_vector.size(); i++) {
				if (m_perf_vector[i].get_metric_id() == metric_id) {
					minimize = m_perf_vector[i].get_metric_minimize();
					return true;
				}
			}
			return false;
		}

		bool get_active_perf_minimize(bool& minimize1, bool& minimize2) const {
			// Say whether the active metrics are to be minimized. Please note that the outputs
			// (minimize1, minimize2) are the arguments of this function. This function will return 
			// true if the operation is successful.
			if (get_perf_minimize(m_active_perf_id_1, minimize1) &&
				get_perf_minimize(m_active_perf_id_2, minimize2)) {
				return true;
			}
			return false;
		}
	};
}

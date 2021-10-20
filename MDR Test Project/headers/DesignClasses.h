#ifndef MDR_DESIGN_CLASSES_H
#define MDR_DESIGN_CLASSES_H

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
		MetricID(const std::string& name, const size_t& num);

		void set(const std::string& name, const size_t& num);

		std::string get_name() const;

		size_t get_num() const;
	};

	class PerfMetric {
		MetricID m_metric_id;
		double m_val = 0;
		bool m_minimize = true;

	public:
		// Default constructor (constructs an empty object)
		PerfMetric() {}

		// Intended constructor
		PerfMetric(const MetricID& id, const double& val, const bool& minimize);

		void set(const MetricID& id, const double& val, const bool& minimize);

		void set_id(const MetricID& id);

		void set_val(const double& val);

		// Set the minimize bool. If true, the dominance relation will choose the
		// design with the minimum value of the performance metric.
		void set_minimize(const double& minimize);

		std::string get_metric_name() const;

		size_t get_metric_id() const;

		// Get the minimize bool. If true, the dominance relation is choosing the
		// design with the minimum value of the performance metric.
		bool get_metric_minimize() const;

		// Return the value of this particular performance metric.
		double get_metric_val() const;
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
			const size_t& active_perf_id_1, const size_t& active_perf_id_2);

		// Constructor for normal use
		Design(const size_t& design_id);

		// Add a performance metric to the existing metric vector
		void add_perf_metric(const PerfMetric& perf_metric);

		// Replace the existing metric vector with a specified performance metric vector
		void set_perf_vector(const std::vector<PerfMetric>& perf_vector);

		// Set the metrics which MDR will use to determine dominance relations
		void set_active_perf_metrics(const size_t& active_perf_id_1, const size_t&
			active_perf_id_2);

		size_t get_design_id() const;

		std::vector<PerfMetric> get_perf_vector() const;

		std::vector<size_t> get_active_perf_metric_ids() const;

		// Given a metric id number, give the value of that performance metric. Please note that
		// the output (perf_val) is an argument of this function. This function will return true
		// if the operation is successful.
		bool get_perf_val(const size_t& metric_id, double& perf_val) const;

		// Given a metric id number, say whether the metric is to be minimized. Please note that
		// the output (minimize) is an argument of this function. This function will return true
		// if the operation is successful.
		bool get_perf_minimize(const size_t& metric_id, bool& minimize) const;

		// Say whether the active metrics are to be minimized. Please note that the outputs
		// (minimize1, minimize2) are the arguments of this function. This function will return 
		// true if the operation is successful.
		bool get_active_perf_minimize(bool& minimize1, bool& minimize2) const;
	};
}

#endif

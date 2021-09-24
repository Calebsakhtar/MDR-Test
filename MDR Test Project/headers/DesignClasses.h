#pragma once

#include <string>
#include <vector>

namespace MDR {

	// Note: I am using classes and not structs for readibility

	class MetricID {

	public:
		// Default constructor (constructs an empty object)
		MetricID();

		// Intended constructor
		MetricID(const std::string& name, const size_t& num);

		void set(const std::string& name, const size_t& num);

		std::string get_name() const;

		size_t get_num() const;
	};

	class PerfMetric {

	public:
		// Default constructor (constructs an empty object)
		PerfMetric();

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

	public:
		// Default constructor (constructs an empty object)
		Design() {}

		// Constructor to be used for copying
		Design(const std::vector<PerfMetric>& perf_vect, const size_t& design_id);

		// Constructor for normal use
		Design(const size_t& design_id);

		// Add a performance metric to the existing metric vector
		void add_perf_metric(const PerfMetric& perf_metric);

		// Replace the existing metric vector with a specified performance metric vector
		void set_perf_vector(const std::vector<PerfMetric>& perf_vector);

		size_t get_design_id() const;

		std::vector<PerfMetric> get_perf_vector() const;

		// Given a metric id number, give the value of that performance metric. Please note that
		// the output (perf_val) is an argument of this function. This function will return true
		// if the operation is successful.
		bool get_perf_val(const size_t& metric_id, double& perf_val) const;

	};
}


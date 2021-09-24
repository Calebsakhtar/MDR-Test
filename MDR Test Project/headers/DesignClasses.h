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

		void set_minimize(const double& minimize);

		std::string get_metric_name() const;

		size_t get_metric_id() const;

		bool get_metric_minimize() const;
	};

	class Design {

	public:
		// Default constructor (constructs an empty object)
		Design() {}

		// Constructor to be used for copying
		Design(const std::vector<PerfMetric>& perf_vect, const size_t& design_id);

		// Constructor for normal use
		Design(const size_t& design_id);

		void add_perf_metric(const PerfMetric& perf_metric);

		void set_perf_vector(const std::vector<PerfMetric>& perf_vector);

		size_t get_design_id() const;

		std::vector<PerfMetric> get_perf_vector() const;

	};
}


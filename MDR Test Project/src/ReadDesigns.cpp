#include <fstream>
#include <string>
#include <vector>

#include "../headers/DesignClasses.h"
#include "../headers/ReadDesigns.h"

void split_string(const std::string& ip_string, const std::string& delim,
	std::vector<std::string>& op_strings) {
	/*Split a string delimited by separators "delim" into a list of the split
	string elements*/

	// Empty the output string
	op_strings.clear();

	// Perform the extraction
	size_t start = 0;
	size_t end = ip_string.find(delim);
	while (end != std::string::npos)
	{
		op_strings.push_back(ip_string.substr(start, end - start));
		start = end + delim.length();
		end = ip_string.find(delim, start);
	}

	op_strings.push_back(ip_string.substr(start, end));
}

void read_design_file(std::vector<MDR::Design>& design_list,
	std::vector<MDR::MetricID>& metricid_list) {

	// Open the file containing the designs
	std::ifstream design_file("designs.csv");

	// Initialise a string to store the lines in
	std::string line;

	// Make a vector to store the lines
	std::vector<std::string> lines;

	// Read all lines
	while (std::getline(design_file, line)) {
		lines.push_back(line);
	}

	// Close the design file and clear the relevant vectors
	design_file.close();
	design_list.clear();
	metricid_list.clear();

	// Make a list to store the metric names
	std::vector<std::string> metric_names;

	// Assign the design names to their vector
	split_string(lines[0], ",", metric_names);

	// Make and store the MetricID object for each metric
	for (size_t i = 0; i < metric_names.size(); i++) {
		MDR::MetricID metricid(metric_names[i], i);

		metricid_list.push_back(metricid);
	}

	// Make a list to store the minimize bools
	std::vector<std::string> minimize_list_str;

	// Assign the minimize bools to their vector
	split_string(lines[1], ",", minimize_list_str);

	std::vector<MDR::PerfMetric> perf_metrics;
	std::vector<std::string> perf_values_str;

	// For each design ...
	for (size_t i = 2; i < lines.size(); i++) {

		perf_metrics.clear();
		perf_values_str.clear();

		split_string(lines[i], ",", perf_values_str);

		// Populate the performance metric vector
		for (size_t j = 0; j < perf_values_str.size(); j++) {
			MDR::PerfMetric metric(metricid_list[j], std::stod(perf_values_str[j]),
				minimize_list_str[j] == "TRUE");
			perf_metrics.push_back(metric);
		}

		// Make the relevant design
		MDR::Design design(perf_metrics, i - 2, 0, 0);

		// Put the design on the output list
		design_list.push_back(design);
	}
}

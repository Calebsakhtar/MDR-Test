#ifndef MDR_READ_DESIGNS_H
#define MDR_READ_DESIGNS_H

#include <fstream>
#include <string>
#include <vector>

#include "../headers/DesignClasses.h"

// The code in this file is of my own design unless otherwise stated

/*Split a string delimited by separators "delim" into a list of the split
string elements.

Code adapted from: https://stackoverflow.com/a/14266139

*/
void split_string(const std::string& ip_string, const std::string& delim,
	std::vector<std::string>& op_strings);

// Reads a design file in this repo's proprietary format
// A section of this code has been adapted from
// https://stackoverflow.com/a/13035743
void read_design_file(std::vector<MDR::Design>& design_list,
	std::vector<MDR::MetricID>& metricid_list);

#endif

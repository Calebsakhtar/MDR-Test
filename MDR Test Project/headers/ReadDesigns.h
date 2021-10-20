#ifndef READ_DESIGNS_H
#define READ_DESIGNS_H

#include <fstream>
#include <string>
#include <vector>

#include "../headers/DesignClasses.h"

/*Split a string delimited by separators "delim" into a list of the split
string elements*/
void split_string(const std::string& ip_string, const std::string& delim,
	std::vector<std::string> op_strings);

void read_design_file(std::vector<MDR::Design> design_list,
	std::vector<MDR::MetricID> metricid_list);

#endif

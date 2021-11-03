// MDR Test Project.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include "../headers/DesignClasses.h"
#include "../headers/MDRFunctions.h"
#include "../headers/ReadDesigns.h"

int main()
{
	//std::string joined("lolxddd,123");
	//std::vector<std::string> list;

	//split_string(joined, ",", list);

	//std::cout << list[0] << "\n";
	//std::cout << list[1] << "\n";

	std::vector<MDR::MetricID> metric_ids;
	std::vector<MDR::Design> designs;

	read_design_file(designs, metric_ids);
	std::vector<MDR::Design> designs_two = designs;

	std::cout << "Number of candidate designs: " << designs.size() << std::endl;

	std::vector<size_t> first_order = { 0,2,1,3 };
	std::vector<size_t> second_order = { 3,2,0,1 };

	MDR::optimize_designs(designs, first_order);
	MDR::optimize_designs(designs_two, second_order);

	std::cout << "Number of designs in pareto front (#1): " << designs.size() << std::endl;

	for (size_t i = 0; i < designs.size() - 1; i++) {
		std::cout << designs[i].get_design_id() << ",";
	}
	std::cout << designs[designs.size() - 1].get_design_id() << std::endl;

	std::cout << "Number of designs in pareto front (#2): " << designs_two.size() << std::endl;

	for (size_t i = 0; i < designs_two.size() - 1; i++) {
		std::cout << designs_two[i].get_design_id() << ",";
	}
	std::cout << designs_two[designs_two.size() - 1].get_design_id() << std::endl;

	std::cout << "Hello World!\n";
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file

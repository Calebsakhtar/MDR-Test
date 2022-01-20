// MDR Test Project.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <string>
#include "../headers/DesignClasses.h"
#include "../headers/MDRFunctions.h"
#include "../headers/ReadDesigns.h"

int main()
{
	std::vector<MDR::MetricID> metric_ids;
	std::vector<MDR::Design> designs;
	std::vector<MDR::Design> designs2;

	read_design_file(designs, metric_ids);
	designs2 = designs;

	std::cout << "Number of candidate designs: " << designs.size() << std::endl;

	std::vector<size_t> first_order = { 0,2 };

	auto pareto_one = MDR::optimize_designs(designs, first_order);

	std::cout << "Number of designs in pareto front (#1): " << designs.size() << std::endl;

	// Create and open a text file
	std::ofstream MyFile("pareto1.csv");

	if (designs.size() > 0) {
		for (size_t i = 0; i < designs.size() - 1; i++) {
			std::cout << designs[i].get_design_id() << ",";
			MyFile << std::to_string(designs[i].get_design_id()) << ",";
		}
		std::cout << designs[designs.size() - 1].get_design_id() << std::endl;
		MyFile << std::to_string(designs[designs.size() - 1].get_design_id());
	}

	// Close the file
	MyFile.close();

	// Perform the 2nd pareto front
	std::vector<size_t> second_order = { 1,3 };

	pareto_one = MDR::optimize_designs(designs2, second_order);

	std::cout << "Number of designs in pareto front (#2): " << designs2.size() << std::endl;

	// Create and open a text file
	std::ofstream MyFile2("pareto2.csv");

	if (designs2.size() > 0) {
		for (size_t i = 0; i < designs2.size() - 1; i++) {
			std::cout << designs2[i].get_design_id() << ",";
			MyFile2 << std::to_string(designs2[i].get_design_id()) << ",";
		}
		std::cout << designs2[designs2.size() - 1].get_design_id() << std::endl;
		MyFile2 << std::to_string(designs2[designs2.size() - 1].get_design_id());
	}

	// Close the file
	MyFile2.close();

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

// SimpleTest.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include "../DiffProcessor/Processor.h"

using namespace DiffProcessor;

Processor* diffProcessor;
SortedLimitedList<double> * sortedList1 = new SortedLimitedList<double>(10);
SortedLimitedList<double> * sortedList2 = new SortedLimitedList<double>(10);
SortedLimitedList<double> * sortedList1_ = new SortedLimitedList<double>(10);
SortedLimitedList<double> * sortedList2_ = new SortedLimitedList<double>(10);
long test_index = 0;

void do_test(int operations)
{
	try
	{
		diffProcessor->do_process(*sortedList1, *sortedList2);
		if (*sortedList1 != *sortedList2 || *sortedList1 != *sortedList2_ || sortedList1->performed_operations() != operations)
		{
			std::cout << "Test case: " << (++test_index) << " Failed. Inputs: mustBeEqual: [";
			sortedList1_->to_stream(std::cout);
			std::cout << "] etalon: [";
			sortedList2_->to_stream(std::cout);
			std::cout << "]" << std::endl;

			std::cout << "Your output ";
			sortedList1->to_stream(std::cout);
			std::cout << std::endl;

			std::cout << "Performed operations: " << sortedList1->performed_operations() << ", expected " << operations << std::endl;
			std::cout << std::endl;
		}
		else
		{
			std::cout << "Test case: " << (++test_index) << " Succeed. Inputs: mustBeEqual: [";
			sortedList1_->to_stream(std::cout);
			std::cout << "] etalon: [";
			sortedList2_->to_stream(std::cout);
			std::cout << "]" << std::endl;
			std::cout << std::endl;
		}
	}
	catch (...)
	{
		std::cout << "Test case: " << (++test_index) << " Exception. Inputs: mustBeEqual: [";
		sortedList1_->to_stream(std::cout);
		std::cout << "] etalon: [";
		sortedList2_->to_stream(std::cout);
		std::cout << "]" << std::endl;

		std::cout << std::endl;
	}
}


void test(double array1[], size_t size1, double array2[], size_t size2, int operations)
{
	sortedList1->from_array(array1, size1);
	sortedList2->from_array(array2, size2);
	sortedList1_->from_array(array1, size1);
	sortedList2_->from_array(array2, size2);
	do_test(operations);
}

int _tmain(int argc, _TCHAR* argv[])
{
	diffProcessor = new Processor(10);

	double needToBeEqual_0[] = { 0, 1, 2, 3, 4, 6, 7 };
	double etalon_0[] = { 0, 1, 2, 3, 4, 5, 6, 7 };
	test(needToBeEqual_0, sizeof(needToBeEqual_0) / sizeof(double), etalon_0, sizeof(etalon_0) / sizeof(double), 1);

	double needToBeEqual_1[] = { 0, 1, 2, 3, 4, 6, 7 };
	double etalon_1[] = { 1, 2, 3, 3 };
	test(needToBeEqual_1, sizeof(needToBeEqual_1) / sizeof(double), etalon_1, sizeof(etalon_1) / sizeof(double), 5);

	double needToBeEqual_2[] = { 0 };
	double etalon_2[] = { 7 };
	test(needToBeEqual_2, sizeof(needToBeEqual_2) / sizeof(double), etalon_2, sizeof(etalon_2) / sizeof(double), 2);

	double needToBeEqual_3[] = { 0, 1, 1, 1, 1, 1, 1 };
	double etalon_3[] = { 9, 9, 9, 9, 9, 9, 9, 9, 9, 9 };
	test(needToBeEqual_3, sizeof(needToBeEqual_3) / sizeof(double), etalon_3, sizeof(etalon_3) / sizeof(double), 17);

	double needToBeEqual_4[] = { 0, 1, 1, 1, 1, 1, 1, 1, 1, 3 };
	double etalon_4[] = { 0, 2, 2, 2, 2, 2, 2, 2, 2, 3 };
	test(needToBeEqual_4, sizeof(needToBeEqual_4) / sizeof(double), etalon_4, sizeof(etalon_4) / sizeof(double), 16);

	double needToBeEqual_5[] = { 0, 1, 2, 3, 4, 6, 7 };
	test(needToBeEqual_5, sizeof(needToBeEqual_5) / sizeof(double), NULL, 0, 7);

	double needToBeEqual_6[] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 };
	double etalon_6[] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
	test(needToBeEqual_6, sizeof(needToBeEqual_6) / sizeof(double), etalon_6, sizeof(etalon_6) / sizeof(double), 2);

	double needToBeEqual_7[] = { 0, 0 };
	double etalon_7[] = { 0, 1, 1, 1, 1, 1, 1, 1, 1, 1 };
	test(needToBeEqual_7, sizeof(needToBeEqual_7) / sizeof(double), etalon_7, sizeof(etalon_7) / sizeof(double), 10);

	delete diffProcessor;

	return 0;
}

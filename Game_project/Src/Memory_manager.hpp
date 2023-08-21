#pragma once

#include "Base_Allocator.hpp"
#include "Linear_Allocator.hpp"
#include "LList_Allocator.hpp"

struct Point {
	double x{1}, y{2};
};

struct test_Obj {
	Point p{};
	Point* pp{};
	double a{};
	float b{};
	int c{};
	char d{};
	
	~test_Obj() {
		std::cout << "DESTROYED\n";
	}
};


//LinearAllocator<float> Float_allocator;
//LinearAllocator<double> Double_allocator;
//
void Initialize_all_alocators();
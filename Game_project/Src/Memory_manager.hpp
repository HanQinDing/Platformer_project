#pragma once

#include "Base_Allocator.hpp"
#include "Linear_Allocator.hpp"
#include "LList_Allocator.hpp"
#include <random>

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
	test_Obj() {	
		std::random_device rd;  // Seed the engine with a random device
		std::mt19937 gen(rd()); // Mersenne Twister engine

		// Define a distribution for generating integers between 1 and 100 (inclusive)
		std::uniform_int_distribution<int> dis(1, 100);
		c = dis(gen);
	}
};


//LinearAllocator<float> Float_allocator;
//LinearAllocator<double> Double_allocator;
//
void Initialize_all_alocators();
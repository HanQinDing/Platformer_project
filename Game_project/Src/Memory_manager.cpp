#include "Memory_manager.hpp"
#include <chrono>


ListAllocator Test_allocator;



void Initialize_all_alocators() {

	//std::cout << "Before Allcoation\n";
	//std::cout << "Size: " << Test_allocator.GetSize() << "\n";
	//std::cout << "Used: " << Test_allocator.GetUsed() << "\n";
	//std::cout << "\n";

	Test_allocator.Initialise(10000);
	/*test_Obj a{}, b{}, c{};
	initializer_list*/
	test_Obj* t2 = new test_Obj[100];
	test_Obj* t = Test_allocator.Allocate<test_Obj, 100>();

	/*test_Obj* t3 = new test_Obj[100];
	test_Obj* t4 = Test_allocator.Allocate<test_Obj, 100>();*/

	auto startTime = std::chrono::high_resolution_clock::now();

	test_Obj* test2 = new test_Obj[100];
	auto endTime = std::chrono::high_resolution_clock::now();

	//int* test4 = Test_allocator.Allocate<int>({ 10 });

	

	test_Obj* test = Test_allocator.Allocate<test_Obj,100>();
	auto endTime2 = std::chrono::high_resolution_clock::now();

	Test_allocator.Print_List();

//	test_Obj* test5 = Test_allocator.Allocate<test_Obj, 100>();



	auto first_duration = std::chrono::duration_cast<std::chrono::microseconds>(endTime - startTime);
	auto second_duration = std::chrono::duration_cast<std::chrono::microseconds>(endTime2 - endTime);

	std::cout << sizeof(test_Obj);
	std::cout << "ALLOCATOR TIME: " << second_duration.count() << "\n";
	std::cout << "NEW TIME: " << first_duration.count() << "\n\n\n";

	test_Obj* check = test2;
	for (int i{ 0 }; i < 10; ++i) {
		std::cout << check->c << "\n";
		++check;
	}

	std::cout << "\n\n\n" ;
	check = test;
	for (int i{ 0 }; i < 10; ++i) {
		std::cout << check->c << "\n";
		++check;
	}


	/*int* test =  Test_allocator.Allocate<int, 20>();

	std::cout << "Size: " << Test_allocator.GetSize() << "\n";
	std::cout << "Used: " << Test_allocator.GetUsed() << "\n";
	Test_allocator.GetFree();
	Test_allocator.Print_List();


	float* test2 =  Test_allocator.Allocate<float, 10>();

	std::cout << "Size: " << Test_allocator.GetSize() << "\n";
	std::cout << "Used: " << Test_allocator.GetUsed() << "\n";
	Test_allocator.GetFree();
	Test_allocator.Print_List();

	double* test3 = Test_allocator.Allocate<double, 5>();

	std::cout << "Size: " << Test_allocator.GetSize() << "\n";
	std::cout << "Used: " << Test_allocator.GetUsed() << "\n";
	Test_allocator.GetFree();
	Test_allocator.Print_List();

	char* test4 = Test_allocator.Allocate<char, 5>();

	std::cout << "Size: " << Test_allocator.GetSize() << "\n";
	std::cout << "Used: " << Test_allocator.GetUsed() << "\n";
	Test_allocator.GetFree();
	Test_allocator.Print_List();

	Point* test5 = Test_allocator.Allocate<Point, 5>();

	std::cout << "Size: " << Test_allocator.GetSize() << "\n";
	std::cout << "Used: " << Test_allocator.GetUsed() << "\n";
	Test_allocator.GetFree();
	Test_allocator.Print_List();

	std::cout << "REWIND\n";


	Test_allocator.Rewind(test2);
	std::cout << "Size: " << Test_allocator.GetSize() << "\n";
	std::cout << "Used: " << Test_allocator.GetUsed() << "\n";
	Test_allocator.GetFree();
	Test_allocator.Print_List();

	Test_allocator.Rewind(test5);
	std::cout << "Size: " << Test_allocator.GetSize() << "\n";
	std::cout << "Used: " << Test_allocator.GetUsed() << "\n";
	Test_allocator.GetFree();
	Test_allocator.Print_List();

	Test_allocator.Rewind(test3);
	std::cout << "Size: " << Test_allocator.GetSize() << "\n";
	std::cout << "Used: " << Test_allocator.GetUsed() << "\n";
	Test_allocator.GetFree();
	Test_allocator.Print_List();

	Test_allocator.Rewind(test4);
	std::cout << "Size: " << Test_allocator.GetSize() << "\n";
	std::cout << "Used: " << Test_allocator.GetUsed() << "\n";
	Test_allocator.GetFree();
	Test_allocator.Print_List();


	Test_allocator.Rewind(test);
	std::cout << "Size: " << Test_allocator.GetSize() << "\n";
	std::cout << "Used: " << Test_allocator.GetUsed() << "\n";
	Test_allocator.GetFree();
	Test_allocator.Print_List();*/

	/*auto startTime = std::chrono::high_resolution_clock::now();

	test_Obj* test2 = new test_Obj();
	auto endTime = std::chrono::high_resolution_clock::now();

	test_Obj* test = Test_allocator.Allocate<test_Obj>();
	auto endTime2 = std::chrono::high_resolution_clock::now();

	auto first_duration = std::chrono::duration_cast<std::chrono::microseconds>(endTime - startTime);
	auto second_duration = std::chrono::duration_cast<std::chrono::microseconds>(endTime2 - endTime);

	std::cout << "ALLOCATOR TIME: " << second_duration.count() << "\n";
	std::cout << "NEW TIME: " << first_duration.count() << "\n";*/

	////int* test = Test_allocator.Allocate<int>(1);
	//////int* test = Test_allocator.Allocate<int>(10);
	////
	////std::cout << "After Allcoation\n";
	////std::cout << "Size: " << Test_allocator.GetSize() << "\n";
	////std::cout << "Used: " << Test_allocator.GetUsed() << "\n";


	//test_Obj* pr = test;
	//if (test) {
	//	for (int i{ 0 }; i < 10; ++i) {
	//		std::cout << "TEST Value: " << pr->p.x << "," << pr->p.y << "\n";
	//		++pr;
	//	}
	//	
	//}
	//std::cout << "\n";
	//
	//test_Obj testo{};
	//testo.~test_Obj();

 //  Test_allocator.Rewind(test);

	//std::cout << "After Deallcoation\n";
	//std::cout << "Size: " << Test_allocator.GetSize() << "\n";
	//std::cout << "Used: " << Test_allocator.GetUsed() << "\n";
	//if (test) {
	//	std::cout << "TEST Value: " << *test << "\n";
	//}
	//std::cout << "\n";

	//Float_allocator.Initialise(20);
	//Double_allocator.Initialise(30);
}

//LinearAllocator Test_allocator;
//
//void Initialize_all_alocators() {
//
//	//std::cout << "Before Allcoation\n";
//	//std::cout << "Size: " << Test_allocator.GetSize() << "\n";
//	//std::cout << "Used: " << Test_allocator.GetUsed() << "\n";
//	//std::cout << "\n";
//
//	Test_allocator.Initialise(1000000);
//
//	auto startTime = std::chrono::high_resolution_clock::now();
//
//	test_Obj* test2 = new test_Obj();
//	auto endTime = std::chrono::high_resolution_clock::now();
//
//	test_Obj* test = Test_allocator.Allocate<test_Obj>();
//	auto endTime2 = std::chrono::high_resolution_clock::now();
//
//	auto first_duration = std::chrono::duration_cast<std::chrono::microseconds>(endTime - startTime);
//	auto second_duration = std::chrono::duration_cast<std::chrono::microseconds>(endTime2 - endTime);
//
//	std::cout << "ALLOCATOR TIME: " << second_duration.count() << "\n";
//	std::cout << "NEW TIME: " << first_duration.count() << "\n";
//
//	////int* test = Test_allocator.Allocate<int>(1);
//	//////int* test = Test_allocator.Allocate<int>(10);
//	////
//	////std::cout << "After Allcoation\n";
//	////std::cout << "Size: " << Test_allocator.GetSize() << "\n";
//	////std::cout << "Used: " << Test_allocator.GetUsed() << "\n";
//
//
//	//test_Obj* pr = test;
//	//if (test) {
//	//	for (int i{ 0 }; i < 10; ++i) {
//	//		std::cout << "TEST Value: " << pr->p.x << "," << pr->p.y << "\n";
//	//		++pr;
//	//	}
//	//	
//	//}
//	//std::cout << "\n";
//	//
//	//test_Obj testo{};
//	//testo.~test_Obj();
//
// //  Test_allocator.Rewind(test);
//
//	//std::cout << "After Deallcoation\n";
//	//std::cout << "Size: " << Test_allocator.GetSize() << "\n";
//	//std::cout << "Used: " << Test_allocator.GetUsed() << "\n";
//	//if (test) {
//	//	std::cout << "TEST Value: " << *test << "\n";
//	//}
//	//std::cout << "\n";
//
//	//Float_allocator.Initialise(20);
//	//Double_allocator.Initialise(30);
//}
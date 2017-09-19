//File Name: Test.cpp
//File Description: Test project function
//File Author: Yunding Li
//File Start Date: 09/16/2017 
//Final Revised Date: 09/17/2017
#include"carRental.h"
int main() {// I do not wrap the ifstream file and function together for you can read the code more clearly.

	RentalCompany great;
	std::cout << "--------------Test the Store Function--------------" << std::endl;
	std::ifstream file("store.csv");
	great.storeCars(file);
	great.showCars();
	file.close();
	std::cout<<std::endl;
	std::cout << "--------------Test the Rent Function--------------" << std::endl;
	file.open("rent.csv");
	great.rentCars(file);
	file.close();
	std::cout << std::endl;
	std::cout << "--------------Test the Return Function--------------" << std::endl;
	file.open("return.csv");
	great.storeCars(file);
	file.close();
	std::cout << std::endl;
	std::cout << "--------------Test the Rent Function After the Return complete--------------" << std::endl;
	file.open("rent.csv");
	great.rentCars(file);
	file.close();
	std::cout << std::endl;
	system("pause");// pause the console to watch the result
}
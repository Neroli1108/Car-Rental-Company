
//File Name: carRental.h
//File Description: carRental Header file
//File Author: Yunding Li
//File Start Date: 09/16/2017
//Final Revised Date: 09/17/2017

#pragma once
#include<iostream>
#include<string>
#include<vector>
#include<sstream>
#include<fstream>
#include<map>
//base class
class CarRental {
protected:
	std::string Plate;
	std::string Brand;
	std::string Model;
public:
	bool available = true;
	CarRental(std::string a, std::string b, std::string c) :Plate(a), Brand(b), Model(c) {};
	std::string carBrand();
	std::string carPlate();
	std::string carModel();
	virtual int getMaxSeats() = 0;
	virtual void carInformation() = 0;
	virtual bool extraRow() {
		return false;
	};
	virtual bool hasSportsPackage() {
		return false;
	};
};

class SUV :public CarRental // suv class
{
	int seats;
	int extraSeats;									// have a extra row it will be 3, otherwise is 0.
public:
	SUV(int seat, int extra_seat, std::string plate, std::string brand, std::string model = "suv") : CarRental(plate, brand, model), seats(seat), extraSeats(extra_seat) {};
	virtual bool extraRow() override;
	int getMaxSeats() override;
	void carInformation() override;
};

class Sedan :public CarRental // sedan class
{
	int seats;
	bool SportsPackage;
public:
	Sedan(int seat, bool sports, std::string plate, std::string brand, std::string model = "sedan") :CarRental(plate, brand, model), seats(seat), SportsPackage(sports) {};
	bool hasSportsPackage() override;
	int getMaxSeats() override;
	void carInformation() override;

};

class customerInfo //customer information class
{
public:
	std::string firstName;
	std::string lastName;
	std::string SSN; // or something unique;
	customerInfo(std::string a, std::string b, std::string c) :firstName(a), lastName(b), SSN(c) {};

};


class RentalCompany { // car rental company class
	std::vector<CarRental*> suvInventory;
	std::vector<CarRental*> sedanInventory;
	std::map<std::string, CarRental*> rentRecord;
	std::vector<customerInfo*> customerTable;

public:
	void storeCars(std::istream&str);
	void showCars();
	void rentCars(std::istream&str);
};
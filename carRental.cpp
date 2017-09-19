//File Name: carRental.cpp
//File Description: Implementation the carRental.h file
//File Author: Yunding Li
//File Start Date: 09/16/2017
//Final Revised Date: 09/17/2017

#include"carRental.h"
#include <locale>

//Implement the base class
std::string CarRental::carBrand() {
	return Brand;
}
std::string CarRental::carPlate() {
	return Plate;
}
std::string CarRental::carModel() {
	return Model;
}
//Implement the SUV class
bool SUV::extraRow() {							// check for SUV extra row
	return extraSeats;
}
int SUV::getMaxSeats() {
	return seats + extraSeats;					//get the max seats
}
void SUV::carInformation() {	// print all the suv information
	std::cout << " This is " << Brand << " " << Model << ". It has " << seats << " seats, and " << extraSeats << " extral seats." << " It`s Plate is " << Plate << std::endl;
	if (available)
		std::cout << " This car is Available. " << std::endl;
	else
		std::cout << " This car is Not Available. " << std::endl;
}

//implement the sedan class

bool Sedan:: hasSportsPackage() {//check whether have the sports package
	return SportsPackage;
}
int Sedan::getMaxSeats() {
	return seats;
}
void Sedan::carInformation() {
	std::cout << " This is " << Brand << " " << Model << ". It has " << seats << " seats. " << "It`s Plate is " << Plate << ". ";
	if (SportsPackage)
		std::cout << "It has the SportsPackage. " << std::endl;
	else
		std::cout << "It does not have the SportsPackage. " << std::endl;
	if (available)
		std::cout << " This car is Available. " << std::endl;
	else
		std::cout << " This car is Not Available. " << std::endl;
}
// implement the car rental company class
void RentalCompany::showCars() { // print all the information of all cars in the Inventary 
	for (int i = 0; i < suvInventory.size(); i++) {
		std::cout << " The " << i+1 << " SUV:" << std::endl;
		suvInventory[i]->carInformation();
	}
	for (int i = 0; i < sedanInventory.size(); i++) {
		std::cout << " The " << i+1 << " Sedan:" << std::endl;
		sedanInventory[i]->carInformation();
	}
}

void RentalCompany::storeCars(std::istream& str) { //store the new car or store the return cars 
	std::vector<std::string> collectData;
	std::string one;
	std::getline(str, one);
	if (one.find("Store") == 0) { // the csv file is storing the new cars not customers returning cars.
		std::getline(str, one); // if format has the title row use this to skip it
		int  errorCount = 0; // record the number of errors
		while (!str.eof()) {
			std::string line;
			std::getline(str, line);
			if (line == "")
				break;
			std::stringstream lineStream(line);
			std::string cell;
			while (std::getline(lineStream, cell, ',')) {// store all the data 
				collectData.push_back(cell);
			}
			if (collectData[0] == "suv") { //0 model 1 plate 2 brand 3 seats 4 extral_seats.
				CarRental* tmp = new SUV(stoi(collectData[3]), stoi(collectData[4]), collectData[ 1], collectData[2], collectData[0]);
				suvInventory.push_back(tmp);
			}
			else if (collectData[0] == "sedan") {//0 model 1 plate 2 brand 3 seats 4 sports.
				bool hasSportsPackage;
				if (collectData[4] == "1")
					 hasSportsPackage = true;
				else
					 hasSportsPackage = false;
				CarRental* tmp = new Sedan(stoi(collectData[3]),hasSportsPackage, collectData[1], collectData[2], collectData[0]);
				sedanInventory.push_back(tmp);
			}
			else { // store error means that the storing car is neither the suv nor the sedan, so we can not store it in the inventary, we record the number of the errors.
				errorCount++;
			}
			collectData.clear();
		}
		// summary the data
		std::cout << " The number of cars in the record is " << collectData.size() / 5 << std::endl;
		std::cout << " Store the number of Suv: " << suvInventory.size() << std::endl;
		std::cout << " Store the number of Seden: " << sedanInventory.size() << std::endl;
		std::cout << " There are " << errorCount << " storing error(s). " << std::endl;
	}
	else if (one.find("Return") == 0) // customer return the car to the company
		//return table format is 0 firstname 1 lastname 2 ssn 3 model 4 plate 5 brand 6 seats 7 extra seats(sportspackage)
	{
		std::getline(str, one); // if format has the title row use this to skip it
		while (!str.eof()) {
			std::string line;
			std::getline(str, line);
			if (line == "")
				break;
			std::stringstream lineStream(line);
			std::string cell;
			while (std::getline(lineStream, cell, ',')) {
				collectData.push_back(cell);
			}

			customerInfo* tmp = new customerInfo(collectData[0], collectData[1], collectData[2]);
			auto it = rentRecord.find(tmp->SSN); //check the record 
			if (it != rentRecord.end()) { // got the record
				bool checkIden = false; // check whether the name match
				for (int i = 0; i < customerTable.size(); i++) {
					if (customerTable[i]->SSN == tmp->SSN) {
						if (tmp->firstName == customerTable[i]->firstName&&tmp->lastName == customerTable[i]->lastName) { // good match
							checkIden = true;
						}
						else
						{
							checkIden = false; // unmatch
						}
						break;
					}
				}
				if (checkIden) { // if match check whether the car information match
					if (collectData[3] == "suv") {
						if (it->second->carPlate() == collectData[4]) {
							if (it->second->carBrand() == collectData[5]) {
								if (it->second->carModel() == collectData[3]) {
									if (it->second->getMaxSeats() == (stoi(collectData[6]) + stoi(collectData[7]))) {
										it->second->available = true;
										rentRecord.erase(it);
										std::cout << " Dear " << tmp->firstName << " " << tmp->lastName << ":	" << "your return action is complete, thank you. " << std::endl;
									}
									else
									{
										std::cout << " Dear " << tmp->firstName << " " << tmp->lastName << ":	" << "We are sorry, your return car equiment is not correct. " << std::endl;
									}
								}
								else
								{
									std::cout << " Dear " << tmp->firstName << " " << tmp->lastName << ":	" << "We are sorry, your return car model is not correct. " << std::endl;
								}
							}
							else
							{
								std::cout << " Dear " << tmp->firstName << " " << tmp->lastName << ":	" << "We are sorry, your return car brand is not correct. " << std::endl;
							}
						}
						else
						{
							std::cout << " Dear " << tmp->firstName << " " << tmp->lastName << ":	" << "We are sorry, your return car plate is not correct. " << std::endl;
						}
					}
					else if (collectData[3] == "sedan") {
						if (collectData[3] == it->second->carModel()) {
							if (collectData[4]==it->second->carPlate()) {
								if (collectData[5] == it->second->carBrand()) {
									if (stoi(collectData[7]) == it->second->hasSportsPackage()) {
										it->second->available = true;
										rentRecord.erase(it);
										std::cout << " Dear " << tmp->firstName << " " << tmp->lastName << ":	" << "your return action is complete, thank you. " << std::endl;
									}
									else
									{
										std::cout << " Dear " << tmp->firstName << " " << tmp->lastName << ":	" << "We are sorry, your return car equiment is not correct. " << std::endl;
									}
								}
								else
								{
									std::cout << " Dear " << tmp->firstName << " " << tmp->lastName << ":	" << "We are sorry, your return car brand is not correct. " << std::endl;
								}
							}
							else
							{
								std::cout << " Dear " << tmp->firstName << " " << tmp->lastName << ":	" << "We are sorry, your return car plate is not correct. " << std::endl;
							}
						}
						else
						{
							std::cout << " Dear " << tmp->firstName << " " << tmp->lastName << ":	" << "We are sorry, your return car model is not correct. " << std::endl;
						}
					}
					else {
						std::cout << " Dear " << tmp->firstName << " " << tmp->lastName << ": " << "We are sorry, your return car type is not correct. " << std::endl;
					}

				}
				else {
					std::cout << " Dear Customer " << tmp->SSN << ": Your member number is not match your name, we can not allow your action now. " << std::endl;
				}
			}
			else
			{
				std::cout << " Dear Customer " << tmp->SSN << ": we do not have your rent record. " << std::endl;
			}
			collectData.clear(); // at this function  i decide to process data one by one not collect them all and process it. this will a little fast.
		}
	}
	else // the file type is neither return nor store
	{
		std::cout << " The type of the input file to store is not correct. " << std::endl;
	}
}


void RentalCompany::rentCars(std::istream&str) {
	std::vector<std::string> collectData;
	std::string one;
	std::getline(str, one);
	if (one.find("Rent") == 0) {
		std::getline(str, one); // if format has the title row use this to skip it
		while (!str.eof()) { // collect all data in the input file.
			std::string line; // format of the csv file is 0 firstname 1 lastname 2 ssn 3 model 4 brand 5 seats 6 extra seats(sportspackage)
			std::getline(str, line);
			if (line == "")
				break;
			std::stringstream lineStream(line);
			std::string cell;
			while (std::getline(lineStream, cell, ',')) {
				collectData.push_back(cell);
			}
			customerInfo* newCust = new customerInfo(collectData[0], collectData[1], collectData[2]);
			if (collectData[3] == "suv") {
				int countNotAvailable = 0, find = 0;
				for (int i = 0; i < suvInventory.size(); i++) {
					if (stoi(collectData[5]) + stoi(collectData[6]) == suvInventory[i]->getMaxSeats() && collectData[4] == suvInventory[i]->carBrand()) {
						if (suvInventory[i]->available) {
							rentRecord[newCust->SSN] = suvInventory[i];
							customerTable.push_back(newCust);
							suvInventory[i]->available = false;
							std::cout <<" "<<rentRecord[newCust->SSN]->carBrand() << " Suv has been checked out by " << newCust->firstName << "," << newCust->lastName << " and the car plate is " << rentRecord[newCust->SSN]->carPlate() << std::endl;
							find++;
							break;
						}
						else {
							countNotAvailable++;
						}
					}
				}
				if (!find) {
					std::cout << " Dear " << newCust->firstName << " " << newCust->lastName << ": ";
					if (countNotAvailable) {
						std::cout << " We are sorry, the car is ran out. " << std::endl;
					}
					else
					{
						std::cout << " we are sorry that we do not have the car meet your request. " << std::endl;
					}
				}
			}
			else if(collectData[3] == "sedan")
			{
				CarRental* request = new Sedan(stoi(collectData[5]), stoi(collectData[6]), "N/A", collectData[4], collectData[3]);
			
				int countNotAvailable = 0, find = 0;
				for (int i = 0; i < sedanInventory.size(); i++) {
					if (collectData[4] == sedanInventory[i]->carBrand()&& sedanInventory[i]->hasSportsPackage() == stoi(collectData[6]) ) {
						if (sedanInventory[i]->available) {
							rentRecord[newCust->SSN] = sedanInventory[i];
							customerTable.push_back(newCust);
							sedanInventory[i]->available = false;
							std::cout <<" "<< rentRecord[newCust->SSN]->carBrand() << " Sedan has been checked out by " << newCust->firstName << "," << newCust->lastName << " and the car plate is " << rentRecord[newCust->SSN]->carPlate();
							if(rentRecord[newCust->SSN]->hasSportsPackage())
								std::cout<<" and it has the sportsPackage. "<< std::endl;
							else
								std::cout << " and it does not have the sportsPackage. " << std::endl;
							find++;
							break;
						}
						else {
							countNotAvailable++;
						}
					}
				}
				if (find==0) {
					std::cout << " Dear " << newCust->firstName << " " << newCust->lastName << ": ";
					if (countNotAvailable) {
						std::cout << " We are sorry, the car is ran out. " << std::endl;
					}
					else
					{
						std::cout << " we are sorry that we do not have the car meet your request. " << std::endl;
					}
				}
			}
			else
			{
				std::cout << " Dear " << newCust->firstName << " " << newCust->lastName << ": ";
				std::cout << " we are sorry that we do not have other car types except the sedan and suv . " << std::endl;
			}

			collectData.clear();
			
		}
		
	}
	else {
		std::cout << " The type of the input file to rent is not correct. " << std::endl;
	}
}


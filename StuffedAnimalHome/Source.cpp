#include <string>
#include <iostream>
#include <fstream>

class StuffedAnimal {
	std::string name;
	std::string animalType;
	public:
		std::string getName() {
			return name;
		}

		std::string getAnimalType() {
			return animalType;
		}

		std::string setName(std::string n) {
			name = n;
		}

		std::string setAnimalType(std::string t) {
			animalType = t;
		}

		void addAnimal() {
			std::cout << "\nEnter Name: ";
			std::cin >> name;
			std::cout << "\nEnter Type: ";
			std::cin >> animalType;
		}
};

void writeAnimal();
void printAllAnimals();
void findAnimal(std::string name);
void deleteAnimal(std::string name);
bool checkAnimal(std::string name);
void intro();

int main() {
	char choice;
	std::string name;
	intro();
	do {
		std::cout << "\n\n\t *-*-*-*-*-* MENU *-*-*-*-*-* \t\n\n";
		std::cout << "\n\n\t1. Add A Patient";
		std::cout << "\n\n\t2. Find A Patient";
		std::cout << "\n\n\t3. Delete A Patient";
		std::cout << "\n\n\t4. Print All Patient Information";
		std::cout << "\n\n\t5. Exit Program";
		std::cout << "\n\n\tSelect A Choice: ";
		std::cin >> choice;
		system("cls");
		switch (choice) {
		case '1':
			writeAnimal();
			break;
		case '2':
			std::cout << "Please Enter Patient Name: ";
			std::cin >> name;
			findAnimal(name);
			break;
		case '3':
			std::cout << "Please Enter Patient Name: ";
			std::cin >> name;
			deleteAnimal(name);
			break;
		case '4':
			printAllAnimals();
			break;
		case '5':
			std::cout << "Exiting Program...\n";
			break;
		}
		std::cin.get();
		std::cin.ignore();
	} while (choice != '5');

	return 0;
}

void intro() {
	std::cout << "\n\n\t-------------------------------------\t\n\n";
	std::cout << "\n\n\tSTEPHANIE'S ANIMAL NURSING HOME\t\n\n";
	std::cout << "\n\n\tWelcome! My name is Stephanie.\t\n\n";
	std::cout << "\n\n\tI take care of aged stuffed animals. \t\n\n";
	std::cout << "\n\n\t-------------------------------------\t\n\n";
}

void writeAnimal() {
	std::fstream file;
	StuffedAnimal a;
	a.addAnimal();
	file.open("StuffedAnimals.txt", std::ios_base::app);
	if (!file) {
		std::cerr << "Unable to open patient records...";
		exit(1); 
	}
	if (checkAnimal(a.getName()) && checkAnimal(a.getAnimalType())) {
		std::cout << "\nPatient exists in our system..." << std::endl;
	}
	else {
		file << "Name: " << a.getName() << std::endl;
		file << "Type: " << a.getAnimalType() << "\n\n";
		std::cout << "Patient has been added...\n";
	}
	file.close();
}

void printAllAnimals() {
	std::ifstream file;
	std::string fileLine;

	file.open("StuffedAnimals.txt");
	if (!file.is_open()) {
		std::cerr << "Unable to open patient records...";
		exit(1);
	}
	while(!file.eof()) {
		getline(file, fileLine);
		std::cout << fileLine << std::endl;
	}
	file.close();
	std::cout << "\nPress Enter to return to Menu..." << std::endl;
}

void findAnimal(std::string name) {
	std::ifstream file;
	std::string fileLine;
	bool found = 0;

	file.open("StuffedAnimals.txt");
	if (!file.is_open()) {
		std::cerr << "Unable to open patient records...";
		exit(1);
	}
	while (!file.eof()) {
		getline(file, fileLine);
		if (fileLine.find(name) != std::string::npos) {
			std::cout << fileLine << std::endl;
			getline(file, fileLine);
			std::cout << fileLine << std::endl;
			found = 1;
		}
	}
	file.close();
	if (!found) {
		std::cout << "\nCould not find " << name << "..." << std::endl;

	}
	std::cout << "\nPress Enter to return to Menu..." << std::endl;
}

void deleteAnimal(std::string name) {
	std::ifstream file;
	std::ofstream temp;
	std::string nameLine;
	std::string typeLine;
	std::string fileLine;
	bool found = 0;

	if (!checkAnimal(name)) {
		std::cout << "\nCould not find " << name << "..." << std::endl;

	}
	else {
		file.open("StuffedAnimals.txt");
		temp.open("temp.txt");
		if (!file.is_open()) {
			std::cerr << "Unable to open patient records...";
			exit(1);
		}
		while (!file.eof()) {
			getline(file, fileLine);
			if (fileLine.find(name) != std::string::npos) {
				nameLine = fileLine;
				getline(file, typeLine);
				found = 1;
			}
			else {
				temp << fileLine << std::endl;
			}
		}
		temp.close();
		file.close();
		remove("StuffedAnimals.txt");
		rename("temp.txt", "StuffedAnimals.txt");
		if (!found) {
			std::cout << "\nCould not find " << name << "..." << std::endl;
		}
		else {
			std::cout << "Patient has been deleted...\n";
		}
	}
	std::cout << "\nPress Enter to return to Menu..." << std::endl;
}

bool checkAnimal(std::string name) {
	std::ifstream file;
	std::string fileLine;

	file.open("StuffedAnimals.txt");
	if (!file.is_open()) {
		std::cerr << "Unable to open patient records...";
		exit(1);
	}
	while (!file.eof()) {
		getline(file, fileLine);
		if (fileLine.find(name) != std::string::npos) {
			return true;
		}
	}
	file.close();
	return false;
}


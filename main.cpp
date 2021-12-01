#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>

const size_t numOfTabs = 12;

int main() {
	std::string str;
	std::cin >> str;
	size_t firstNum = 1;
	size_t lastNum = numOfTabs;
	std::string fileName = "Audero-MD5-Rainbow-Table-master/md5_rainbow_table_part_";
	std::ifstream file;
	std::string line;

	file.open(fileName + std::to_string(firstNum) + ".csv");
	if (!file.is_open()) {
		return -1;
	}
	getline(file, line);
	std::string firstHash = line.substr(1, 32);
	file.close();

	file.open(fileName + std::to_string(lastNum) + ".csv");
	std::string lastHash;
	while (std::getline(file, line, '\n')) {
		lastHash = line.substr(1, 32);
	}
	file.close();
	

	if (str >= firstHash && str <= lastHash) {
		int midNum;
		while (firstNum < lastNum) {
			midNum = (firstNum + lastNum) / 2;
			file.open(fileName + std::to_string(midNum) + ".csv");
			std::string lastMidHash;
			while (std::getline(file, line, '\n')) {
				lastMidHash = line.substr(1, 32);
			}
			file.close();

			if (str >= firstHash && str <= lastMidHash) {
				lastNum = midNum;
				file.open(fileName + std::to_string(lastNum) + ".csv");
				while (std::getline(file, line, '\n')) {
					lastHash = line.substr(1, 32);
				}
				file.close();
			}
			else {
				firstNum = midNum + 1;
				file.open(fileName + std::to_string(firstNum) + ".csv");
				getline(file, line);
				firstHash = line.substr(1, 32);
				file.close();
			}
		}

		file.open(fileName + std::to_string(firstNum) + ".csv");
		while (std::getline(file, line, '\n')) {
			if (str == line.substr(1, 32)) { 
				size_t original_end = line.find('"', 36);
				std::string original = line.substr(36, original_end - 35 - 1);
				std::cout << "Original: " << original << std::endl;
				break;
			}
		}
	}
	
}

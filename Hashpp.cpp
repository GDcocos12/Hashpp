#include <iostream>
#include <iomanip>
#include <string>
#include <bitset>
#include <vector>
#include <fstream>
#include <sstream>

std::string toBinary(std::string const& str) {
	std::string binary = "";
	for (char const& c : str) {
		binary += std::bitset<8>(c).to_string() + ' ';
	}
	return binary;
}

std::string encrypt(std::string string, int key) {
	std::string s = string;
	std::string ss = s;
	std::reverse(ss.begin(), ss.end());
	std::vector<int> decstr;

	for (int i = 0; i < ss.length(); i++) {
		decstr.push_back(int(ss[i]));
	}

	for (int p = 0; p < decstr.size(); p++) {
		decstr[p] += key;
	}

	std::string respdec = "";
	for (int i = 0; i < decstr.size(); i++) {
		respdec += char(decstr[i]);
	}

	std::string sj = toBinary(respdec);

	std::string output = "";
	int zero = 0;
	int ones = 0;
	for (int i = 0; i < sj.length(); i++) {
		if (sj[i] == '0') {
			if (zero == 2) {
				output += "#";
				zero = 0;
			}
			else {
				output += "!";
				zero += 1;
			}
		}
		else if (sj[i] == '1') {
			if (ones == 2) {
				output += "z";
				ones = 0;
			}
			else {
				output += "+";
				ones += 1;
			}
		}
	}

	return output;
}

std::string decrypt(std::string string, int key) {
	std::string s = "";
	for (int i = 0; i < string.length(); i++) {
		if (string[i] == '#' || string[i] == '!') {
			s += "0";
		}
		else if (string[i] == 'z' || string[i] == '+') {
			s += "1";
		}
	}

	std::string str_data = "";
	std::vector<int> decstr;

	std::stringstream sstream(s);
	while (sstream.good())
	{
		std::bitset<8> bits;
		sstream >> bits;
		char c = char(bits.to_ulong());
		str_data += c;
	}

	for (int i = 0; i < str_data.length()-1; i++) {
		decstr.push_back(str_data[i]);
	}

	for (int o = 0; o < decstr.size(); o++) {
		decstr[o] -= key;
	}

	std::string respdec = "";
	for (int i = 0; i < decstr.size(); i++) {
		respdec += decstr[i];
	}

	std::string finaloutput = "";
	for (int i = respdec.length(); i >= 0; i--) {
		finaloutput += respdec[i];
	}

	return finaloutput;
}

int main() {
	int mode;
	std::cout << "Mode(1 - encrypt, 2 - decrypt): ";
	std::cin >> mode;
	if (mode == 1) {
		std::string stri;
		std::cout << "String to encode: ";
		std::cin.ignore();
		std::getline(std::cin, stri);
		int key;
		std::cout << "Key: ";
		std::cin >> key;
		std::cout << encrypt(stri, key) << std::endl;
		system("pause");
	}
	else if (mode == 2) {
		std::string stri;
		std::cout << "Code: ";
		std::cin.ignore();
		std::getline(std::cin, stri);
		int key;
		std::cout << "Key(Enter the key that the string is encoded with): ";
		std::cin >> key;
		std::cout << decrypt(stri, key) << std::endl;
		system("pause");
	}
	else {
		std::cout << "Error! Mode not found!" << std::endl;
	}
}
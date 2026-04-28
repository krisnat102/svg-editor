#include <fstream>
#include <sstream>
#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include "Figure.h"
#include "Managers.h"

using std::vector;
using std::string;

#pragma region FileManager Methods
void FileManager::readFile() {
	std::ifstream file(fileName, std::ios::in);

	if (!file.is_open()) {
		std::cout << "The file is either inaccessible or not found.";
		return;
	}

	bool readFigures = false;
	string line;
	while (std::getline(file, line)) {
		if (line.find("</svg>") != string::npos) break; // stops when it reaches the end of the figures

		if (line.find("<svg>") != string::npos) readFigures = true;

		if (readFigures) {
			Figure* figure = stringToFigure(line);

			if (figure != nullptr) {
				canvas.push_back(figure);
			}
		}
	}
}

Figure* FileManager::stringToFigure(string strFigure) const {
	string shapeType;
	if (strFigure.find("<rect") != string::npos) shapeType = "rect";
	else if (strFigure.find("<ellipse") != string::npos) shapeType = "ellipse";
	else if (strFigure.find("<line") != string::npos) shapeType = "line";
	else return nullptr;

	string color = "black";
	unsigned strokeWidth = 1;
	unsigned values[4] = { 0, 0 ,0 ,0 };
	vector<string> substrings = splitStr(strFigure);

	getValues(substrings, values);

	if (shapeType == "rect") {
		return new Rectangle(values[0], values[1], values[2], values[3], color);
	}
	else if (shapeType == "ellipse") {
		return new Ellipse(values[0], values[1], values[2], values[3], color);
	}
	else if (shapeType == "line") {
		return new Line(values[0], values[1], values[2], values[3], strokeWidth);
	}

	std::cout << "Unrecongized figure.";
	return nullptr;
}

void FileManager::getValues(const vector<string> substrings, unsigned* values) const {
	for (unsigned i = 0; i < substrings.size(); i++) {
		string valStr = extractAtrValue(substrings[i]);

		if (valStr == "") continue;

		// x, cx, x1
		if (substrings[i].find("x=") == 0 || substrings[i].find("cx=") == 0 || substrings[i].find("x1=") == 0) {
			unsigned value = (unsigned)std::abs(std::stoi(valStr)); // makes sure the value is always positive, because our coordinate system is only with positive numbers
			values[0] = value;
		}
		// y, cy, y1
		else if (substrings[i].find("y=") == 0 || substrings[i].find("cy=") == 0 || substrings[i].find("y1=") == 0) {
			unsigned value = (unsigned)std::abs(std::stoi(valStr));
			values[1] = value;
		}
		// width, rx, x2
		else if (substrings[i].find("width=") == 0 || substrings[i].find("rx=") == 0 || substrings[i].find("x2=") == 0) {
			unsigned value = (unsigned)std::abs(std::stoi(valStr));
			values[2] = value;
		}
		// height, ry, y2
		else if (substrings[i].find("height=") == 0 || substrings[i].find("ry=") == 0 || substrings[i].find("y2=") == 0) {
			unsigned value = (unsigned)std::abs(std::stoi(valStr));
			values[3] = value;
		}

	}
}

string FileManager::extractAtrValue(const string token) const {
	unsigned start = token.find_first_of("'\"");
	unsigned end = token.find_last_of("'\"");
	++start; // skips the "

	if (start >= end) return "";

	return token.substr(start, end - start);
}

vector<string> FileManager::splitStr(string str) const { //rework so it doesnt crash when theres a space inside the color attribute
	const char WHITESPACE = ' ';

	vector<string> tokens;
	unsigned start = 0;
	size_t end = str.find(WHITESPACE);

	while (end != string::npos) {
		tokens.push_back(str.substr(start, end - start));
		start = end + 1;
		end = str.find(WHITESPACE, start);
	}

	tokens.push_back(str.substr(start));
	return tokens;
}
#pragma endregion

void CommandManager::print() const {
	for (unsigned i = 0; i < file.canvas.size(); i++) {
		std::cout << file.canvas[i]->info() << std::endl;
	}
}

void CommandManager::erase(string param) {
	int i = std::stoi(param) - 1;

	if (i >= file.canvas.size()) return;
	file.canvas.erase(file.canvas.begin() + i);
}

void CommandManager::translateParamToCoords(const vector<string> param, unsigned& x, unsigned& y, int& n) const {
	unsigned i = 0;

	if (param[0].find("=") == string::npos) {
		i++;
		n = std::stoi(param[0]);
	}

	unsigned equalPos1 = param[i].find("=");
	unsigned equalPos2 = param[i + 1].find("=");
	if (equalPos1 == string::npos || equalPos2 == string::npos) return; // skips if theres no =

	string strX = param[i].substr(equalPos1 + 1);
	string strY = param[i + 1].substr(equalPos2 + 1);

	if (strX == "" || strY == "") return;

	x = (unsigned) std::abs(std::stoi(strX));
	y = (unsigned) std::abs(std::stoi(strY));
}

void CommandManager::translate(const vector<string> param) const {
	if (param.size() < 2) return;

	unsigned x = 0, y = 0;
	int n = -1;
	translateParamToCoords(param, x, y, n);

	if (n != -1) {
		file.canvas[n - 1]->move(x, y);
		return;
	}

	for (unsigned i = 0; i < file.canvas.size(); i++) {
		file.canvas[i]->move(x, y);
	}
}

void CommandManager::within(const vector<string> option) const {
	if (option[0] == "circle") {

	}
	else if (option[0] == "rectangle") {

	}
}

int main() {
	FileManager file = FileManager("Figures.svg");
	file.readFile();
	CommandManager manager = CommandManager(file);
	manager.print();
	std::cout << std::endl;
	vector<string> test;
	test.push_back("2");
	test.push_back("horizontal=10");
	test.push_back("vertical=10");
		manager.translate(test);
		manager.print();
}
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
void FileManager::openFile(std::string fileStr) {
	fileName = fileStr;
	std::ifstream file(fileName, std::ios::in);

	if (!file.is_open()) {
		std::cout << "The file is either inaccessible or not found.";
		return;
	}

	bool readFigures = false;
	string line;
	while (std::getline(file, line)) {
		if (line.find("</svg") != string::npos) break; // stops when it reaches the end of the figures

		if (readFigures) {
			Figure* figure = stringToFigure(line);

			if (figure != nullptr) {
				canvas.push_back(figure);
			}
		}

		if (line.find("<svg") != string::npos) readFigures = true; // starts reading only when it reaches the figures
	}

	std::cout << "Successfully opened " << fileName << std::endl;
}

void FileManager::closeFile()
{
	if (fileName != "") std::cout << "Successfully closed " << fileName << std::endl;
	else {
		std::cout << "No file open. Invalid command" << std::endl;
		return;
	}

	fileName = "";
	canvas.clear();
}

Figure* FileManager::stringToFigure(string strFigure) const {
	string shapeType;
	if (strFigure.find("rect") != string::npos) shapeType = "rect";
	else if (strFigure.find("ellipse") != string::npos) shapeType = "ellipse";
	else if (strFigure.find("line") != string::npos) shapeType = "line";
	else return nullptr;

	string color = "black";
	unsigned strokeWidth = 1;
	unsigned values[4] = { 0, 0 ,0 ,0 };
	vector<string> substrings = splitStr(strFigure);

	getValues(substrings, values, &color, &strokeWidth);

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

void FileManager::getValues(const vector<string> substrings, unsigned* values, string* color, unsigned* strokeWidth) const {
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

		if (substrings[i].find("fill") == 0) {
			*color = valStr;
		}

		if (substrings[i].find("stroke-width") == 0) {
			*strokeWidth = (unsigned)std::abs(std::stoi(valStr));
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

void CommandManager::create(const std::vector<std::string> param) {
	if (param.size() < 5) return;

	string str;
	str += param[0] + " ";
	str += "x='" + param[1] + "' "; // we assign these so we can reuse string to figure and they get recognized 
	str += "y='" + param[2] + "' ";
	str += "width='" + param[3] + "' ";
	str += "height='" + param[4] + "' ";

	if (param.size() == 6) { // assings the final value that depends on the type of object
		if (param[0] == "line" && param.size() == 6) {
			str += "stroke-width='" + param[5] + "'";
		}
		else {
			str += "fill='" + param[5] + "'";
		}
	}

	std::cout << str;

	file.canvas.push_back(file.stringToFigure(str));
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
	if (option.size() == 0) return;

	bool isEmpty = true;

	if (option[0] == "circle" && option.size() == 4) {
		unsigned cx = (unsigned)std::abs(std::stoi(option[1]));
		unsigned cy = (unsigned)std::abs(std::stoi(option[2]));
		unsigned r = (unsigned)std::abs(std::stoi(option[3]));

		for (unsigned i = 0; i < file.canvas.size(); i++) {
			if (file.canvas[i]->isWithinCircle(cx, cy, r)) {
				std::cout << file.canvas[i]->info() << std::endl;
				isEmpty = false;
			}
		}

		if (isEmpty) {
			std::cout << "No figures are located within circle " << cx << " " << cy << " " << r;
		}
	}
	else if (option[0] == "rectangle" && option.size() == 5) {
		unsigned x = (unsigned)std::abs(std::stoi(option[1]));
		unsigned y = (unsigned)std::abs(std::stoi(option[2]));
		unsigned width = (unsigned)std::abs(std::stoi(option[3]));
		unsigned heigt = (unsigned)std::abs(std::stoi(option[3]));

		for (unsigned i = 0; i < file.canvas.size(); i++) {
			if (file.canvas[i]->isWithinRectangle(x, y, width, heigt)) {
				std::cout << file.canvas[i]->info() << std::endl;
				isEmpty = false;
			}
		}

		if (isEmpty) {
			std::cout << "No figures are located within rectangle " << x << " " << y << " " << width << " " << heigt;
		}
	}
}

int main() {
	FileManager file = FileManager("Figures.svg");
	file.openFile();
	CommandManager manager = CommandManager(file);
	manager.print();
	std::cout << std::endl;
	vector<string> test;
	test.push_back("line");
	test.push_back("0");
	test.push_back("0");
	test.push_back("150");
	test.push_back("150");
	test.push_back("5");
	manager.create(test);
	manager.print();
}
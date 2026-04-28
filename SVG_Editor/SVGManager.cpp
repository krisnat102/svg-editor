#include <fstream>
#include <sstream>
#include <iostream>
#include <string>
#include <vector>
#include "Figure.cpp"

class FileManager {
public:

	FileManager() = default;

	void readFile(std::string fileName);
	void createFile(std::string name);

	std::vector<Figure*> canvas;

private:
	Figure* stringToFigure(std::string strFigure) const;
	std::vector<std::string> splitStr(std::string str) const;
	std::string extractAtrValue(const std::string token) const;
};

#pragma region FileManager Methods

void FileManager::readFile(std::string fileName) {
	std::ifstream file(fileName, std::ios::in);
	
	if (!file.is_open()) {
		std::cout << "The file is either inaccessible or not found.";
		return;
	}

	bool readFigures = false;
	std::string line;
	while (std::getline(file, line)) { 
		if (line.find("</svg>") != std::string::npos) break; // stops when it reaches the end of the figures

		if (line.find("<svg>") != std::string::npos) readFigures = true;

		while (readFigures) {
			Figure* figure = stringToFigure(line);

			if (figure != nullptr) {
				canvas.push_back(figure);
			}
		}
	}
}

Figure* FileManager::stringToFigure(std::string strFigure) const {
	std::vector<std::string> substrings = splitStr(strFigure); // divides the string by whitespaces

	std::string shapeType = substrings[0];

	std::string valueStr;
	std::vector<int> valueList;
	for (int i = 1; i < substrings.size() - 2; i++) { // skips the figure type and color, only looks at ints
		valueStr = extractAtrValue(substrings[i]); // gets only the number value from them
		int value = std::stoi(valueStr); // converts the value to int
		valueList.push_back(value);
	}

	if (shapeType == "rect") {
		return new Rectangle(valueList[0], valueList[1], valueList[2], valueList[3], extractAtrValue(substrings[5]));
	}
	else if (shapeType == "ellipse") {
		return new Ellipse(valueList[0], valueList[1], valueList[2], valueList[3], extractAtrValue(substrings[5]));;
	}
	else if (shapeType == "line") {
		// add for line
	}
	else {
		std::cout << "Unrecongized figure.";
		return nullptr;
	}
}

std::string FileManager::extractAtrValue(const std::string token) const
{
	size_t start = token.find_first_of("='");
	if (start == std::string::npos) return "";

	start += 2; // skips the ="

	size_t end = token.find_last_of("'\"");

	if (start >= end) return "";
	return token.substr(start, end - start);
}

std::vector<std::string> FileManager::splitStr(std::string str) const { //rework so it doesnt crash when theres a space inside the color attribute
	const char WHITESPACE = ' ';

	std::vector<std::string> tokens;
	size_t start = 0;
	size_t end = str.find(WHITESPACE);

	while (end != std::string::npos) {
		tokens.push_back(str.substr(start, end - start));
		start = end + 1;
		end = str.find(WHITESPACE, start);
	}

	tokens.push_back(str.substr(start));
	return tokens;
}

#pragma endregion

class CommandManager {
public:
	CommandManager(FileManager* file)
		:file(file) {
	}

	void print() const;
	void create();
	void translate(std::string param) const;
	void within(std::string option) const;
private:
	FileManager* file;
};

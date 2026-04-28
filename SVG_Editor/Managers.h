#pragma once

class FileManager {
public:

	FileManager(std::string fileName)
		:fileName(fileName) {
	}

	void readFile();
	void createFile(std::string name);

	std::vector<Figure*> canvas;

private:
	std::string extractAtrValue(const std::string token) const;
	Figure* stringToFigure(std::string strFigure) const;
	std::vector<std::string> splitStr(std::string str) const;
	void getValues(const std::vector<std::string> substrings, unsigned* values) const;

	std::string fileName;
};

class CommandManager {
public:
	CommandManager(FileManager& file)
		:file(file) {
	}

	void print() const;
	void erase(std::string param);
	void create();
	void translate(const std::vector<std::string> param) const;
	void within(const std::vector < std::string> option) const;

private:
	FileManager& file;
	void translateParamToCoords(const std::vector<std::string> param, unsigned& x, unsigned& y, int& n) const;
};
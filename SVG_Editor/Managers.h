#pragma once

class FileManager {
public:

	FileManager(){
	}

	void openFile(std::string fileName);
	void createFile(std::string name);
	void closeFile();
	Figure* stringToFigure(std::string strFigure) const;

	std::vector<Figure*> canvas;

private:
	std::string extractAtrValue(const std::string token) const;
	std::vector<std::string> splitStr(std::string str) const;
	void getValues(const std::vector<std::string> substrings, unsigned* values, std::string* color, unsigned* strokeWidth) const;

	std::string fileName;
};

class CommandManager {
public:
	CommandManager(FileManager& file)
		:file(file) {
	}

	void print() const;
	void erase(const std::string param);
	void create(const std::vector<std::string> param);
	void translate(const std::vector<std::string> param) const;
	void within(const std::vector < std::string> option) const;

private:
	FileManager& file;
	void translateParamToCoords(const std::vector<std::string> param, unsigned& x, unsigned& y, int& n) const;
};
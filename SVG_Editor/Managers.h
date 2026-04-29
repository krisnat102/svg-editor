#pragma once
#include <vector>
#include <string>
#include "Figure.h"

class FileManager {
public:

	FileManager() {
		isFileOpen = false;
		fileName = "";
	}

	~FileManager() {
		deleteData();
	}

	void openFile(std::string fileName);
	void closeFile();
	void saveFile();
	void saveAs(std::string newFilePath);
	Figure* stringToFigure(std::string strFigure) const;
	std::vector<std::string> splitStr(std::string str) const;

	bool isOpen() const {
		return isFileOpen;
	}

	Figure* getFigureAt(int n) const {
		return canvas[n];
	}

	unsigned figureCount() const {
		return canvas.size();
	}

	void deleteFigureAt(unsigned n) {
		delete canvas[n];
		canvas.erase(canvas.begin() + n);
	}

	void addFigure(Figure* figure) {
		canvas.push_back(figure);
	}

private:
	std::string extractAtrValue(const std::string token) const;
	void getValues(const std::vector<std::string> substrings, unsigned* values, std::string* color, unsigned* strokeWidth) const;
	void saveToFile(std::string readFrom, std::string writeTo) const;
	void createFile(const std::string name);
	void deleteData();

	bool isFileOpen;
	std::string fileName;
	std::vector<Figure*> canvas;
};

class CommandManager {
public:
	CommandManager() {
	}

	void startProgram();

private:
	FileManager file;
	void translateParamToCoords(const std::vector<std::string> param, unsigned& x, unsigned& y, int& n) const;

	void print() const;
	void erase(const std::string param);
	void create(const std::vector<std::string> param);
	void translate(const std::vector<std::string> param);
	void within(const std::vector < std::string> option) const;
	void close();
	void save();
	void saveAs(std::string path);
	void exit();
	void open(std::string fileName);
	void help() const;
};
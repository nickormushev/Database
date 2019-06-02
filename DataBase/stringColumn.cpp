#include "stringColumn.h"
#include <iostream>
#include <string>


void StringColumn::printCell(int cellIndex) const {
	std::cout << this->stringCell[cellIndex];
}

void StringColumn::deleteCells(std::vector<int> rowIndexes) {
	for (int i = 0; i < rowIndexes.size(); i++) {
		if (rowIndexes[i] - i < this->stringCell.size()) {
			this->stringCell.erase(this->stringCell.begin() + rowIndexes[i] - i);
			this->setSize(this->getSize() - 1);
		}
	}
};

void StringColumn::addCell(int rowIndex, std::string targetValue) {
	if (targetValue == "") { return; }

	if (this->stringCell.size() < rowIndex + 1) {
		this->stringCell.resize(rowIndex + 1);
		this->setSize(rowIndex + 1);
	}

	this->stringCell[rowIndex] = targetValue;
}

void StringColumn::setExtistingCell(std::vector<int> rowIndexes, std::string targetValue) {

	for (int i = 0; i < rowIndexes.size(); i++) {
		this->addCell(rowIndexes[i], targetValue); //the row indexes start from zero that is why a + 1 is needed
	}
};

int StringColumn::numOfDigitsCharacters(int cellIndex) const {
	return this->stringCell[cellIndex].size();
}

std::vector<int> StringColumn::searchColumn(std::string searchedValue) const {
	std::vector<int> foundRows;

	for (int i = 0; i < this->stringCell.size(); i++) {
		if (this->stringCell[i] == searchedValue) { foundRows.push_back(i); }
	}

	return foundRows;
};

std::string StringColumn::getValue(int index) const {
	return (index < this->stringCell.size()) ? this->stringCell[index] : "";
};

ColumnTemplate* StringColumn::clone() {
	return new StringColumn(*this);
}

void StringColumn::serialize(std::ostream& out) const {
	out << "Column string ";

	ColumnTemplate::serialize(out);

	for (size_t i = 0; i < this->stringCell.size(); i++)
	{
		out << this->stringCell[i] << " ";
	}
	out << "ColumnEnd ";
}

void StringColumn::deserialize(std::istream& in) {
	std::string fileData;
	
	ColumnTemplate::deserialize(in);

	while (in >> fileData && fileData != "ColumnEnd")
	{
		this->stringCell.push_back(fileData);
	}
}
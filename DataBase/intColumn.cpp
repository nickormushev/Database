#include "intColumn.h"
#include <iostream>

void IntColumn::printCell(int cellIndex) const {
	std::cout << this->intCell[cellIndex];
};

std::string IntColumn::getValue(int index) const {
	return (index < this->intCell.size()) ? std::to_string(this->intCell[index]) : "";
};

void IntColumn::deleteCells(std::vector<int> rowIndexes) {
	for (int i = 0; i < rowIndexes.size(); i++) {
		if (rowIndexes[i] - i < this->intCell.size()) {
			this->intCell.erase(this->intCell.begin() + rowIndexes[i] - i);
			this->setSize(this->getSize() - 1);
		}
	}
};

void IntColumn::accumulate(mathop opearation, double base, int startValue, std::vector<int> rowIndexes) {
	
	double result = base;
	for (size_t i = startValue; i < rowIndexes.size(); i++)
	{
		result = opearation(result, this->intCell[rowIndexes[i]]);
	}

	std::cout << "The result of the operation is: " << result << std::endl;
}

void IntColumn::addCell(int rowIndex, std::string targetValue) {
	
	if (targetValue == "") { return; }
	int targetIntValue = std::stoi(targetValue);

	if (this->intCell.size() < rowIndex + 1) {
		this->intCell.resize(rowIndex + 1);
		this->setSize(rowIndex + 1);
	}

	this->intCell[rowIndex] = targetIntValue;
}

void IntColumn::setExtistingCell(std::vector<int> rowIndexes, std::string targetValue) {

	for (int i = 0; i < rowIndexes.size(); i++) {
		this->addCell(rowIndexes[i], targetValue);
	}
};

int IntColumn::numOfDigitsCharacters(int cellIndex) const {
	int otherInt = this->intCell[cellIndex];
	if (otherInt == 0) return 1;
	int i = 0;
	while (otherInt != 0) {
		otherInt = otherInt / 10;
		i++;
	}

	return i;
};

std::vector<int> IntColumn::searchColumn(std::string searchedValue) const {
	int intSearchedValue = std::stoi(searchedValue);
	std::vector<int> foundRows;

	for (int i = 0; i < this->intCell.size(); i++) {
		if (this->intCell[i] == intSearchedValue) { foundRows.push_back(i); }
	}

	return foundRows;
};

ColumnTemplate* IntColumn::clone() {
	return new IntColumn(*this);
}

void IntColumn::serialize(std::ostream& out) const {
	out << "Column int ";

	ColumnTemplate::serialize(out);

	for (size_t i = 0; i < this->intCell.size(); i++)
	{
		out << this->intCell[i] << " ";
	}
	out << "ColumnEnd ";
}

void IntColumn::deserialize(std::istream& in) {
	std::string fileData;
	
	ColumnTemplate::deserialize(in);

	while (in >> fileData && fileData != "ColumnEnd")
	{
		this->intCell.push_back(std::stoi(fileData));
	}
}
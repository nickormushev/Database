#include "DoubleColumn.h"

void DoubleColumn::printCell(int cellIndex) const {
	std::cout << this->doubleCell[cellIndex];
};

std::string DoubleColumn::getValue(int index) const {
	return (index < this->doubleCell.size()) ? std::to_string(this->doubleCell[index]) : "";
};

void DoubleColumn::deleteCells(std::vector<int> rowIndexes) {
	for (int i = 0; i < rowIndexes.size(); i++) {
		if (rowIndexes[i] - i < this->doubleCell.size()) {
			this->doubleCell.erase(this->doubleCell.begin() + rowIndexes[i] - i );
			this->setSize(this->getSize() - 1);
		}
	}
};

void DoubleColumn::accumulate(mathop opearation, double base, int startValue, std::vector<int> rowIndexes) {
	
	double result = base;

	for (size_t i = startValue; i < rowIndexes.size(); i++)
	{
		result = opearation(result, this->doubleCell[rowIndexes[i]]);
	}

	std::cout << "The result of the operation is: " << result << std::endl;
}

void DoubleColumn::addCell(int rowIndex, std::string targetValue) {
	if (targetValue == "") { return; }
	double targetDoubleValue = std::stod(targetValue);

	if (this->doubleCell.size() < rowIndex + 1) { // the plus one is if the size is equal to x that means elements are from 0 to x - 1
		this->doubleCell.resize(rowIndex + 1);
		this->setSize(rowIndex + 1);
	}

	this->doubleCell[rowIndex] = targetDoubleValue;
}

void DoubleColumn::setExtistingCell(std::vector<int> rowIndexes, std::string targetValue) {
	
	for (int i = 0; i < rowIndexes.size(); i++) {
		this->addCell(rowIndexes[i], targetValue);
	}
};

int DoubleColumn::numOfDigitsCharacters(int cellIndex) const {
	
	double otherDouble = this->doubleCell[cellIndex];
	if (otherDouble == 0) return 1;
	std::string stringDouble = std::to_string(otherDouble); 

	int j = 0; // counts how many zeroes there are after the decimal sign. Removes the bonus ones
	for (int i = 0; i < stringDouble.size(); i++) {
		j++;
		if (stringDouble[i] != '0') { j = 0; }
		if (stringDouble[i] == '.') { j++; } //some error came up that the . was not counted as a symbol
	}
	return stringDouble.size() - j; // the double was with a precision of 8 so size() return a higher value - j removes the bonuse zeroes
}

std::vector<int> DoubleColumn::searchColumn(std::string searchedValue) const {
	double doubleSearchedValue = std::stod(searchedValue);
	std::vector<int> foundRows;

	for (int i = 0; i < this->doubleCell.size(); i++) {
		if (this->doubleCell[i] == doubleSearchedValue) { foundRows.push_back(i); }
	}

	return foundRows;
};

ColumnTemplate* DoubleColumn::clone() {
	return new DoubleColumn(*this);
}

void DoubleColumn::serialize(std::ostream& out) const {
	out << "Column double ";
	
	ColumnTemplate::serialize(out);

	for (size_t i = 0; i < this->doubleCell.size(); i++)
	{
		out << this->doubleCell[i] << " ";
	}
	out << "ColumnEnd ";
}

void DoubleColumn::deserialize(std::istream& in) {
	std::string fileData;
	
	ColumnTemplate::deserialize(in);

	while (in >> fileData && fileData != "ColumnEnd")
	{
		this->doubleCell.push_back(std::stod(fileData));
	}
}
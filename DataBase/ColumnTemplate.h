#pragma once

#include <vector>
#include <string>
#include <iostream>
using mathop = double(*)(double, double);

/**
 * Abstract class that is used for having columns of different types(int, double string).
 */

class ColumnTemplate
{
	int columnId;
	int columnSize;
	std::string columnName;
	std::string columnType;

public:

	ColumnTemplate(int newSize = 0, std::string newColumnName = "", int newColumnId = 1, std::string newColumnType = "unknown") : 
		columnSize(newSize),
		columnName(newColumnName), 
		columnId(newColumnId), 
		columnType(newColumnType) {};

	void setName(std::string newColumnName);
	void setSize(int colSize);
	int getSize() const;
	std::string getName() const;
	std::string getType() const;
	void printType() const;
	
	virtual std::vector<int> searchColumn(std::string searchedValue) const = 0;
	/// returns how many digits or numbers a word or a number is made up of
	virtual int numOfDigitsCharacters(int cellIndex) const = 0;
	virtual std::string getValue(int index) const = 0;
	virtual void printCell(int cellIndex) const = 0;
	///changes cell values with given rowIndexes to the targetValue
	virtual void setExtistingCell(std::vector<int> rowIndexes, std::string targetValue) = 0;
	virtual void deleteCells(std::vector<int> rowIndexes) = 0;
	///not only adds cells but can change cell values and resize row vector
	virtual void addCell(int rowIndex, std::string targetValue) = 0;
	///a higher order function that performs an operation on the chosen rows
	virtual void accumulate(mathop opearation, double base, int startValue, std::vector<int> rowIndexes) = 0;
	virtual ColumnTemplate* clone() = 0;
	virtual void serialize(std::ostream& out) const {
		out << this->columnType <<" "<<  this->columnId << " " << this->columnName << " " << this->columnSize << " ";
	};
	virtual void deserialize(std::istream& in) {
		in >> this->columnType
		>> this->columnId
		>> this->columnName
		>> this->columnSize;
	};
	virtual ~ColumnTemplate() {};

};


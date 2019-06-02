#pragma once
#include "ColumnTemplate.h"

class DoubleColumn: public ColumnTemplate
{
	std::vector<double> doubleCell;

public:
	DoubleColumn(int newSize = 0, std::string newColumnName = "", int newColumnId = 1, 
		std::string newColumnType = "", std::vector<double> newVector = std::vector<double>()):
		ColumnTemplate(newSize, newColumnName, newColumnId, newColumnType), doubleCell(newVector) {};

	void deleteCells(std::vector<int> rowIndexes) override;
	void printCell(int cellIndex) const override;
	///changes cell values with given rowIndexes to the targetValue
	void setExtistingCell(std::vector<int> rowIndexes, std::string targetValue) override;
	///not only adds cells but can change cell values and resize row vector
	void addCell(int rowIndex, std::string targetValue) override;
	/** 
	 * returns how many digits or numbers a word or a number is made up of. The variable j
	 * is used to count the extra zeroes found in the precisioun 8 with which i resceived the doubles.
	 */
	int numOfDigitsCharacters(int cellIndex) const override;
	std::vector<int> searchColumn(std::string searchedValue) const override;
	///a higher order function that performs an operation on the chosen rows
	void accumulate(mathop opearation, double base, int startValue, std::vector<int> rowIndexes) override;
	std::string getValue(int index) const override;
	ColumnTemplate* clone() override;
	void serialize(std::ostream& out) const override;
	void deserialize(std::istream& in) override;

};


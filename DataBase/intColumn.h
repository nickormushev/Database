#pragma once

#include "ColumnTemplate.h"

class IntColumn: public ColumnTemplate
{
	std::vector<int> intCell;

public:
	IntColumn(int newSize = 0, std::string newColumnName = "", int newColumnId = 1,
		std::string newColumnType = "unknown", std::vector<int> newVector = std::vector<int>()) :
		ColumnTemplate(newSize, newColumnName, newColumnId, newColumnType), intCell(newVector) {};

	void deleteCells(std::vector<int> rowIndexes) override;
	void printCell(int cellIndex) const override;
	///changes cell values with given rowIndexes to the targetValue
	void setExtistingCell(std::vector<int> rowIndexes, std::string targetValue) override;
	///not only adds cells but can change cell values and resize row vector
	void addCell(int rowIndex, std::string targetValue) override;
	/// returns how many digits or numbers a word or a number is made up of
	int numOfDigitsCharacters(int cellIndex) const override;
	std::vector<int> searchColumn(std::string searchedValue) const override;
	///a higher order function that performs an operation on the chosen rows
	void accumulate(mathop opearation, double base, int startValue, std::vector<int> rowIndexes) override;
	std::string getValue(int index) const override;
	ColumnTemplate* clone() override;
	void serialize(std::ostream& out) const override;
	void deserialize(std::istream& in) override;
};


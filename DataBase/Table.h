#pragma once
#include <iostream>

#include "ColumnTemplate.h"
#include "doubleColumn.h"
#include "intColumn.h"
#include "stringColumn.h"
/**
 * The table class is made up of columns from different typse (int, double string)
 * which the user can manipulate. The numOfCol variable is the table size 
 */
class Table
{
	char * name;
	int capacity, numOfCol;
	ColumnTemplate ** columns;
	std::string sourceFile;

public:
	Table();
	Table(const char * name, ColumnTemplate ** columns, int capacity, int numOfCol, std::string sourceFile);
	Table(Table const & other);
	~Table();
	
	Table& operator=(Table const & other);
	
	char * getName() const;
	int getSize() const;
	ColumnTemplate ** getColumns() const;
	int getMaxColumnSize();
	std::string getFileName() const;
	void copy(const char * name, ColumnTemplate ** columns, int capacity, int numOfCol, std::string sourceFile);
	void destroy();
	void getColumnTypes() const;
	/// prints the whole table.
	void print() const;
	/* 
	* Since i didn't know what setw was i implemented my own. Count the num of characters and 
	* add intervals till we reach 10. Now we have a shiny nice looking table.
	*/
	void printRow(int rowIndex) const;
	/// used by print
	void printColumnNames() const;
	///searches in the given column for the searchedValue and prints all the rows with that value
	void tableSelect(int column, std::string searchedValue) const;
	/**
	* The function uses a columnId and a searchValue he wishes to search for in that column. Once the value is found
	* on the same row, but in the targetColumn, the value is changed to the targetValue.
	*/
	void updateCells(int columnId, std::string searchValue, int targetColumnId, std::string targetValue);
	/**
	* Generates a column of a the given types and sends it to the columnSupportFunction so 
	* it can add it to the double pointer array.
	*/
	void addColumn(std::string colName, std::string colType);
	void addRow(std::vector<std::string> RowValues);
	void deleteRow(int columnId, std::string searchValue);
	void setName(std::string newName);
	/// Counts the rows in a table that contain the searched value in the respective column
	void countRows(int columnId, std::string searchedValue);
	/**
	* The function performs an operation on n number of cells. n depends on the searchColumn and
	* the search value you are trying to find in that column. On all rows the value is found, the operation is performed
	* on the respective cells from the target column
	*/
	void aggregate( int searchColumnId, std::string searchValue, int targetColumnId, std::string operation);
	void serialize(std::ostream& out) const;
	void deserialize(std::istream& in, std::string sourceFile);
	/**
	 * Receives a new column and adds it to the double pointer array.
	 */
	void addColumnSupportFunction(ColumnTemplate * newCol);

};


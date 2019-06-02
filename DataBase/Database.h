#pragma once
#include "Table.h"
#include "ColumnTemplate.h"

#include <vector>
#include <string>
#include <iostream>

/*! 
 * The database class's purpose is to hold different tables the user can manipulate so he can have
 * more than one table open at a time. It is used to save and load tables and to collect data from them.
 */
class Database
{
	std::vector<Table> tables;

public:
	Database(std::vector<Table> tables = std::vector<Table>()):
			tables(tables){};

	/// saves a single table to a file
	void save(std::string fileName, std::string tableName) const;
	void loadTable(std::string fileName);
	/// lists table names
	void showTables() const;
	///uses the name of the table to find it's index in the vector and returns it
	int findTable(std::string tableName) const;
	///lists the columns and their types
	void describe(std::string tableName) const;
	void printTable(std::string tableName) const;
	///searches in the given column for the searchValue and prints all the rows with that value
	void dbSelect(int column, std::string searchedValue, std::string tableName) const;
	void addColumn(std::string tableName, std::string columnName, std::string colType);
	/** 
	 * The function uses a columnId and a searchValue he wishes to search for in that column. Once the value is found
	 * on the same row, but in the targetColumn, the value is changed to the targetValue.
	 */
	void updateCells(std::string tableName, int columnId, std::string searchValue, int targetColumnId, std::string targetValue); 
	void addRow(std::string tableName, std::vector<std::string> Row);
	/// The function searches for a value in a column. Once it finds it, it deletes thr row that contains it.
	void deleteRow(std::string tableName, int columnId, std::string searchValue);
	void renameTable(std::string tableOldName, std::string tableNewName);
	/// Counts the rows in a table that contain the searched value in the respective column
	void countRowsInTable(std::string tableName, std::string searchedValue, int columnIndex);
	/**
	* The funtion performs an operation on n number of cells. n depends on the searchColumn and 
	* the search value you are trying to find in that column. On all rows the value is found, the operation is performed
	* on the respective cells from the target column
	*/
	void aggregate(std::string tableName, int searchColumn, std::string searchValue, int targetColumn, std::string operation); 
	/**
	* The funtion creates a new table by performing an innerJoin on two tables 
	* based on a column given from the each of the two tables.
	*/
	void innerJoin(std::string newTableName, std::string firstTableName, std::string secondTableName, int firstTableColIndex, int secondTableColIndex);
	///removes a table from a vector, without keeping the changes made to it in the file
	void close(std::string tableName);
	void addNewTable(std::string tableName);
};


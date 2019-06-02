#include "Database.h"
#include <fstream>

void Database::showTables() const {
	for (int i = 0; i < this->tables.size(); i++) {
		std::cout << this->tables[i].getName() << " ";
	}
	std::cout << std::endl;
}

void Database::renameTable(std::string tableOldName, std::string tableNewName) {
	for (size_t i = 0; i < this->tables.size(); i++)
	{
		if (tableNewName.compare(this->tables[i].getName()) == 0) {
			std::cout << "The new name for the table already exists" << std::endl;
			return;
		}
	}
	int tableIndex = this->findTable(tableOldName);
	if (tableIndex != -1) {
		this->tables[tableIndex].setName(tableNewName);
		std::cout << "Table succesfully renamed" << std::endl;
	}
};

void Database::innerJoin(std::string newTableName, std::string firstTableName, std::string secondTableName,
	int firstTableColIndex, int secondTableColIndex) {

	int firstTableIndex = this->findTable(firstTableName);
	int secondTableIndex = this->findTable(secondTableName);
	if (firstTableIndex == -1 || secondTableIndex == -1) {
		return;
	}

	ColumnTemplate ** colsTableOne = this->tables[firstTableIndex].getColumns();
	ColumnTemplate ** colsTableTwo = this->tables[secondTableIndex].getColumns();

	int numOfColOne = this->tables[firstTableIndex].getSize();
	int numOfColTwo = this->tables[secondTableIndex].getSize();
	int newTableSize = numOfColOne + numOfColTwo;
	
	if (firstTableColIndex > numOfColOne || secondTableColIndex > numOfColTwo) {
		return;
	}

	Table newTable(newTableName.c_str(), nullptr, newTableSize * 2, 0, "");
	bool firstRowOfNewTableFlag = true;

	for (size_t i = 0; i < colsTableOne[firstTableColIndex]->getSize(); i++) {
		for (size_t j = 0; j < colsTableTwo[secondTableColIndex]->getSize(); j++) {
			if (colsTableOne[firstTableColIndex]->getValue(i) == colsTableTwo[secondTableColIndex]->getValue(j)) {
				std::vector<std::string> row;
				for (size_t k = 0; k < numOfColOne; k++) {
					if (firstRowOfNewTableFlag) { newTable.addColumn(colsTableOne[k]->getName(), colsTableOne[k]->getType()); }
					row.push_back(colsTableOne[k]->getValue(i));
				}

				for (size_t k = 0; k < numOfColTwo; k++) {
					if (firstRowOfNewTableFlag) { 
						newTable.addColumn(colsTableTwo[k]->getName(), colsTableTwo[k]->getType()); 
					}
					row.push_back(colsTableTwo[k]->getValue(j));
				}
				
				firstRowOfNewTableFlag = false;
				newTable.addRow(row);
			}
		}
	}

	this->tables.push_back(newTable);
}

void Database::countRowsInTable(std::string tableName, std::string searchedValue, int columnIndex) {
	int tableIndex = this->findTable(tableName);
	if (tableIndex != -1) {
		this->tables[tableIndex].countRows(columnIndex, searchedValue);
	}
}

void Database::aggregate(std::string tableName, int searchColumn, std::string searchValue,
						int targetColumn, std::string operation) {
	int tableIndex = this->findTable(tableName);
	if (tableIndex != -1) {
		this->tables[tableIndex].aggregate(searchColumn, searchValue, targetColumn, operation);
	}
};

int Database::findTable(std::string tableName) const {
	int tableIndex = 0;

	while (tableIndex < this->tables.size() && tableName.compare(this->tables[tableIndex].getName()) != 0) { tableIndex++; }

	if (tableIndex != tables.size()) {
		return tableIndex;
	} else {
		std::cout << "No such table was found in this database" << std::endl;
		return -1; // means error
	}

}

void Database::describe(std::string tableName) const {
	int tableIndex = this->findTable(tableName);

	if (tableIndex != -1) {
		this->tables[tableIndex].getColumnTypes();
	}
}

void Database::addRow(std::string tableName, std::vector<std::string> Row) {
	int tableIndex = this->findTable(tableName);
	if (tableIndex != -1) {
		this->tables[tableIndex].addRow(Row);
	}
}

void Database::printTable(std::string tableName) const {
	int tableIndex = this->findTable(tableName);

	if (tableIndex != -1) {
		this->tables[tableIndex].print();
	}
}

void Database::updateCells(std::string tableName, int columnId, std::string searchValue, int targetColumnId, std::string targetValue) {
	int tableIndex = this->findTable(tableName);

	if (tableIndex != -1) {
		this->tables[tableIndex].updateCells(columnId, searchValue, targetColumnId, targetValue);
	}
}

void Database::dbSelect(int column, std::string searchedValue, std::string tableName) const {
	int tableIndex = this->findTable(tableName);
	
	if (tableIndex != -1) {
		this->tables[tableIndex].tableSelect(column, searchedValue);
	}
}

void Database::addColumn(std::string tableName, std::string columnName, std::string colType) {
	int tableIndex = this->findTable(tableName);
	if (tableIndex != -1) {
		this->tables[tableIndex].addColumn(columnName, colType);
	}
}

void Database::deleteRow(std::string tableName, int columnId, std::string searchValue) {
	int tableIndex = this->findTable(tableName);

	if (tableIndex != -1) {
		this->tables[tableIndex].deleteRow(columnId, searchValue);
	}
}

void Database::save(std::string tableName, std::string fileName) const {
	int tableIndex = this->findTable(tableName);
	
	if (tableIndex != -1) {
		
		if (fileName == "") {
			fileName = this->tables[tableIndex].getFileName();
			if (fileName == "") {
				std::cerr << "Please enter save as instead of save. This table was not loaded from a file" << std::endl;
				return;
			}
		}

		std::ofstream out(fileName);
		this->tables[tableIndex].serialize(out);
		out.close();
		std::cout << "Table saved successfully!" << std::endl;
	}
}

void Database::loadTable(std::string fileName) {
	std::string fileData;	
	std::ifstream in(fileName);
	if (in) {
		while (in >> fileData)
		{
			if (fileData == "Table") {
				Table newTable;
				newTable.deserialize(in, fileName);
				this->tables.push_back(newTable);
			}
		}
		std::cout << "File loaded successfully" << std::endl;
	}
	else {
		std::cerr << "No such file found" << std::endl;
	}
	in.close();
}

void Database::addNewTable(std::string tableName) {
	Table newTable;
	newTable.setName(tableName);
	this->tables.push_back(newTable);
	std::cout << "New table successfylly created!" << std::endl;
}

void Database::close(std::string tableName) {
	int tableIndex = this->findTable(tableName);
	if (tableIndex != -1) {
		this->tables.erase(this->tables.begin() + tableIndex);
	}
	std::cout << "Table closed successfully" << std::endl;
}
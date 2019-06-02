#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "DoubleColumn.h"
#include "Table.h"
#include "intColumn.h"
#include "ColumnTemplate.h"
#include "Database.h"


void help() {
	std::cout << "These are the available commands:" << '\n';
	std::cout << "open, close, save, saveAs, exit, addTable, showTables, describe, addColumn, print" <<'\n';
	std::cout << "select, update, delete, insert, innerJoin, rename, count, aggregate" << '\n';
}

void doubleColumntTest() {
	std::vector<double> testVector;
	for (int i = 0; i < 10; i++) { testVector.push_back((double)i / 2); }

	DoubleColumn doubleColumn(10, "Pesho", 1, "double", testVector);
	/*DoubleColumn doubleDefault;
	std::cout << "doubleColumn size is " << doubleColumn.getSize() << '\n';
	std::cout << "doubleColumn's name is "; doubleDefault.printType(); std::cout << '\n';
	std::cout << "doubleColumn cell five has a value of "; 
	doubleColumn.printCell(5);
	std::cout << '\n';
	doubleColumn.setNewCellData(3.14);
	std::cout << "doubleColumn size is " << doubleColumn.getSize() << '\n';
	doubleColumn.printCell(10);
	*/	
	doubleColumn.printCell(5);
	std::cout << '\n' << doubleColumn.numOfDigitsCharacters(5) << '\n';

}

void TableAndDbTest() {
	
	//Testing prerequisites
	std::vector<double> testDoubleVector;
	std::vector<int> testIntVector;
	std::vector<double> testDoubleVector2;
	for (int i = 0; i < 10; i++) {
		testDoubleVector.push_back((double)i / 2);
		testIntVector.push_back(i / 2);
		if(i%2 != 0) testDoubleVector2.push_back((double)i/2);

	}

	IntColumn intColumn(10, "Gosho", 1, "int", testIntVector);
	DoubleColumn doubleColumn2(10, "Miro", 1, "double", testDoubleVector2);
	DoubleColumn doubleColumn(10, "Pesho", 1, "double", testDoubleVector);

	ColumnTemplate ** columnsTest = new ColumnTemplate * [2];
	ColumnTemplate ** columnsTest2 = new ColumnTemplate *[2];

	//intColumn.printType();
	//intColumn.printCell(5);
	columnsTest[0] = &doubleColumn;
	columnsTest[1] = &intColumn;
	columnsTest2[0] = &intColumn;
	columnsTest2[1] = &doubleColumn2;

	char t[5] = "Test";
	char testName2[5] = "Pate";

	Table testTable(t, columnsTest, 10, 2, "");
	Table testTable2(testName2, columnsTest2, 10, 2, "");
	
	//Just testing the tables
	//------------------
	//std::cout << testTable.getName() << '\n';
	//testTable.getColumnTypes();  
	//Table testTableCopy(testTable);
	//std::cout << testTableCopy.getName() << '\n';
	//testTable.print();
	//testTable.tableSelect(0,"4.5");
	//------------------

	std::vector <Table> testDbVector;
	testDbVector.push_back(testTable);
	testDbVector.push_back(testTable2);

	Database testDb(testDbVector);
	
	//DbSelect Test, print, describe and showTables Tests. It just calls the functions for me to see that they work
	//------------------
	//testDb.dbSelect(1, "4", "Test"); 
	//testDb.printTable("Test");
	//testDb.describe("Test");
	//testDb.showTables();
	//------------------

	//addColumn test. I left it uncommented to check if any errors will show up if i have an empty column + print so I can see the result
	//------------------
	testDb.addColumn("Test", "Sasho", "string");
	//testDb.printTable("Test");
	//------------------

	//Testing some local table funtions which are self explanitory
	//------------------
	//testTable.addColumn("Sasho", "string");
	//testTable.getColumnTypes();
	//------------------

	//Updating table cell test;
	//------------------
	//testDb.updateCell("Test", 1, "4", 1, "1");
	//testDb.printTable("Test");
	//------------------

	//Testing row deletion
	//------------------
	//testDb.deleteRow("Test", 1, "4");
	//testDb.printTable("Test");
	//------------------

	//Testing adding a row(the insert command)
	//------------------
	//std::vector<std::string> rowValues;
	//rowValues.push_back("5.5");
	//rowValues.push_back("5");
	//rowValues.push_back("Hello");
	//testDb.addRow("Test", rowValues);
	//testDb.printTable("Test");
	//------------------

	//Table rename test
	//------------------
	//testDb.renameTable("Test", "renamedTable");
	//testDb.printTable("renamedTable");
	//------------------

	//Count rows in table test. 
	//------------------
	//testDb.countRowsInTable("Test", "4", 1);
	//testDb.printTable("Test");
	//------------------

	//Aggregate test. The function performs min, max, +, * operations on two cells
	//------------------
	//testDb.aggregate("Test", 1, "3", 0, "max"); 
	//------------------

	//InnerJoin test
	//------------------
	testDb.innerJoin("Best", "Test", "Pate", 0, 1); 
	testDb.printTable("Best");
	//------------------

	//Serialization and deseriolization tests
	//------------------
	//testDb.printTable("Test");
	//testDb.save("test.txt", "Test");
	//Database newDb;
	//newDb.loadTable("test.txt");
	//newDb.printTable("Test");
	//------------------


}



int main() {

	
	std::cout << R"(
 _   _  _  _     _  _       ______ ______ 
| \ | |(_)| |   (_)( )      |  _  \| ___ \
|  \| | _ | | __ _ |/  ___  | | | || |_/ /
| . ` || || |/ /| |   / __| | | | || ___ \
| |\  || ||   < | |   \__ \ | |/ / | |_/ /
\_| \_/|_||_|\_\|_|   |___/ |___/  \____/                                           
                                   
)" << '\n';
	
	
	std::cout << "Welcome please enter a command! If you want to exit write exit"<<'\n';
	std::string command = "";
	Database db;
	std::string fileName;

	while (command != "exit") {
		std::cout << "//>";
		std::cin >> command;

		if (command == "saveAs") {
			std::string tableName;
			std::cout << "Please enter file name:";
			std::cin >> fileName;
			std::cout << "Please enter table name:";
			std::cin >> tableName;
			db.save(tableName, fileName);
		} else if (command == "save") {
			std::string tableName;
			std::cout << "Please enter table name:";
			std::cin >> tableName;
			db.save(tableName, "");
		} else if (command == "open") {
			std::cout << "Please enter file name:";
			std::cin >> fileName;
			db.loadTable(fileName);
		} else if (command == "help") {
			help();
		} else if (command == "innerJoin") {
			std::string newTableName, firstTableName, secondTableName;
			int firstTableColIndex, secondTableColIndex;

			std::cout << "Please enter these parameters in this order: " <<'\n'
			<< "1) The name of the new table " << '\n'
			<< "2,3) The names of the two tables you want to inner join" << '\n'
			<< "3,4) The columns of the two tables you entered by which you will inner join. Count from zero" << '\n' << "//>"
			<< "//>";

			std::cin >> newTableName >> firstTableName >> secondTableName >> firstTableColIndex >> secondTableColIndex;
			db.innerJoin(newTableName, firstTableName, secondTableName, firstTableColIndex, secondTableColIndex);
		} else if (command == "aggregate") {
			std::string tableName, operation, searchValue;
			int searchCol, targetCol;

			std::cout << "Please enter these parameters in this order: " << '\n'
			<< "1) The table name" << '\n'
			<< "2) The index of the search column, count from zero." << '\n'
			<< "3) The value in the search column you are looking for." << '\n'
			<< "4) The target column. The operation will be performed on the values from this column. "<<'\n'
			<< "On the cells that mach the rows on which maching values were found in the search column"
			<< "5) The operation" << '\n' << "//>";

			std::cin >> tableName >> searchCol >> searchValue >> targetCol >> operation;
			std::cout << "The answer is: ";
			db.aggregate(tableName, searchCol, searchValue, targetCol, operation);
		} else if (command == "count") {
			std::string tableName, searchedValue;
			int columnIndex;

			std::cout << "Please enter these parameters in this order: " << '\n'
			<< "1) The table name" << '\n'
			<< "2) The searched value" << '\n'
			<< "3) The index column of the column you will search in" << '\n'
			<< "The function will give you the amount of rows in which the value is found in the search column" << '\n'
			<< "//>";

			std::cin >> tableName >> searchedValue >> columnIndex;
			db.countRowsInTable(tableName, searchedValue, columnIndex);
		} else if (command == "showTables") {
			db.showTables();
		} else if (command == "describe") {
			std::string tableName;
			std::cout << "Please enter the name of the table you want to describe" << '\n' << "//>";
			std::cin >> tableName;
			db.describe(tableName);
		} else if (command == "print") {
			std::string tableName;
			std::cout << "Please enter the name of the table you want to print" << '\n' << "//>";
			std::cin >> tableName;
			db.printTable(tableName);
		} else if (command == "rename") {
			std::string oldName, newName;
			std::cout << "Enter the old and then new table names" << '\n' << "//>";
			std::cin >> oldName >> newName;
			db.renameTable(oldName, newName);
		} else if (command == "addColumn") {
			std::string tableName, columnName, colType;
			std::cout << "Enter the table name in which you will add an empty column, the new column name and the new column type" <<'\n' <<"//>";
			std::cin >> tableName >> columnName >> colType;
			db.addColumn(tableName, columnName, colType);
		} else if (command == "insert") {
			std::vector<std::string> row;
			std::string tableName, rowCell;

			std::cout << "Enter the table name and the values of your row in this order. " << '\n'
			<< "If you enter too many values, this will not work. So add as many as your table size or less" << '\n'
			<< "Enter !quit(the ! is in case you want the cell to have quit as a value) to stop entering cell values" << '\n' << "//>";
			
			std::cin >> tableName;
			std::cout << "//>";
			std::cin >> rowCell;

			while (rowCell!="!quit")
			{
				row.push_back(rowCell);
				std::cout << "Value added successfully" << '\n'
				<< "//>";
				std::cin >> rowCell;
			}
			db.addRow(tableName, row);
		} else if (command == "delete") {
			std::string tableName, searchValue;
			int columnId;

			std::cout << "This command deletes rows. To do so you select a column and a value to search for!" << '\n'
			<< "If you find the value in the column, it is deleted. If not it stays!" << '\n'
			<< "Enter the parameters in this order: table name, column id, search value" << '\n' << "//>";

			std::cin >> tableName >> columnId >> searchValue;
			db.deleteRow(tableName, columnId, searchValue);
		} else if (command == "update") {
			std::string tableName, targetValue, searchValue;
			int colId, targetColId;
			std::cout << "All rows from the search column that contain the search value," << '\n'
			<< "resceive the target value in the corresponding target column." << '\n'
			<< "Enter the parameters int this order tableName, columnId, searchValue, targetColumnId, targetValue" << '\n'
			<< "Count from zero" << '\n' << "//>";
			std::cin >> tableName >> colId >> searchValue >> targetColId >> targetValue;
			db.updateCells(tableName, colId, searchValue, targetColId, targetValue);
		} else if (command == "select") {
			int col;
			std::string searchedValue, tableName;

			std::cout << "Print all rows with a certain value" << '\n'
			<< "Enter paramaters in this order: tableName, searched value, col" <<'\n'
			<< "//>";

			std::cin >>  tableName >> searchedValue >> col;
			db.dbSelect(col, searchedValue, tableName);
		} else if (command == "close") {
			std::string tableName;
			std::cin >> tableName;
			db.close(tableName);
		}
		else if (command == "addTable") {
			std::string tableName;	
			std::cout << "Enter new table name" << std::endl;
			std::cin >> tableName;
			db.addNewTable(tableName);
		} else {
			std::cout << "For help with commands write help" << '\n';
		}
	}
	

	//doubleColumntTest();
	//TableAndDbTest();

	return 0;
}

// потоци винаги се подават по референция
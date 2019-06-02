#include "Table.h"
#include <cstring>

void printX(int numberOfChars, std::string x, int numberOfTimes) {
	for (int i = numberOfChars - 1; i < numberOfTimes; i++) {
		std::cout << x;
	}
}

void clearScreen() {
	std::cout << std::endl << std::endl << std::endl << std::endl << std::endl << std::endl
	<< std::endl << std::endl << std::endl << std::endl << std::endl << std::endl;
}

double minimum(double x, double y) {
	if (x <= y) { return x; }
	return y;
}

double maximum(double x, double y) {
	if (x >= y) { return x; }
	return y;
}

ColumnTemplate * factoryType(std::string type) {
	
	if (type == "int") {
		return new IntColumn();
	} else if (type == "double") {
		return new DoubleColumn();
	} else if (type == "string") {
		return new StringColumn();
	}
	return nullptr;
}

void Table::copy(const char * newName, ColumnTemplate ** newCol, int newCapacity, int newNumOfCol, std::string sourceFile) {
	
	this->sourceFile = sourceFile;

	this->name = new char[strlen(newName) + 1];
	strcpy_s(this->name, strlen(newName) + 1 ,newName);
	
	this->columns = new ColumnTemplate * [newCapacity];

	if (newCol != nullptr) {
		for (int i = 0; i < newNumOfCol; i++) {
			this->columns[i] = newCol[i]->clone();
		}
	}

	this->capacity = newCapacity;
	this->numOfCol = newNumOfCol;
}

Table::Table()
{
	this->sourceFile = "";
	this->name = nullptr;
	this->columns = new ColumnTemplate * [10];
	this->capacity = 10;
	this->numOfCol = 0;
}

Table::Table(const char * _name, ColumnTemplate ** _columns, int _capacity, int _numOfCol, std::string _sourceFile) {
	this->copy(_name, _columns, _capacity, _numOfCol, _sourceFile);
};

Table::Table(Table const & other){
	this->copy(other.name, other.columns, other.capacity, other.numOfCol, other.sourceFile);
}

Table::~Table()
{
	this->destroy();
}

Table& Table::operator=(Table const & other) {
	
	if (this != &other) {
		this->destroy();
		this->copy(other.name, other.columns, other.capacity, other.numOfCol, other.sourceFile);
	}

	return *this;
}

void Table::destroy() {
	if (this->name != nullptr) {
		delete[] this->name;
		this->name = nullptr;
	}

	if (this->columns != nullptr) {
		
		for (size_t i = 0; i < this->numOfCol; i++)
		{
			delete[] this->columns[i];
		}

		delete[] this->columns;
		this->columns = nullptr;
	}
}

int Table::getSize() const {
	return this->numOfCol;
}

char * Table::getName() const {
	return this->name;
}

void Table::setName(std::string newName) {
	delete[] this->name;
	this->name = new char[newName.size() + 1];
	strcpy_s(this->name, newName.size() + 1,newName.c_str());
}

ColumnTemplate ** Table::getColumns() const {
	return this->columns; 
}

void Table::getColumnTypes() const {
	
	for (int i = 0; i < this->numOfCol; i++) {
		this->columns[i]->printType();

		if (i + 1 != this->numOfCol) { std::cout << "| "; }
		if (i != 0 && i % 2 == 0) { std::cout << std::endl; }
	}

	std::cout << std::endl;
}

void Table::tableSelect(int column, std::string searchedValue) const {
	std::vector<int> rowIndexes = this->columns[column]->searchColumn(searchedValue);
	
	this->printColumnNames();
	for (int i = 0; i < rowIndexes.size(); i++) {
		this->printRow(rowIndexes[i]);
	}
}


void Table::countRows(int columnId, std::string searchedValue) {
	std::vector<int> rowIndexes = this->columns[columnId]->searchColumn(searchedValue);
	std::cout << "The number of rows with this value is: " << rowIndexes.size() << std::endl;
}

void Table::aggregate(int searchColumnId, std::string searchValue, int targetColumnId, std::string operation) {
	if (this->columns[targetColumnId]->getType() == "string") {
		std::cout << "The target column is of type string. The operation can not work" << std::endl;
		return; 
	}
	
	std::vector<int> rowIndexes = this->columns[searchColumnId]->searchColumn(searchValue);
	
	if (operation == "sum") {
		this->columns[targetColumnId]->accumulate([](double x, double y) { return x + y; }, 0, 0, rowIndexes);
	}
	else if (operation == "product") {
		this->columns[targetColumnId]->accumulate([](double x, double y) { return x * y; }, 1, 0, rowIndexes);
	}
	else if (operation == "max") {
		this->columns[targetColumnId]->accumulate(maximum, -DBL_MAX, 0, rowIndexes);
	}
	else if (operation == "min") {
		this->columns[targetColumnId]->accumulate(minimum, DBL_MAX, 0, rowIndexes);
	}
	else { 
		std::cout << "The operation input is invalid. Take care commands are case sensitive." << std::endl;
		std::cout<<"Write them as sum, max, min, product!" << std::endl; 
	}
};

void Table::updateCells(int columnId, std::string searchValue, int targetColumnId, std::string targetValue) {
	if (columnId >= this->numOfCol) return;

	std::vector<int> rowIndexes = this->columns[columnId]->searchColumn(searchValue);
	this->columns[targetColumnId]->setExtistingCell(rowIndexes, targetValue);
}

void Table::serialize(std::ostream& out) const {
	out << "Table " << strlen(this->name) + 1 << " " << this->name << " " << this->capacity << " " << this->numOfCol << " ";
	for (size_t i = 0; i < this->numOfCol; i++)
	{
		this->columns[i]->serialize(out);
	}
	out << "TableEnd ";
}

std::string Table::getFileName() const {
	return this->sourceFile;
}

void Table::deserialize(std::istream& in, std::string sourceFile) {
	
	this->sourceFile = sourceFile;

	std::string fileData;
	int nameSize;

	in >> nameSize;
	
	this->name = new char[nameSize];

	in >> this->name
	>> this->capacity
	>> this->numOfCol;
	
	this->columns = new ColumnTemplate * [this->capacity];

	int i = 0;

	while (in >> fileData && fileData != "TableEnd")
	{
		if (fileData == "Column") {
			in >> fileData;
			this->columns[i] = factoryType(fileData);
			this->columns[i]->deserialize(in);
		}
		i++;
	}
}

int Table::getMaxColumnSize() {

	int max = this->columns[0]->getSize();
	for (size_t i = 1; i < this->numOfCol; i++)
	{
		if (max < this->columns[i]->getSize()) {
			max = this->columns[i]->getSize();
		}
	}

	return max;
}

void Table::addRow(std::vector<std::string> rowValues) {
	
	if (this->numOfCol < rowValues.size()) { 
		std::cerr << "You have entered too many values. Your table is not big enough. Add more columns or enter less values!" <<std::endl;
		return; 
	};

	int maxColSize = this->getMaxColumnSize();

	std::cout << std::endl;
	for (size_t i = 0; i < this->numOfCol; i++)
	{
		this->columns[i]->addCell(maxColSize, rowValues[i]);
	}

}

void Table::deleteRow(int columnId, std::string searchValue) {
	if (columnId >= this->numOfCol) return;
	
	std::vector<int> rowIndexes = this->columns[columnId]->searchColumn(searchValue);
	if (!rowIndexes.empty()) {
		for (int i = 0; i < this->numOfCol; i++) {
			this->columns[i]->deleteCells(rowIndexes);
		}
	}

}

void Table::addColumnSupportFunction(ColumnTemplate * newCol) {

	if (this->numOfCol < this->capacity) {
		this->columns[this->numOfCol - 1] = newCol;
		return;
	}

	this->capacity = this->capacity * 2;

	ColumnTemplate ** otherColumns = new ColumnTemplate *[this->capacity];

	for (int i = 0; i < this->numOfCol; i++) {
		otherColumns[i] = this->columns[i];
	}

	otherColumns[this->numOfCol - 1] = newCol;
	this->destroy();
	this->columns = otherColumns;
}

void Table::addColumn(std::string colName, std::string colType) {
	
	if (colType == "double") {
		this->addColumnSupportFunction(new DoubleColumn(0, colName, ++this->numOfCol, colType, std::vector<double>()));
	}
	else if (colType == "int") {
		this->addColumnSupportFunction(new IntColumn(0, colName, ++this->numOfCol, colType, std::vector<int>()));
	}
	else {
		this->addColumnSupportFunction(new StringColumn(0, colName, ++this->numOfCol, colType, std::vector<std::string>()));
	}
}

void Table::printRow(int rowIndex) const {
	for (int j = 0; j < this->numOfCol; j++) {
		std::cout << "|";
		if (rowIndex < this->columns[j]->getSize()) {

			this->columns[j]->printCell(rowIndex);
			printX(this->columns[j]->numOfDigitsCharacters(rowIndex), " ", 10);
		}
		else {
			printX(0, " ", 10);
		}
	}
	std::cout << "|" << std::endl;
	printX(0, "-", 12 * this->numOfCol + 1); // the plus one is for beauty. It looks nicer with it
	std::cout << std::endl;
}


void Table::printColumnNames() const {

	for (int i = 0; i < this->numOfCol; i++) {
		std::cout << "|" << this->columns[i]->getName();
		printX(this->columns[i]->getName().size(), " ", 10);
	}

	std::cout << "|" << std::endl;
	printX(0, "-", 12 * this->numOfCol + 1); // the plus one is for beauty. It looks nicer with it
	std::cout << std::endl;
}

void Table::print() const {
	
	int pageSelector = 1;
	std::string command = "";

	while (command != "quit") {
		
		if (command == "next") { pageSelector++; }
		if (command == "prev" && pageSelector != 1) { pageSelector--; }
		
		clearScreen();
		this->printColumnNames();
		for (int i = 12 * (pageSelector - 1); i < pageSelector * 12; i++) {
			this->printRow(i);
		}

		std::cout << "These are the first ten rows of this table. If you to continue to the next page write next. "
		<< "If you to go back to the previous page write prev. "
		<< "If you want to exit enter quit"<<std::endl;	

		do {
			std::cout << "//>";
			std::cin >> command;
		} while (command != "next" && command != "prev" && command != "quit");

	}
}

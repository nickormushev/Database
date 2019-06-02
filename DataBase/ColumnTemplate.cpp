#pragma once
#include <iostream>
#include <string>

#include "ColumnTemplate.h"


void ColumnTemplate::setName(std::string newColumnName) {
	this->columnName = newColumnName;
}

int ColumnTemplate::getSize() const {
	return this->columnSize;
}

void ColumnTemplate::setSize(int colSize) {
	this->columnSize = colSize;
};

std::string ColumnTemplate::getName() const {
	return this->columnName;
}

std::string ColumnTemplate::getType() const {
	return this->columnType;
}

void ColumnTemplate::printType() const {
	std::cout << "The type of the column with a name: " << this->columnName << " is " << this->columnType << ". ";
};

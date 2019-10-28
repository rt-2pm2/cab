/**
 * @file datastorage.cpp
 * @author Luigi Pannocchi
 */

#include "datastorage.hpp"


DataStorage()::DataStorage(Record* p, int nrow, int ncol, int type) : 
	data(nrow, ncol, type) 
{
	parent = p;
}

void DataStorage::load() {
	return;
};

void DataStorage::getData() {
	return
}

Record* DataStorage::getParent() {
	return parent;
}


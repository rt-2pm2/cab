/**
 * @file datastorage.cpp
 * @author Luigi Pannocchi
 */

#include "datastorage.hpp"


DataStorage::DataStorage(Record* p){
	parent = p;
}


Record* DataStorage::getParent() {
	return parent;
}


ImgStorage::ImgStorage(Record* pR, int id) : DataStorage(pR) {
	imgData.camId = id;
}

void ImgStorage::loadData(void * d) {

	imgDataStr& data = (imgDataStr&) d;

	data.leftImage.copyTo(imgData.leftImage);
	data.rightImage.copyTo(imgData.rightImage);
	imgData.camId = data.camId;
	imgData.timestamp = data.timestamp;

	return;
};

void* ImgStorage::getData() {	
	return (void *) &imgData;
}


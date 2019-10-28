/**
 * @file cab.hpp
 * @author Luigi Pannocchi
 *
 */
#pragma once
#include <pthread.h>
#include <opencv2/core/mat.hpp>
#include "datastorage.hpp"


struct Record;


/**
 * Single record data structure.
 */
struct Record {	
	Record* next;
	DataStorage* pData;
	int readers;

	// Constructor
	Record(int id):
		readers(0), 
		next(NULL) {
			pData = new ImgStorage(this, id); 
		};
};


class CAB {
	public:
		CAB(int num, int id);
		Record* free_;
		Record* mrr_;

		/**
		 * Return a pointer to the data class 
		 * to write into.
		 */
		DataStorage* reserveRecordWR();
		void releaseRecordWR(DataStorage* pBD); 

		DataStorage* reserveRecordRD();
		void releaseRecordRW(DataStorage* bdp);

		void insertData(imgDataStr d);


	private:
		bool active_writer_;
		pthread_mutex_t cab_mx_;

};

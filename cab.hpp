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
	Record(int nrow, int ncol, int type):
		readers(0), 
		next(NULL) {
			pData = new DataStorage(this, nrow, ncol, type); 
		};
};


class CAB {
	public:
		CAB(int n);
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

		void insertData(cv::Mat data);


	private:
		bool active_writer_;
		pthread_mutex_t cab_mx_;

};

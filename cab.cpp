#include "cab.hpp"

CAB::CAB(int nRecords) {
	// Initialize mutex
	pthread_mutex_init(&cab_mx_, NULL);
	active_writer_ = false;
	mrr_ = NULL;

	// Create the list of Records
	Record* currentRec = new Record(10, 10, CV_8U);
	for (int i = 0; i < nRecords; i++) {
		if (i == 0) 
			free_ = currentRec;
		else {
			currentRec->next = new Record(10, 10, CV_8U);
			currentRec = currentRec->next;
		}
	}
}


DataStorage* CAB::reserveRecordRD() {
	pthread_mutex_lock(&cab_mx_);
	mrr_->readers++;
	pthread_mutex_unlock(&cab_mx_);

	return mrr_->pData;
}

DataStorage* CAB::reserveRecordWR() {
	pthread_mutex_lock(&cab_mx_);
	active_writer_ = true;
	
	active_writer_ = true;	
	// Take a pointer to the free space, 
	// reserve it and update the free space
	// pointer.
	//
	Record* pR = free_;
	free_ = pR->next;
	pthread_mutex_unlock(&cab_mx_);

	return pR->pData;
}


void CAB::insertData(cv::Mat data) {	
	pthread_mutex_lock(&cab_mx_);
	active_writer_ = true;	
	// Take a pointer to the free space, 
	// reserve it and update the free space
	// pointer.
	//
	Record* pR = free_;
	free_ = pR->next;
	pthread_mutex_unlock(&cab_mx_);

	// Load the data in memory.
	pR->pData->load(data);

	// Update the MRR
	pthread_mutex_lock(&cab_mx_);
	active_writer_ = false;

	// If the MRR is not used, recycle it. 
	if (mrr_ != NULL && mrr_->readers == 0) {
		mrr_->next = free_;
		free_ = mrr_;
	}
	mrr_ = pR;
	pthread_mutex_unlock(&cab_mx_);

	return;
}


void CAB::releaseRecordWR(DataStorage* pBD) {
	// Update the MRR
	pthread_mutex_lock(&cab_mx_);
	active_writer_ = false;
	// If the MRR is not used, recycle it. 
	if (mrr_->readers == 0) {
		mrr_->next = free_;
		free_ = mrr_;
	}
	mrr_ = pBD->getParent();
	pthread_mutex_unlock(&cab_mx_);

	return;
}


void CAB::releaseRecordRW(DataStorage* pBD) {
	// Take the reference to the 
	// Record containing the data.
	Record* rc = pBD->getParent();

	pthread_mutex_lock(&cab_mx_);
	// Update the counter of reader of the Record
	rc->readers--;
	if (rc->readers == 0 && rc != mrr_) {
			rc->next = free_;
			free_ = rc;
	}
	pthread_mutex_lock(&cab_mx_);
}

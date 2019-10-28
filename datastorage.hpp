/**
 * @file datastorage.hpp
 * @author Luigi Pannocchi
 *
 */
#pragma once
#include <pthread.h>
#include <opencv2/core/mat.hpp>

struct Record;

/**
 * Data storage class.
 * Temporary I hardcoded the data type.
 */
class DataStorage {
	private:
		int size;
		Record* parent;

	public:
		// Constructor
		DataStorage(Record* p);	

		// Load
		virtual void load();

		// GetData
		virtual void getData();
		
		// Get pointer to Parent Record
		Record* getParent();
};



/**
 * Data structure for stereo camera image pair
 * 
 * camId       : integer ID # (Front Left Pair=0, Front Right Pair=1, Bottom Pair=2 ) 
 * leftImage   : cv::Mat file containing left image from stereo camera pair
 * rightImage  : cv::Mat file containing right image from stereo camera pair
 * timestamp   : timestamp of the image reading
 * mx          : mutex for access the structure
 *
 */
struct imgDataStr{
	// ONLY IMAGE CLASS
	//Contains stereo pair
	//Different class for each camera
	int camId;
	cv::Mat leftImage;
	cv::Mat rightImage;

	// Used to get timestamp in timespec format
	// Now it's in long ints of microseconds (or nanoseconds on the sim)
	uint64_t timestamp;
    std::mutex mx;    
};

/** 
 * Class wrapper for image data
 */
class imgHandler : DataStorage {
private: 
	imgDataStr imgData;

public:
    imgHandler(int idNum, Record* pR);
    ~imgHandler();

    /**
    * Update the image data to the class with uint64_t timestamps
    */
    void updateImgPair(
			cv::Mat& newImgLeft, 
			cv::Mat& newImgRight, 
			uint64_t newTime);

    /**
     * Get the image data, return to calling function
     */
    void getImgPair(cv::Mat& imgLeft,
			cv::Mat& imgRight,
			uint64_t& storedTime);

    /**
     * Get cam ID
     */
    int getCamId();
};

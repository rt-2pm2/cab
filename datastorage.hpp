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
		virtual ~DataStorage();

		// Load (to be defined in the Child)
		virtual void loadData(void *) = 0;

		// GetData (to be defined in the Child)
		virtual void* getData() = 0;
		
		// Get pointer to Parent Record
		Record* getParent();
};



/**
 * Data structure for stereo camera image pair
 * 
 * camId       : int ID # (Front Left Pair=0, Front Right Pair=1, Bottom Pair=2 ) 
 * leftImage   : cv::Mat file containing left image from stereo camera pair
 * rightImage  : cv::Mat file containing right image from stereo camera pair
 * timestamp   : timestamp of the image reading
 *
 */
struct imgDataStr{
	int camId;
	cv::Mat leftImage;
	cv::Mat rightImage;

	uint64_t timestamp;
};


/** 
 * Class wrapper for image data
 */
class ImgStorage : public DataStorage {
private: 
	imgDataStr imgData;

public:
    ImgStorage(Record* pR, int idNum);
    ~ImgStorage();

    /**
    * Load the data into the Storage copying the content.
	* 
	*/
    void loadData(void *);

    /**
     * Get the reference to the image data.
     */
    void* getData();

    /**
     * Get cam ID
     */
    int getCamId();
};

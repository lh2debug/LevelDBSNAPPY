#ifndef MEM_H_
#define MEM_H_

#include <sstream>
#include <iostream>
#include <string>
#include <stdexcept>
#include <cassert>
#include <cstdlib>
#include <vector>
#include <fstream>

using std::string;
using std::cout;
using std::ifstream;
using std::ofstream;
using std::logic_error;
using std::vector;
using std::runtime_error;
using std::stringstream;

class MemcacheFile {
public:
	MemcacheFile(int filenum, string mode);

	inline string Iter(){
		assert(Valid());
		return keys_[index_++];
	}

	inline bool Valid(){
		if (mode_ != "r")
			throw logic_error("Function Iter and Valid only can be used in read mode!");
		return !keys_.empty() && (index_ >= 0) && (index_ < keys_.size());
	}


	inline void Put(string k){
		if (mode_ != "w")
			throw logic_error("Function Update only can be used in write mode!");
		keys_.push_back(k);
	}

	~MemcacheFile();

private:
	vector<string> keys_;
	int index_;
	int file_num_;
	string mode_; // "w" means write mode "r" means read mode
	static string pathname_;

	void LoadFile();

	void SaveFile();

};

class MemFile{
public:
	static MemFile* getInstance(){
		if (NULL == instance_)
			instance_ = new MemFile();
		return instance_;
	}
	static void resetInstance(){
                assert(instance_ != NULL);
		instance_->index_ = 0;
	}
	bool Valid(){
		return !keys_.empty() && (index_ >= 0) && (index_ < keys_.size());
	}

	inline int Iter(){
		assert(Valid());
		return keys_[index_++];
	}

private:
	static MemFile* instance_;
	static string pathname_;
	vector<int> keys_;
	int index_;
	MemFile();
};




#endif

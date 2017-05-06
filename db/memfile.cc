#include "memfile.h"

string MemcacheFile::pathname_ = "/home/lh2debug/lhh/test_files/";
string MemFile::pathname_ = "/home/lh2debug/lhh/test_files/data.txt";
MemFile* MemFile::instance_ = NULL;

MemcacheFile::MemcacheFile(int filenum, string mode) :
	file_num_(filenum), mode_(mode){

	keys_.clear();
	if (mode_ == "r"){
		LoadFile();
		index_ = (keys_.empty()) ? -1 : 0;
	}
	else if (mode_ == "w"){

	}
	else
		throw logic_error("Wrong mode! Mode only can be r or w!");

}

MemcacheFile::~MemcacheFile() {
	if (mode_ == "w"){
		SaveFile();
	}
}

void MemcacheFile::LoadFile() {
	stringstream ss;
	ss << file_num_;
	string filename = pathname_ + ss.str() + ".bpf";
	ifstream fin(filename);
	if (!fin)
		throw runtime_error(string("cannot open file ") + filename);
	string k;
	while (fin >> k)
		keys_.push_back(k);
}

void MemcacheFile::SaveFile(){
	stringstream ss;
	ss << file_num_;
	string filename = pathname_ + ss.str() + ".bpf";
	ofstream fout(filename, std::ios::out);
	for (auto& k : keys_){
		fout << k << " ";
	}
}



MemFile::MemFile() :
	index_(0){
	keys_.clear();
	ifstream fin(pathname_);
		if (!fin)
		throw runtime_error(string("cannot open file ") + pathname_);
	int k;
	while (fin >> k)
		keys_.push_back(k);
}



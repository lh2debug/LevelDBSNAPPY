#ifndef DBSTAT_H_
#define DBSTAT_H_

#include <vector>
#include <iostream>
#include <sstream>
#include <string>
#include "version_set.h"
#include "port/port_posix.h"

namespace leveldb{


using std::ostream;
using std::endl;
using std::vector;
using std::string;
using std::stringstream;

class DBStat{
  public:
    static void PrintDiskSpace(const string& message, ostream& os);

    static void PrintLevelSstNum(ostream& os);

    static void PrintCompactDeleteKeyPercent(ostream& os);

    static void PrintTrivialMoveNum(ostream& os);

    static VersionSet* vset_;
    
    // print distribution of file nums in low_level and high_level when compacting
    static void PrintCompactResult(std::ostream&);

    // update lh_compact_times, level_compact_times and so on.
    static void UpdateWhileCompact(int ll_num, int hl_num, int level);

    // update while addfile in the compaction
    static void UpdateWhileWriteFile(int level);

    static void UpdateWhileIterKeyInCompact(Iterator* iter, bool drop);

    static void UpdateWhileTrivialMove(int level);

    static void UpdateStatIOWhileIterKey(bool isDrop, bool isDel, string key);

    static void PrintDelCompactIO(std::ostream&);

    static bool isOldKey(string&);

    static void Clear();

    static int flag_file_index_;

    static bool flag_key_range_same_;

   private:

    static int trivialmove_level;    

    static int trivialmove_num[100];

    static long long int deleted_key_num;

    static long long int all_key_num;

    static long long int all_kv_num;

    static long long int deleted_kv_num;

    static long long int del_key_io;

    static long long int trush_io;

    // ll_num + hl_num compact times
    static int lh_compact_times[100][100];
    // max ll_num
    static int ll_max;
    // max hl_num
    static int hl_max;
    // max level
    static int level_max;
    // level compact time
    static int level_compact_times[100];

    // number of level file reads and writes when compaction 
    static int level_read_file_nums[100];
    static int level_write_file_nums[100];
    static int64_t diskspace_; // byte unit
    static int64_t ComputeDiskSpaceToken(Version* version);

};



}

#endif

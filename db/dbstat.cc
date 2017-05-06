#include "dbstat.h"
#include "db/dbformat.h"
#include <cstring>
#include <iostream>

namespace leveldb{

long long int DBStat::deleted_key_num = 0;
long long int DBStat::all_key_num = 0;
int DBStat::trivialmove_num[100] = {0};
int DBStat::trivialmove_level = -1;
long long int DBStat::trush_io = 0;
long long int DBStat::del_key_io = 0;
int DBStat::flag_file_index_ = -1;
bool DBStat::flag_key_range_same_ = true;

long long int DBStat::all_kv_num = 0;
long long int DBStat::deleted_kv_num = 0;


int64_t DBStat::diskspace_ = 0;
VersionSet* DBStat::vset_ = NULL;

void DBStat::UpdateStatIOWhileIterKey(bool isDrop, bool isDel, string key){
  if (isDrop){
    if (isDel){
      del_key_io += key.size();
    } else if (isOldKey(key)) {
      trush_io += key.size() + 100;
    }
  } else {
    if (isDel) {
      del_key_io += 2 * key.size();
    } else if (isOldKey(key)){
      trush_io += (key.size() + 100) * 2;
    }
  }

}

bool DBStat::isOldKey(string& key){
  long long int number;
  stringstream ss;
  ss << key;
  ss >> number;
  if (flag_key_range_same_){
    number /= 100;
    number = number % 1000;
  } else {
    number /= 100000000000000;
  }
  return number <= flag_file_index_;

}

void DBStat::PrintDelCompactIO(ostream& os){
  os << "del key io is " << del_key_io / 1.0 / 1024 / 1024 << " MB" << endl;
  os << "trush io is " << trush_io / 1.0 / 1024 / 1024 << " MB" << endl;
}

int64_t DBStat::ComputeDiskSpaceToken(Version* version){
  diskspace_ = 0;
  for (int level = 0;level < config::kNumLevels;++level){
    for (int index = 0;index < version->files_[level].size();++index){
      diskspace_ += (version->files_[level][index])->file_size;
    }
  }
  return diskspace_;
}

void DBStat::PrintTrivialMoveNum(ostream& os){
  for (int i=0;i<=trivialmove_level;++i){
    os << "Level " << i << " trivialmove num is " << trivialmove_num[i] << endl;
  }
}

void DBStat::UpdateWhileTrivialMove(int level){
  if (level > trivialmove_level) trivialmove_level = level;
  trivialmove_num[level]++;
}

void DBStat::PrintDiskSpace(const string& message, ostream& os){
  Version* version = vset_->current();
  os << message << " The disk space token is " 
     << ComputeDiskSpaceToken(version) / 1048576.0
     << " MB"
     << endl;
}

void DBStat::PrintLevelSstNum(ostream& os){
  Version* version = vset_->current();
  for (int level=0;level < config::kNumLevels;++level)
    if (version->files_[level].size() != 0)
      os << "Level " << level << " has " << version->files_[level].size() << " sstable." << endl;
}



void DBStat::UpdateWhileIterKeyInCompact(Iterator* iter, bool drop){
  int key_size = iter->key().ToString().size();
  int value_size = iter->value().ToString().size();

  all_kv_num += key_size + value_size;
  all_key_num += key_size;
  if (drop){
    deleted_kv_num += key_size + value_size;
    deleted_key_num += key_size; 
  }
  
}

void DBStat::PrintCompactDeleteKeyPercent(ostream& os){
  double key_percent = deleted_key_num / 1.0 / all_key_num * 100;
  double kv_percent = deleted_kv_num / 1.0 / all_kv_num * 100;
  os << "The percent of deleted key size in compaction is " << key_percent << "%" << endl; 
  os << "The percent of deleted key-value size in compaction is " << kv_percent << "%" << endl;
}

int DBStat::lh_compact_times[100][100] = {0};
int DBStat::hl_max = -1;
int DBStat::ll_max = -1;
int DBStat::level_max = -1;
int DBStat::level_compact_times[100] = {0};
int DBStat::level_read_file_nums[100] = {0};
int DBStat::level_write_file_nums[100] = {0};

void DBStat::Clear(){
  memset(lh_compact_times, 0, sizeof(int) * 100 * 100);
  memset(level_compact_times, 0, sizeof(int) * 100);
  memset(level_write_file_nums, 0, sizeof(int) * 100);
  memset(level_read_file_nums, 0, sizeof(int) * 100);
  memset(trivialmove_num, 0, sizeof(int) * 100);
  trivialmove_level = -1;
  hl_max = -1;
  ll_max = -1;
  level_max = -1;
  deleted_key_num = 0;
  all_key_num = 0;
  deleted_kv_num = 0;
  all_kv_num = 0;
  del_key_io = 0;
  trush_io = 0;
}

void DBStat::UpdateWhileCompact(int ll_num, int hl_num, int level){
  if (hl_num > hl_max) hl_max = hl_num;
  if (ll_num > ll_max) ll_max = ll_num;
  if (level > level_max)  level_max = level;
  lh_compact_times[ll_num][hl_num]++;
  level_compact_times[level]++;
  level_read_file_nums[level] += ll_num;
  level_read_file_nums[level + 1] += hl_num;
}

void DBStat::PrintCompactResult(std::ostream &os){
  
  // print hl_num+ll_num times
  for (int i = 0; i <= ll_max; i++){
      for (int j = 0; j < hl_max; j++){
      if (lh_compact_times[i][j] == 0) continue;
      os << i << "+" << j << " compaction times: " << lh_compact_times[i][j] << std::endl;
    }
  }
  
  for (int i = 0;i < level_max + 1;++i){
    os << "Level " << i << " compact times: " << level_compact_times[i] << std::endl;
    os << "Level " << i << " read file nums: " << level_read_file_nums[i] << std::endl; 
    os << "Level " << i << " write file nums: "<< level_write_file_nums[i] << std::endl;
  }
}

void DBStat::UpdateWhileWriteFile(int level){
  level_write_file_nums[level]++;
  if (level > level_max) level_max = level;
}


}

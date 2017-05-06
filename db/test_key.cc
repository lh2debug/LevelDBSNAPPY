#include <sstream>
#include <iostream>
#include <string>
#include <stdexcept>
#include <cassert>
#include <cstdlib>
#include <vector>
#include <stdint.h>
#include <fstream>
#include <string.h>
#include "memfile.h"

#define TEST_TIME 10
#define KEY_RANGE 10000000
#define FILE_NUM 27

using namespace std;

class Random {
 private:
  uint32_t seed_;
 public:
  explicit Random(uint32_t s) : seed_(s & 0x7fffffffu) {
    // Avoid bad seeds.
    if (seed_ == 0 || seed_ == 2147483647L) {
      seed_ = 1;
    }
  }
  uint32_t Next() {
    static const uint32_t M = 2147483647L;   // 2^31-1
    static const uint64_t A = 16807;  // bits 14, 8, 7, 5, 2, 1, 0
    // We are computing
    //       seed_ = (seed_ * A) % M,    where M = 2^31-1
    //
    // seed_ must not be zero or M, or else all subsequent computed values
    // will be zero or M respectively.  For all other values, seed_ will end
    // up cycling through every number in [1,M-1]
    uint64_t product = seed_ * A;

    // Compute (product % M) using the fact that ((x << 31) % M) == x.
    seed_ = static_cast<uint32_t>((product >> 31) + (product & M));
    // The first reduction may overflow by 1 bit, so we may need to
    // repeat.  mod == M is not possible; using > allows the faster
    // sign-bit-based test.
    if (seed_ > M) {
      seed_ -= M;
    }
    return seed_;
  }
  // Returns a uniformly distributed value in the range [0..n-1]
  // REQUIRES: n > 0
  uint32_t Uniform(int n) { return Next() % n; }

  // Randomly returns true ~"1/n" of the time, and false otherwise.
  // REQUIRES: n > 0
  bool OneIn(int n) { return (Next() % n) == 0; }

  // Skewed: pick "base" uniformly from range [0,max_log] and then
  // return "base" random bits.  The effect is to pick a number in the
  // range [0,2^max_log-1] with exponential bias towards smaller numbers.
  uint32_t Skewed(int max_log) {
    return Uniform(1 << Uniform(max_log + 1));
  }
};


void swap_char(char* a, char* b){
  char tmp = *a;
  *a = *b;
  *b = tmp;
}

struct StatUtil {
  static int cycle_;
  static int cnt_;
  static char* bmark_;
  static int file_index_;
  static void GenerateKey(char key[], int file_num){
    int len = strlen(key);
    snprintf(key, 4,"%03d", file_num);
    key[3] = '0';
    swap_char(key, key + len - 3);
    swap_char(key + 1, key + len - 2);
    swap_char(key + 2, key + len - 1);
  }

};

int StatUtil::cycle_ = 3;
int StatUtil::cnt_ = 10;
int StatUtil::file_index_ = 0;
char* StatUtil::bmark_ = NULL;


int main(){
  Random rand(1000);
  /*
  for (int i = 0;i < TEST_TIME;++i){
    const int old_k = rand.Next() % KEY_RANGE;
    if (old_k < 0){
      cout << "old_k "<< old_k << endl;
      throw runtime_error("Old_key is less than zero!");
    }
    const int k = StatUtil::GenerateKey(old_k, FILE_NUM);
    if (FILE_NUM != k % StatUtil::timestampsize_){
      cout << "old_k "<< old_k << endl;
      cout << "k " <<  k << endl;
      throw runtime_error("Key is not seted in right way!");
    }
    if (k < 0) {
      cout << "old_k " << old_k;
      cout << "k " <<  k << endl;
      throw runtime_error("Key is less than zero!");
    }
  }
  */
  MemcacheFile* f = new MemcacheFile(0, "w");
  for (int i = 0;i < TEST_TIME;++i){
    const int k = rand.Next() % KEY_RANGE;
    char key[100];
    snprintf(key, sizeof(key), "%016d", k);
    StatUtil::GenerateKey(key, FILE_NUM);
    f->Put(key);
  }
  delete f;
  return 0;
}

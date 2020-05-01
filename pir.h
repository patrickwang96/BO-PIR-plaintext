//
// Created by Ruochen WANG on 24/4/2020.
//

#ifndef BO_PIR_PIR_H
#define BO_PIR_PIR_H

#include <bitset>
#include <vector>
#include <unordered_map>

#define RECORD_LEN (1)
#define K 16
#define L (K/2)
#define RECORD_COUNT (1024 * 1024)
#define NUM_TRAIL 5

typedef std::bitset<RECORD_LEN> Record;

typedef std::vector<Record> RecordSet;

typedef uint64_t u64;
typedef uint32_t u32;
typedef uint8_t u8;

std::vector<int> genS(RecordSet &db);

RecordSet genHints(const std::vector<int> &S, RecordSet &db);

RecordSet preprocessing(RecordSet &db);

//RecordSet query(u64 u);

std::vector<int> query(u64 u, std::vector<int> &S, int &hint_index);

Record answer(std::vector<int> s, RecordSet &db);

Record decode(Record a);

std::vector<RecordSet> genLHintSets(RecordSet &db, int l, std::vector<std::vector<int>> &S_list);

std::vector<std::vector<int>>
queryLSets(int l, std::vector<int> u, std::vector<std::vector<int>> &S_list);

RecordSet genDb(int n);

#endif //BO_PIR_PIR_H

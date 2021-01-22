#pragma once
#include <vector>
#include <string>
#include <bitset>
#include <random>
#include <iostream>
#include <chrono>
#include <ctime>

using vector = std::vector<double>;
using vec_it = vector::iterator;

std::string toBinary(unsigned long long n) {
  return std::bitset<64>(n).to_string();
}

// helper vector
double fRand(double fMin, double fMax) {
  double f = (double)rand() / RAND_MAX;
  return fMin + f * (fMax - fMin);
}
void fillRandomVec(vector& vec) {
  for (auto i = 0; i < vec.size(); ++i) {
    //std::bitset<64> tmp;
    //for (int j = 0; j < 64; ++j) tmp[j] = rand() % 2;
    //unsigned long long tmp_ull = tmp.to_ullong();
    //vec[i] = (double&)tmp_ull;

    vec[i] = fRand(DBL_MIN, DBL_MAX);
  }
}
void printVec(vector& vec) {
  for (auto i : vec) std::cout << i << std::endl;
  std::cout << std::endl;
}
bool isSortedVec(vector & vec) {
  for (int i = 1; i < vec.size(); ++i) {
    if (vec[i - 1] > vec[i]) return false;
  }
  return true;
}

// radix
size_t isolateBits(unsigned long long n, size_t start_bit, size_t end_bit) {
  n <<= start_bit;
  n >>= end_bit;
  return n;
}
void radixSortBit(vector& cop, vec_it begin, vec_it end, size_t start_bit, size_t end_bit) {
  int ss = 1 << (end_bit - start_bit);

  std::vector<size_t> count(ss);
  //std::cout << ss << std::endl;

  size_t start_offset = 64 - end_bit, end_offset = 64 - (end_bit - start_bit);
  for (auto i = begin; i < end; ++i)
    ++count[isolateBits((unsigned long long&)(*i), start_offset, end_offset)];
  for (int i = 1; i < count.size(); ++i)
    count[i] += count[i - 1];
  for (auto i = end - 1; i >= begin; --i)
    cop[count[isolateBits((unsigned long long&)(*i), start_offset, end_offset)]-- - 1] = *i;
  for (auto i = begin, j = cop.begin(); i < end; ++i, ++j)
    *i = *j;
}
void radixSortRegion(vector& cop, vec_it begin, vec_it end, size_t start_bit, size_t end_bit, size_t chank_size = 16) {
  int i = start_bit;
  for (; i + chank_size < end_bit; i += chank_size) {
    radixSortBit(cop, begin, end, i, i + chank_size);
  }
  radixSortBit(cop, begin, end, i, end_bit);
}
void radixSort_double(vec_it begin, vec_it end, size_t chank_size = 18) {
  vector cop(end - begin);
  radixSortRegion(cop, begin, end, 0, 52, chank_size);
  radixSortRegion(cop, begin, end, 52, 64, chank_size);
  auto rev = end;
  for (auto i = begin; i < end; ++i) {
    if (*i < 0) {
      rev = i;
      break;
    }
  }
  if (rev != end) {
    std::reverse(begin, rev);
    std::reverse(begin, end);
  }
}

// qsort
void quickSort(vec_it start, vec_it end_it) {
  int size = std::distance(start, end_it);
  if (size <= 1) return;

  auto partition_idx = start;
  for (auto i = start; i != end_it; i++) {
    if (*i <= *end_it) {
      std::iter_swap(i, partition_idx);
      partition_idx++;
    }
  }

  std::iter_swap(partition_idx, end_it);
  quickSort(start, partition_idx - 1);
  quickSort(partition_idx, end_it);
}

// heap sort
void heapify(vector& arr, int i, int size_) {
  int largest, l = (2 * i) + 1, r = l + 1;

  if (l < size_ && arr[l] > arr[i])
    largest = l;
  else
    largest = i;

  if (r < size_ && arr[r] > arr[largest]) largest = r;

  if (largest != i) {
    std::swap(arr[i], arr[largest]);
    heapify(arr, largest, size_);
  }
}
void heapSort(vector& arr) {
  for (int i = (arr.size() / 2); i >= 0; i--) heapify(arr, i, arr.size());
  int cur_size = arr.size();
  for (int i = arr.size() - 1; i > 0; i--) {
    std::swap(arr[0], arr[i]);
    cur_size--;
    heapify(arr, 0, cur_size);
  }
}

// wgmlgz sort
void mergeSort(vec_it begin, vec_it end) {
  if (std::distance(begin, end) == 1) return;
  auto mid = begin + std::distance(begin, end) / 2;
  std::cout << std::distance(begin, mid) << std::endl;
  mergeSort(begin, mid);
  mergeSort(mid, end);
  std::inplace_merge(begin, mid, end);
}
void wgmlgzSort(vec_it begin, vec_it end, size_t max_mem = 1) {
  auto getMem = [&]() -> size_t {
    return std::distance(begin, end) * 8 + (1 << 18) * 4;
  };
  if (max_mem == 0 || 10 * 1024 * 1024 > max_mem) {
    std::sort(begin, end);
    return;
  }
  if (max_mem == 1 || getMem() <= max_mem) {
    radixSort_double(begin, end);
    return;
  }

  auto mid = begin + std::distance(begin, end) / 2;
  wgmlgzSort(begin, mid, max_mem);
  wgmlgzSort(mid, end, max_mem);

  std::inplace_merge(begin, mid, end);
}


#include <iostream>
#include <functional>
#include <fstream>
#include "radix.h"

//#define N 20000000

std::vector<double> vec;
std::chrono::time_point<std::chrono::system_clock> start, end;

std::ofstream csv("result.csv");

void createSpike(int mb) { std::vector<int8_t> vec(mb * 1024 * 1024); }
void log(std::string str = "") {
  std::cout << std::boolalpha;
  std::cout << str << std::endl;
  //createSpike(100);
}

void startTest(std::string sort_name) {
  log(sort_name);
  log("fill start");
  fillRandomVec(vec);
  log("fill end");

  log("sort start " + std::string(isSortedVec(vec) ? "true" : "false"));
  start = std::chrono::system_clock::now();
}
double endTest() {
  end = std::chrono::system_clock::now();
  std::chrono::duration<double> elapsed_seconds = end - start;
  log("sort end " + std::string(isSortedVec(vec) ? "true " : "false ") + std::to_string(elapsed_seconds.count()) + "s");
  log();
  return elapsed_seconds.count();
  //csv << elapsed_seconds.count() << ", ";
}

double h_sort(int N, int tests = 3) {
  std::ofstream out_file("heap_sort.csv", std::ios::app);
  vec.resize(N);
  out_file << N;
  double averange = 0;
  for (int i = 0; i < tests; ++i) {
    startTest("heap sort");
    heapSort(vec);
    auto res = endTest();
    averange += res;
    out_file << ", " << res;
  }
  out_file << std::endl;
  out_file.close();
  averange /= tests;
  return averange;
}
double q_sort(int N, int tests = 3) {
  std::ofstream out_file("quick_sort.csv", std::ios::app);
  vec.resize(N);
  out_file << N;
  double averange = 0;
  for (int i = 0; i < tests; ++i) {
    startTest("quick sort");
    quickSort(vec.begin(), vec.end());
    auto res = endTest();
    averange += res;
    out_file << ", " << res;
  }
  out_file << std::endl;
  out_file.close();
  averange /= tests;
  return averange;
}
double r_sort(int N, int tests = 3) {
  std::ofstream out_file("radix_sort.csv", std::ios::app);
  vec.resize(N);
  out_file << N;
  double averange = 0;
  for (int i = 0; i < tests; ++i) {
    startTest("radix sort");
    radixSort_double(vec.begin(), vec.end(), 18);
    auto res = endTest();
    averange += res;
    out_file << ", " << res;
  }
  out_file << std::endl;
  out_file.close();
  averange /= tests;
  return averange;
}
double w_sort(int N, int tests = 3) {
  std::ofstream out_file("wgmlgz_sort.csv", std::ios::app);
  vec.resize(N);
  out_file << N;
  double averange = 0;
  for (int i = 0; i < tests; ++i) {
    startTest("wgmlgz sort");
    wgmlgzSort(vec.begin(), vec.end(), 50 * 1024 * 1024);
    auto res = endTest();
    averange += res;
    out_file << ", " << res;
  }
  out_file << std::endl;
  out_file.close();
  averange /= tests;
  return averange;
}

void testSorts(int N) {
  log("[test start] number of Elements -> " + std::to_string(N));
  log("create start");
  vec.resize(N);
  log("create end\n");

  //for (int i = 1; i < 27; ++i) {
  //  startTest("radix " + std::to_string(i) + " bit");
  //  radixSort_double(vec.begin(), vec.end(), i);
  //  endTest();
  //}
  csv << N << ", ";
  csv << h_sort(N) << ", ";
  csv << q_sort(N) << ", ";
  csv << r_sort(N) << ", ";
  csv << w_sort(N) << std::endl;
  
  //startTest("std::qsort");
  //auto cmpFunction = [](const void* a, const void* b) -> int {
  //  if (*(double*)a > *(double*)b) return 1;
  //  else if (*(double*)a < *(double*)b) return -1;
  //  else return 0;
  //};
  //std::qsort(&vec[0], vec.size(), sizeof(double), cmpFunction);
  //endTest();
  //log("[test end] number of Elements -> " + std::to_string(N) + "\n");
}

void testRadixBits() {
  std::ofstream out_file("wgmlgz_sort.csv");
  vec.resize(10000000);
  for (int i = 1; i < 27; ++i) {
    startTest("radix " + std::to_string(i) + " bit");
    radixSort_double(vec.begin(), vec.end(), i);
    auto res = endTest();
    out_file << i << ", " << res << std::endl;
  }
  out_file.close();
}

int main() {
  testRadixBits();
  return 0;
  //fillRandomVec(v);
  //mergeSort(v.begin(), v.end());
  //std::cout << std::boolalpha <<isSortedVec(v);

    ///return 0;
  std::ofstream out_file;
  out_file.open("heap_sort.csv");
  out_file.close();
  out_file.open("quick_sort.csv");
  out_file.close();
  out_file.open("radix_sort.csv");
  out_file.close();
  out_file.open("wgmlgz_sort.csv");
  out_file.close();
  csv << "N, heap_sort, quick_sort, radix_sort, wgmlgz_sort" << std::endl;
  for (int i = 50000000; i < 20000001; i += 2000000)
    testSorts(i);
  log("end!");
  for (;;)
    ;
  //radixSort(vec);
}
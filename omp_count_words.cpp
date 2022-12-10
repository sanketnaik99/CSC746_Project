#include "likwid-stuff.h"
#include <boost/algorithm/string.hpp>
#include <chrono>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <map>
#include <omp.h>
#include <sstream>
#include <string.h>
#include <vector>

void getStats(std::map<std::string, int> &M) {

  // Declare a multimap
  std::multimap<int, std::string> MM;

  // Insert every (key-value) pairs from
  // map M to multimap MM as (value-key)
  // pairs
  for (auto &it : M) {
    MM.insert({it.second, it.first});
  }

  // Print top 5 least frequently occuring words
  auto it = MM.begin();

  std::cout << "The 5 least frequently occuring words are - " << std::endl;
  for (int i = 0; i < 5; i++) {
    std::cout << it->second << ' ' << it->first << std::endl;
    it++;
  }

  // Print top 5 most frequently occuring words
  auto it2 = MM.rbegin();
  std::cout << "\n\nThe 5 most frequently occuring words are - " << std::endl;
  for (int i = 0; i < 5; i++) {
    std::cout << it2->second << ' ' << it2->first << std::endl;
    it2++;
  }
  std::cout << "\n" << std::endl;

  return;
}

int main(int argc, char **argv) {

  // Get Input Filename from the commmand line
  std::string inputFilename = argv[1];

  std::cout << "The input filename is - " << inputFilename << std::endl;

  // Read file and store the data in vectors
  // std::vector<std::vector<std::string>> allStrings;
  std::vector<std::string> allStrings;

  std::fstream dataFile;
  dataFile.open(inputFilename, std::ios::in);

  std::cout << "Reading File..." << std::endl;

  if (dataFile.is_open()) {
    std::string currentLine;
    while (getline(dataFile, currentLine)) {
      // std::cout << "Current Line - " << currentLine << std::endl;
      allStrings.push_back(currentLine);
    }
  }

  std::cout << "Done Reading File! Total Number of Lines = "
            << allStrings.size() << std::endl;

  std::cout << "MAX NUM THREADS - " << omp_get_max_threads() << std::endl;

  // Go over every word in every line
  int numStrings = allStrings.size();

  std::map<std::string, int> wordMap;

  std::map<int, int> threadWorkCount;

  // Record Start Time
  std::chrono::time_point<std::chrono::high_resolution_clock> start_time =
      std::chrono::high_resolution_clock::now();

#pragma omp parallel
  {
#pragma omp for
    for (int i = 0; i < numStrings; i++) {

      std::string word;
      int thread_id = omp_get_thread_num();
      std::vector<std::string> result;
      boost::split(result, allStrings[i], boost::is_any_of(" "));

      for (int i = 0; i < result.size(); i++) {
        word = result[i];
        std::map<std::string, int>::iterator it = wordMap.find(word);

        if (it == wordMap.end()) {
          wordMap.insert(std::pair<std::string, int>(word, 1));
        } else {
          it->second = it->second + 1;
        }

        // Calculate the work done by each thread
        std::map<int, int>::iterator it2 = threadWorkCount.find(thread_id);
        if (it2 == threadWorkCount.end()) {
          threadWorkCount.insert({thread_id, 1});
        } else {
          it2->second = it2->second + 1;
        }
      }
    }
  }

  // Record End Time
  std::chrono::time_point<std::chrono::high_resolution_clock> end_time =
      std::chrono::high_resolution_clock::now();
  std::chrono::duration<double> elapsed = end_time - start_time;

  std::cout << "\nWord Counting Completed!\n" << std::endl;

  getStats(wordMap);

  std::cout << "\n Elapsed time is : " << elapsed.count()
            << std::setprecision(8) << " " << std::endl;

  std::cout << "\n\nWork Done by Threads - " << std::endl;

  for (auto const &t : threadWorkCount) {
    std::cout << "Thread ID - " << t.first << " | Total Number of words - "
              << t.second << std::endl;
  }

  std::cout << "\n\n" << std::endl;
  return 0;
}
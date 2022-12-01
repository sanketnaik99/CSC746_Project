#include <chrono>
#include <iomanip>
#include <fstream>
#include <iostream>
#include <vector>
#include <string.h>
#include <sstream>
#include <iterator>
#include <map>
#include <omp.h>
#include "likwid-stuff.h"


void getStats(std::map<std::string, int>& M)
{
  
    // Declare a multimap
    std::multimap<int, std::string> MM;
  
    // Insert every (key-value) pairs from
    // map M to multimap MM as (value-key)
    // pairs
    for (auto& it : M) {
        MM.insert({ it.second, it.first });
    }
  
    // Print top 5 least frequently occuring words
    auto it = MM.begin();

    std::cout << "The 5 least frequently occuring words are - " << std::endl;
    for (int i = 0; i < 5; i++) {
        std::cout << it->second << ' '
             << it->first << std::endl;
        it++;
    }

    // Print top 5 most frequently occuring words
    auto it2 = MM.rbegin();
    std::cout << "\n\nThe 5 most frequently occuring words are - " << std::endl;
    for (int i = 0; i < 5; i++){
        std::cout << it2->second << ' '
             << it2->first << std::endl;
        it2++;
    }
    std::cout << "\n" << std::endl;
}


int main(int argc, char ** argv){
    
    // Get Input Filename from the commmand line
    std::string inputFilename = argv[1];

    std::cout << "The input filename is - " << inputFilename << std::endl;
        
    // Read file and store the data in vectors
    // std::vector<std::vector<std::string>> allStrings;
    std::vector<std::string> allStrings;


    std::fstream dataFile;
    dataFile.open(inputFilename, std::ios::in);

    std::cout << "Reading File..." << std::endl;

    if (dataFile.is_open()){
        std::string currentLine;
        while(getline(dataFile, currentLine)){
            // std::cout << "Current Line - " << currentLine << std::endl;
            allStrings.push_back(currentLine);
        }
    }

    std::cout << "Done Reading File! Total Number of Lines = " << allStrings.size() << std::endl;

    std::cout << "MAX NUM THREADS - " << omp_get_max_threads() << std::endl;

    // Go over every word in every line
    int numStrings = allStrings.size();

    std::map<std::string, int> wordMap;


    // Initialize LIKWID Marker API
    // LIKWID_MARKER_INIT;

    // // Add each thread to the marker API
    // #pragma omp parallel
    // {
    //     // ID of the thread in the current team
    //     int thread_id = omp_get_thread_num();
    //     // Number of threads in the current team
    //     int nthreads = omp_get_num_threads();

    // #pragma omp critical
    //     {
    //         std::cout << "Hello world, I'm thread " << thread_id << " out of " << nthreads << " total threads. " << std::endl; 
    //     }

    //     // Each thread must add itself to the Marker API, therefore must be
    //     // in parallel region
    //     LIKWID_MARKER_THREADINIT;
    //     // Register region name
    //     LIKWID_MARKER_REGISTER(MY_MARKER_REGION_NAME);
    // }


    // Record Start Time
    std::chrono::time_point<std::chrono::high_resolution_clock> start_time = std::chrono::high_resolution_clock::now();

    #pragma omp parallel
    {
        // LIKWID_MARKER_START(MY_MARKER_REGION_NAME);

        #pragma omp for
        for (int i = 0; i < numStrings; i++){
        std::istringstream iss(allStrings[i]);
        std::string word;

        while (iss >> word){
            // std::cout << word << std::endl;
            
            std::map<std::string, int>::iterator it = wordMap.find(word); 

            if (it == wordMap.end()){
                wordMap.insert(std::pair<std::string, int>(word, 1));
            }else{
                it->second = it->second + 1;
            }

            }

        }

        // LIKWID_MARKER_STOP(MY_MARKER_REGION_NAME);
    }


    // Record End Time
    std::chrono::time_point<std::chrono::high_resolution_clock> end_time = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = end_time - start_time;

    std::cout << "\nWord Counting Completed!\n" << std::endl;

    getStats(wordMap);

    std::cout << "\n Elapsed time is : " << elapsed.count() << std::setprecision(8) << " " << std::endl;

    // Close Marker API and write results to file for further evaluation done
    // by likwid-perfctr
    // std::cout << "Closing LIKWID MARKER" << std::endl;
    // LIKWID_MARKER_CLOSE;

    return 0;
}
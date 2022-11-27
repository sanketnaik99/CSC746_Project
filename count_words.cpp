#include <chrono>
#include <iomanip>
#include <fstream>
#include <iostream>
#include <vector>
#include <string.h>
#include <sstream>
#include <iterator>
#include <map>

void sort(std::map<std::string, int>& M)
{
  
    // Declare a multimap
    std::multimap<int, std::string> MM;
  
    // Insert every (key-value) pairs from
    // map M to multimap MM as (value-key)
    // pairs
    for (auto& it : M) {
        MM.insert({ it.second, it.first });
    }
  
    // Print the multimap
    for (auto& it : MM) {
        std::cout << it.second << ' '
             << it.first << std::endl;
    }
}


int main(int argc, char ** argv){
    
    // Get Input Filename from the commmand line
    std::string inputFilename = argv[1];

    std::cout << "The input filename is - " << inputFilename << std::endl;
        

    // Read file and store the data in vectors
    std::vector<std::string> allStrings;

    std::fstream dataFile;
    dataFile.open(inputFilename, std::ios::in);

    std::cout << "\nReading File..." << std::endl;

    if (dataFile.is_open()){
        std::string currentLine;
        while(getline(dataFile, currentLine)){
            // std::cout << "Current Line - " << currentLine << std::endl;
            allStrings.push_back(currentLine);
        }
    }

    std::cout << "Done Reading File! Total Number of Lines = " << allStrings.size() << std::endl;

    std::cout << allStrings[0] << std::endl;

    // Go over every word in every line
    int numStrings = allStrings.size();

    std::map<std::string, int> wordMap;

    // Record Start Time
    std::chrono::time_point<std::chrono::high_resolution_clock> start_time = std::chrono::high_resolution_clock::now();

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

    // Record End Time
    std::chrono::time_point<std::chrono::high_resolution_clock> end_time = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = end_time - start_time;


    std::cout << "\n\n\nWord Map Counts\n\n" << std::endl;

//     for(auto it = wordMap.cbegin(); it != wordMap.cend(); ++it)
// {
//     std::cout << it->first << " " << it->second << "\n";
// }

    sort(wordMap);

    std::cout << "\n Elapsed time is : " << elapsed.count() << std::setprecision(8) << " " << std::endl;

    return 0;
}
#include <iostream>
#include <fstream>
#include <filesystem>
#include <vector>
#include <string>

using namespace std;
namespace fs = std::filesystem;


#include "SlidingWindow.h"


int main(int argc, char** argv) {
    //Paths and files
    string dna_path = "./data/dna/";
    string align_path = "./data/alignment/";
    string target_path = "./data/results/";

    string dna_file = (char*)argv[2];
    string align_file = (char*)argv[1];
    string file_name = align_file;

    // Check existing of result
    bool exists = false;

    for (const auto& entry : fs::directory_iterator(target_path))
        if (entry.path().string() == target_path + file_name) {
            exists = true;
            break;
        }

    // Searching for Similarities
    SlidingWindow* sw = new SlidingWindow(align_path + align_file);
    try {
        if (exists) {
            cout << "File for original sequence already exists." << endl;
        }
        else {
            sw->search(dna_path + dna_file, target_path + file_name);
        }
    }
    catch (std::bad_alloc e) {
        cout << "****** Error. Buffer overflowed. ******" << endl;
    }
    catch (std::runtime_error e) {
        cout << e.what() << endl;
    }
    delete sw;
    return 0;
}
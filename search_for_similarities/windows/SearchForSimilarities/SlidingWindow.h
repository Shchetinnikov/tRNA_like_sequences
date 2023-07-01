#pragma once
#include <fstream>
#include <string>
#include <vector>
#include <regex>

#include "Alignment.h"
#include "SmithWaterman.h"

using namespace std;

typedef struct buffer {
    string line;
    int alignment_len;
    int start;
    int end;
    double z_value;
} buffer;

typedef struct th_task {
    vector<int> S1;
    vector<vector<float>> pwm;
    buffer ans;
} th_task;

int evaluate_z_value(void* arg);


class SlidingWindow {
private:
    buffer buf;
    int offset = 20;   // step of sliding window
private:
    string dna_file;            // alignment directory paths        
    string align_file;          // dna directory paths
    Alignment* alignment;       // alignment
private:
    void open_file(ifstream& input, const string& path);
    void codering(vector<int>& S1, const string& line) const;
public:
    SlidingWindow(const string align_file);
public:
    int get_offset() { return this->offset; }
public:
    void search(const string dna_file, const string target_file);
public:
    ~SlidingWindow() { delete this->alignment; }
};




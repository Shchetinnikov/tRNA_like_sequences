#pragma once

#include <fstream>
#include <vector>
#include <string>
#include <numeric>

using namespace std;

class Alignment {
private:
	int L;						   // length of sequence
	int N;						   // count of sequences
	vector<string> aligned_lines;  // aligned sequences
	vector<vector<float>> pwm;     // positional-weight matrix
private:
	void open_file(ifstream& input, const string& path) const;	
	void pfm_matrix(vector<vector<float>>& pfm, const vector<string>& lines) const;
	void pwm_matrix(vector<vector<float>>& pwm, const vector<vector<float>>& pfm);
public:
	Alignment(const string align_file);
public:
	int get_count()  { return this->N; }
	int get_length() { return this->L; }
	vector<vector<float>> get_pwm() { return this->pwm; }
public:
	vector<vector<float>> calculate_pwm();
public:
	~Alignment() {}
};
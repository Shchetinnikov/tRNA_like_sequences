#include "Alignment.h"

#include <iostream>


/**************** Constructor ****************/
Alignment::Alignment(const string align_file) {
	ifstream input;
	string line;

	this->open_file(input, align_file);

	while (getline(input, line)) {
		if (line.find(">") == -1) {
			this->aligned_lines.push_back(line);
		}
	}

	this->N = aligned_lines.size();
	this->L = aligned_lines[0].length();

	this->pwm = vector<vector<float>>(5, vector<float>(this->L, 0));

	input.close();
}


/**************** Methods ****************/
vector<vector<float>> Alignment::calculate_pwm() {
	vector<vector<float>> pfm(5, vector<float>(this->L, 0));		// frequency of each base in the i-position
	pfm_matrix(pfm, this->aligned_lines);
	pwm_matrix(this->pwm, pfm);

	return this->pwm;
}



/**************** Secondary functions ****************/
void Alignment::open_file(ifstream& input, const string& path) const {
	input.open(path);

	if (!input.is_open()) {
		throw runtime_error("Error. Could not open file.");
	}
	return;
}


void Alignment::pfm_matrix(vector<vector<float>>& pfm, const vector<string>& lines) const {
	for (auto line : lines) {
		for (int i = 0; i < this->L; i++) {
			switch (line[i])
			{
			case 'A': pfm[0][i] += 1; break;
			case 'T': pfm[1][i] += 1; break;
			case 'C': pfm[2][i] += 1; break;
			case 'G': pfm[3][i] += 1; break;
			case 'N': pfm[4][i] += 1; break;
			default: break;
			}
		}
	}
}

void Alignment::pwm_matrix(vector<vector<float>>& pwm, const vector<vector<float>>& pfm) {
	vector<float> bases_freq(5, 0);										// frequency of each bases in data
	vector<vector<float>> fisher_inf(5, vector<float>(this->L, 0));		// matrix of Fisher information
	vector<float> avg_weight(this->L, 0);								// average weight of bases in each column

	int N = this->aligned_lines.size();

	for (int i = 0; i < pfm.size(); i++) {
		for (auto el : pfm[i]) {
			bases_freq[i] += el;
		}
	}

	for (int i = 0; i < fisher_inf.size(); i++) {
		for (int j = 0; j < fisher_inf[0].size(); j++) {
			//fisher_inf[i][j] = pfm[i][j] * log((pfm[i][j]) / (bases_freq[i]));
			//fisher_inf[i][j] = pfm[i][j] * log((pfm[i][j] + 0.7133741 * N) / (bases_freq[i] + 4 * 0.7133741 * N));
			if (bases_freq[i] == 0) {
				fisher_inf[i][j] = 0;
			}
			else {
				fisher_inf[i][j] = pfm[i][j] * log((pfm[i][j]) / (bases_freq[i]) + 1);
			}
		}
	}
	
	float col_fisher_inf;
	for (int j = 0; j < fisher_inf[0].size(); j++) {
		
		col_fisher_inf = 0;
		for (int k = 0; k < fisher_inf.size(); k++) {
			col_fisher_inf += fisher_inf[k][j];
		}
		
		avg_weight[j] = 0.2 * col_fisher_inf;
	}

	for (int i = 0; i < pwm.size(); i++) {
		for (int j = 0; j < pwm[0].size(); j++) {
			pwm[i][j] = fisher_inf[i][j] - avg_weight[j];
		}
	}
}
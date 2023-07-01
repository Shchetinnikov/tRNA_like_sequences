#pragma once

#include <vector>
#include <tuple>
#include <algorithm>
#include <stdexcept>

using namespace std;

class SmithWaterman {
protected:
    class Node {
    private:
        tuple<int, int> indexes;
        Node* prev_node;
        double f_value;
    public:
        Node();
        Node(tuple<int, int> indexes, Node* prev_node);
        Node(tuple<int, int> indexes, Node* prev_node, double f_value);
    public:
        tuple<int, int> get_indexes() { return this->indexes; }
        Node* get_prev() { return this->prev_node; }
        bool has_prev() { return this->prev_node != nullptr; }
        double get_F_value() { return this->f_value; }
    public:
        void set_value(double value) { this->f_value = value; }
        void set_parent(Node* node) { this->prev_node = node; }
        void set_value_parent(double value, Node* node) { 
            this->f_value = value; 
            this->prev_node = node; 
        }
    public:
        ~Node() {}
    };
private:
    float gap_price = 0.5;
    int d_max = 20;
private:
    vector<vector<float>> pwm;
    vector<int> S1;
    vector<int> S2;
    int L1;
    int L2;
    vector<vector<Node*>> nodes;
    vector<tuple<int, int>> matrix_path;
    int alignment_len;
    double sum_weight;
private:
    tuple<double, int> maxF_x(int i, int j);
    tuple<double, int> maxF_y(int i, int j);
    int calc_matrix_path();
public:
    double calc_F_value(int i, int j);
    double calc_Z_value();
public:
    SmithWaterman(const vector<int>& S1, const vector<vector<float>>& pwm);
public:
    double get_F_value()    { return this->calc_F_value(this->L1, this->L2); }
    double get_sum_weight() { return this->sum_weight; }
    double get_Z_value()    { return this->calc_Z_value(); }
    vector<tuple<int, int>> get_matrix_path() { return this->matrix_path; }
    int get_matrix_size()   { return this->nodes.size(); }
    int get_alignment_len() { return this->alignment_len; }
public:
    ~SmithWaterman() {
        for (auto node_i : this->nodes)
            for (auto node_ij : node_i)
                if (node_ij)
                    delete node_ij;
    }
};
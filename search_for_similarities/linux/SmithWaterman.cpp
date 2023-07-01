#include "SmithWaterman.h"

#include <iostream>


/**************** Constructor ****************/
SmithWaterman::Node::Node() {
    this->indexes = tuple(0, 0);
    this->prev_node = nullptr;
    this->f_value = 0;
}

SmithWaterman::Node::Node(tuple<int, int> indexes, Node* prev_node) {
    this->indexes = indexes;
    this->prev_node = prev_node;

    if (get<0>(indexes) == 0)
        this->f_value = (-1) * 0.5 * (1 + log(get<1>(indexes)));
    else
        this->f_value = (-1) * 0.5 * (1 + log(get<0>(indexes)));
}


SmithWaterman::Node::Node(tuple<int, int> indexes, Node* prev_node, double f_value) {
    this->indexes = indexes;
    this->prev_node = prev_node;
    this->f_value = f_value;
}


SmithWaterman::SmithWaterman(const vector<int>& S1, const vector<vector<float>>& pwm) {
    this->S1 = S1;
    this->S2 = vector<int>(pwm[0].size(), 0);
    this->L1 = S1.size();
    this->L2 = S2.size();
    this->pwm = pwm;
    this->alignment_len = 0;
    this->sum_weight = 0;

    for (int i = 0; i < this->L2; i++) {
        this->S2[i] = i + 1;
    };

    this->nodes = vector<vector<Node*>>(this->L1 + 1, vector<Node*>(this->L2 + 1, nullptr));

    int i = 0;
    int j = 0;

    this->nodes[0][0] = new Node();
    for (i = 1; i <= this->L1; i++) {
        for (j = 1; j <= this->L2; j++) {
            this->nodes[i][j] = new Node(tuple(i, j), nullptr, 0.0);
        }
    }

    for (i = 1; i <= this->L1; i++) {
        this->nodes[i][0] = new Node(tuple(i, 0), this->nodes[i - 1][0]);
    }
    for (j = 1; j <= this->L2; j++) {
        nodes[0][j] = new Node(tuple(0, j), nodes[0][j - 1]);
    }

    this->calc_F_value(this->L1, this->L2);
    this->calc_matrix_path();
}


/**************** Methods ****************/
tuple<double, int> SmithWaterman::maxF_x(int i, int j) {
    vector<double> F_x_values;
    double f_value;
    vector<double>::iterator result;
    int k;

    for (k = 1; (k <= this->d_max) && (i - k >= 0); k++) {
        f_value = this->calc_F_value(i - k, j) - this->gap_price * (1 + log(k));
        F_x_values.push_back(f_value);
    }

    result = max_element(F_x_values.begin(), F_x_values.end());
    k = distance(F_x_values.begin(), result) + 1;

    return tuple(*result, k);
}

tuple<double, int> SmithWaterman::maxF_y(int i, int j) {
    vector<double> F_y_values;
    double f_value;
    vector<double>::iterator result;
    int l;

    for (l = 1; l <= this->d_max && j - l >= 0; l++) {
        f_value = this->calc_F_value(i, j - l) - this->gap_price * (1 + log(l));
        F_y_values.push_back(f_value);
    }

    result = max_element(F_y_values.begin(), F_y_values.end());
    l = distance(F_y_values.begin(), result) + 1;

    return tuple(*result, l);
}


double SmithWaterman::calc_F_value(int i, int j) {
    if (i > this->L1 || j > this->L2)
        throw runtime_error("Error. Indexes are out of range.");
    else if (i == 0 || j == 0)
        return nodes[i][j]->get_F_value();
    else if (this->nodes[i][j]->has_prev())
        return this->nodes[i][j]->get_F_value();

    double r1;
    double r4 = 0.0;
    tuple<double, int> t2, t3;
    double max_r = 0;

    r1 = this->calc_F_value(i - 1, j - 1) + this->pwm[this->S1[i - 1] - 1][j - 1];
    t2 = this->maxF_x(i, j);
    t3 = this->maxF_y(i, j);

    max_r = max({ r1, get<0>(t2), get<0>(t3), r4 });

    if (max_r == r1 || max_r == r4) {
        this->nodes[i][j]->set_value_parent(max_r, this->nodes[i - 1][j - 1]);
    }
    else if (max_r == get<0>(t2)) {
        this->nodes[i][j]->set_value_parent(max_r, this->nodes[i - get<1>(t2)][j]);
    }
    else if (max_r == get<0>(t3)) {
        this->nodes[i][j]->set_value_parent(max_r, this->nodes[i][j - get<1>(t3)]);
    }

    return max_r;
}


double SmithWaterman::calc_Z_value() {
    double mean_Wrnd = 28.55;
    double std_Wrnd = 2.58;
    double W = this->sum_weight;
    return (W - mean_Wrnd) / std_Wrnd;
}


int SmithWaterman::calc_matrix_path() {
    this->matrix_path = vector<tuple<int, int>>();
    Node* node = this->nodes[this->L1][this->L2];

    int i, i_prev, j, j_prev;

    if (node->has_prev()) {
        this->matrix_path.push_back(node->get_indexes());

        i = get<0>(node->get_indexes());
        j = get<1>(node->get_indexes());

        while (node->has_prev()) {
            node = node->get_prev();
            this->matrix_path.push_back(node->get_indexes());

            i_prev = get<0>(node->get_indexes());
            j_prev = get<1>(node->get_indexes());

            if (i * j != 0) {
                if ((i - i_prev) == 1 && (j - j_prev) == 1) {
                    this->sum_weight += this->pwm[this->S1[i - 1] - 1][j - 1];
                }
            }
            if ((i - i_prev) * (j - j_prev) == 1) {
                this->alignment_len++;
            }
            else if ((i - i_prev) == 0) {
                this->alignment_len += (j - j_prev);
            }
            else if ((j - j_prev) == 0) {
                this->alignment_len += (i - i_prev);
            }

            i = i_prev;
            j = j_prev;
        }
        return 0;
    }
    else
        return 1;
}

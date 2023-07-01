#include <iostream>
#include <tuple>
#include <vector>
#include <thread>
#include <mutex>
#include <chrono>

#include "SlidingWindow.h"

mutex mtx;


int evaluate_z_value(void* arg) {
    th_task* t = (th_task*)arg;

    SmithWaterman* SW = new SmithWaterman(t->S1, t->pwm);
    t->ans.z_value = SW->get_Z_value();

    ///
    /*mtx.lock();
    cout << t->ans.line << "  ";
    cout << t->ans.start << " " << t->ans.end << "  ";
    cout << t->ans.z_value << endl;
    mtx.unlock();*/
    ///

    delete SW;
    return 0;
}


/**************** Constructor ****************/
SlidingWindow::SlidingWindow(const string align_file) {
    int L;

    this->buf.line = "";
    this->buf.z_value = 0;
    this->align_file = align_file;
    this->alignment = new Alignment(align_file);
    this->alignment->calculate_pwm();
}


/**************** Methods ****************/
void SlidingWindow::search(const string dna_file, const string target_file) {
    auto t_start = std::chrono::high_resolution_clock::now();

    // Initialize vars
    ifstream input;
    ofstream output(target_file);

    this->dna_file = dna_file;
    this->open_file(input, this->dna_file);

    // Aligment settings
    vector<vector<float>> pwm = this->alignment->get_pwm();
    int L = pwm[0].size();

    // Window vars
    string window_line = "";            // line under window visor
    string input_line;                  // truncated input line
    vector<int> S1(L + 40, 0);          // codered input line

    int counter = 0;                    // count of iterations
    int start = 0;                      // index of begining of line


    // Threads settings
    int th_num = 5;
    th_task* task;
    thread* th;

    // Skip header
    getline(input, input_line);
    input_line = "";

    while (!input.eof()) {
        vector<thread*> ths;
        vector<th_task*> tasks;

        for (int i = 0; i < th_num; i++) {
            if (window_line.length() < L + 40 && !input.eof()) {
                getline(input, input_line);
                input_line = regex_replace(input_line, regex("\r"), "");
                window_line += input_line;
                i--;
            }
            else if (window_line.length() >= L + 40) {
                // Read line and coder
                input_line = window_line.substr(0, L + 40);
                codering(S1, input_line);

                // Create task for thread
                task = new th_task();
                task->pwm = pwm;
                task->S1 = S1;
                task->ans.start = start;
                task->ans.end = start + L + 40 - 1;
                task->ans.line = input_line;
                tasks.push_back(task);

                // Create thread
                th = new thread(evaluate_z_value, task);
                ths.push_back(th);

                // Interation of window
                window_line = window_line.substr(this->offset, window_line.length() - offset);
                start = start + offset;
                counter++;
            }
            else {
                counter++;

                // Read line and coder
                input_line = window_line;
                codering(S1, input_line);

                // Create task for thread
                task = new th_task();
                task->pwm = pwm;
                task->S1 = S1;
                task->ans.start = start;
                task->ans.end = start + input_line.size() - 1;
                task->ans.line = input_line;
                tasks.push_back(task);

                // Create thread
                th = new thread(evaluate_z_value, task);
                ths.push_back(th);
                break;
            }
        }
        for (int i = 0; i < ths.size(); i++) {
            ths[i]->join();
        }

        int min_len;
        for (int i = 0; i < ths.size(); i++) {
            // Threshold control
            if (tasks[i]->ans.z_value >= 3) {
                // Buffer control
                if (this->buf.line.size() != 0) {
                    //min_len = min(this->buf.alignment_len, tasks[i]->ans.alignment_len);
                    //if (this->buf.end > tasks[i]->ans.start && (this->buf.end - tasks[i]->ans.start) >= 0.3 * min_len) {

                    // Overlap control
                    if (this->buf.end > tasks[i]->ans.start) {
                        if (tasks[i]->ans.z_value >= this->buf.z_value) {
                            this->buf.line = tasks[i]->ans.line;
                            this->buf.start = tasks[i]->ans.start;
                            this->buf.end = tasks[i]->ans.end;
                            this->buf.alignment_len = tasks[i]->ans.alignment_len;
                            this->buf.z_value = tasks[i]->ans.z_value;
                        }
                    }
                    else {
                        output << this->buf.line << "  "
                            << this->buf.start << "  " << this->buf.end << "  "
                            << this->buf.z_value << endl;

                        this->buf.line = tasks[i]->ans.line;
                        this->buf.start = tasks[i]->ans.start;
                        this->buf.end = tasks[i]->ans.end;
                        this->buf.alignment_len = tasks[i]->ans.alignment_len;
                        this->buf.z_value = tasks[i]->ans.z_value;
                    }
                }
                else {
                    this->buf.line = tasks[i]->ans.line;
                    this->buf.start = tasks[i]->ans.start;
                    this->buf.end = tasks[i]->ans.end;
                    this->buf.alignment_len = tasks[i]->ans.alignment_len;
                    this->buf.z_value = tasks[i]->ans.z_value;
                }
            }
            else {
                if (this->buf.line.size() != 0) {
                    output << this->buf.line << "  "
                        << this->buf.start << "  " << this->buf.end << "  "
                        << this->buf.z_value << endl;

                    this->buf.line = "";
                }
            }
            delete tasks[i];
            delete ths[i];
        }
        if (this->buf.line.size() != 0 && input.eof()) {
            output << this->buf.line << "  "
                << this->buf.start << "  " << this->buf.end << "  "
                << this->buf.z_value << endl;

            this->buf.line = "";
        }

        //cout << counter << endl;
    }

    auto t_end = std::chrono::high_resolution_clock::now();
    cout << std::chrono::duration<double, std::milli>(t_end - t_start).count() << endl;

    input.close();
    output.close();
}



/**************** Secondary functions ****************/
void SlidingWindow::open_file(ifstream& input, const string& path) {
    input.open(path);
    if (!input.is_open()) {
        throw runtime_error("Error. Could not open file.");
    }
    return;
}

void SlidingWindow::codering(vector<int>& S1, const string& line) const {
    for (unsigned int i = 0; i < line.length(); i++) {
        switch (line[i])
        {
        case 'A':
            S1[i] = 1;
            break;
        case 'T':
            S1[i] = 2;
            break;
        case 'C':
            S1[i] = 3;
            break;
        case 'G':
            S1[i] = 4;
            break;
        case 'N':
            S1[i] = 5;
            break;
        default:
            break;
        }
    }
}
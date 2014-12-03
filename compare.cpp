#include <cstdlib>
#include <iostream>
#include <fstream>
#include <vector>
#include <iterator>
#include <cmath>
#include <iomanip>

using namespace std;

int line_len = 100;
vector<float> get_data(char *filename)
{
    ifstream file( filename, ios::binary );
    if( !file.is_open()) {
        cout << "file \"" << filename << "\" not open" << endl;
        exit(0);
    }
    file.seekg(0, ios::end );
    int num_bytes = file.tellg();
    cout << "for " << filename << ":\nnum_bytes = " << num_bytes << endl;
    if(num_bytes % sizeof(float) != 0) {
        cout << "\nwarning, file does not evenly break into floats" << endl;
    }
    vector<float> buffer(num_bytes/sizeof(float));

    file.seekg( 0, ios::beg);
    file.read(reinterpret_cast<char *>(buffer.data()), num_bytes);

    return buffer;
}
void print_line(int N) {
    for(int i = 0; i < N; i++) 
        cout << "-";
    cout << endl;
}

void print_header(){
    print_line(line_len);
    cout << "| " << left << setw(10) << "tolerance";
    cout << "| " << setw(20 + 3) << "# non-equal elements" ;
    cout << "| " << setw(13) << "sum of diffs";
    cout << "| " << setw(12) << "avg diff";
    cout << "| " << setw(12) << "max diff" ;
    cout << endl;
    print_line(line_len);
}
void analyze(vector<float> buff1, vector<float> buff2, float tolerance) 
{
    //vector<float> buff3(buff1.size());
    int num_different = 0;
    float sum_difference = 0;
    float biggest_percent = 0;
    int biggest_diff_idx = -1;

    for(int i = 0; i < buff1.size(); i++) {
        float val = buff2[i] - buff1[i];
        sum_difference += val;
        if(val > tolerance) {
            num_different++;
        }
        if(val > tolerance && buff1[i] > tolerance) {
            float percent_diff = 100.0 *(val / buff1[i]);
            if(percent_diff > biggest_percent) {
                biggest_percent = percent_diff;
                biggest_diff_idx = i;
            }
        }
    }
    float avg_diff;
    if(num_different == 0) {
        avg_diff = 0;
    } else {
        avg_diff = (sum_difference / (float)num_different);
    }
    cout << "| " << setw(10) << tolerance 
         << "| " << setw(10) << right << num_different << " / " << left << setw(10) << buff1.size() 
         << "| " << setw(13) << sum_difference 
         << "| " << setw(12) << avg_diff
         << "| " << biggest_percent << "%";
    if(biggest_diff_idx > 0) {
        cout << " ( " << buff1[biggest_diff_idx] << " vs " << buff2[biggest_diff_idx] << " )";
    }
    cout << endl;
}

int main( int argc, char **argv )
{
    float tolerance = -6;
    if( argc < 3 ) {
        cout << "requires 2 files names" << endl;
        return 0;
    }
    if( argc > 3) {
        tolerance = atoi(argv[3]);
    }

    vector<float> buff1 = get_data(argv[1]);
    vector<float> buff2 = get_data(argv[2]);

    if(buff1.size() != buff2.size()) {
        cout << "error, files are different size: "  
             << buff1.size() << " for file1 vs "  
             << buff2.size() << " for file2" << endl;
        return 0;
    }

    print_header();
    for(int tol = tolerance-3; tol < tolerance+4; tol++) {
        analyze(buff1, buff2, pow(10.0, tol));
    }
    print_line(line_len);
    return 0;
}

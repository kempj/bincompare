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
    //cout << num_bytes << " = num_bytes( " << filename << " )" << endl;
    if(num_bytes % sizeof(float) != 0) {
        cout << "\nwarning, file does not evenly break into floats" << endl;
    }
    vector<float> buffer(num_bytes/sizeof(float));

    file.seekg( 0, ios::beg);
    file.read(reinterpret_cast<char *>(buffer.data()), num_bytes);
    file.close();

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

void print_diff(vector<float> buff1, vector<float> buff2, float tolerance){
    int count = 0;
    for(int i = 0; i < buff1.size(); i++) {
        float diff = buff1[i] = buff2[i];
        if(abs(diff) > tolerance) {
            cout << left << "(i=" << i << ": " << setw(12) << diff << " - " << setw(12) << buff1[i] <<  ") ";
            count++;
            if(count % 3 == 0) {
                cout << endl;
                if(count == 120) {
                    count = 0;
                    char control = cin.get();
                    if(control == 'q') {
                        break;
                    }
                    if(control == 'c') {
                        count = 121;
                    }
                }
            }
        }
    }
    print_header();
    analyze(buff1, buff2, tolerance);
}

void print_as_char(vector<float> buff){
    char *buffer = (char*)buff.data();
    int buffer_length = buff.size() * sizeof(float);
    int line_len = 120;
    int page_len = 20;
    int count = 0;
    int line_count = 0;
    for(int i = 0; i < buffer_length; i++) {
        if(buffer[i] >= 32 && buffer[i] <= 126) {
            cout << buffer[i];
            count++;
            if(count%(line_len) == 0) {
                cout << endl;
                count = 0;
                line_count++;
            }
        }
        if(i%1000== 0) {
            cout << endl << "i=" << i << "/" << buffer_length << "(" 
                 << setprecision(4) << 100.0* ( i / (float)buffer_length) 
                 << "%)" << endl;
            count = 0;
            line_count++;
        }
        if(line_count == page_len) {
            line_count = 0;
            char control = cin.get();
            if('q' == control) {
                break;
            }
            if('c' == control) {
                line_count = page_len + 1;
            }
            if('g' == control) {
                i = buffer_length - 20000;
                count = 0;
                line_count = 0;
                cout << endl << endl 
                     << "-------------------------------------------------------" 
                     << endl << endl;
            }
        }
    }
    cout << endl;
}


int main( int argc, char **argv )
{
    float tol_exp = -6;
    int tol_range = 3;
    if( argc < 3 ) {
        cout << "requires 2 files names" << endl;
        cout << "with an optional tolerance range and value" << endl;
        return 0;
    }
    if( argc > 3) {
        tol_range = atoi(argv[3]);
    }
    if( argc > 4) {
        tol_exp = atoi(argv[4]);
    }

    vector<float> buff1 = get_data(argv[1]);
    vector<float> buff2 = get_data(argv[2]);

    print_as_char(buff1);

    if(buff1.size() != buff2.size()) {
        cout << "error, files are different size: "  
             << buff1.size() << " for file1 vs "  
             << buff2.size() << " for file2" << endl;
        return 0;
    }
    if(tol_range == -1){
        print_diff(buff1, buff2, pow(10,tol_exp));
                
    } 

    print_header();
    for(int tol = tol_exp - tol_range; tol <= tol_exp + tol_range; tol++) {
        analyze(buff1, buff2, pow(10.0, tol));
    }
    return 0;
}

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
    if(num_bytes % sizeof(float) != 0) {
        cout << "\nwarning, file does not evenly break into floats" << endl;
    }
    vector<float> buffer(num_bytes/sizeof(float));

    file.seekg( 0, ios::beg);
    file.read(reinterpret_cast<char *>(buffer.data()), num_bytes);
    file.close();

    return buffer;
}


void print_diff(vector<float> buff1, vector<float> buff2, float tolerance){
    cout << "printing elemnts that differ by at least " << tolerance << endl;
    int count = 0;
    for(int i = 0; i < buff1.size(); i++) {
        float diff = buff1[i] = buff2[i];
        if(abs(diff) > tolerance) {
            cout << left << "(i=" << i << ": " << setw(12) << buff1[i] << " +/- " << setw(12) << diff <<  ") ";
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
}

void print_as_char(vector<float> buff){
    char *buffer = (char*)buff.data();
    int buffer_length = buff.size() * sizeof(float);
    int line_len = 16;
    int page_len = 20;
    int count = 0;
    int line_count = 0;
    for(int i = 0; i < buffer_length; i++) {
        if(buffer[i] >= 32 && buffer[i] <= 126) {
            cout << buffer[i];
        } else {
            cout << ' ';
        }
        count++;
        if(count%(line_len) == 0) {
            count = 0;
            cout << '|';
            if(line_count == page_len) {
                line_count = 0;
                char control = cin.get();
                if('q' == control) {
                break;
                }
                if('c' == control) {
                    line_count = page_len + 1;
                }
            }
            line_count++;
            cout << endl << setw(8) << left << i+1;
        }
    }
    cout << endl;
}


int main( int argc, char **argv )
{
    int op = 0;
    int tol_exp = -6;
    if( argc < 2 || argc > 5 ) {
        cout << "requires a file and an opreation for it" << endl;
        cout << "with an optional second file and tolerance" << endl;
        cout << "\t(file1, op, file2, tol)" << endl;
        return 0;
    }
    if(argc > 4) {
        tol_exp = atoi(argv[4]);
    }
    if(argc > 2) {
        op = atoi(argv[2]);
    }
    vector<float> buff1 = get_data(argv[1]);

    if(op == 0) {
        print_as_char(buff1);
    } else {
        if(op == 1 && argc > 3) {
            print_diff(buff1, get_data(argv[3]), pow(10,tol_exp));
        } else {
            cout << "Invalid args" << endl;
        }
    }

    return 0;
}

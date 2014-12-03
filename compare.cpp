#include <cstdlib>
#include <iostream>
#include <fstream>
#include <vector>
#include <iterator>
#include <cmath>

using namespace std;

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


void analyze(vector<float> buff, float tolerance) 
{
    int num_different = 0;
    float sum_difference = 0;

    for(int i = 0; i < buff.size(); i++) {
        sum_difference += buff[i];
        if(buff[i] > tolerance) {
            num_different++;
        }
    }
    cout << endl;
    cout << "number of non-equal elements: " << num_different
         << " / " << buff.size() << endl;
    cout << "total sum of difference: " << sum_difference << endl;
    cout << "average over all elements: " << (sum_difference / (float)buff.size()) << endl;
    cout << "average difference for non-equal elements: " << (sum_difference / (float)num_different) << endl;
}

int main( int argc, char **argv )
{
    float tolerance = .000001;
    if( argc < 3 ) {
        cout << "requires 2 files names" << endl;
        return 0;
    }
    if( argc > 3) {
        tolerance = pow(10, atoi(argv[3]));
    }

    vector<float> buff1 = get_data(argv[1]);
    vector<float> buff2 = get_data(argv[2]);

    if(buff1.size() != buff2.size()) {
        cout << "error, files are different size: "  
             << buff1.size() << " for file1 vs "  
             << buff2.size() << " for file2" << endl;
        return 0;
    }

    vector<float> buff3(buff1.size());
    for(int i = 0; i < buff1.size(); i++) {
        buff3[i] = buff2[i] - buff1[i];
    }
    analyze(buff3, tolerance);

    return 0;
}

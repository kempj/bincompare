#include <cstdlib>
#include <iostream>
#include <fstream>
#include <vector>
#include <iterator>

using namespace std;

vector<double> get_data(char* filename)
{

}
int main( int argc, char **argv )
{
    if( argc < 3 ) {
        cout << "requires 2 files names, an optional data type," << endl;
        cout << "\tand whether to store both files in memory" << endl;
        return 0;
    }
    ifstream file1( argv[1], ios::binary );
    ifstream file2( argv[2], ios::binary );
    int data_type = 0;
    if( argc > 3 ) {
        data_type = atoi( argv[3] );
    }
    bool in_memory = true;
    if( argc > 4 ) {
        if( atoi( argv[3] ) == 0 ) {
            in_memory = false;
        }
    }
    if( !file1.is_open() || !file2.is_open()) {
        cout << "file not open" << endl;
        return 0;
    }
    file1.seekg( ios::end );
    int num_bytes1 = file1.tellg();

    vector<double> buff1;
    vector<double> buff2;

    cout << buff1.size() << endl;
    cout << buff2.size() << endl;

    cout << buff1 << endl;
    cout << buff2 << endl;
    //for(auto element : buff1) {
    //    cout << element << ", ";
    //}
    cout << endl;

    return 0;
}

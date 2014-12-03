#include <cstdlib>
#include <iostream>
#include <fstream>

using namespace std;
int main( int argc, char **argv )
{
    double val1[] = {42,43,44,45};
    double val2[] = { 1, 2, 3, 4};
    ofstream file1( "test1", ios::binary );
    ofstream file2( "test2", ios::binary );

    cout << sizeof(val1) << endl;
    file1.write(reinterpret_cast<char *>(&val1), sizeof(val1));
    file2.write(reinterpret_cast<char *>(&val2), sizeof(val2));
    
    file1.close();
    file2.close();

    return 0;
}

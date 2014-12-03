#include <cstdlib>
#include <iostream>
#include <fstream>

using namespace std;
int main( int argc, char **argv )
{
    float val1[] = {42,43,44,45,46,47,48,49.1};
    float val2[] = { 1.5, 2.5, 3.5, 4.5, 5.5, 6.5, 7.5, 8.5};
    ofstream file1( "test1", ios::binary );
    ofstream file2( "test2", ios::binary );

    cout << "sizeof(float[4]) = " << sizeof(val1) << endl;
    cout << "sizeof(float) = " << sizeof(float) << endl;
    file1.write(reinterpret_cast<char *>(&val1), sizeof(val1));
    file2.write(reinterpret_cast<char *>(&val2), sizeof(val2));
    
    file1.close();
    file2.close();

    return 0;
}

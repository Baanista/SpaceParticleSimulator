#ifndef debughelp_HPP
#define debughelp_HPP
#include <vector>
using namespace std;

void printvecint(vector<int> vec)
{
    for (int i = 0; i < vec.size(); i++)
    {
        cout << vec[i] << ',';
    }
    cout << endl;
}


#endif
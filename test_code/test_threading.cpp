#include <string>
#include <iostream>
#include <thread>

using namespace std;

bool continuer = true;

// The function we want to execute on the new thread.
void task1(string msg)
{
    while (continuer)
    {
        cout << "task1 says: " << msg << endl;
    }
}

int main()
{
    // Constructs the new thread and runs it. Does not block execution.
    thread t1(task1, "Hello");

    // Do other things...
    
    cin >> continuer;
    // Makes the main thread wait for the new thread to finish execution, therefore blocks its own execution.
    t1.join();
}
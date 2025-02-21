#include <iostream>
#include <cstdlib>

using namespace std;

int main(int argc, char *argv[])
{
    double average;
    //cout << argc << endl;
    //for (int i = 1; i < argc; i++) cout << i << " " <<argv[i] << endl;
    if (argc < 2)
    {
        cout << "Please input numbers to find average.";
    }
    else
    {
        cout << "---------------------------------" << endl;
        for (int i = 1; i <= argc - 1; i++)
        {
            average += atoi(argv[i]);
        }
        average = average / (argc-1);
        cout << "Average of " << argc - 1 << " numbers = " << average << endl;

        cout << "---------------------------------" << endl;
    }
}

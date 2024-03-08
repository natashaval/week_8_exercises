#include <iostream>
#include <random>
#include <vector>

using namespace std;

int main()
{
    mt19937_64 rng(42);
    normal_distribution<double> dist(0, 1);

    const int N = 100000;
    vector<double> rand_list(N);
    for(int i = 0; i < N; i++)
    {
        rand_list[i] = dist(rng);
    }

    const int bins = 101;
    // int histogram[101];
    std::vector<int> histogram(bins, 0);
    // for(int i = 0; i < bins; i++)
    // {
    //     histogram[i] = 0;
    // }

// #pragma omp parallel for reduction(+:histogram[:bins])
#pragma omp parallel
{
    std::vector<int> sum_tmp(bins, 0); // partial histogram
    #pragma omp for // split into parallel region of FOR
    for(int i = 0; i < N; i++)
    {
        double x = rand_list[i];
        if(x < -3 || x >= 3)
        {
            continue;
        }

        int idx = static_cast<int>(((x + 3) / 6) * bins);
        // histogram[idx]++;
        sum_tmp[idx]++;
    }

    // A similar construct is critical, which guarantees that threads will only run the code in the construct one at a time, i.e. sequentially.
    #pragma omp critical
    {
        for (int i = 0; i < bins; i++)
        {
            histogram[i] += sum_tmp[i];
        }
    }
}
// PRAGMA PARALLEL REGION ENDS HERE

    for(int i = 0; i < bins; i++)
    {
        cout << (-3 + (i + 0.5)*(6.0/bins)) << " " <<  histogram[i] << endl;
    }

    return 0;
}
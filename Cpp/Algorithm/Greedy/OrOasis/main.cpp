/**
 * @file main.cpp
 * @author Sang Tan Truong (sang.truong@outlook.com.vn)
 * @brief OrOasis
 * @link
 * https://www.hackerearth.com/practice/algorithms/greedy/basics-of-greedy-algorithms/practice-problems/algorithm/oroasis-7e736f17/
 * @version 0.1
 * @date 2024-05-02
 *
 * @copyright Copyright (c) 2024
 *
 */
#include <ctime>
#include <iostream>
#include <map>
#include <bits/stdc++.h>


#define TEST

#ifdef TEST
int main1() {
#else
int main() {
#endif
    using namespace std;
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int test;
    cin>>test;

    assert(test>=1 && test<=1e5);

    int totalN = 0;

    while(test--)
    {
        int N;
        cin>>N;

        assert(N>=2 && N<=1e6);
        totalN += N;

        vector<int> A(N);
        for(auto &e: A)
        {
            cin>>e;
            assert(e>0 && e<=1e9);
        }

        vector<vector<int>> bitSum(30, vector<int> (N));

        for(int i=0; i<N; i++)
        {
            for(int bit=0; bit<30; bit++)
            {
                bitSum[bit][i] = (((1<<bit)&A[i]) > 0);
                if(i)   bitSum[bit][i] += bitSum[bit][i-1];
            }
        }

        auto getSum = [&](int bit, int l, int r)
        {
            if(l == 0)      return bitSum[bit][r];
            return (bitSum[bit][r] - bitSum[bit][l-1]);
        };

        auto check = [&](int l, int r)
        {
            for(int bit=0; bit<30; bit++)
            {
                if(bitSum[bit][N-1]>0 && getSum(bit, l, r)==0)
                    return false;
            }

            return true;
        };

        auto check2 = [&](int l, int r)
        {
            for(int bit=0; bit<30; bit++)
            {
                if(bitSum[bit][N-1]!=0 && getSum(bit, l, r)==bitSum[bit][N-1])
                    return false;
            }

            return true;
        };

        int sm = N+1;
        vector<int> val(N+1);

        for(int i=0, j=0; i<N; i++)
        {
            while(j<i && check(j+1, i))     j++;

            if(check(j, i) && check2(j, i))
            {
                sm = min(sm, i-j+1);
                val[i-j+1] += 1;
            }
        }

        if(sm == N+1)
        {
            cout<<-1<<"\n";
            continue;
        }

        cout<<sm<<" "<<val[sm]<<"\n";
    }

    assert(totalN<=1e6);
}
#ifdef TEST
int main() {
    ::freopen("input.txt", "r", stdin);
    ::freopen("output.txt", "w", stdout);
    ::clock_t tStart = ::clock();
    main1();
    std::cout << std::endl;
    ::printf("Time taken: %.10fs\n",
           (double)(::clock() - tStart) / CLOCKS_PER_SEC);
    ::fclose(stdin);
    ::fclose(stdout);
    return EXIT_SUCCESS;
}
#endif

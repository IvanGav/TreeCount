#include <vector>
#include <iostream>
#include <iomanip>

using namespace std;

const long MAX_N = 1427;
const long BILLION = 1000000000;

void tree_count() {
    int n = 0;
    //initializing 2d vector to all 0's
    vector<vector<long long>> arr(MAX_N,vector<long long>(100,0));
    //hardcoding first 4 answers
    arr[0][0] = 1;
    arr[1][1] = 1;
    arr[2][2] = 2;
    arr[3][2] = 1;
    arr[4][3] = 4;
    int start = 5;
    //run until no more input
    while(std::cin >> n) {
        //return if number is > MAX_N
        if(n > MAX_N) return;
        //if we didn't calculate far enough yet, calculate until the number of nodes we need
        for(int n0 = start; n0 <= n; n0++) {
            //go through all heights 
            for(int h = 1; h < 99; h++) {
                //go through all combinations of sizes of both branches
                for(int i = 0; i < n0; i++) {
                    arr[n0][h+1] += (arr[i][h] * arr[n0-i-1][h]) % BILLION; //case 1: h1 = h2
                    arr[n0][h+1] += (arr[i][h-1] * arr[n0-i-1][h]) % BILLION; //case 2: h1 = h2-1
                    arr[n0][h+1] += (arr[i][h] * arr[n0-i-1][h-1]) % BILLION; //case 3: h1-1 = h2
                    arr[n0][h+1] = arr[n0][h+1] % BILLION; //always do % BILLION or it just breaks
                }
            }
        }
        //update up to which n we calculated the numbers
        start = std::max(n+1,start);
        long long sum = 0;
        for(int i = 0; i < 100; i++) {
            sum += arr[n][i];
            sum = sum % BILLION;
        }
        std::string s = std::to_string(sum);
        //add leading zeros if the number is less than 9 digits
        while(s.length() < 9) {
            s = "0" + s;
        }
        std::cout << s << std::endl;
    }
}

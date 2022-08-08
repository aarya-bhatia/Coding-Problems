#include <bits/stdc++.h>
using namespace std;

class Solution {
    public:
    double getMedian(const vector<int> &v){
        if(v.empty()) return 0;
        int n = v.size();
        if(n % 2 == 1) return v[(n-1)/2];
        return double(v[n/2 - 1]+v[n/2])/2;
    }

    double findMedianSortedArrays(vector<int>& x, vector<int>& y) {
        if(x.empty()) return getMedian(y);
        else if(y.empty()) return getMedian(x);

        vector<int> merged(x.size() + y.size());
        size_t x_idx = 0, y_idx = 0, idx = 0;
        while(x_idx < x.size() && y_idx < y.size())
        {
            if(x[x_idx] < y[y_idx]){
                merged[idx++] = x[x_idx++]; 
            } else {
                merged[idx++] = y[y_idx++]; 
            }
        }
        while(x_idx<x.size()){
            merged[idx++] = x[x_idx++]; 
        }
        while(y_idx<y.size()){
            merged[idx++] = y[y_idx++]; 
        }
        
        return getMedian(merged);

    }
};

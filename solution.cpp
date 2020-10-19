#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <math.h>
#include <queue>
#include <unordered_set>
#include <iostream>
#include <vector>
#include <limits>
#include <utility> // pair
#include <tuple>
#include <algorithm>
#include <map>
#define MINUS_INT_MAX INT_MAX * (-1);

/*
    [1, 2, 2, 3, 1]

    [1, 2, 2, 3, 1], [1, 2, 2, 3], [2, 2, 3, 1], [1, 2, 2], [2, 2, 3], [2, 2]
*/

struct MyCompare{
public:
    bool operator()(const std::pair<int, int> &p1, const std::pair<int, int> &p2) const{
        return p1.second > p2.second;
    }
};

class Solution {
public:
    int findShortestSubArray(std::vector<int>& nums) {
        if(nums.size() <= 0) {
            return -1;
        }

        /*
            [ 7, 3, 3, 5, 1 ]

            ans: 
                degree is 2 ( bcuz: [3, 3], there are 2 number "3" )
                the minimum length of answer array is 2 ( length([3, 3]) == 2 )
        */

        int min_array_length = INT_MAX;
        int degree = 0;
        std::map< int, int > freq_map;   // {number, appear times}
        std::map< int, std::pair< int, int > > appear_map; // {first appear index,last appear index}

        for(int i = 0 ; i < nums.size() ; i++) {
            if ( freq_map.find(nums[i]) == freq_map.end() ) {
                // could not found the num in array
                freq_map[nums[i]] = 1;
                appear_map[nums[i]] = {i, i}; // assign the first appear index and the last appear index
            } else {
                // found the num in array
                freq_map[nums[i]]++;
                appear_map[nums[i]].second = i; // update last appear index
            }
            degree = std::max(degree, freq_map[nums[i]]);
        }

        printf("degree: %d\n", degree);

        // print
        printf("freq map:\n");
        printf("{num\t:\tappear times\t}\n");
        for(std::map<int, int>::iterator it = freq_map.begin(); it != freq_map.end(); ++it) {
            printf("{%d\t:\t\t%d\t}\n", it->first, it->second);
        }

        printf("appear index map:\n");
        printf("{num:\t{first appear\t:\tlast appear\t}}\n");
        for(std::map< int, std::pair< int, int > >::iterator it = appear_map.begin(); it != appear_map.end(); ++it) {
            std::pair<int, int> tmp_pair = it->second;

            printf("{%d:\t{\t%d\t:\t\t%d\t}}\n", it->first, tmp_pair.first, tmp_pair.second);
        }

        for(std::map<int, int>::iterator it = freq_map.begin(); it != freq_map.end(); ++it) {
            
            if (degree == it->second) { // find the num which appearing times is equal to degree 

                std::pair<int, int> tmp_array = appear_map[it->first];
                min_array_length = std::min((tmp_array.second - tmp_array.first), min_array_length);
            }
        }

        return min_array_length + 1;
    }

};

int main(int argc, char *argv[]) {
    Solution *s = new Solution();

    std::vector<int> nums1{ 7, 3, 3, 5, 1 };
    printf("output:%d\n", s -> findShortestSubArray(nums1));

}
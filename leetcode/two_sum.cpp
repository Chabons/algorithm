#include <stdio.h>
#include <unordered_map>
#include <vector>

std::vector<int> twoSum(std::vector<int>& a, int target)
{
    std::unordered_map<int, int> tmp;
    for (int i = 0; i < a.size(); ++i) {
        int diff = target - a[i];
        if (tmp.count(diff) > 0) return {tmp[diff], i};

        tmp[a[i]] = i;
    }

    return {};
}


int main(int argc, const char **argv) {
    std::vector<int> a {5,6,7,2};

    std::vector<int> res = twoSum(a, 9);
    printf("%d %d\n", res[0], res[1]);
    return 0;
}

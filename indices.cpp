#include <iostream>
#include <vector>
#include <unordered_map>

std::vector<int> twoSum(const std::vector<int>& nums, int target) {
    std::unordered_map<int, int> numMap;

    for (int i = 0; i < nums.size(); ++i) {
        int complement = target - nums[i];

        auto it = numMap.find(complement);
        if (it != numMap.end()) {

            return {it->second, i};
        }

                numMap[nums[i]] = i;
    }

        return {};
}

int main() {
    int n;
    std::cout << "Enter the number of elements in the array: ";
    std::cin >> n;

    std::vector<int> nums;
    std::cout << "Enter the elements of the array, separated by space: ";
    for (int i = 0; i < n; ++i) {
        int num;
        std::cin >> num;
        nums.push_back(num);
    }

    int target;
    std::cout << "Enter the target sum: ";
    std::cin >> target;

    std::vector<int> result = twoSum(nums, target);

    if (!result.empty()) {
        std::cout << "Output: [" << result[0] << ", " << result[1] << "]" << std::endl;
    } else {
        std::cout << "No solution found." << std::endl;
    }

    return 0;
}

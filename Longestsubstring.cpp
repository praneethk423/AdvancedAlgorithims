#include <iostream>
#include <vector>

using namespace std;

string longestCommonSubstring(const string& str1, const string& str2, vector<vector<int>>& dp) {
    int m = str1.length();
    int n = str2.length();

    int maxLength = 0;
    int endIndex = 0;

    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            if (str1[i - 1] == str2[j - 1]) {
                dp[i][j] = dp[i - 1][j - 1] + 1;

                if (dp[i][j] > maxLength) {
                    maxLength = dp[i][j];
                    endIndex = i - 1;  // or j - 1, since both strings are assumed to be of equal length
                }
            } else {
                dp[i][j] = 0;
            }
        }
    }

    cout << "   ";
    for (int j = 0; j <= n; j++) {
        cout << str2[j] << "  ";
    }
    cout << endl;

    for (int i = 0; i <= m; i++) {
        if (i == 0) cout << " ";
        else cout << str1[i - 1] << " ";

        for (int j = 0; j <= n; j++) {
            cout << dp[i][j] << "  ";
        }
        cout << endl;
    }

    string result = str1.substr(endIndex - maxLength + 1, maxLength);

    return result;
}

int main() {
    string str1, str2;

    cout << "Enter the first string: ";
    cin >> str1;
    cout << "Enter the second string: ";
    cin >> str2;

    int m = str1.length();
    int n = str2.length();

    vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));

    string lcs = longestCommonSubstring(str1, str2, dp);

    cout << "Longest Common Substring: " << lcs << " (length: " << lcs.length() << ")" << endl;

    return 0;
}

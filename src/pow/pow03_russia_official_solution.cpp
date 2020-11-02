#include <iostream>
#include <vector>
#include <stdexcept>
typedef std::vector<int> VI;
typedef std::vector<VI> VVI;
// global upper bound on winnings: <= 500 coins of value <= 2^{10}
// (fits into a 32-bit int)
const int INF = 500 * 1024 + 1;
// n = #coins, m = #players,
// x[i] is the value of the i-th coin, and
// dp[i][j], where i <= j is the maximum possible winnings
// of the first player given that the game starts with coins
// x[i], x[i+1], ..., x[j-1].
// This recursive function computes dp[i][j], that is, the maximum possible
// winnings of the first player given that the game starts with coins
// x[i], x[i+1], ..., x[j-1].
int max_winnings(int i, int j, int n, int m, const VI& x, VVI& dp) {
    // If (i, j) is not a valid interval, return 0.
    if (j < i) return 0;
    // If there are fewer than 1 coins available, the first
    // player will not get a coin, so his/her winnings are 0.
    if (j - i < 1) return dp[i][j] = 0;
    // If we have already computed the value for this state,
    // we don’t compute it again.
    if (dp[i][j] != -1) return dp[i][j];
    // The following implements the recurrent formula from above.
    int winnings_kth_left = INF, winnings_kth_right = INF;
    for (int l = 0; l < m; ++l) {
        winnings_kth_left = std::min(
        winnings_kth_left,
        max_winnings(i + l + 1, j - (m - l - 1), n, m, x, dp));
        winnings_kth_right = std::min(
        winnings_kth_right,
        max_winnings(i + l, j - (m - l), n, m, x, dp));
    }
    dp[i][j] = std::max(x[i] + winnings_kth_left, x[j-1] + winnings_kth_right);
    return dp[i][j];
}

int main() {
    std::ios_base::sync_with_stdio(false);
    int t;
    // Read in the number of test cases.
    for (std::cin >> t; t > 0; --t) {
        int n, m, k;
        std::cin >> n >> m >> k;
        // Read in all the values of the coins.
        VI x;
        x.reserve(n);
        for (int i = 0; i < n; ++i) {
            int v;
            std::cin >> v;
            x.push_back(v);
        }
        // Make sure our dp array is initialized to -1, which stands for
        // "not computed yet".
        VVI dp(n+1, VI(n+1, -1));
        // Consider all options for the behaviour of the first ‘k‘ players.
        // Any number of them (0 through k) could take the leftmost coins.
        // We take the minimum winnings for the k-th player out of all these.
        int maximal_winnings = INF;
        for (int i = 0; i <= k; ++i)
        maximal_winnings = std::min(
        maximal_winnings,
        max_winnings(i, n - (k - i), n, m, x, dp));
        std::cout << maximal_winnings << "\n";
    }
}
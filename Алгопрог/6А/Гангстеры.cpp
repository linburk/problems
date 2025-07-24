import java.util.Scanner;
import static java.lang.Integer.max;

public class Main {
    private static void input(int[] array, Scanner cin) {
        for (int i = 0; i < array.length; ++i)
            array[i] = cin.nextInt();
    }
    public static void main(String[] args) {
        Scanner cin = new Scanner(System.in);
        int n, k, t;
        n = cin.nextInt();
        k = cin.nextInt();
        t = cin.nextInt();
        int[] times = new int[n];
        int[] rich = new int[n];
        int[] size = new int[n];
        input(times, cin);
        input(rich, cin);
        input(size, cin);
        int[][] gang_time = new int[t + 1][2];
        for (int i = 0; i < n; ++i) {
            gang_time[times[i]][0] = rich[i];
            gang_time[times[i]][1] = size[i];
        }
        int[][] dp = new int[t + 1][k + 2];
        for (int i = 1; i <= t; ++i) {
            for (int j = 1; j <= k; ++j) {
                dp[i][j] = max(dp[i - 1][j - 1], max(dp[i - 1][j + 1], dp[i - 1][j])) + (gang_time[i][1] == j ? gang_time[i][0] : 0);
            }
        }
        int res = 0;
        for (int i = 0; i <= k; ++i) {
            res = max(res, dp[t][i]);
        }
        System.out.println(res);
    }
}
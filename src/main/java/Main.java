import java.io.*;
import java.util.*;

public class Main {
    static int n;
    static int[] a, tree;

    static void add(int i, int num) {
        while (i <= n) {
            tree[i] += num;
            i += i & -i;
        }
    }

    static void update(int x) {
        int left = edge(x);
        int right = edge(x + 1);
        a[x] ^= 1;
        add(x, edge(x) - left);
        if (x < n) {
            add(x + 1, edge(x + 1) - right);
        }
    }

    static int edge(int i) {
        if (i < 2 || i > n) return 0;
        return a[i] == a[i - 1] ? 0 : 1;
    }

    static int sum(int num) {
        int res = 0;
        while (num > 0) {
            res += tree[num];
            num -= num & -num;
        }
        return res;
    }

    public static void main(String[] args) throws Exception {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        StringTokenizer st = new StringTokenizer(br.readLine());
        n = Integer.parseInt(st.nextToken());
        int q = Integer.parseInt(st.nextToken());
        a = new int[n + 1];
        tree = new int[n + 1];
        st = new StringTokenizer(br.readLine());
        for (int i = 1; i <= n; i++) {
            while (!st.hasMoreTokens()) {
                st = new StringTokenizer(br.readLine());
            }
            a[i] = Integer.parseInt(st.nextToken());
        }
        for (int i = 2; i <= n; i++) {
            if (a[i] != a[i - 1]) {
                add(i, 1);
            }
        }
        StringBuilder sb = new StringBuilder();
        for (int i = 0; i < q; i++) {
            st = new StringTokenizer(br.readLine());
            int op = Integer.parseInt(st.nextToken());
            if (op == 1) {
                int x = Integer.parseInt(st.nextToken());
                update(x);
            } else {
                int l = Integer.parseInt(st.nextToken());
                int r = Integer.parseInt(st.nextToken());
                int k = sum(r) - sum(l);
                sb.append((k + 1) / 2).append('\n');
            }
        }
        System.out.print(sb);
    }
}


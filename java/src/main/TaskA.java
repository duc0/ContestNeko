package main;

import java.util.Scanner;
import java.io.PrintWriter;

public class TaskA {
    public void solve(int testNumber, Scanner in, PrintWriter out) {
        int n = in.nextInt();
        int result = n / 2;
        out.println(result);
        for (int i = 0; i < result - 1; i++) {
            out.print(2 + " ");
        }
        out.print(n % 2 == 0 ? 2 : 3);
    }
}

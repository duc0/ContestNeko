package main;

import cfm.collections.PrefixCountTrie;

import java.io.PrintWriter;
import java.util.Scanner;

public class Contacts {
    public void solve(int testNumber, Scanner in, PrintWriter out) {
        int nQueries;
        nQueries = Integer.parseInt(in.nextLine());

        PrefixCountTrie trie = new PrefixCountTrie(26);

        for (int i = 0; i < nQueries; i++) {
            String line = in.nextLine();
            String[] tokens = line.split(" ");
            String command = tokens[0];
            if (command.equals("add")) {
              String value = tokens[1];
              trie.add(toSequence(value));
            } else if (command.equals("find")) {
              String value = tokens[1];
              out.println(trie.countPrefix(toSequence(value)));
            }
        }

    }

    private static int[] toSequence(String s) {
        int[] result = new int[s.length()];
        for (int i = 0; i < s.length(); i++) {
            result[i] = s.charAt(i) - 'a';
        }
        return result;
    }
}

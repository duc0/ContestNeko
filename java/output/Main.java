import java.io.OutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.PrintWriter;
import java.util.Scanner;

/**
 * Built using CHelper plug-in
 * Actual solution is at the top
 */
public class Main {
    public static void main(String[] args) {
        InputStream inputStream = System.in;
        OutputStream outputStream = System.out;
        Scanner in = new Scanner(inputStream);
        PrintWriter out = new PrintWriter(outputStream);
        Contacts solver = new Contacts();
        solver.solve(1, in, out);
        out.close();
    }

    static class Contacts {
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

    static class PrefixCountTrie extends Trie {
        public PrefixCountTrie(int branchingFactor) {
            super(branchingFactor);
        }


        protected Trie.TrieNode newTrieNode() {
            return new PrefixCountTrie.PrefixCountTrieNode(branchingFactor);
        }


        protected void visited(Trie.TrieNode node) {
            ((PrefixCountTrie.PrefixCountTrieNode) node).count++;
        }

        public int countPrefix(int[] sequence) {
            Trie.TrieNode current = root;
            for (int value : sequence) {
                if (current.children[value] == null) {
                    return 0;
                }
                current = current.children[value];
            }
            return ((PrefixCountTrie.PrefixCountTrieNode) current).count;
        }

        static final class PrefixCountTrieNode extends Trie.TrieNode {
            private int count;

            public PrefixCountTrieNode(int branchingFactor) {
                super(branchingFactor);
            }

        }

    }

    static class Trie {
        protected final int branchingFactor;
        protected final Trie.TrieNode root;

        public Trie(int branchingFactor) {
            this.branchingFactor = branchingFactor;
            root = newTrieNode();
        }

        public void add(int[] sequence) {
            Trie.TrieNode current = root;
            for (int value : sequence) {
                if (current.children[value] == null) {
                    current.children[value] = newTrieNode();
                }
                current = current.children[value];
                visited(current);
            }
        }

        protected Trie.TrieNode newTrieNode() {
            Trie.TrieNode result = new Trie.TrieNode(branchingFactor);
            return result;
        }

        protected void visited(Trie.TrieNode node) {

        }

        protected static class TrieNode {
            final Trie.TrieNode[] children;

            public TrieNode(int branchingFactor) {
                this.children = new Trie.TrieNode[branchingFactor];
            }

        }

    }
}


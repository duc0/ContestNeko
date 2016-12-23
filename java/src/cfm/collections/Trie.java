package cfm.collections;

public class Trie {
    protected final int branchingFactor;
    protected final TrieNode root;

    public Trie(int branchingFactor) {
        this.branchingFactor = branchingFactor;
        root = newTrieNode();
    }

    public void add(int[] sequence) {
        TrieNode current = root;
        for (int value : sequence) {
            if (current.children[value] == null) {
                current.children[value] = newTrieNode();
            }
            current = current.children[value];
            visited(current);
        }
    }

    protected TrieNode newTrieNode() {
        TrieNode result = new TrieNode(branchingFactor);
        return result;
    }

    protected void visited(TrieNode node) {

    }

    protected static class TrieNode {
        final TrieNode[] children;

        public TrieNode(int branchingFactor) {
            this.children = new TrieNode[branchingFactor];
        }
    }
}

package cfm.collections;

public class PrefixCountTrie extends Trie {
    public PrefixCountTrie(int branchingFactor) {
        super(branchingFactor);
    }

    @Override
    protected TrieNode newTrieNode() {
        return new PrefixCountTrieNode(branchingFactor);
    }

    @Override
    protected void visited(TrieNode node) {
        ((PrefixCountTrieNode)node).count++;
    }

    public int countPrefix(int[] sequence) {
        TrieNode current = root;
        for (int value : sequence) {
            if (current.children[value] == null) {
                return 0;
            }
            current = current.children[value];
        }
        return ((PrefixCountTrieNode) current).count;
    }

    static final class PrefixCountTrieNode extends TrieNode {
        // Number of prefixes that ended up at this node.
        private int count;

        public PrefixCountTrieNode(int branchingFactor) {
            super(branchingFactor);
        }
    }

}

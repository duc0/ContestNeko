#include "global.hpp"

#ifndef SEGMENTTREE_H
#define SEGMENTTREE_H

template <class T, class Q> class SegmentTree {
    struct TreeNode {
        bool leaf = true; // All elements in the leaf node's segment are the same
        T value;
        Q query;
        int leftChild = -1,
                rightChild =
                -1; // index of the left and right children, -1 for no child
    };

protected:
    vector<TreeNode> node;
    const T defaultValue;

    int addNode(int l, int r) {
        TreeNode newNode;
        newNode.value = defaultValue;
        node.push_back(newNode);
        return (int)node.size() - 1;
    }

    void splitNode(int p, int l, int r) {
        assert(node[p].leaf);
        int m = (l + r) / 2;
        node[p].leaf = false;
        if (node[p].leftChild == -1) {
            int c = addNode(l, m);
            node[p].leftChild = c;
            c = addNode(m + 1, r);
            node[p].rightChild = c;
        }
        int lc = node[p].leftChild;
        int rc = node[p].rightChild;
        node[lc].leaf = true;
        node[rc].leaf = true;
        node[lc].value = node[p].value;
        node[rc].value = node[p].value;
        split(node[p].query, node[lc].query, node[rc].query, node[p].value, l, m,
              r);
    }

    void update(int p, int l, int r, int i, int j, const T &v) {
        if (j < l || i > r)
            return;
        int m = (l + r) / 2;
        if (i <= l && r <= j) { // [i,j] covers [l,r]
            if (node[p].leaf) {
                node[p].query = updateLeaf(node[p].query, node[p].value, v, l, r);
                node[p].value = v;
                return;
            } else {
                node[p].leaf = true;
                node[p].value = v;
            }
        } else if (node[p].leaf) { // [i,j] intersects [l, r]
            splitNode(p, l, r);
        }
        update(node[p].leftChild, l, m, i, j, v);
        update(node[p].rightChild, m + 1, r, i, j, v);
        node[p].query =
                merge(node[node[p].leftChild].query, node[node[p].rightChild].query);
    }

    Q query(int p, int l, int r, int i, int j) {
        if (i <= l && r <= j) { // [i,j] contains [l,r]
            return node[p].query;
        }
        if (node[p].leaf) { // [i,j] intersects [l, r]
            splitNode(p, l, r);
        }
        int m = (l + r) / 2;
        Q ret;
        if (j <= m) {
            ret = query(node[p].leftChild, l, m, i, j);
        } else if (i >= m + 1) {
            ret = query(node[p].rightChild, m + 1, r, i, j);
        } else {
            ret = merge(query(node[p].leftChild, l, m, i, j),
                        query(node[p].rightChild, m + 1, r, i, j));
        }
        node[p].query =
                merge(node[node[p].leftChild].query, node[node[p].rightChild].query);
        return ret;
    }

    int minIndex, maxIndex;
    int root;

protected:
    // Merges the query from left and right children
    virtual Q merge(const Q& leftSide, const Q& rightSide) = 0;

    // Return the updated query in a leaf node if its old value is oldV and new value is curV
    virtual Q updateLeaf(const Q &current, const T &oldValue, const T &currentValue, int leftIndex, int rightIndex) = 0;

    // Modify the query in the current node and it's left and right children when a split action happens.
    virtual Q split(Q & current, Q &leftChild, Q &rightChild, const T &currentValue, int leftIndex, int midIndex, int rightIndex) = 0;

public:
    explicit SegmentTree(int minIndex, int maxIndex, T defaultValue)
            : defaultValue(defaultValue), minIndex(minIndex), maxIndex(maxIndex) {
        root = addNode(minIndex, maxIndex);
    }

    // Set all elements in [i, j] to be v
    void update(int i, int j, T v) { update(root, minIndex, maxIndex, i, j, v); }

    // Query augmented data in [i, j]
    Q query(int i, int j) { return query(root, minIndex, maxIndex, i, j); }

    // Query augmented data in the whole range
    Q query() { return query(root, minIndex, maxIndex, minIndex, maxIndex); }
};


template <class T, class Q> class SimpleSegmentTree : SegmentTree<T, Q> {

public:
    virtual Q initLeaf(const T &value, int leftIndex, int rightIndex) = 0;


private:
    virtual Q updateLeaf(const Q &current, const T &oldValue, const T &currentValue, int leftIndex,
                         int rightIndex) override {
        return initLeaf(currentValue, leftIndex, rightIndex);
    }

    virtual Q split(Q &current, Q &leftChild, Q &rightChild, const T &currentValue, int leftIndex, int midIndex,
                    int rightIndex) override {
        leftChild = initLeaf(currentValue, leftIndex, midIndex);
        rightChild = initLeaf(currentValue, midIndex + 1, rightIndex);
    }

    SimpleSegmentTree(int minIndex, int maxIndex, T defaultValue) : SegmentTree<T, Q>(minIndex, maxIndex, defaultValue) { }
};


#endif
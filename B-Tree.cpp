#include <iostream>
#include <vector>
using namespace std;

class BTreeNode {
public:
    vector<int> keys;
    int t;
    vector<BTreeNode*> children;
    bool isLeaf;

    BTreeNode(int _t, bool _isLeaf) : t(_t), isLeaf(_isLeaf) {}

    void traverse() {
        int i;
        for (i = 0; i < keys.size(); i++) {
            if (!isLeaf)
                children[i]->traverse();

            cout << " " << keys[i];
        }

        if (!isLeaf)
            children[i]->traverse();
    }

    BTreeNode* search(int k) {
        int i = 0;

        while (i < keys.size() && k > keys[i])
            i++;

        if (i < keys.size() && keys[i] == k)
            return this;

        if (isLeaf)
            return nullptr;

        return children[i]->search(k);
    }

    void insertNonFull(int k) {
        int i = keys.size() - 1;

        if (isLeaf) {
            keys.push_back(0);

            while (i >= 0 && keys[i] > k) {
                keys[i + 1] = keys[i];
                i--;
            }

            keys[i + 1] = k;
        }
        else {
            while (i >= 0 && keys[i] > k)
                i--;

            if (children[i + 1]->keys.size() == 2 * t - 1) {
                splitChild(i + 1, children[i + 1]);

                if (keys[i + 1] < k)
                    i++;
            }

            children[i + 1]->insertNonFull(k);
        }
    }

    void splitChild(int i, BTreeNode* y) {
        BTreeNode* z = new BTreeNode(y->t, y->isLeaf);

        for (int j = 0; j < t - 1; j++)
            z->keys.push_back(y->keys[j + t]);

        if (!y->isLeaf) {
            for (int j = 0; j < t; j++)
                z->children.push_back(y->children[j + t]);
        }

        int middleKey = y->keys[t - 1];

        y->keys.resize(t - 1);

        if (!y->isLeaf)
            y->children.resize(t);

        children.insert(children.begin() + i + 1, z);

        keys.insert(keys.begin() + i, middleKey);
    }
};

class BTree {
private:
    BTreeNode* root;
    int t;

    void destroyTree(BTreeNode* node) {
        if (!node)
            return;

        if (!node->isLeaf) {
            for (BTreeNode* child : node->children)
                destroyTree(child);
        }

        delete node;
    }

public:
    BTree(int _t) : root(nullptr), t(_t) {}

    ~BTree() {
        destroyTree(root);
    }

    void traverse() {
        if (root != nullptr)
            root->traverse();

        cout << endl;
    }

    BTreeNode* search(int k) {
        return (root == nullptr) ? nullptr : root->search(k);
    }

    void insert(int k) {
        if (root == nullptr) {
            root = new BTreeNode(t, true);
            root->keys.push_back(k);
        }
        else {
            if (root->keys.size() == 2 * t - 1) {
                BTreeNode* s = new BTreeNode(t, false);

                s->children.push_back(root);
                s->splitChild(0, root);

                int i = (s->keys[0] < k) ? 1 : 0;

                s->children[i]->insertNonFull(k);

                root = s;
            }
            else {
                root->insertNonFull(k);
            }
        }
    }
};

int main() {
    BTree tree(3);

    int values[] = {10, 20, 5, 6, 12, 30, 7, 17};

    for (int val : values)
        tree.insert(val);

    cout << "In-order traversal of the B-Tree:";
    tree.traverse();

    int keyToFind = 6;

    cout << "Searching for " << keyToFind << ": "
         << (tree.search(keyToFind) != nullptr ? "Found" : "Not Found")
         << endl;

    keyToFind = 15;

    cout << "Searching for " << keyToFind << ": "
         << (tree.search(keyToFind) != nullptr ? "Found" : "Not Found")
         << endl;

    return 0;
}
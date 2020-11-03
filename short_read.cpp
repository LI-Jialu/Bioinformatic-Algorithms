//CSCI3220 2020 - 21 First Term Assignment 2
//I declare that the assignment here submitted is original except for source material explicitly acknowledged, 
//and that the same or closely related material has not been previously submitted for another course.
//I also acknowledge that I am aware of University policyand regulations on honesty in academic work,
//and of the disciplinary guidelinesand procedures applicable to breaches of such policyand regulations,
//as contained in the following websites.
//University Guideline on Academic Honesty :
//http ://www.cuhk.edu.hk/policy/academichonesty/
//Student Name : LI Jialu
//Student ID : 1155107895


#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <algorithm>
#include<bits/stdc++.h>
using namespace std;

struct TrieNode {
    //Core 
    int par; //Index of parent 
    int nxt[5]; //Index of edges/childs 

    //Extra info for Suffix Trie 
    bool isLeaf;
    int leftmost;

    //Extra info for Suffix Tree 
    int suffix_tree_par, lt, rt;

    TrieNode() {
        par = -1;
        memset(nxt, -1, sizeof(nxt)); //let all nxt[] be -1 at beginning 
        isLeaf = false;
        leftmost = 0x3f3f3f3f; //set leftmost initial very big 
    }
};

char idx2nuc[] = "$ACGT";
inline int nuc2idx(char nuc) {
    switch (nuc) {
    case '$': return 0;
    case 'A': return 1;
    case 'C': return 2;
    case 'G': return 3;
    case 'T': return 4;
    }
    return -1;
}

static const int MXN = 10000000;
TrieNode pool[MXN]; //initialize 10000000 nodes 
int pool_cur = 1;
int trie_root = 0;
void trie_insert(string ori_str, int offset) {
    int cur_node = trie_root; //when initialized, the current node is the root 
    string str = ori_str.substr(offset, ori_str.size() - offset);
    for (int i = 0; i < str.size(); i++) {
        int nxt_idx = nuc2idx(str[i]); //Map char to the order of child 

         //if the current child of this current node is still -1 
         //then create an edge 
        if (pool[cur_node].nxt[nxt_idx] == -1) {
            pool[cur_node].nxt[nxt_idx] = pool_cur; //set the edge's child to pool_cur
            pool[pool_cur].par = cur_node; //set the edge's par to cur_node 
            pool_cur++;
        }

        //now the child become the current node 
        cur_node = pool[cur_node].nxt[nxt_idx];

        //Suffix trie: set marks on the node 
        pool[cur_node].leftmost = min(pool[cur_node].leftmost, i + offset + 1);
    }
    //Mark the leaf node 
    pool[cur_node].isLeaf = true;
}

// Count children 
int child_cnt[MXN];
void count_children() {
    for (int i = 0; i < pool_cur; i++) {
        child_cnt[i] = 0;
        for (int j = 0; j < 5; j++) {
            if (pool[i].nxt[j] != -1) {
                child_cnt[i]++;
            }
        }
    }
}

//Compress leaf 
void compress() {
    for (int i = 0; i < pool_cur; i++) {
        if (pool[i].isLeaf) { //find the node that is leaf node 
            int cur_node = i;
            int lt = -1;
            int rt = pool[i].leftmost;
            while (child_cnt[cur_node] <= 1) { //no or one child 
                lt = pool[cur_node].leftmost; //beginning 
                cur_node = pool[cur_node].par; //find the parent of the current child 
            }
            pool[i].suffix_tree_par = cur_node;
            pool[i].lt = lt;
            pool[i].rt = rt;
        }
    }
}

void print_leaf(int i) {
    //if the node has no edge, print the lt and rt of it 
    if (child_cnt[i] == 0) {
        cout << pool[i].lt << "-" << pool[i].rt << endl;
    }

    // if the node has child, then go to the child do DFS
    if (pool[i].nxt[0] != -1) {
        print_leaf(pool[i].nxt[0]);
    }

    if (pool[i].nxt[1] != -1) {
        print_leaf(pool[i].nxt[1]);
    }

    if (pool[i].nxt[2] != -1) {
        print_leaf(pool[i].nxt[2]);
    }

    if (pool[i].nxt[3] != -1) {
        print_leaf(pool[i].nxt[3]);
    }

    if (pool[i].nxt[4] != -1) {
        print_leaf(pool[i].nxt[4]);
    }
}


//To verify if the substring is in the string 
void search(string A, string str) {
    int cur_node = trie_root;
    bool have = true; //initially suppose the substring is in the string 
    int i;
    for (i = 0; i < str.size(); i++) {
        int nxt_idx = nuc2idx(str[i]); //Map char to the order of child 
        if (pool[cur_node].nxt[nxt_idx] == -1) {
            have = false; //if can't find one character, then doesn't have this substring 
            break;
        }
        cur_node = pool[cur_node].nxt[nxt_idx];
    }

    if (have == true) {
        cout << "Yes" << endl;
    }
    else {
        cout << "No" << endl;
    }
}


int main() {

    string A, B;
    cin >> A;
    cin >> B;

    //insert all suffixes in to the suffix trie 
    for (int i = 0; i < A.size(); i++) {
        trie_insert(A, i);
    }

    //count the number of children of each node 
    count_children();

    //compress the trie into tree 
    compress();

    //print all leaf of the suffix tree 
    print_leaf(0);

    //search substring B in string A 
    search(A, B);

    return 0;
}

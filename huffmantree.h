#ifndef HUFFMANTREE_H
#define HUFFMANTREE_H
#include <QString>
#include <iostream>
#include <string>
using namespace std;
struct TreeNode
{
    int weight;
    char ch;
    TreeNode *leftChild;
    TreeNode *rightChild;
    string code;
public:

    TreeNode()
    {
        leftChild = NULL;
        rightChild = NULL;
        code = "";
    }
    TreeNode(int weight,TreeNode *leftChild =NULL,TreeNode *rightChild =NULL,char ch = '$')
    {
        this->weight = weight;
        this->leftChild = leftChild;
        this->rightChild = rightChild;
        this->ch = ch;
        code = "";
    }
    TreeNode(const TreeNode& a)
    {
       this->weight = a.weight;
       this->ch  = a.ch;
       this->code = a.code;
       this->leftChild = a.leftChild;
       this->rightChild = a.rightChild;
    }
    bool operator<(TreeNode node){return weight<node.weight;}
    bool operator>(TreeNode node){return weight>node.weight;}
};


class HuffmanTree
{
private:
    TreeNode *root;

public:
    HuffmanTree();
    ~HuffmanTree()
    {delete root;}
    TreeNode *getRoot(){return root;}
    int create(string s,int i,TreeNode*& r);
    void createTree(string s,int i);
};

#endif // HUFFMANTREE_H

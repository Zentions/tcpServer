#include "huffmantree.h"

int HuffmanTree::create(string s,int i,TreeNode*& r)
{
    r = new TreeNode(0);
    if(s[i]!='@') {r->ch = s[i];return i+1;}
    else
    {
        r->ch = '@';
        int n= create(s,i+1,r->leftChild);
        int m = create(s,n,r->rightChild);
        return m;
    }
}
void HuffmanTree::createTree(string s,int i)
{
   create(s,i,root);
}
HuffmanTree::HuffmanTree()
{
   root = NULL;
}

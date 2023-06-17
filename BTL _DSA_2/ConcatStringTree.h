#ifndef __CONCAT_STRING_TREE_H__
#define __CONCAT_STRING_TREE_H__

#include "main.h"

static int St_id = 1;
enum BalanceValue{ LH = -1, EH = 0, RH = 1 };

struct Node_PT {
    int data;
    Node_PT *pLeft, *pRight;
    BalanceValue balance;
    Node_PT(int value) : data(value), pLeft(NULL), pRight(NULL), balance(EH) {}
};

class ParentsTree {
public:
    Node_PT* root; 
    int nPT;

    ParentsTree();
    ParentsTree(int value);
    ~ParentsTree();
    int size() const;
    string toStringPreOrder() const;            
    void RotationRight(Node_PT* &pR);
    void RotationLeft(Node_PT* &pR);
    bool BalanceLeft(Node_PT* &pR);
    bool BalanceRight(Node_PT* &pR);
    bool Insert_AVL(Node_PT* &pR, int &value);
    void insert_PT(int &value);
    bool Remove_AVL(Node_PT* &pR , int &value);
    void remove_PT(int&value);
};

struct Node {
    ParentsTree Root_PT; 
    int length , leftLength;
    string data; 
    int id;  
    Node* left;
    Node* right;

    Node(string s) { 
        this->data = s; 
        this->length = (int)s.length(); 
        this->leftLength = 0; 
        this->left = this->right = nullptr; 
        if(St_id > 10000000) throw overflow_error("Id is overflow!"); 
        else {this->id = St_id;}
        this->Root_PT.root = new Node_PT(this->id);
        this->Root_PT.nPT = 1;
    }
    Node(string s, const int L , const int LL) { 
        this->data = s; 
        this->length = L; 
        this->leftLength = LL; 
        this->left = this->right = nullptr; 
        if(St_id > 10000000) throw overflow_error("Id is overflow!"); 
        else {this->id = St_id;}
        this->Root_PT.root = new Node_PT(this->id);
        this->Root_PT.nPT = 1;
    }
};   

class ConcatStringTree {
public:
    Node* Root;

    ConcatStringTree();
    ConcatStringTree(const char * s);
    ~ConcatStringTree();
    int length() const;
    char get(int index);
    int indexOf(char c);
    string toStringPreOrder() const;
    string toString() const;
    ConcatStringTree concat(const ConcatStringTree & otherS) const;
    ConcatStringTree subString(int from, int to) const;
    ConcatStringTree reverse() const;
    int getParTreeSize(const string & query) const;
    string getParTreeStringPreOrder(const string & query) const;
};

class ReducedConcatStringTree; // forward declaration

class HashConfig {
public:  // private
    int p;  
    double c1, c2;
    double lambda;
    double alpha;
    int initSize;

    HashConfig();
    HashConfig(int P , double C1 , double C2 , double Lambda , double Alpha , int IntSize);    
    friend class ReducedConcatStringTree;
    friend class LitStringHash;
};

struct LitNode {
    string str;
    int nLink;

    LitNode() : str("") , nLink(0) {}
};

class LitStringHash {
public: 
    HashConfig config;
    LitNode* Arr;
    int nE , id_last;

    LitStringHash(const HashConfig & hashConfig);
    ~LitStringHash();
    int getLastInsertedIndex() const;
    string toString() const;
    void ReHashing();
    bool Certain(string s , int &id , int &id_ok);
    int HashFuntion(string s);
    int Quad_Probing(string s , int i);
};

class ReducedConcatStringTree : public ConcatStringTree {
public:
    LitStringHash * litStringHash;

    ReducedConcatStringTree reverse() {}
    ReducedConcatStringTree subString(int from , int to) {}
    ReducedConcatStringTree concat(const ReducedConcatStringTree & otherS);
    ReducedConcatStringTree(const char * s);
    ReducedConcatStringTree(const char * s, LitStringHash * litStringHash);
    ~ReducedConcatStringTree();
};

#endif // __CONCAT_STRING_TREE_H__
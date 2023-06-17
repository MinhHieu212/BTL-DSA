#include "ConcatStringTree.h"

//  PARENTSTREE  ------ NODE_PT -----

ParentsTree::ParentsTree() : root(nullptr) , nPT(0) {}
ParentsTree::ParentsTree(int value) { 
    this->root = new Node_PT(value); 
    this->nPT = 1;
}
void ParentsTree::RotationRight(Node_PT* &pR) {
    Node_PT* p = pR->pLeft;
    pR->pLeft = p->pRight;
    p->pRight = pR;
    pR = p;
}
void ParentsTree::RotationLeft(Node_PT* &pR) {
    Node_PT* p = pR->pRight;
    pR->pRight = p->pLeft;
    p->pLeft = pR;
    pR = p;
}
bool ParentsTree::BalanceLeft(Node_PT* &pR) {
    if(pR->balance == EH) { pR->balance = LH; return  true; }
    else if(pR->balance == RH) { pR->balance = EH; return false; }
    else {  // pR->balance == LH
        if(pR->pLeft->balance == EH) { 
            RotationRight(pR);  
            pR->balance = RH; pR->pRight->balance = LH;
            return true;
        }else if(pR->pLeft->balance == LH) {
            RotationRight(pR);
            pR->balance = pR->pRight->balance = EH;
            return false;
        }else {
            RotationLeft(pR->pLeft); RotationRight(pR);
            if(pR->balance == EH) {pR->pLeft->balance = pR->pRight->balance = EH;}
            else if(pR->balance == LH) {pR->pLeft->balance = EH; pR->pRight->balance = RH;}
            else if(pR->balance == RH) {pR->pLeft->balance = LH; pR->pRight->balance = EH;}
            pR->balance = EH;
            return false;
        }
    }
}
bool ParentsTree::BalanceRight(Node_PT* &pR) {
    if(pR->balance == EH) { pR->balance = RH; return  true; }
    else if(pR->balance == LH) { pR->balance = EH; return false; }
    else {  // pR->balance == RH
        if(pR->pRight->balance == EH) { 
            RotationLeft(pR);  
            pR->balance = LH; pR->pLeft->balance = RH;
            return true;
        }else if(pR->pRight->balance == RH) {
            RotationLeft(pR);
            pR->balance = pR->pLeft->balance = EH;
            return false;
        }else {
            RotationRight(pR->pRight); RotationLeft(pR);
            if(pR->balance == EH) {pR->pLeft->balance = pR->pRight->balance = EH;}
            else if(pR->balance == RH) {pR->pRight->balance = EH; pR->pLeft->balance = LH;}
            else if(pR->balance == LH) {pR->pRight->balance = RH; pR->pLeft->balance = EH;}
            pR->balance = EH;
            return false;
        }
    }
}
bool ParentsTree::Insert_AVL(Node_PT* &pR, int &value) {
    if(pR) {
        if(value < pR->data) {
            if(Insert_AVL(pR->pLeft, value)) return BalanceLeft(pR);
            else return false;
        }else {
            if(Insert_AVL(pR->pRight, value)) return BalanceRight(pR);
            else return false;
        }
    } else { pR = new Node_PT(value); return true;}
}
void ParentsTree::insert_PT(int &value) {
    Insert_AVL(this->root , value);
    this->nPT++;
}
bool ParentsTree::Remove_AVL(Node_PT* &pR , int &value) { 
    if(!pR) return false;
    else {
        if(value < pR->data) {
            if(Remove_AVL(pR->pLeft , value)) return !BalanceRight(pR);
            else return false;
        }else if(value > pR->data){
            if(Remove_AVL(pR->pRight , value)) return !BalanceLeft(pR);
            else return false;
        }else {
            if(pR->pLeft && pR->pRight) {
                Node_PT *p = pR->pLeft;
                while(p->pRight) p = p->pRight;
                pR->data = p->data; 
                if(Remove_AVL(pR->pLeft , p->data)) return !BalanceRight(pR);
                else return false;
            }else if(pR->pLeft) {
                Node_PT* p = pR;
                pR = pR->pLeft;   // cout << "  Delete id = " << value << endl;
                delete p; 
                return true;
            }else if(pR->pRight) {
                Node_PT* p = pR;
                pR = pR->pRight;  //  cout << "  Delete id = " << value << endl;
                delete p;   
                return true;
            }else {  // cout << "  Delete id = " << value << endl;
                delete pR; pR = nullptr;
                return true;
            }
        }
    }
    return false;
}
void ParentsTree::remove_PT(int &value) {
    Remove_AVL(this->root, value);
    this->nPT--;
}
int ParentsTree::size() const {
    return this->nPT;
}
void NLR(Node_PT* pR, string &str) {
    if(pR) {
        str = str + "(id=" + to_string(pR->data) + ");";
        NLR(pR->pLeft, str);
        NLR(pR->pRight, str);
    }
}
string ParentsTree::toStringPreOrder() const {
    if(this->nPT == 0) return "ParentsTree[]";
    string str = "";
    NLR(this->root, str);
    str.erase(str.length() - 1);
    return "ParentsTree[" + str +"]";
}
void Clear_PT(Node_PT* pR) {
    if(pR) {
        Clear_PT(pR->pLeft);
        Clear_PT(pR->pRight);
        delete pR; pR = nullptr;
    }
}
ParentsTree::~ParentsTree() {
    Clear_PT(this->root);
}


//  CONCATSTRINGTREE ------  NODE  -------
 

ConcatStringTree::ConcatStringTree() {
    this->Root = nullptr; 
}
ConcatStringTree::ConcatStringTree(const char * s) {
    Root = new Node(s); St_id++;  
}
int ConcatStringTree::length() const {
    return Root->length;
}
char ConcatStringTree::get(int index) {
    if(index < 0 || index > Root->length - 1) throw out_of_range("Index of string is invalid!");
    Node* tmp = this->Root;
    while(tmp->left && tmp->right) {
        if(index < tmp->leftLength) { tmp = tmp->left; }
        else { index -= tmp->leftLength; tmp = tmp->right; }
    }
    return tmp->data[index];
}
void Re_indexOf(Node* root , char c , int & res , int & tmp , bool &flag) {  
    if(!flag) return;
    if(root) {
        Re_indexOf(root->left , c , res , tmp , flag);
        Re_indexOf(root->right , c , res , tmp , flag);
        if(root->data != "") {
            for(int i = 0 ; i < root->length ; i++) {
                if(root->data[i] == c) {
                    res = i;
                    flag = false;
                    return;
                }
            }
            tmp += root->length;
        }
    }
}
int ConcatStringTree::indexOf(char c) {
    int res = -1 , tmp = 0;
    bool flag = true;
    Re_indexOf(this->Root , c , res , tmp , flag);
    if(flag) return -1;
    else return tmp + res;
}
void Re_toStringPreOrder(Node* root , string &res) {
     if(root) {
        res = res + "(LL=" + to_string(root->leftLength) + ",L=" + to_string(root->length) + ",";
        if(root->data == "") res += "<NULL>);";
        else res += "\"" + root->data + "\");";   
        Re_toStringPreOrder(root->left , res);
        Re_toStringPreOrder(root->right , res);
     }   
}
string ConcatStringTree::toStringPreOrder() const {
    string res = "";
    Re_toStringPreOrder(Root , res);
    res.erase(res.length() - 1);
    return "ConcatStringTree[" + res + "]";
}
void Re_toString(Node* root , string &res) {
    if(root) {
        if(!root->left || !root->right) {
            res += root->data;
        }
        Re_toString(root->left , res);
        Re_toString(root->right , res);
    }
}
string ConcatStringTree::toString() const {
    string res = "";
    Re_toString(Root , res);
    return "ConcatStringTree[\"" + res + "\"]";
}
void Insert_PT_Node(Node* &pR, int &value) {  
    if(pR->left) pR->left->Root_PT.insert_PT(value);
    if(pR->right) pR->right->Root_PT.insert_PT(value);
}
ConcatStringTree ConcatStringTree::concat(const ConcatStringTree & otherS) const {
    ConcatStringTree res(""); 
    res.Root->left = this->Root;
    res.Root->right = otherS.Root;
    res.Root->leftLength = this->Root->length;
    res.Root->length = this->Root->length + otherS.Root->length;
    Insert_PT_Node(res.Root , res.Root->id);
    return res;
}
Node* Clone(Node* root) {
    if(root == nullptr) return nullptr;
    Node* NewNode = new Node(root->data, root->length , root->leftLength);
    NewNode->left = Clone(root->left);
    NewNode->right = Clone(root->right);
    return NewNode;
}
Node* Re_SubString(Node * root , int &from , int &Cur_len) {
    if(root) {
        root->left = Re_SubString(root->left , from , Cur_len);
        root->right = Re_SubString(root->right , from , Cur_len);
        if(root->data != "") {   // node leaf
            int Pre_len = Cur_len;
            Cur_len += root->length;
            if(Pre_len <= from && from < Cur_len) { 
                root->data = root->data.substr(from - Pre_len);
                root->length = root->data.length();
            } else if(from >= Cur_len) { 
                delete root;
                root = nullptr;
            }
        } 
        return root;
    }
}
Node* ReR_SubString(Node * root , int &to , int &Cur_len) {
    if(root) {
        root->right = ReR_SubString(root->right , to , Cur_len);
        root->left = ReR_SubString(root->left , to , Cur_len);
        if(root->data != "") {   // node leaf
            int Pre_len = Cur_len - root->length;
            if(Pre_len < to && to <= Cur_len) {
                root->data = root->data.substr(0 , to - Pre_len);
                root->length = root->data.length();
            } else if(to <= Pre_len) { 
                root = nullptr;
            } 
            Cur_len = Pre_len;
        } else {    
            if(root->left == nullptr && root->right == nullptr) {
                delete root;
                root = nullptr;
            }
        }
        return root;
    }
}
void FixLen(Node* root) { 
    if(root){
        FixLen(root->left);
        FixLen(root->right);
        if(root->data == ""){
            if(root->left != nullptr && root->leftLength != root->left->length) {
            root->length -= root->leftLength;
            root->leftLength = root->left->length;
            root->length += root->leftLength;
            }
            if(root->right != nullptr && root->length - root->leftLength != root->right->length){
                root->length = root->leftLength;
                root->length += root->right->length;
            }
            if(root->left == nullptr) {
                root->length -= root->leftLength;
                root->leftLength = 0;
            }
            if(root->right == nullptr) {
                root->length = root->leftLength;
            }
        }
    }
}
ConcatStringTree ConcatStringTree::subString(int from, int to) const {
    if(from < 0 || from > Root->length - 1 || to < 0 || to > Root->length -1) throw out_of_range("Index of string is invalid!");
    if(from >= to) throw logic_error("Invalid range!");
    ConcatStringTree ans(""); St_id--;
    ans.Root = Clone(Root);
    int id = 0;
    ans.Root = Re_SubString(ans.Root , from , id);
    ans.Root = ReR_SubString(ans.Root , to , ans.Root->length);
    FixLen(ans.Root);
    return ans;
}
void reverse_str(string &s) {
    int len = s.length();
    if(len % 2 == 0) len--;
    for(int i = len/2 ; i > -1 ; --i) {
        swap(s[i] , s[s.length() - i - 1]);
    } 
}
void Re_reverse(Node* root) {
    if(root->data != "") reverse_str(root->data);
    Node* tmp = root->left;
    root->left = root->right;
    root->right = tmp;
    if(root->left != nullptr) Re_reverse(root->left);
    if(root->right != nullptr) Re_reverse(root->right);
}
ConcatStringTree ConcatStringTree::reverse() const {
    ConcatStringTree ans(""); St_id--;
    ans.Root = Clone(Root);
    Re_reverse(ans.Root); 
    FixLen(ans.Root);
    return ans;
}
void Del_NodeCST(Node* pR , int &id) {
    if(pR) {
        pR->Root_PT.remove_PT(id);   
        if(pR->Root_PT.size() == 0) { 
            Del_NodeCST(pR->left , pR->id);
            Del_NodeCST(pR->right , pR->id);
            delete pR; pR = nullptr;  
        }
    }
}
ConcatStringTree::~ConcatStringTree() {
    Del_NodeCST(this->Root , this->Root->id);
} 
int ConcatStringTree::getParTreeSize(const string & query) const {
    for(int i = 0 ; i < query.length() ; i++) {
        if(query[i] == 'r' || query[i] == 'l') continue;
        else throw runtime_error("Invalid character of query");
    }
    Node *p = this->Root;
    for(int i = 0 ; i < query.length() ; i++) {
        if(query[i] == 'l') {
            if(p->left) p = p->left;
            else throw runtime_error("Invalid query: reaching NULL");
        }else {
            if(p->right) p = p->right;
            else throw runtime_error("Invalid query: reaching NULL");
        }
    }
    return p->Root_PT.size();
}
string ConcatStringTree::getParTreeStringPreOrder(const string & query) const {
    for(int i = 0 ; i < query.length() ; i++) {
        if(query[i] == 'r' || query[i] == 'l') continue;
        else throw runtime_error("Invalid character of query");
    }
    Node *p = this->Root;
    for(int i = 0 ; i < query.length() ; i++) {
        if(query[i] == 'l') {
            if(p->left) p = p->left;
            else throw runtime_error("Invalid query: reaching NULL");
        }else {
            if(p->right) p = p->right;
            else throw runtime_error("Invalid query: reaching NULL");
        }
    }
    return p->Root_PT.toStringPreOrder();
}


// ----------------class HashConfig ---------------------


HashConfig::HashConfig() {
    this->alpha = 0; this->c1 = 0; this->c2 = 0; this->initSize = 0; this->lambda = 0; this->p = 0;
}
HashConfig::HashConfig(int P , double C1 , double C2 , double Lambda , double Alpha , int IntSize) {
    this->alpha = Alpha; this->c1 = C1; this->c2 = C2; this->initSize = IntSize; this->lambda = Lambda; this->p = P;
}    


// ----------------class LitStringHash ---------------------


LitStringHash::LitStringHash(const HashConfig & hashConfig) {
    this->config = hashConfig;
    int size = this->config.initSize;
    this->Arr = new LitNode[size]; 
    this->id_last = -1;
    this->nE = 0;
}
int LitStringHash::getLastInsertedIndex() const {
    return this->id_last;
}
string LitStringHash::toString() const { 
    if(Arr != nullptr) {
        string str = "";
        for(int i = 0 ; i < this->config.initSize ; i++) {
            if(Arr[i].str != "") str += ("(litS=\"" + Arr[i].str + "\");");
            else str += "();";
        }
        str = str.erase(str.length() - 1);
        return "LitStringHash[" + str + "]";
    }else  return "LitStringHash[]";;
}
void LitStringHash::ReHashing() {
    int preSize = this->config.initSize; bool lastId = true;
    int newSize = this->config.alpha * this->config.initSize;
    this->config.initSize = newSize;
    LitNode* NewArr = new LitNode[newSize];
    for(int i = 0 ; i < preSize ; i++) {
        if(this->Arr[i].str != "") {
            int j = 0;
            while(j < newSize) {
                int index = Quad_Probing(this->Arr[i].str , j);
                if(NewArr[index].str == "") {
                    if(this->id_last == i && lastId) {lastId = false; this->id_last = index;}
                    NewArr[index] = this->Arr[i];
                    break;
                } else {
                    j++;
                }
            }
            if(j >= newSize) throw runtime_error("No possible slot");
        }
    } 
    delete[] this->Arr; 
    this->Arr = NewArr;
}
bool LitStringHash::Certain(string s, int &id_s , int &id_ok) {
    int i = 0; bool first = true;
    while (i < this->config.initSize) {
        int index = this->Quad_Probing(s , i);
        if(this->Arr[index].str == "") {
            if(first) {
                id_ok = index;
                first = false;
            } 
            i++;
        } else if(this->Arr[index].str == s) {
            id_s = index;
            return true;
        } else {
            i++;
        }
    }
    return false;
}
int LitStringHash::HashFuntion(string s) {
    int H = 0; int P = 1;
    for(int i = 0 ; i < (int)s.length() ; i++) {
        H += s[i]*P;
        P = P * this->config.p;
    }
    H = H % this->config.initSize;
    return H;
}
int LitStringHash::Quad_Probing(string s, int i) {
    int H = this->HashFuntion(s);
    int id = ((int)(H + this->config.c1 * i + this->config.c2 * i * i)) % this->config.initSize;
    return id;
}
LitStringHash::~LitStringHash() {
    if(this->Arr != nullptr ){
        delete[] this->Arr; this->Arr = nullptr; 
        this->nE = 0;
        this->id_last = -1;
    }
}


// ----------------class ReducedConcatStringTree ---------------------


ReducedConcatStringTree ReducedConcatStringTree::concat(const ReducedConcatStringTree & otherS) {
    ReducedConcatStringTree ans("");
    ans.litStringHash = this->litStringHash;
    ans.Root->left = this->Root;
    ans.Root->right = otherS.Root;
    ans.Root->leftLength = this->Root->length;
    ans.Root->length = this->Root->length + otherS.Root->length;
    Insert_PT_Node(ans.Root, ans.Root->id);
    return ans;
}
ReducedConcatStringTree::ReducedConcatStringTree(const char * s) : ConcatStringTree(s) {}
ReducedConcatStringTree::ReducedConcatStringTree(const char * s, LitStringHash * litStringHash) : ConcatStringTree() {
    this->litStringHash = litStringHash;
    if(this->litStringHash->Arr == nullptr) {
        int size = this->litStringHash->config.initSize;
        this->litStringHash->Arr = new LitNode[size];
    } 
    bool ck = false;
    int id_s = -1 , id_ok = -1;
    if(this->litStringHash->Certain(s , id_s , id_ok)) {
        if(id_s != -1) this->Root = new Node(this->litStringHash->Arr[id_s].str);
        if(id_s != -1) this->litStringHash->Arr[id_s].nLink++;
    } else {
        this->Root = new Node(s); 
        if(id_ok != -1) this->litStringHash->Arr[id_ok].str = this->Root->data;
        if(id_ok != -1) this->litStringHash->Arr[id_ok].nLink++;
        ck = true;
        this->litStringHash->nE++;
        this->litStringHash->id_last = id_ok;
    }
    if(id_ok == -1 && id_s == -1) throw runtime_error("No possible slot");
    if(ck) {
        double n = (double)this->litStringHash->nE / this->litStringHash->config.initSize;
        if(n > this->litStringHash->config.lambda) {
            this->litStringHash->ReHashing();
        }
    }
    St_id++;
}
ReducedConcatStringTree::~ReducedConcatStringTree(){ 
    if(this->litStringHash->Arr != nullptr && this->Root->data != ""){
        int i = 0; 
        while(i < this->litStringHash->config.initSize) {
            int index = this->litStringHash->Quad_Probing(this->Root->data , i);
            if(this->litStringHash->Arr[index].str == this->Root->data) {
                this->litStringHash->Arr[index].nLink--; 
                if(this->litStringHash->Arr[index].nLink == 0) {
                    this->litStringHash->Arr[index].str = "";
                    this->litStringHash->nE--;
                }
                break;
            } else {
                i++;
            } 
        } 
    }      
    if(this->litStringHash->nE == 0) {
        delete[] this->litStringHash->Arr;
        this->litStringHash->Arr = nullptr;
        this->litStringHash->id_last = -1;
    }
}
    









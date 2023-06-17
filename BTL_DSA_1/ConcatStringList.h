#ifndef __CONCAT_STRING_LIST_H__
#define __CONCAT_STRING_LIST_H__

#include "main.h"

struct CharALNode{      // Node of Class concatStringList
    string s;
    CharALNode* next;
    CharALNode() : s("") , next(nullptr) {}
    CharALNode(string S) : s(S) , next(nullptr) {}
};
struct List{            // Head and Tail of Class concatStringList
    CharALNode* head = nullptr;
    CharALNode* tail = nullptr;
};
struct RefNode{      // Node of Class ReferencesList
    CharALNode * Address;
    int nRef;
    RefNode * next;
    RefNode() : Address(nullptr) , nRef(0) , next(nullptr) {}
    RefNode(CharALNode* add) : Address(add) , nRef(1) , next(nullptr) {}
};
struct ListR{            // Head and Tail of Class ReferancesList
    RefNode* head = nullptr;
    RefNode* tail = nullptr;
};
struct DelNode{      // Node of Class DeleteStringList
    CharALNode* heahref;
    CharALNode* tailref;
    bool H_ok , T_ok;
    DelNode* next;
    DelNode() : heahref(nullptr) , tailref(nullptr) , next(nullptr) , H_ok(true) , T_ok(true) {}
    DelNode(List A) : heahref(A.head) , tailref(A.tail) , next(nullptr) , H_ok(true) , T_ok(true) {}
};
struct ListD{        // Head and Tail of Calss DeleteStringList
    DelNode* head = nullptr;
    DelNode* tail = nullptr;
};


class ConcatStringList {
private:
    List A;
    string str;
    int nC;
public:
    class ReferencesList; // forward declaration
    class DeleteStringList; // forward declaration

public:
    static ReferencesList refList;
    static DeleteStringList delStrList;
    
    // TODO: may provide some attributes
public:
    ConcatStringList() {
        str = "";
        nC = 0;
    }
    ConcatStringList(const char* s) {
        A.head = new CharALNode(s);
        A.tail = A.head;
        str = s;
        nC = str.length();
        refList.NewRef(this->A);
    }
    ConcatStringList(const ConcatStringList & other){
        this->A = other.A;
        this->nC = other.nC;
        this->str = other.str;
        refList.OldRef(this->A);
    }
    int length() const {
        return nC;
    }
    char get(int index) const {
        if(index < 0 || index >= nC) 
            throw out_of_range("Index of string is invalid!");
        return str[index];    
    }
    int indexOf(char c) const {
         for(int i = 0 ; i < nC ; i++){
            if(c == str[i]) return i;
         }
         return -1;
    }
    std::string toString() const {
        std::string tmp = "";
        CharALNode* p = this->A.head;
        while(p != this->A.tail->next){
            tmp += p->s;
            p = p->next;
        }
        return tmp;
    }
    ConcatStringList concat(const ConcatStringList & otherS) const {  // concat two concatStringList
        ConcatStringList tmp;
        tmp.A.head = this->A.head;
        tmp.A.tail = this->A.tail;
        tmp.A.tail->next = otherS.A.head;
        tmp.A.tail = otherS.A.tail;
        tmp.str = this->str + otherS.str;
        tmp.nC = this->nC + otherS.nC;
        refList.OldRef(tmp.A);
        return tmp;
    }
    ConcatStringList subString(int from, int to) const {   // cut from -> to index and return a new concatStringList 
        if(from < 0 || from >= nC || to < 0 || to > nC) throw out_of_range("Index of string is invalid");
        if(from >= to) throw logic_error("Invalid range");
        ConcatStringList tmp;
        CharALNode* OthNode = this->A.head;
        tmp.A.head = new CharALNode(OthNode->s);
        OthNode = OthNode->next;
        CharALNode* p = tmp.A.head;
        while(OthNode != this->A.tail->next){
            CharALNode* tmp = new CharALNode(OthNode->s);
            p->next = tmp;
            p = p->next;
            OthNode = OthNode->next;
        }
        tmp.A.tail = this->A.tail; 
        tmp.nC = this->nC;
        tmp.str = this->str;
        tmp.nC = to - from + 1;
        p = tmp.A.head;
        while(p != nullptr){
            if(from <= p->s.length() - 1){
                p->s = p->s.substr(from);
                to -= from;
                tmp.A.head = p;
                break;
            }else{
                from -= p->s.length();
                to -= p->s.length();
                CharALNode* node = p;
                p = p->next;
                delete node;
                node = nullptr;
            }
        }
        while(p != nullptr){
            if(to <= p->s.length()){
                p->s = p->s.substr(0, to);
                tmp.A.tail = p; 
                break;
            }else{
                to -= p->s.length();
                p = p->next;
            }
        }
        p = p->next;
        while(p != nullptr){
            CharALNode* node = p;
            p = p->next;
            delete node;
            node = nullptr;
        }
        p = tmp.A.head;
        string tmpstr = "";
        while(p != tmp.A.tail->next){
            tmpstr += p->s;
            p = p->next;
        }
        tmp.str = tmpstr;
        refList.NewRef(tmp.A);
        return tmp;
    }
    ConcatStringList reverse() const {   // Reverse and return a new concatStringList 
        ConcatStringList tmp;
        CharALNode* OthNode = this->A.head;
        tmp.A.head = new CharALNode(OthNode->s);
        OthNode = OthNode->next;
        CharALNode* p = tmp.A.head;
        while(OthNode != this->A.tail->next){
            CharALNode* tmp = new CharALNode(OthNode->s);
            p->next = tmp;
            p = p->next;
            OthNode = OthNode->next;
        }
        tmp.A.tail = this->A.tail; 
        tmp.nC = this->nC;
        tmp.str = this->str;
        tmp.A.tail = tmp.A.head;
        CharALNode* prev = nullptr;
        CharALNode* curr = tmp.A.head;
        CharALNode* nxt = nullptr;
        while(curr != nullptr){
            nxt = curr->next;
            curr->next = prev;
            prev = curr;
            curr = nxt;
        }
        tmp.A.head = prev;
        curr = tmp.A.head;
        string tmpstr = "";
        while(curr != tmp.A.tail->next){
            int len = curr->s.length();
            if(len % 2 == 0) len--;
            for(int i = len/2 ; i > -1 ; --i){
                swap(curr->s[i] , curr->s[curr->s.length() - 1 -i]);
            }
            tmpstr += curr->s; 
            curr = curr->next;
        }
        tmp.str = tmpstr;
        refList.NewRef(tmp.A);
        return tmp;
    }
    ~ConcatStringList() {    
            refList.DecNRef(this->A);    //   decrease number of references
            delStrList.AddNodeDel(this->A);  // add a new node for DeleteStringList
            refList.sort(); 
            delStrList.CheckConcat();    // sort node of ReferencesList
            delStrList.CheckAndRemove();   // check node has total nREf = 0 , remove this concatStringList, remove this node of deleteStringList
            if(refList.check()) refList.RemoveList();   // if total nRef of ReferencesList == 0 clear all node;
    }
public:
    class ReferencesList {
        // TODO: may provide some attributes
        private:
            ListR B;
            int nN;
        public:
            ReferencesList() : nN(0) {}
            void NewRef(const List Ref) {   // method update references Head ans tail of new concatStringList
                if(B.head != nullptr){   // have a node head
                    if(Ref.head == Ref.tail){    //   update nRef for new ConcatSringList (1 node)
                        RefNode* tmp = new RefNode(Ref.head);
                        tmp->nRef++;
                        B.tail->next = tmp;
                        B.tail = tmp;
                        nN++;
                    }else{   // update nRef for new ConcatStringList (n node)   
                        RefNode* tmpT = new RefNode(Ref.tail);
                        RefNode* tmpH = new RefNode(Ref.head);
                        tmpH->next = tmpT;
                        B.tail->next = tmpH;
                        B.tail = tmpT;
                        nN += 2;
                    }     
                }else{   // first node 
                     if(Ref.head == Ref.tail){    //   update nRef for new ConcatSringList
                        RefNode* tmp = new RefNode(Ref.head);
                        tmp->nRef++;
                        B.head = tmp;
                        B.tail = tmp;
                        nN++;
                    }else{   // update nRef for new ConcatStringList (n node) 
                        RefNode* tmpT = new RefNode(Ref.tail);
                        RefNode* tmpH = new RefNode(Ref.head);
                        tmpH->next = tmpT;
                        B.head = tmpH;
                        B.tail = tmpT;
                        nN += 2;
                    }   
                }
                refList.sort();
            }
            void OldRef(const List Ref){   // method update references Head and tail of old concatStringList
                RefNode* p = B.head;
                while(p != B.tail->next){    
                    if(p->Address == Ref.head) p->nRef++;
                    if(p->Address == Ref.tail) p->nRef++;
                    p = p->next;
                }
                refList.sort();
            }
            void DecNRef(const List Ref){    // method decrease number of References 
                RefNode* p = B.head;
                while(p != B.tail->next){
                    if(Ref.head == p->Address) p->nRef--;
                    if(Ref.tail == p->Address) p->nRef--;
                    p = p->next;
                }
            }
            int GetNRef(CharALNode* cnode){    // method get Number of References
                RefNode* p = B.head;
                while(p != B.tail->next){
                    if(p->Address == cnode) {
                        return p->nRef;
                        break;
                    }
                    p = p->next;
                }
            }
            int size() const { 
                return nN;
            }
            int refCountAt(int index) const {  // method print number of references at index
                if(index < 0 || index >= nN) throw out_of_range("Index of references list is invalid!");
                RefNode* p = B.head;
                for(int i = 0 ; i < index ; i++){
                    p = p->next;
                }
                return p->nRef;
            }
            std::string refCountsString() const{    // method print all number of references in ReferencesList
                if(nN == 0) return "RefCounts[]";
                string str = "";
                str += "RefCounts[";
                RefNode* p = B.head;
                while(p->next != B.tail->next){
                    str += to_string(p->nRef);
                    str += ",";
                    p = p->next;
                }  
                str += to_string(p->nRef);
                str += "]";
                return str;
            }
            void sort() {   // sort node in referencesList acsending oder and move '0' to the end
                for(RefNode* p = B.head ; p != B.tail->next ; p = p->next){
                    if(p->nRef == 0) p->nRef = 100;
                }
                for(RefNode* p = B.head ; p != B.tail ; p = p->next){
                    RefNode* min = p;
                    for(RefNode* q = p->next ; q != B.tail->next ; q = q->next){
                        if(min->nRef > q->nRef){
                            min = q;
                        }
                    }
                    CharALNode* tmp = min->Address;
                    int tmpN = min->nRef;
                    min->Address = p->Address;
                    min->nRef = p->nRef;
                    p->Address = tmp;
                    p->nRef = tmpN;
                }
                for(RefNode* p = B.head ; p != B.tail->next ; p = p->next){
                    if(p->nRef == 100) p->nRef = 0;
                }
            }
            bool check(){   // condition remove all node of ReferencesList
                RefNode* p = B.head;
                while(p != B.tail->next){
                    if(p->nRef != 0) return false;
                    p = p->next;
                }
                return true;
            }
            void RemoveList(){  
                while(B.head != B.tail->next){
                    RefNode* node = B.head;
                    B.head = node->next;
                    delete node;
                    node = nullptr;
                    // if(B.head == nullptr){
                    //     B.tail = nullptr;
                    // }
                }
                nN = 0;
            }
            ~ReferencesList() {
                while(B.head != nullptr){
                    RefNode* tmp = B.head;
                    B.head = B.head->next;
                    delete tmp;
                    tmp = nullptr;
                    if(B.head == nullptr) B.tail = nullptr;
                }
                nN = 0;
            }
    };

    class DeleteStringList {
        // TODO: may provide some attributes
        private:
            ListD C;
            int nE;
        public:
            DeleteStringList() : nE(0) {}
            void AddNodeDel(const List Del) {   // add new node when delete a concatStringList
                DelNode* tmp = new DelNode(Del);
                if(C.head == nullptr){
                    C.head = tmp;
                    C.tail = C.head;
                }else{
                    C.tail->next = tmp;
                    C.tail = tmp;
                }
                nE++; 
            }
            int size() const {
                return nE;
            }
            void CheckConcat(){
                DelNode* p = C.head;
                while(p != C.tail->next){
                    if((refList.GetNRef(p->heahref) + 1) > 2 && (refList.GetNRef(p->heahref) + 1) % 2) p->H_ok = false;
                    if((refList.GetNRef(p->tailref) + 1) > 2 && (refList.GetNRef(p->tailref) + 1) % 2) p->T_ok = false;
                    p = p->next;
                }
            }
            std::string totalRefCountsString() const { // return string all total references of node in deletestringList 
                if(nE == 0) return "TotalRefCounts[]";
                string res = "TotalRefCounts[";
                DelNode* p = C.head;
                while(p != C.tail->next){
                    if(p->heahref != p->tailref)
                        res += to_string((refList.GetNRef(p->heahref) + refList.GetNRef(p->tailref)));   // concatStringList (n node)
                    else   // concatStringList (1 node)
                        res += to_string(refList.GetNRef(p->heahref));
                    p = p->next;
                    res += ",";
                }
                if(res[res.length()-1] == ',') res = res.erase(res.length()-1);
                return res + "]";
            }
            void CheckAndRemove(){  // check node has total nREf = 0 , remove this concatStringList, remove this node of deleteStringList
                DelNode* p = C.head;   
                DelNode* pre = nullptr;
                while(p != C.tail->next) {
                    if(refList.GetNRef(p->heahref) + refList.GetNRef(p->tailref) == 0){      // remove all node of concatStringList 
                        --nE;   
                        CharALNode* h = p->heahref;  
                        CharALNode* t = p->tailref;
                        DelNode* Dnode = C.head;
                        if(p->H_ok && p->T_ok){
                            while(h != t->next){
                                CharALNode* node = h; 
                                h = h->next;
                                delete node;
                                node = nullptr;
                            }
                        }
                        if(p == C.head){   // remove node in DeleteStringList
                            DelNode* node = C.head;
                            C.head = C.head->next;
                            delete node;
                            node = nullptr;
                            p = C.head;
                            continue;
                        }else if(p == C.tail){
                            DelNode* node = C.tail;
                            C.tail = pre;
                            C.tail->next = nullptr;
                            delete node;
                            node = nullptr; 
                            p = pre;
                        }else{
                            DelNode* node = p;
                            pre->next = p->next;
                            delete node;
                            node = nullptr;
                            p = pre;
                        }
                    }
                    pre = p;
                    p = p->next;
                }
            }
            ~DeleteStringList() {
                if(nE > 0){
                    while(C.head != nullptr ){
                        DelNode* tmp = C.head;
                        C.head = C.head->next;
                        delete tmp;
                        tmp = nullptr;
                        if(C.head == nullptr) C.tail == nullptr;
                    }
                    nE = 0;
                }
            }
    };

};


ConcatStringList::ReferencesList ConcatStringList::refList = ConcatStringList::ReferencesList();
ConcatStringList::DeleteStringList ConcatStringList::delStrList = ConcatStringList::DeleteStringList();

#endif // __CONCAT_STRING_LIST_H__
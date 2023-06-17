#include "ConcatStringTree.h"

void tc1()
{
    ConcatStringTree s1("acbcad");
 
    cout << s1.length() << endl;
    cout << s1.get(1) << endl;
    try
    {
        cout << "char at index 10: " << s1.get(10) << endl;
    }
    catch (const out_of_range &ofr)
    {
        cout << "Exception out_of_range: " << ofr.what() << endl;
    }
    cout << s1.indexOf('b') << endl;
}
void tc2()
{
    ConcatStringTree s1("Hello");
    ConcatStringTree s2(",_t");
    ConcatStringTree s3 = s1.concat(s2);
    cout << s3.toStringPreOrder() << endl;
    cout << s3.toString() << endl;
    cout << s3.subString(5, 6).toString() << endl;
    cout << s3.reverse().toString() << endl;
}
void tc3()
{
    ConcatStringTree *s1 = new ConcatStringTree("a");
    ConcatStringTree *s2 = new ConcatStringTree("b");
    ConcatStringTree *s3 = new ConcatStringTree(s1->concat(*s2));

    cout << s3->getParTreeSize("l") << endl;
    cout << s3->getParTreeStringPreOrder("l") << endl;

    delete s1;
    delete s2;
    delete s3;
}
void tc4()
{
    HashConfig hashConfig(
        2,
        0.5,
        0.5,
        0.5,
        2,
        4);
    LitStringHash *litStringHash = new LitStringHash(hashConfig); 

    ReducedConcatStringTree *s1 = new ReducedConcatStringTree("a", litStringHash);
    ReducedConcatStringTree *s2 = new ReducedConcatStringTree("bb", litStringHash);

    cout << s1->toString() << endl;
    cout << s2->toString() << endl;
    ReducedConcatStringTree *s3 = new ReducedConcatStringTree("bb", litStringHash);

    cout << litStringHash->getLastInsertedIndex() << endl;
    cout << litStringHash->toString() << endl;

    delete litStringHash;   
    delete s3;
    delete s1;
    delete s2;
}
void tc5()
{
    ConcatStringTree s1("Hello");
    cout << "Please focus to id: " << s1.getParTreeStringPreOrder("") << endl;
    ConcatStringTree s2("an-nyeong-ha-se-yo");
    cout << "Please focus to id: " << s2.getParTreeStringPreOrder("") << endl;
    ConcatStringTree s3("nee how");
    cout << "Please focus to id: " << s3.getParTreeStringPreOrder("") << endl;
}
void tcMHH() {
    HashConfig hashConfig(
    2,
    0.5,
    0.5,
    0.75,
    2,
    4);
    LitStringHash* Hashtable = new LitStringHash(hashConfig);
    ReducedConcatStringTree* s0 = new ReducedConcatStringTree("Nguyen" , Hashtable);
    cout << Hashtable->toString() << endl;
    ReducedConcatStringTree* s1 = new ReducedConcatStringTree("Hieu" , Hashtable);
    cout << Hashtable->toString() << endl;
    ReducedConcatStringTree* s2 = new ReducedConcatStringTree("Danh" , Hashtable);
    cout << Hashtable->toString() << endl;
    ReducedConcatStringTree* s3 = new ReducedConcatStringTree("Binh" , Hashtable);
    cout << Hashtable->toString() << endl;
    ReducedConcatStringTree* s4 = new ReducedConcatStringTree("Hieu" , Hashtable);
    cout << Hashtable->toString() << endl;
    ReducedConcatStringTree* s5 = new ReducedConcatStringTree(s1->concat(*s2));
    ReducedConcatStringTree* s6 = new ReducedConcatStringTree(s3->concat(*s4));
    ReducedConcatStringTree* s7 = new ReducedConcatStringTree(s5->concat(*s6));
    ReducedConcatStringTree* s10 = new ReducedConcatStringTree(s2->concat(*s3));
    // ReducedConcatStringTree* s9 = new ReducedConcatStringTree(s2->concat(*s3));
    // ReducedConcatStringTree* s12 = new ReducedConcatStringTree(s2->concat(*s3));
    cout << s7->toStringPreOrder() << endl;
    
    // delete s7;
    // cout << Hashtable->toString() << endl;
    // delete s6;
    // cout << Hashtable->toString() << endl;
    // delete s5;
    // cout << Hashtable->toString() << endl;
    delete s4;
    cout << Hashtable->toString() << endl;
    delete s3;
    cout << Hashtable->toString() << endl;
    delete s2;
    cout << Hashtable->toString() << endl;
    delete s1;
    cout << Hashtable->toString() << endl;
    delete s0;
    cout << Hashtable->toString() << endl;
    
    // ReducedConcatStringTree* s11 = new ReducedConcatStringTree("Nguyen" , Hashtable);
    
    // ReducedConcatStringTree* s14 = new ReducedConcatStringTree("Ha" , Hashtable);

    // cout << Hashtable->toString() << endl;


}

void bkel4()
{
    HashConfig hashConfig(
        2,
        0.5,
        0.5,
        0.75,
        1.5,
        4);
        
    LitStringHash *litStringHash = new LitStringHash(hashConfig);
    ReducedConcatStringTree *s1 = new ReducedConcatStringTree("a", litStringHash);
    ReducedConcatStringTree *s2 = new ReducedConcatStringTree("bb", litStringHash);
    cout << s1->toString() << endl;
    cout << s2->toString() << endl;
    ReducedConcatStringTree *s3 = new ReducedConcatStringTree(s1->concat(*s2));
    ReducedConcatStringTree *s4 = new ReducedConcatStringTree("a", litStringHash);
    ReducedConcatStringTree *s5 = new ReducedConcatStringTree("bb", litStringHash);
    ReducedConcatStringTree *s6 = new ReducedConcatStringTree(s4->concat(*s5));
    ReducedConcatStringTree *s7 = new ReducedConcatStringTree(s3->concat(*s4));

    cout << litStringHash->getLastInsertedIndex() << endl;
    cout << litStringHash->toString() << endl;

    ReducedConcatStringTree *s8 = new ReducedConcatStringTree("c", litStringHash);

    ReducedConcatStringTree *s9 = new ReducedConcatStringTree("dd", litStringHash);
    cout << "bla" << endl;
    cout << litStringHash->getLastInsertedIndex() << endl;
    cout << litStringHash->toString() << endl;
    ReducedConcatStringTree *s10 = new ReducedConcatStringTree("e", litStringHash);
    ReducedConcatStringTree *s11 = new ReducedConcatStringTree("f", litStringHash);
    cout << litStringHash->getLastInsertedIndex() << endl;
    cout << litStringHash->toString() << endl;
    cout<<"delete s3"<<endl;
    delete s3;
    cout<<"delete s6"<<endl;
    delete s6;
    cout<<"delete s1"<<endl;
    delete s1;
    cout<<"delete s2"<<endl;
    delete s2;
    cout<<"delete s4"<<endl;
    delete s4;
    cout<<"delete s5"<<endl;
    delete s5;
    cout<<"delete s7"<<endl;
    delete s7;
    cout<<"delete s8"<<endl;
    delete s8;
    cout<<"delete s9"<<endl;
    delete s9;
    cout<<"delete s10"<<endl;
    delete s10;
    cout<<"delete s11"<<endl;
    delete s11;
    cout<<"delete litStringHash"<<endl;
    delete litStringHash;
    cout << "delete completed" << endl;
}
int main() {

    tc1();
    return 0;
}
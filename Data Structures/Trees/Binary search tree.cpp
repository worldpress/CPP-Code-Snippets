// Binary search tree data structure
// this is not a balanced tree
// search, insertion and remove take O(h) [h is the height of the tree]

#include <iostream>
#include <cstdio>

using namespace std;

short CC_;
#define PP getchar();
#define NL cout<<"\n";
#define pqueue priority_queue
#define test(x_, i_) ((x_&1<<i_)!=0)
#define DC(x_) cout<<">>> "<<#x_<<"\n";DA(x_.begin(), x_.end());
#define DD(x_) cout<<">>>>( "<<++CC_<<" ) "<<#x_<<": "<<x_<<endl;
#define SS printf(">_<LOOOOOK@MEEEEEEEEEEEEEEE<<( %d )>>\n",++CC_);
#define EXT(st_) cout<<"\n>>>Exicution Time: "<<(double)(clock()-st_)/CLOCKS_PER_SEC<<endl;


template <typename T>
class bst{
private:
    class Node{
    public:
        T data;
        //left and right child
        Node *lChild, *rChild;
        Node(){
            data = T();
            rChild= lChild= NULL;
        }
        Node(const T& dt){
            data = dt;
            rChild= lChild= NULL;
        }
    };
    Node* root;
    int nodeCount;    
    
public:
    //default constructor
    bst(){
        root= NULL;
        nodeCount= 0;
    }
    
    inline bool empty(){
        return nodeCount == 0;
    }
    
    inline int size(){
        return nodeCount;
    }
    
    //find element in tree, returns it's pointer, returns NULL if not found
    T* find(Node* root, const T& target){
        if(root == NULL) return NULL;
        if(root->data == target) return &(root->data);
        
        if(root->data >target) return find(root->lChild, target);
        else return find(root->rChild, target);
    }
    
    //wrapper function
    T* find(const T& target){
        if(empty()) return NULL;
        return find(root, target);
    }
    
    void insert(Node** troot, const T& dt){
        nodeCount++;
        if(*troot == NULL){
            *troot = new Node(dt);
            return;
        }
        
        if((*troot)->data == dt){
            nodeCount--;
            return;
        }
        if((*troot)->data > dt){
            insert(&((*troot)->lChild), dt);
            return;
        }
        else{
            insert(&((*troot)->rChild), dt);
            return;
        }
    }
    
    //wrapper function
    void insert(const T& dt){
        if(empty()){
            nodeCount++;
            root= new Node(dt);
            return;
        }
        else insert(&root, dt);   
    }
    
    
    void remove(Node** doom, const T& target){
        if(*doom == NULL) return;
        if((*doom)->data == target){
            nodeCount--;
            bool l= (*doom)->lChild != NULL;
            bool r= (*doom)->rChild != NULL;
            //if the node is a leaf
            if(!r && !l){
                *doom= NULL;
                delete *doom;
                return;
            }
            Node** newRoot= &(*doom)->rChild;
            //finding new root
            if(newRoot != NULL){
//                DD(newRoot->rChild)
                while((*newRoot)->lChild != NULL){
                    newRoot = &((*newRoot)->lChild);
                }
            }
            else{
                newRoot= &(*doom)->lChild;
                while((*newRoot)->rChild != NULL){
                    newRoot = &((*newRoot)->rChild);
                }
            } 
//            DD(newRoot->data)
            swap((*doom)->data, (*newRoot)->data);
            *newRoot= NULL;
            delete *newRoot;
            return;
        }
        
        if((*doom)->data > target)
            remove(&(*doom)->lChild, target);
        else
            remove(&(*doom)->rChild, target);
    }
    
    void remove(const T& target){
        if(!empty()) remove(&root, target);
    }
    
    //traverse and print each element in-order
    void inOrder(Node* root){
        if(root == NULL) return;
        inOrder(root->lChild);
        std::cout<< root->data <<" ";
        inOrder(root->rChild);
    }
    
    //in order traversal wrapper function
    void inOrder(){
        if(empty()) return;
        inOrder(root);
        std::cout<<std::endl;
    }
    
    void clear(Node* doom){
        if(doom == NULL) return;
        clear(doom->lChild);
        clear(doom->rChild);
        
        delete doom;
    }
    
    //wrapper fucntion
    inline void clear(){
        if(!empty()){
            clear(root);
            nodeCount= 0;
        }
    }
    
    ~bst(){
        clear();
    }
};


int main(void)
{
    using namespace std;
    
    bst<int> t;
    
    t.insert(5);
    t.insert(1);
    t.insert(0);
    t.insert(32);
    t.insert(12);
    t.insert(3);
    t.insert(4);
    
    t.inOrder();
    t.clear();
    t.remove(5);
    t.remove(5);
    t.remove(0);
    t.remove(32);
    t.remove(4);
    
    t.inOrder();
    
//    cout<< *t.find(5) <<endl;
    
    return 0;
}
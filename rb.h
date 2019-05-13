#ifndef rb_h
#define rb_h
#include <string>
#include <list>
using namespace std;

template <typename T>
class rb{
    private:
        struct Key;
        struct Node;
        Node *root;
        Node * sentinel;
        struct Node{
            char color;
            Key *key;
            Node *left;
            Node *right;
            Node *parent;
            Node(char c, T k, Node* p, Node* l, Node* r){
                color=c;
                key = new Key(k);
                parent = p;
                left = l;
                right = r; 
            }
            Node(){
                color='B';
                key = NULL;
                parent = NULL;
                left = NULL;
                right = NULL; 

            }
        };
        struct Key{
            T key;
            Key(T k){
                key=k;
            }
        };
        Node* minimum(Node*node);
        void leftRotate(Node* node);
        void rightRotate(Node* node);
        void insertFix(Node* node);
        void removeFix(Node* node);
        void transplant(Node* u, Node* v);
        Node* look(Node* node, T value);
        void print(Node* node, int depth, int rec[], int n);
        int height(Node* node);

  public:
    // Construtor
    rb();
    // Search
    bool search(T value);
    // Insert
    void insert(T value);
    // Remove
    void remove(T value);
    // Maximum
    T max();
    // Minimum
    T min();
    // Print ?
    void printRB(int n);
};

#endif
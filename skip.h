#ifndef skip_h
#define skip_h
#include <string>
#include <list>
using namespace std;

template <typename T>
class skip{
    private:
        struct Key;
        struct Node;
        Node *header;
        Node *sentinel;
        struct Node{
            int level;
            Key *key;
            Node *up;
            Node *down;
            Node *next;
            Node *prev;
            Node(T value,int lvl){
                key = new Key(value);
                level=lvl;
                up = NULL;
                down= NULL;
                next = NULL;
                prev = NULL;
            }
            Node(int lvl){
                key = NULL;
                level=lvl;
                up = NULL;
                down= NULL;
                next = NULL;
                prev = NULL;

            }
        };
        struct Key{
            T key;
            Key(T k){
                key=k;
            }
        };
        Node* insertAbove(Node* node);

  public:
    // Construtor
    skip();
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
    // Print
    void printSkip();
};

#endif
#include <iostream>
#include <stdio.h>
#include <climits>
#include <string> 
#include <cmath>
#include "rb.h"

using namespace std;

template <typename T>
rb<T>::rb(){
    sentinel=new Node();
    sentinel->left=sentinel;
    sentinel->right=sentinel;
    sentinel->parent=sentinel;
    root=new Node();
    root->parent=sentinel;
}

template <typename T>
typename rb<T>::Node *rb<T>::look(Node *node, T value){
    //cout << "///// LOOK " << value << endl;
    if(node->key==NULL)
        return sentinel;
    if(node->key->key==value)
        return node;
    if(value < node->key->key)
        return look(node->left,value);
    return look(node->right,value);
}

template <typename T>
bool rb<T>::search(T value){
    //cout << "///// SEARCH " << value << endl;
    Node *node=look(root,value);
    if(node->key!=NULL && node->key->key==value)
        return true;
    else
        return false;
}

template <typename T>
void rb<T>::insert(T value){
    //cout << "///// INSERT " << value << endl;
    // New node is red
    Node *new_node=new Node('R',value,NULL,NULL,NULL);
    Node *y=sentinel;
    Node *x=root;
    // Standard BST
    while(x->key!=NULL){
        y=x;
        if(x->key->key==value)
            return;
        if(value<x->key->key){
            x=x->left;
        }
        else{
            x=x->right;
        }
    }
    new_node->parent=y;
    if(y->key==NULL){
        root=new_node;
    }
    else if(new_node->key!=NULL && new_node->key->key<y->key->key){
        y->left=new_node;
    }
    else{
        y->right=new_node;
    }
    new_node->left=sentinel;
    new_node->right=sentinel;
    // Changes colors and performs rotations to restore the red-black properties
    insertFix(new_node);
}


template <typename T>
void rb<T>::remove(T value){
    //cout << "///// REMOVE " << value << endl;
    Node *node=look(root,value);
    // Node not found, can't be removed
    if(node->key==NULL)
        return;
    Node *y=node;
    Node *x=NULL;
    char original_color=y->color;
    //  Node has fewer than two children -> removed from the tree, and we want y to be the parent
    if(node->left->key==NULL){
        x=node->right;
        transplant(node,node->right);
    }
    //  Node has fewer than two children -> removed from the tree, and we want y to be the parent
    else if(node->right->key==NULL){
        x=node->left;
        transplant(node,node->left);
    }
    // Node has two children, then y should be node's successor, and y moves into  node's position in the tree.
    else{
        y=minimum(node->right);
        // Remember y's color before being removed
        original_color=y->color;
        // Keep track of x, it goes to y's original position and might break some property
        x=y->right;
        if(y->parent->key!=NULL && node->key!=NULL && y->parent->key->key==node->key->key){
            x->parent=y;
        }
        else{
            transplant(y,y->right);
            y->right=node->right;
            y->right->parent=y;
        }
        transplant(node,y);
        y->left=node->left;
        y->left->parent=y;
        y->color=node->color;
    }
    if(original_color=='B'){
        // Changes colors and performs rotations to restore the red-black properties
        removeFix(x);
    }
}

template <typename T>
void rb<T>::leftRotate(Node *node){
    Node *y = node->right;
    node->right = y->left;

    if(y->left->key!=NULL){
        y->left->parent=node;
    } 
    y->parent=node->parent;

    if(node->parent->key==NULL){
        root=y;
    }
    else if(node->key!=NULL && node->parent->left->key!=NULL && node->key->key==node->parent->left->key->key){
        node->parent->left=y;
    }
    else{
        node->parent->right=y;
    }
    y->left=node;
    node->parent=y;
}

template <typename T>
void rb<T>::rightRotate(Node *node){
    Node *y = node->left;
    node->left = y->right;

    if(y->right->key!=NULL){
        y->right->parent=node;
    } 
    y->parent=node->parent;

    if(node->parent->key==NULL){
        root=y;
    }
    else if(node->key!=NULL && node->parent->right->key!=NULL && node->key->key==node->parent->right->key->key){
        node->parent->right=y;
    }
    else{
        node->parent->left=y;
    }
    y->right=node;
    node->parent=y;
}

/*  Properties that might be broken upon call of fix:
        2) root is black
        4) a red node cannot have red children
    'node' is always red since it comes from insert
*/
template <typename T>
void rb<T>::insertFix(Node *node){
    while(node->parent->color=='R'){
        if(node->parent->key!=NULL && node->parent->parent->left->key!=NULL &&  node->parent->key->key==node->parent->parent->left->key->key){
            Node *uncle=node->parent->parent->right;
            // Case 1: Node's uncle is red
            if(uncle->color=='R'){
                node->parent->color='B';
                uncle->color='B';
                node->parent->parent->color='R';
                node=node->parent->parent;
            }
            else{
                // Case 2: Node's uncle is black and node is a right child
                if(node->key!=NULL && node->parent->right->key!=NULL && node->key->key==node->parent->right->key->key){
                    node=node->parent;
                    // Transform in case 3 since node and its parent are red
                    leftRotate(node);
                }
                // Case 3: Node's uncle is black and node is a left child
                node->parent->color='B';
                node->parent->parent->color='R';
                rightRotate(node->parent->parent);
            }
        }
        else{ // same but instead of right is left
            Node *uncle=node->parent->parent->left;
            // Case 1: Node's uncle is red
            if(uncle->color=='R'){
                node->parent->color='B';
                uncle->color='B';
                node->parent->parent->color='R';
                node=node->parent->parent;
            }
            else{
                if(node->key!=NULL && node->parent->left->key!=NULL && node->key->key==node->parent->left->key->key){
                    node=node->parent;
                    rightRotate(node);
                }
                node->parent->color='B';
                node->parent->parent->color='R';
                leftRotate(node->parent->parent);
            }
        }
    }
    // making sure the root is black
    root->color='B';
}

template <typename T>
void rb<T>::removeFix(Node *node){
    while(node->key!=NULL && root->key!=NULL &&  node->key->key!=root->key->key && node->color=='B'){
        if(node->key!=NULL && node->parent->left->key!=NULL && node->key->key==node->parent->left->key->key){
            Node *sibling=node->parent->right;
            // Case 1) sibling is red, it must have black children, rotate parent
            //         new sibling is black, we have Case 2)
            if(sibling->color=='R'){
                sibling->color='B';
                node->parent->color='R';
                leftRotate(node->parent);
                sibling=node->parent->right;
            }
            // Case 2) since sibling and its children are all black, we take
            //         one black off node and sibling, leaving node with 1 black 
            //         and sibling red 
            if(sibling->left->color=='B' && sibling->right->color=='B'){
                sibling->color='R';
                node=node->parent;
            }
            else{
                // Case 3) sibling is black, its left child is red and its right 
                //         child is black, we switch colors between sibling and 
                //         its left child and then perform a right rotation on sibling.
                //         New sibling of node is black with a red right child -> Case 4)
                if(sibling->right->color=='B'){
                    sibling->left->color='B';
                    sibling->color='R';
                    rightRotate(sibling);
                    sibling=node->parent->right;
                }
                // Case 4) sibling is black, its right child is red. Remove extra black
                //         on node by left rotating parent.
                sibling->color=node->parent->color;
                node->parent->color='B';
                sibling->right->color='B';
                leftRotate(node->parent);
                node=root;
            }
        }
        else{ // same but instead of right is left
            Node *sibling=node->parent->left;
            if(sibling->color=='R'){
                sibling->color='B';
                node->parent->color='R';
                rightRotate(node->parent);
                sibling=node->parent->left;
            }
            if(sibling->left->color=='B' && sibling->right->color=='B'){
                sibling->color='R';
                node=node->parent;
            }
            else{
                if(sibling->left->color=='B'){
                    sibling->right->color='B';
                    sibling->color='R';
                    leftRotate(sibling);
                    sibling=node->parent->left;
                }
                sibling->color=node->parent->color;
                node->parent->color='B';
                sibling->left->color='B';
                rightRotate(node->parent);
                node=root;
            }
        }
    }
    node->color='B';
}

template <typename T>
typename rb<T>::Node *rb<T>::minimum(Node *node){
    Node *curr=node;
    while(curr->left->key!=NULL){
        curr=curr->left;
    }
    return curr;
}

template <typename T>
void rb<T>::transplant(Node *u, Node *v){
    if(u->parent->key==NULL)
        root=v;
    else if(u->key!=NULL && u->parent->left->key!=NULL &&  u->key->key==u->parent->left->key->key)
        u->parent->left=v;
    else
        u->parent->right=v;
    // we can assign it even if u->parent is sentinel
    v->parent=u->parent;
}


template <typename T>
T rb<T>::max(){
    Node *curr=root;
    while(curr->right->key!=NULL){
        curr=curr->right;
    }
    return curr->key->key;
}


template <typename T>
T rb<T>::min(){
    Node *curr=root;
    while(curr->left->key!=NULL){
        curr=curr->left;
    }
    return curr->key->key;
}

template <typename T>
void rb<T>::print(Node* curr,int depth,int rec[], int n){
    int i;
    int n2=n/2;
    if(curr==NULL){
        return;
    }
    printf("\t");
    for(i=0;i<depth;i++){
        if(i==depth-1){
            printf("%*s%s\u2014\u2014\u2014",n2," ",rec[depth-1]?"\u0371":"\u221F");
        }
        else{
            printf("%*s%s    ",n2," ",rec[i]?"\u23B8":"  ");
        }
    }
    if(curr->key==NULL)
        cout << "o" <<  endl;
    else if(curr->key!=NULL && curr->left->key==NULL && curr->right->key==NULL){
        printf("(%c)%-*d\n", char(curr->color), n, curr->key->key);
    }
    else{
        printf("(%c)%-*d\n",char(curr->color),  n, curr->key->key);
        rec[depth]=1;
        print(curr->right,depth+1,rec,n);
        rec[depth]=0;
        print(curr->left,depth+1, rec,n);
    }
}


template <typename T>
void rb<T>::printRB(int n){
    int nr = log10(n);
    int rec[1000006];
    print(root,0,rec,nr);
}
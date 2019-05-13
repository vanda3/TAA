#include "skip.h"
#include <iostream>
#include <stdio.h>
#include <climits>
#include <iomanip>
#include <cmath>

using namespace std;

template <typename T>
skip<T>::skip(){
    header = new Node(0);
    sentinel = new Node(0);
    sentinel->prev = header;
    header->next = sentinel;
    srand(time(NULL));
}

template <typename T>
bool skip<T>::search(T value){
    //cout << "///// SEARCH " << value << endl;
    Node *tmp = header;
    // At each level
    while (true){
        // Find highest value lower than value or value
        while (tmp->next->key != NULL && tmp->next->key->key <= value){
            tmp = tmp->next;
        }
        // Until reach level 0
        if (tmp->down != NULL)
            tmp = tmp->down;
        else
            break;
    }

    if (tmp->key != NULL && value == tmp->key->key)
        return true;
    return false;
}

template <typename T>
void skip<T>::insert(T value){
    //cout << "///// INSERT " << value << endl;
    int random;
    Node *new_node = new Node(value, 0);
    Node *tmp = header;
    // For each level
    while (true){
        // Find highest value lower than value or value (tmp)
        while (tmp->next->key != NULL && tmp->next->key->key <= value){
            tmp = tmp->next;
        }
        // Until reach level 0
        if (tmp->down != NULL)
            tmp = tmp->down;
        else
            break;
    }
    // Value already exists
    if (tmp->key != NULL && value == tmp->key->key)
        return;
    // Insert value after tmp and fix pointers
    Node *nxt = tmp->next;
    tmp->next = new_node;
    new_node->next = nxt;
    new_node->prev = tmp;
    nxt->prev = new_node;
    // While heads, value goes up a level
    while (true){
        random = rand() % 2 + 1;
        if (random == 1)
            return;
        else
            new_node = insertAbove(new_node);
    }
}


template <typename T>
typename skip<T>::Node *skip<T>::insertAbove(Node *node){
    Node *tmp = node->prev;
    bool fl = false;
    // Find first element previous to inserted node that goes up
    while (true){
        // Level above already exists - fl true
        if (tmp->up != NULL) {
            tmp = tmp->up;
            fl = true;
            break;
        }
        // We reached header, new level needs to be created
        if (tmp->up == NULL && tmp->prev == NULL)
            break;
        tmp = tmp->prev;
    }
    Node *new_node;
    if (!fl) new_node = new Node(node->key->key, tmp->level + 1);
    else new_node = new Node(node->key->key, tmp->level);
    // Create new level: Create new header and sentinel, link them to previous header and sentinel
    //    insert node by linking it to header and sentinel.
    if (!fl){
        Node *new_header = new Node(header->level + 1);
        Node *new_sentinel = new Node(sentinel->level + 1);
        header->up = new_header;
        sentinel->up = new_sentinel;
        Node *tmp_header = header;
        Node *tmp_sentinel = sentinel;
        new_sentinel->down = tmp_sentinel;
        new_header->down = tmp_header;
        sentinel = new_sentinel;
        header = new_header;
        new_node->prev = header;
        new_node->next = sentinel;
        node->up = new_node;
        new_node->down = node;
        header->next = new_node;
        sentinel->prev = new_node;
    }
    // Add node to existing level by inserting it next to tmp. Fix pointers.
    else{
        new_node->next = tmp->next;
        tmp->next->prev = new_node;
        node->up = new_node;
        new_node->down = node;
        tmp->next = new_node;
        new_node->prev = tmp;
    }
    return new_node;
}

template <typename T>
void skip<T>::remove(T value){
    //cout << "///// REMOVE " << value << endl;
    Node *tmp = header;
    // For each level
    while (true){
        // Find highest value lower than value or value (tmp)
        while (tmp->next->key != NULL && tmp->next->key->key <= value)
            tmp = tmp->next;
        // Until reach level 0
        if (tmp->down != NULL)
            tmp = tmp->down;
        else
            break;
    }
    if (tmp->key != NULL && value == tmp->key->key){
        // Remove value on upper levels. Fix pointers.
        while(tmp!=NULL){
            Node *tmp_left=tmp->prev;
            Node *tmp_right=tmp->next;
            Node *tmp_up=tmp->up;
            tmp_left->next=tmp_right;
            tmp_right->prev=tmp_left;
            tmp=tmp_up;
            tmp=NULL;
        }
    }
}

template <typename T>
T skip<T>::max(){
    // Go down to level 0 from sentinel, and turn left
    Node *tmp=sentinel;
    while(tmp->down!=NULL){
        tmp=tmp->down;
    }
    return tmp->prev->key->key;
}

template <typename T>
T skip<T>::min(){
    // Go down to level 0 from header, and turn right
    Node *tmp=header;
    while(tmp->down!=NULL){
        tmp=tmp->down;
    }
    return tmp->next->key->key;
}

template <typename T>
void skip<T>::printSkip(){
    Node *tmph = header;
    Node *tmp;
    while (tmph != NULL){
        tmp=tmph;
        cout << tmph->level << ": HEADER -> ";
        while (tmp->next->next != NULL){
            tmp = tmp->next;
            cout << tmp->key->key << " -> ";
        }
        cout << "SENTINEL " << endl;
        tmph = tmph->down;
    }
}
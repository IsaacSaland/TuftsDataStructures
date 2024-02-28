/*
 *  CharLinkedList.h
 *  Isaac Saland
 *  2/6/2024
 *
 *  CS 15 HW 2 Cheshire ConCATenation - Time to get linked up in Fur
 *
 *  header file for CharLinkedList that contains all the functions,
 *  constructors, and variables to be implemented in the .cpp file
 *
 */

#ifndef CHAR_LINKED_LIST_H
#define CHAR_LINKED_LIST_H
#include <string>

class CharLinkedList {
    public:
        CharLinkedList();
        CharLinkedList(char c);
        CharLinkedList(char arr[], int size);
        CharLinkedList(const CharLinkedList &other);
        CharLinkedList &operator=(const CharLinkedList &other);
        ~CharLinkedList();

        bool isEmpty() const;
        void pushAtFront(char c);
        std::string toString() const;
        std::string toReverseString() const;
        void removeAt(int index);
        void popFromBack();
        void popFromFront();
        void clear();
        void insertAt(char c, int index);
        void pushAtBack(char c);
        void insertInOrder(char c);
        void replaceAt(char c, int index);
        int size() const;
        char first() const;
        char last() const;
        void concatenate(CharLinkedList *other);
        char elementAt(int index) const;

    private:
        struct Node{
            char info;
            Node *before;
            Node *after;
        };
        int numNodes;
        Node *front;
        Node *back;

        void del(Node* currNode);
        void removePop(int index);
        Node* findNode(Node *currNode, int index) const;
};

#endif

#ifndef NODE_H
#define NNODE_H
#include <string>

class Node{
    private:
    Node *parent;
    Node *child;
    Node *next;
    std::string fileType;
    std::string name;

    public:
    Node();
    Node *getChild();
    void addChild(Node *child);
    Node *getNext();
    void setNext(Node *next);
    Node *getParent();
    void setParent(Node* parent);
    std::string getFileType();
    std::string getName();
    void setName(std::string name);
    
    


};

#endif
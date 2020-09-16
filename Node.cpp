#include <string>
#include "Node.hpp"

Node::Node()
{
    this->child = nullptr;
    this->parent = nullptr;
    this->name = "";
    this->fileType = "";
}

Node::Node(Node *child, Node *parent, Node *next, std::string name, std::string fileType)
{
    this->next = next;
    this->child = child;
    this->parent = parent;
    this->name = name;
    this->fileType = fileType;
}

Node::Node(Node *source)
{
    if (!source)
        return;
    this->next = source->getNext();
    this->child = source->getChild();
    this->parent = source->getParent();
    this->name = source->getName();
    this->fileType = source->getFileType();
}

Node *Node::getChild()
{
    return this->child;
}
void Node::addChild(Node *child)
{
    this->child = child;
}
Node *Node::getNext()
{
    return this->next;
}
void Node::setNext(Node *next)
{
    this->next = next;
}
Node *Node::getParent()
{
    return parent;
}
void Node::setParent(Node *parent)
{
    this->parent = parent;
}
std::string Node::getFileType()
{
    return this->fileType;
}

std::string Node::getName()
{
    return this->name;
}
void Node::setName(std::string name)
{
    this->name = name;
}
#ifndef LINKLIST1_H_INCLUDED
#define LINKLIST1_H_INCLUDED

typedef struct Node{
    int data;
    Node* p_next;
} Node;

typedef struct LinkList {
    Node header, tail;
    int length;
} LinkList;

void initLinkList(LinkList* linkList);

void insertLinkList(LinkList* linkList, int idx, int data);

void removeLinkList(LinkList* linkList, int idx);

int getNodeData(LinkList* linkList, int idx);

void clearLinkList(LinkList* linkList);

int LinkListSize(const LinkList* linkList);

#endif // LINKLIST1_H_INCLUDED

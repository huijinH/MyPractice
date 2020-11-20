#ifndef LINKLIST2_H_INCLUDED
#define LINKLIST2_H_INCLUDED

typedef struct Node2 {
    int data;
    Node2* p_prev;
    Node2* p_next;
}Node2;

typedef struct LinkList22 {
    Node2 header, tail;
    int length;
} LinkList2;

void initLinkList2(LinkList2* linkList2);

void insertLinkList2(LinkList2* linkList2, int idx, int data);

void removeLinkList2(LinkList2* linkList2, int idx);

int getNodeData2(LinkList2* linkList2, int idx);

void clearLinkList2(LinkList2* linkList2);

int LinkListSize2(const LinkList2* linkList2);

#endif // LINKLIST2_H_INCLUDED

#include "LinkList1.h"

void initLinkList(LinkList* linkList)
{
    linkList -> header.p_next = &(linkList -> tail);
    linkList -> length = 0;
}

void insertLinkList(LinkList* linkList, int idx, int data)
{
    if (idx < 1 || idx > linkList -> length + 1)
        return;

    Node* node = new Node;
    node -> p_next = nullptr;
    node -> data = data;

    Node* itor = &(linkList -> header);
    for (int i = 1; i <= linkList -> length + 1; i++, itor = itor -> p_next)
    {
        Node* mid = itor -> p_next;
        if (i == idx)
        {
            itor -> p_next = node;
            node -> p_next = mid;
            linkList -> length++;
            break;
        }
    }
}

void removeLinkList(LinkList* linkList, int idx)
{
    if (idx < 1 || idx > linkList -> length)
        return;

    Node* itor = &(linkList -> header);
    for (int i = 1; i <= linkList -> length; i++, itor = itor -> p_next)
    {
        Node* mid = itor -> p_next;
        Node* last = mid -> p_next;
        if (i == idx)
        {
            itor -> p_next = last;
            delete mid;
            mid = nullptr;
            linkList -> length--;
            break;
        }
    }
}

int getNodeData(LinkList* linkList, int idx)
{
    if (idx < 1 || idx > linkList -> length)
        return - 1;

    Node* itor = &(linkList -> header);
    for (int i = 1; i <= linkList -> length; i++, itor = itor -> p_next)
    {
        if (i == idx)
        {
            return itor -> p_next -> data;
        }
    }
}

void clearLinkList(LinkList* linkList)
{
    while (linkList -> header.p_next != &(linkList -> tail))
    {
        Node* first = &(linkList -> header);
        Node* mid = first -> p_next;
        Node* last = mid -> p_next;

        first -> p_next = last;
        delete mid;
        mid = nullptr;
        linkList -> length--;
    }
}

int LinkListSize(const LinkList* linkList)
{
    return linkList -> length;
}

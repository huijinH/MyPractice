#include "LinkList2.h"

void initLinkList2(LinkList2* linkList2)
{
    linkList2 -> header.p_prev = nullptr;
    linkList2 -> header.p_next = &(linkList2 -> tail);
    linkList2 -> tail.p_prev = &(linkList2 -> header);
    linkList2 -> tail.p_next = nullptr;
    linkList2 -> length = 0;
}

void insertLinkList2(LinkList2* linkList2, int idx, int data)
{
    if (idx < 1 || idx > linkList2 -> length + 1)
        return;
    Node2* node = new Node2;
    node -> p_prev = nullptr;
    node -> p_next = nullptr;
    node -> data = data;

    Node2* itor = &(linkList2 -> header);
    for (int i = 1; i <= linkList2 -> length + 1; i++, itor = itor -> p_next)
    {
        Node2* midNode2 = itor -> p_next;
        if (i == idx)
        {
            itor -> p_next = node;
            node -> p_next = midNode2;
            node -> p_prev = itor;
            midNode2 -> p_prev = node;
            linkList2 -> length++;
            break;
        }
    }
}

void removeLinkList2(LinkList2* linkList2, int idx)
{
    if (idx < 1 || idx > linkList2 -> length)
        return;

    Node2* itor = &(linkList2 -> header);
    for (int i = 1; i <= linkList2 -> length; i++, itor = itor -> p_next)
    {
        Node2* mid = itor -> p_next;
        Node2* last = mid -> p_next;
        if (i == idx)
        {
            itor -> p_next = last;
            last -> p_prev = itor;
            delete mid;
            mid = nullptr;
            linkList2 -> length--;
            break;
        }
    }
}

int getNodeData2(LinkList2* linkList2, int idx)
{
    if (idx < 1 || idx > linkList2 -> length)
        return -1;

    Node2* itor = &(linkList2 -> header);
    for (int i = 1; i <= linkList2 -> length; i++, itor = itor -> p_next)
    {
        if (i == idx)
        {
            return itor -> p_next -> data;
        }
    }
    return -1;
}

void clearLinkList2(LinkList2* linkList2)
{
    while (linkList2 -> header.p_next != &(linkList2 -> tail))
    {
        Node2* first = &(linkList2 -> header);
        Node2* mid = first -> p_next;
        Node2* last = mid -> p_next;

        first -> p_next = last;
        last -> p_prev = first;
        delete mid;
        mid = nullptr;
        linkList2 -> length--;
    }
}

int LinkListSize2(const LinkList2* linkList2)
{
    return linkList2 -> length;
}

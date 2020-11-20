#include <iostream>
#include "SeqList.h"
#include "LinkList1.h"
#include "LinkList2.h"

using namespace std;

void testSeqList();

void testLinkList1();

void testLinkList2();

int main()
{
    testSeqList();
    cout << "==========" << endl;
    testLinkList1();
    cout << "==========" << endl;
    testLinkList2();

    return 0;
}

void testLinkList1()
{
    LinkList* linkList = new LinkList;

    initLinkList(linkList);

    insertLinkList(linkList, 1, 100);
    insertLinkList(linkList, 2, 200);
    insertLinkList(linkList, 3, 300);
    insertLinkList(linkList, 2, 400);
    insertLinkList(linkList, 3, 600);
    insertLinkList(linkList, 7, 600);
    insertLinkList(linkList, 1, 110);
    insertLinkList(linkList, 6, 660);
    for (Node* tmpNode = linkList -> header.p_next; tmpNode != &(linkList -> tail); tmpNode = tmpNode -> p_next)
    {
        cout << tmpNode -> data << " ";
    }
    cout << endl;

    removeLinkList(linkList, 1);
    removeLinkList(linkList, 3);
    removeLinkList(linkList, 3);
    removeLinkList(linkList, 4);
    for (Node* tmpNode = linkList -> header.p_next; tmpNode != &(linkList -> tail); tmpNode = tmpNode -> p_next)
    {
        cout << tmpNode -> data << " ";
    }
    cout << endl;

    int res1, res2;
    res1 = getNodeData(linkList, 2);
    res2 = getNodeData(linkList, 1);
    cout << res1 << " " << res2 << endl;

    int length = LinkListSize(linkList);
    cout << length << endl;

    clearLinkList(linkList);
    for (Node* tmpNode = linkList -> header.p_next; tmpNode != &(linkList -> tail); tmpNode = tmpNode -> p_next)
    {
        cout << tmpNode -> data << " ";
    }
    cout << endl;
}

void testLinkList2()
{
    LinkList2* linkList = new LinkList2;

    initLinkList2(linkList);

    insertLinkList2(linkList, 1, 100);
    insertLinkList2(linkList, 2, 200);
    insertLinkList2(linkList, 3, 300);
    insertLinkList2(linkList, 2, 400);
    insertLinkList2(linkList, 3, 600);
    insertLinkList2(linkList, 7, 600);
    insertLinkList2(linkList, 1, 110);
    insertLinkList2(linkList, 6, 660);
    for (Node2* tmpNode = linkList -> header.p_next; tmpNode != &(linkList -> tail); tmpNode = tmpNode -> p_next)
    {
        cout << tmpNode -> data << " ";
    }
    cout << endl;

    removeLinkList2(linkList, 1);
    removeLinkList2(linkList, 3);
    removeLinkList2(linkList, 3);
    removeLinkList2(linkList, 4);
    for (Node2* tmpNode = linkList -> header.p_next; tmpNode != &(linkList -> tail); tmpNode = tmpNode -> p_next)
    {
        cout << tmpNode -> data << " ";
    }
    cout << endl;

    int res1, res2;
    res1 = getNodeData2(linkList, 2);
    res2 = getNodeData2(linkList, 1);
    cout << res1 << " " << res2 << endl;

    int length = LinkListSize2(linkList);
    cout << length << endl;

    clearLinkList2(linkList);
    for (Node2* tmpNode = linkList -> header.p_next; tmpNode != &(linkList -> tail); tmpNode = tmpNode -> p_next)
    {
        cout << tmpNode -> data << " ";
    }
    cout << endl;
}

void testSeqList()
{
    SeqList seqList;
    ElementType element0 = {0, "james"};
    ElementType element1 = {1, "curry"};
    ElementType element2 = {2, "kobe"};
    ElementType element3 = {3, "green"};
    ElementType element4 = {4, "love"};
    ElementType tmpElement = {0, "james"};
    vector<int> idxArr;

    initSeqList(&seqList);
    cout << "init:" << endl;

    bool isempty = isEmpty(&seqList);
    cout << "empty:" << isempty << endl;

    bool isfull = isFull(&seqList);
    cout << "full:" << isfull << endl;

    insertSeqList(&seqList, 0, element0);
    insertSeqList(&seqList, 1, element1);
    insertSeqList(&seqList, 4, element4);
    insertSeqList(&seqList, 2, element2);
    insertSeqList(&seqList, 4, element4);
    cout << "insert:" << endl;
    for (int i = 0; i < seqList.length; i++)
    {
        cout << seqList.datas[i].id << " " << seqList.datas[i].name << endl;
    }

    removeElement(&seqList, 1);
    cout << "remove:" << endl;
    for (int i = 0; i < seqList.length; i++)
    {
        cout << seqList.datas[i].id << " " << seqList.datas[i].name << endl;
    }

    idxArr = getElementIdx(&seqList, tmpElement);
    cout << "getIdx:" << endl;
    for (size_t i = 0; i < idxArr.size(); i++)
    {
        cout << idxArr.at(i) << endl;
    }
}

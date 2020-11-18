#include <iostream>
#include "SeqList.h"

using namespace std;

void testSeqListAction();

int main()
{
    testSeqListAction();

    return 0;
}

void testSeqListAction()
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

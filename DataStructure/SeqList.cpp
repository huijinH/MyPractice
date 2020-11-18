#include "SeqList.h"

void initSeqList(SeqList* seqList)
{
    seqList -> length = 0;
}

void insertSeqList(SeqList* seqList, int idx, ElementType element)
{
    if (idx < 0 || idx > MAX_SIZE - 1 || seqList -> length == MAX_SIZE)
        return;

    if (idx <= seqList -> length)
    {
        for (int i = seqList -> length - 1; i >= idx; i--)
        {
            seqList -> datas[i + 1] = seqList -> datas[i];
        }
        seqList -> datas[idx] = element;
        seqList -> length++;
    }
}

void removeElement(SeqList* seqList, int idx)
{
    if (idx < 0 || idx > seqList -> length - 1)
        return;
    for (int i = idx; i < seqList -> length - 1; i++)
    {
        seqList -> datas[i] = seqList -> datas[i + 1];
    }
    seqList -> length--;
}

vector<int> getElementIdx(SeqList* seqList, ElementType element)
{
    vector<int> idxArr;
    for (int i = 0; i < seqList -> length; i++)
    {
        if (element.id == seqList -> datas[i].id && element.name == seqList -> datas[i].name)
            idxArr.push_back(i);
    }
    return idxArr;
}

bool isEmpty(SeqList* seqList)
{
    if (seqList -> length == 0)
    {
        return true;
    }
    return false;
}

bool isFull(SeqList* seqList)
{
    if (seqList -> length == MAX_SIZE)
    {
        return true;
    }
    return false;
}

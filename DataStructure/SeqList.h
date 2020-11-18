#ifndef SEQLIST_H_INCLUDED
#define SEQLIST_H_INCLUDED

#include <vector>
#include <string>

using namespace std;

#define MAX_SIZE 255

// element type
typedef struct {
    int id;
    string name;
} ElementType;

// seqList
typedef struct {
    ElementType datas[MAX_SIZE];
    int length;
} SeqList;

void initSeqList(SeqList* seqList);

void insertSeqList(SeqList* seqList, int idx, ElementType element);

void removeElement(SeqList* seqList, int idx);

vector<int> getElementIdx(SeqList* seqList, ElementType element);

bool isEmpty(SeqList* seqList);

bool isFull(SeqList* seqList);

#endif // SEQLIST_H_INCLUDED

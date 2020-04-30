#ifndef sort_h
#define sort_h

#include <stdlib.h>
#include <string.h>

void BubbleSort( int* t, int nSize );
void InsertionSort( int* t, int nSize );
void SelectionSort( int* t, int nSize );
void MixedSort( int* t, int nSize );
void HalfInsertionSort( int* t, int nSize );
void QuickSort( int* t, int pocz, int nSize );
void HeapSort( int* t, int nSize );
void UpDate( int* t, int l, int p );
void MergeSort( int* t,int *, int left, int right );
void Merge( int* t, int* tmp, int left, int mid, int right );
void NaturalSort( int* t, int nSize );
bool Copy( int *t, int* i, int* tmp, int* ix, int nLast );
void CopySerie( int *t, int* i, int* tmp, int* ix, int nLast );
#endif




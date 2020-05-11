#ifndef SORT_MERGE
#define SORT_MERGE

/* sortiert den int-Array seq in den 
   Indexgrenzen left und right */
void quickSort(int *seq, int left, int right);

/* verschmelzt die sortierten Bereiche des Arrays seq 
   in den Indexgrenzen 0 bis len/2-1 bzw. len/2 bis len-1
   zu einem sortierten Array seq_sort der Länge len */ 
void merge(int *seq, int *seq_sort, int len);

#endif

/**
* @author Buta Sabina
* @group 30422
*
* Assignment requirements
* Compare the following sorting methods:
* -insertion sort, insertion sort with binary search, selection sort, bubble sort
*
* Personal interpretation of the complexity of the average,
best and worst testing cases.
* SELECTION SORT
*
* 
*/


#include "direct_sort.h"

#include "catch2.hpp"

#include <iostream>

namespace lab01
{

void bubbleSort(int* values, int n, Operation* opAsg, Operation* opCmp)
{
    bool sorted = false;
    while (!sorted) {
        sorted = true;
        for (int i = 0; i < n - 1; i++) {
            if (opCmp)opCmp->count();
            if (values[i] > values[i + 1]) {
                int aux = values[i];
                if (opAsg) opAsg->count();
                values[i] = values[i + 1];
                if (opAsg) opAsg->count();
                values[i + 1] = aux;
                if (opAsg) opAsg->count();
                sorted = false;
            }
        }
        n--;
    }
}

void selectionSort(int* values, int n, Operation* opAsg, Operation* opCmp)
{
    for (int i = 0; i < n - 1; i++) {
        int min = i;
        for (int j = i + 1; j < n; j++) {
            if (opCmp)opCmp->count();
            if (values[j] < values[min]) {
                min = j;
            }
        }
        if (min != i) {
            int aux = values[i];
            if (opAsg) opAsg->count();
            values[i] = values[min];
            if (opAsg) opAsg->count();
            values[min] = aux;
            if (opAsg) opAsg->count();
        }
    }
}

void insertionSort(int* values, int n, Operation* opAsg, Operation* opCmp)
{
    for (int j = 1; j < n; j++) {
        int buffer = values[j];
        if (opAsg) opAsg->count();
        int i = j - 1;
        while (i >= 0 && values[i] > buffer) {
            if (opCmp)opCmp->count();
            values[i + 1] = values[i];
            if (opAsg) opAsg->count();
            i = i - 1;
        }
        if (opCmp && i>=0) opCmp->count(); // while-ul da fail din cauza conditiei de a iesi din array
        values[i + 1] = buffer;
        if (opAsg) opAsg->count();
    }
}

int binarySearch(int* values, int element, int low, int high, Operation *opCmp) {
    while (low <= high) {
        int mid = low + (high - low) / 2; // to prevent integer overflow
        if (opCmp) opCmp->count();
        if (element == values[mid]) {
            return mid + 1;
        }
        if (opCmp) opCmp->count();
        if (element > values[mid]) {
            low = mid + 1;
        }
        else {
            high = mid - 1;
        }
    }
    return low;
}

void binaryInsertionSort(int* values, int n, Operation* opAsg, Operation* opCmp)
{
    for (int j = 1; j < n; j++) {
        int buffer = values[j];
        if (opAsg) opAsg->count();
        int i = j - 1;
        int location = binarySearch(values, buffer, 0, i, opCmp);
        while (i >= location) {
            values[i + 1] = values[i];
            if (opAsg) opAsg->count();
            i--;
        }
        values[i + 1] = buffer;
        if (opAsg) opAsg->count();
    }
}

void demonstrate(int size)
{
    int* values = (int*)malloc(size*sizeof(int));
    int* values_original = (int*)malloc(size * sizeof(int));
    FillRandomArray(values_original, size, 0, 50, false, UNSORTED);//unsorted, ascending or descending
    printf("Initial array is:\n");
    for (int i = 0; i < size; i++) {
        printf("%d ", values_original[i]);
    }
    CopyArray(values, values_original, size);

    //insertion
    printf("\n");
    printf("Sorted array with insertion is:\n");
    insertionSort(values, size);
    for (int i = 0; i < size; i++) {
        printf("%d ", values[i]);
    }
    printf("\n");
    CopyArray(values, values_original, size);

    //insertion with binary search
    printf("\n");
    printf("Sorted array with insertion and binary search is:\n");
    binaryInsertionSort(values, size);
    for (int i = 0; i < size; i++) {
        printf("%d ", values[i]);
    }
    printf("\n");
    CopyArray(values, values_original, size);

    //selection
    printf("\n");
    printf("Sorted array with selection is:\n");
    selectionSort(values, size);
    for (int i = 0; i < size; i++) {
        printf("%d ", values[i]);
    }
    printf("\n");
    CopyArray(values, values_original, size);

    //bubble
    printf("\n");
    printf("Sorted array with bubble is:\n");
    bubbleSort(values, size);
    for (int i = 0; i < size; i++) {
        printf("%d ", values[i]);
    }
    printf("\n");
}

TEST_CASE("Direct sorting methods")
{
       int data[100];
       FillRandomArray(data, 100);
       insertionSort(data, 100);
       REQUIRE( IsSorted(data, 100) );

       FillRandomArray(data, 100);
       binaryInsertionSort(data, 100);
       REQUIRE(IsSorted(data, 100));
}

void performance(Profiler& profiler, AnalysisCase whichCase)
{
    int values[10000];
    int valuesOriginal[10000];
    if (whichCase == AVERAGE) {
        for (int attempts = 0; attempts < 5; attempts++) {
            for (int size = 100; size <= 10000; size += 100) {
                FillRandomArray(valuesOriginal, size, 10, 50000, false, UNSORTED);

                //insertion
                CopyArray(values, valuesOriginal, size);
                Operation opAsg = profiler.createOperation("insAsg", size);
                Operation opCmp = profiler.createOperation("insCmp", size);//copy paste pt toti algoritmii
                insertionSort(values, size, &opAsg, &opCmp);

                //insertion with binary search
                CopyArray(values, valuesOriginal, size);
                Operation opAsgBin = profiler.createOperation("insBinAsg", size);
                Operation opCmpBin = profiler.createOperation("insBinCmp", size);
                binaryInsertionSort(values, size, &opAsgBin, &opCmpBin);

                //bubbleSort
                CopyArray(values, valuesOriginal, size);
                Operation opAsgBub = profiler.createOperation("bubAsg", size);
                Operation opCmpBub = profiler.createOperation("bubCmp", size);
                bubbleSort(values, size, &opAsgBub, &opCmpBub);

                //selectionSort()
                CopyArray(values, valuesOriginal, size);
                Operation opAsgSel = profiler.createOperation("selAsg", size);
                Operation opCmpSel = profiler.createOperation("selCmp", size);
                selectionSort(values, size, &opAsgSel, &opCmpSel);
            }
        }
        profiler.divideValues("insAsg", 5);
        profiler.divideValues("insCmp", 5);
        profiler.addSeries("insOp", "insAsg", "insCmp");

        profiler.divideValues("insBinAsg", 5);
        profiler.divideValues("insBinCmp", 5);
        profiler.addSeries("insBinOp", "insBinAsg", "insBinCmp");

        profiler.divideValues("bubAsg", 5);
        profiler.divideValues("bubCmp", 5);
        profiler.addSeries("bubOp", "bubAsg", "bubCmp");

        profiler.divideValues("selAsg", 5);
        profiler.divideValues("selCmp", 5);
        profiler.addSeries("selOp", "selAsg", "selCmp");

        profiler.createGroup("Total_Operations", "insOp", "insBinOp", "bubOp", "selOp");
        
    }
    else if (whichCase == BEST) {
        for (int size = 100; size <= 10000; size += 100) {
            //insertion
            FillRandomArray(valuesOriginal, size, 10, 50000, false, ASCENDING);

            CopyArray(values, valuesOriginal, size);
            Operation opAsg = profiler.createOperation("insAsg", size);
            Operation opCmp = profiler.createOperation("insCmp", size);
            insertionSort(values, size, &opAsg, &opCmp);

            //insertion with binary search
            CopyArray(values, valuesOriginal, size);
            Operation opAsgInsBin = profiler.createOperation("insBinAsg", size);
            Operation opCmpInsBin = profiler.createOperation("insBinCmp", size);
            binaryInsertionSort(values, size, &opAsgInsBin, &opCmpInsBin);

            //bubbleSort
            CopyArray(values, valuesOriginal, size);
            Operation opAsgBub = profiler.createOperation("bubAsg", size);
            Operation opCmpBub = profiler.createOperation("bubCmp", size);
            bubbleSort(values, size, &opAsgBub, &opCmpBub);

            //selectionSort
            CopyArray(values, valuesOriginal, size);
            Operation opAsgSel = profiler.createOperation("selAsg", size);
            Operation opCmpSel = profiler.createOperation("selCmp", size);
            selectionSort(values, size, &opAsgSel, &opCmpSel);
        }
        profiler.addSeries("insOp", "insAsg", "insCmp");
        profiler.addSeries("insBinOp", "insBinAsg", "insBinCmp");
        profiler.addSeries("bubOp", "bubAsg", "bubCmp");
        profiler.addSeries("selOp", "selAsg", "selCmp");

        profiler.createGroup("Total_Operations", "insOp", "insBinOp", "bubOp", "selOp");
    }
    else {
        for (int size = 100; size <= 10000; size += 100) {
            //insertion
            FillRandomArray(valuesOriginal, size, 10, 50000, false, DESCENDING);

            CopyArray(values, valuesOriginal, size);
            Operation opAsg = profiler.createOperation("insAsg", size);
            Operation opCmp = profiler.createOperation("insCmp", size);
            insertionSort(values, size, &opAsg, &opCmp);

            //insertion with binary search
            CopyArray(values, valuesOriginal, size);
            Operation opAsgInsBin = profiler.createOperation("insBinAsg", size);
            Operation opCmpInsBin = profiler.createOperation("insBinCmp", size);
            binaryInsertionSort(values, size, &opAsgInsBin, &opCmpInsBin);

            //bubbleSort
            CopyArray(values, valuesOriginal, size);
            Operation opAsgBub = profiler.createOperation("bubAsg", size);
            Operation opCmpBub = profiler.createOperation("bubCmp", size);
            bubbleSort(values, size, &opAsgBub, &opCmpBub);

            //selectionSort
            FillRandomArray(valuesOriginal, size, 10, 50000, false, ASCENDING);
            CopyArray(values, valuesOriginal, size);
            int aux = values[size-1];
            for (int i = size - 1; i>0 ; i--) {
                values[i] = values[i - 1];
            }
            values[0] = aux;
            Operation opAsgSel = profiler.createOperation("selAsg", size);
            Operation opCmpSel = profiler.createOperation("selCmp", size);
            selectionSort(values, size, &opAsgSel, &opCmpSel);
        }
        profiler.addSeries("insOp", "insAsg", "insCmp");
        profiler.addSeries("insBinOp", "insBinAsg", "insBinCmp");
        profiler.addSeries("bubOp", "bubAsg", "bubCmp");
        profiler.addSeries("selOp", "selAsg", "selCmp");

        profiler.createGroup("Total_Operations", "insOp", "insBinOp", "bubOp", "selOp");
    }
}

void benchmark(Profiler& profiler, AnalysisCase whichCase)
{
    // TODO: Write your benchmarks here, as explained in the readme
    // You should use profiler.startTimer/stopTimer for measuring and plotting measured time
}

} // namespace lab01

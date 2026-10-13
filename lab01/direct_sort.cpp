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
* The algorithm divides the array into two parts: the left side is sorted and the right side unsorted;
* It finds the minimum in the right side and then swaps it with the first unsorted element that divides the two parts.
* 
* Best case - ASCENDING array
* The algorithm compares the first element with the rest of the array but since it's sorted it performs 0 swaps and n-1 comparisons. It does
* the same with the second element and so on, leading to a complexity of T(n)=n*(n-1)/2 in terms of comparisons but of assignments it's
* T(n)=0.
* 
* Worst case - a permutation of the sorted array either to the right or to the left
* If we take the DESCENDING array "7 6 5 4 3 2 1" 1 would swap with 7, 6 with 2 and so on, therefore there would be half swaps performed.
* Instead we can take an array like "6 1 2 3 4 5". The number of comparisons remains the same as in the best case, however there would be
* T(n)=3(n-1) assignments/swaps that take place, since the swap function is considered to be 3 different operations.
* 
* Average case
* Since it's roughly as bad as the worst case, its complexity in terms of comparisons is T(n)=n*(n-1)/2, and assignments are slightly less
* than T(n)=3(n-1).
* 
* INSERTION SORT
* We have again a sorted part of the array and an unsorted one. However, the algorithm takes a current element(buffer), finds its position
* in the already sorted array and shifts with one element to the right the rest of the elements that are larger than it.
* 
* Best case - Sorted ASCENDING array
* There are only T(n)=n-1 comparisons that take place because the while keeps failing when testing if the element before the buffer is larger.
* The loop runs for n-1 times and since the while is ignored in this case, there will be two assignments that take place, the one before the while and
* the one after it => T(n)=2(n-1) assignments.
* 
* Worst case - sorted DESCENDING array
* Each element is smaller than all the elements before it, so the buffer will be compared with all previous elements.
* There will be 1 comparison in the first iteration, then 2 comparisons and so on up until n-1 in the last one.
* Added up will lead to T(n)=n*(n-1)/2 comparisons. Since the while is not ignored anymore,
* the assignment inside it will take place as well, happening n*(n-1)/2 times. Therefore, in terms of assignments, T(n)=2(n-1)+n(n-1)/2.
* 
* Average case
* As mentioned before, the average case is roughly as bad as the worst case, therefore it has slightly less but approximately the same complexities:
* T(n)=n*(n-1)/4 comparisons and T(n)=2(n-1)+n(n-1)/4 assignments since, on average, the element is inserted in the middle
* of the sorted part of the array.
* 
* BINARY INSERTION SORT
* Works exactly like insertion sort, however the searching is optimized. Instead of searching backwards one by one to find the buffer's position,
* the algorithm uses Binary Search to find it faster. The loop to shift the elements still takes place.
* 
* Best case - ASCENDING sorted array
* The algorithm keeps dividing in half the searching of the buffer's position. There are log(i)+1 for each i => in terms of comparisons there will
* be T(n)=nlog(n); The assignments remain the same as in insertion sort T(n)=2(n-1).
* 
* Worst case - DESCENDING sorted array
* The binary search function is again called therefore leading to T(n)=nlog(n) comparisons and the assignments are as in insertion sort
* T(n)=2(n-1)+n*(n-1)/2.
* 
* Average case
* Same number of comparisons => T(n)=nlog(n); and roughly the same amount of assignments, T(n)=2(n-1)+n(n-1)/4.
* 
* BUBBLE SORT
* Works by repeatedly swapping adjacent elements that are out of order.
* 
* Best case - sorted ASCENDING array
* Since the array is sorted, the while only runs one time and the inner loop check once for every adjacent pair => T(n)=n-1 comparisons
* The condition never triggers thus no assignments take place => T(n)=0 in terms of assignments
* 
* Worst case - sorted DESCENDING array
* Since the algorithm is optimized with the "n--" because the largest element will be pushed to the last index each iteration,
* there are n-1 comparisons followed by n-2 and so on leading to T(n)=n*(n-1)/2 comparisons.
* Each comparison will lead to a swap that consists of 3 operations => T(n)=3*n(n-1)/2 assignments.
* 
* Average case
* Comparisons will be roughly the same as in the worst case => T(n)=n*(n-1)/2 (due to early exit), same with assignments T(n)=3*n(n-1)/4.
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
        if (element < values[mid]) {
            high = mid - 1;
        }
        else {
            low = mid + 1;
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

       FillRandomArray(data, 100);
       selectionSort(data, 100);
       REQUIRE(IsSorted(data, 100));

       FillRandomArray(data, 100);
       bubbleSort(data, 100);
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
        //grouping without selection sort since its complexity of n^2 forces the other algorithms look constant
        profiler.createGroup("Total_Operations_Linear", "insOp", "insBinOp", "bubOp");
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

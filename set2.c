#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h> // Include for boolean data type

#define MAX_ELEMENTS 100 // Maximum number of elements in a set

// Function to input elements of a set
void inputSetElements(int set[], int *numElements) {
    printf("Enter the number of elements in the set: ");
    scanf("%d", numElements);
    printf("Enter the elements :\n");
    for (int i = 0; i < *numElements; i++) {
        scanf("%d", &set[i]);
    }
}

// Function to display elements of a set
void displaySetElements(int set[], int numElements) {
    printf("{ ");
    for (int i = 0; i < numElements; i++) {
        printf("%d ", set[i]);
    }
    printf("}\n");
}

// Function to find the union of two sets (using a more efficient approach)
void findUnion(int set1[], int size1, int set2[], int size2) {
    int unionSet[MAX_ELEMENTS], unionSize = 0;
    bool seen[MAX_ELEMENTS] = {false}; // Keep track of elements already added

    // Add elements from set1
    for (int i = 0; i < size1; i++) {
        unionSet[unionSize++] = set1[i];
        seen[set1[i]] = true; // Mark as seen
    }

    // Add elements from set2 that are not already in the union
    for (int i = 0; i < size2; i++) {
        if (!seen[set2[i]]) {
            unionSet[unionSize++] = set2[i];
            seen[set2[i]] = true; // Mark as seen
        }
    }

    printf("Union of sets: ");
    displaySetElements(unionSet, unionSize);
}


// Function to find the intersection of two sets (using a more efficient approach)
void findIntersection(int set1[], int size1, int set2[], int size2) {
    int intersectionSet[MAX_ELEMENTS], intersectionSize = 0;
    bool seen[MAX_ELEMENTS] = {false}; // Keep track of elements already added

    for (int i = 0; i < size1; i++) {
        for (int j = 0; j < size2; j++) {
            if (set1[i] == set2[j] && !seen[set1[i]]) { // Check if already added
                intersectionSet[intersectionSize++] = set1[i];
                seen[set1[i]] = true; // Mark as seen
                break; // Optimization: Once found, no need to check further in set2
            }
        }
    }

    printf("Intersection of sets: ");
    displaySetElements(intersectionSet, intersectionSize);
}


// Function to find the difference of two sets (set1 - set2)
void findDifference(int set1[], int size1, int set2[], int size2) {
    int differenceSet[MAX_ELEMENTS], differenceSize = 0;
    bool seen[MAX_ELEMENTS] = {false}; // Keep track of elements in set2

    for (int i = 0; i < size2; i++) {
        seen[set2[i]] = true;
    }

    for (int i = 0; i < size1; i++) {
        if (!seen[set1[i]]) {
            differenceSet[differenceSize++] = set1[i];
        }
    }

    printf("Difference of sets (A - B): ");
    displaySetElements(differenceSet, differenceSize);
}


// Function to check if two sets are disjoint (more efficient)
int areDisjoint(int set1[], int size1, int set2[], int size2) {
    bool seen[MAX_ELEMENTS] = {false}; // Keep track of elements in set2

    for (int i = 0; i < size2; i++) {
        seen[set2[i]] = true;
    }

    for (int i = 0; i < size1; i++) {
        if (seen[set1[i]]) {
            return 0; // Not disjoint
        }
    }

    return 1; // Disjoint
}

// Function to find the Cartesian product of two sets
void findCartesianProduct(int set1[], int size1, int set2[], int size2) {
    printf("Cartesian Product: ");
    for (int i = 0; i < size1; i++) {
        for (int j = 0; j < size2; j++) {
            printf("(%d, %d) ", set1[i], set2[j]);
        }
    }
    printf("\n");
}

int main() {
    int setA[MAX_ELEMENTS], sizeA, setB[MAX_ELEMENTS], sizeB, choice;

    // Input elements for Set A
    printf("Enter elements for Set A:\n");
    inputSetElements(setA, &sizeA);

    // Input elements for Set B
    printf("Enter elements for Set B:\n");
    inputSetElements(setB, &sizeB);

    // Menu for set operations
    printf("\n--- Menu ---\n");
    printf("1. Union\n");
    printf("2. Intersection\n");
    printf("3. Difference\n");
    printf("4. Check if Disjoint\n");
    printf("5. Cartesian Product\n");
    printf("6. Exit\n");

    printf("Enter your choice: ");
    scanf("%d", &choice);

    // Perform operations based on user's choice
    while (choice != 6) {
        switch (choice) {
            case 1:
                findUnion(setA, sizeA, setB, sizeB);
                break;
            case 2:
                findIntersection(setA, sizeA, setB, sizeB);
                break;
            case 3:
                findDifference(setA, sizeA, setB, sizeB);
                break;
            case 4:
                if (areDisjoint(setA, sizeA, setB, sizeB)) {
                    printf("Sets are disjoint\n");
                } else {
                    printf("Sets are not disjoint\n");
                }
                break;
            case 5:
                findCartesianProduct(setA, sizeA, setB, sizeB);
                break;
            default:
                printf("Invalid choice! Please try again.\n");
        }
        printf("\nEnter your choice: ");
        scanf("%d", &choice);
    }

    printf("Exiting...\n");
    return 0;
}

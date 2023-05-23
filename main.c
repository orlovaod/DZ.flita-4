#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTICES 100

void deleteVertex(int matrix[MAX_VERTICES][MAX_VERTICES], int numVertices, int vertex) {
    int i, j;

    // Shift rows up
    for (i = vertex; i < numVertices - 1; i++) {
        for (j = 0; j < numVertices; j++) {
            matrix[i][j] = matrix[i + 1][j];
        }
    }

    // Shift columns left
    for (i = 0; i < numVertices; i++) {
        for (j = vertex; j < numVertices - 1; j++) {
            matrix[i][j] = matrix[i][j + 1];
        }
    }
}

void sortVertices(int matrix[MAX_VERTICES][MAX_VERTICES], int numVertices) {
    int i, j, k, degree[MAX_VERTICES], temp;

    // Calculate degree for each vertex
    for (i = 0; i < numVertices; i++) {
        degree[i] = 0;
        for (j = 0; j < numVertices; j++) {
            if (matrix[i][j] == 1) {
                degree[i]++;
            }
        }
    }

    // Sort vertices in ascending order based on degree
    for (i = 0; i < numVertices - 1; i++) {
        for (j = 0; j < numVertices - i - 1; j++) {
            if (degree[j] > degree[j + 1]) {
                // Swap vertices
                temp = degree[j];
                degree[j] = degree[j + 1];
                degree[j + 1] = temp;

                // Swap rows
                for (k = 0; k < numVertices; k++) {
                    temp = matrix[j][k];
                    matrix[j][k] = matrix[j + 1][k];
                    matrix[j + 1][k] = temp;
                }

                // Swap columns
                for (k = 0; k < numVertices; k++) {
                    temp = matrix[k][j];
                    matrix[k][j] = matrix[k][j + 1];
                    matrix[k][j + 1] = temp;
                }
            }
        }
    }
}

void printMatrix(int matrix[MAX_VERTICES][MAX_VERTICES], int numVertices) {
    int i, j;

    for (i = 0; i < numVertices; i++) {
        for (j = 0; j < numVertices; j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
}

int main() {
    FILE *file;
    int matrix[MAX_VERTICES][MAX_VERTICES];
    int numVertices, vertexToDelete, i, j;

    // Open the input file
    file = fopen("input.txt", "r");
    if (file == NULL) {
        printf("Error opening the file.\n");
        return 1;
    }

    // Read the adjacency matrix from the file
    fscanf(file, "%d", &numVertices);
    for (i = 0; i < numVertices; i++) {
        for (j = 0; j < numVertices; j++) {
            fscanf(file, "%d", &matrix[i][j]);
        }
    }

    // Close the file
    fclose(file);

    // Print the original matrix
    printf("Original Matrix:\n");
    printMatrix(matrix, numVertices);

    // Get the vertex to delete from the user
    printf("Enter the vertex to delete: ");
    scanf("%d", &vertexToDelete);

    // Delete the specified vertex
    deleteVertex(matrix, numVertices, vertexToDelete);

    // Sort the remaining vertices based on degree
    sortVertices(matrix, numVertices - 1);

    // Print the modified matrix
    printf("\nModified Matrix:\n");
    printMatrix(matrix, numVertices - 1);

    return 0;
}

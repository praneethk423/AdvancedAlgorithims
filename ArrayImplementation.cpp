#include <iostream>
using namespace std;

void convertToCompact(int sparseMatrix[][5], int compactMatrix[][10], int &size) {
    size = 0;
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 5; j++)
            if (sparseMatrix[i][j] != 0)
                size++;

    int k = 0;
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 5; j++)
            if (sparseMatrix[i][j] != 0)
            {
                compactMatrix[0][k] = i;
                compactMatrix[1][k] = j;
                compactMatrix[2][k] = sparseMatrix[i][j];
                k++;
            }
}

void displayCompactMatrix(int compactMatrix[][10], int size) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < size; j++)
            cout << " " << compactMatrix[i][j];
        cout << "\n";
    }
}

int main() {
    int sparseMatrix[4][5];

    cout << "Enter the elements of the sparse matrix (4x5):" << endl;
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 5; j++)
            cin >> sparseMatrix[i][j];

    int size;
    int compactMatrix[3][10];

    convertToCompact(sparseMatrix, compactMatrix, size);

    cout << "Compact Matrix:" << endl;
    displayCompactMatrix(compactMatrix, size);

    return 0;
}

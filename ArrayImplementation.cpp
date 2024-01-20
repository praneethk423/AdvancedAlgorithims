#include<iostream>
using namespace std;

class SparseNode
{
public:
    int row;
    int col;
    int value;
    SparseNode* next;
};

void addSparseNode(SparseNode** head, int row, int col, int value)
{
    SparseNode* newNode = new SparseNode();
    newNode->row = row;
    newNode->col = col;
    newNode->value = value;
    newNode->next = nullptr;

    if (*head == nullptr)
    {
        *head = newNode;
    }
    else
    {
        SparseNode* temp = *head;
        while (temp->next != nullptr)
        {
            temp = temp->next;
        }
        temp->next = newNode;
    }
}

void printSparseMatrix(SparseNode* head)
{
    SparseNode* current = head;

    cout << "Row positions: ";
    while (current != nullptr)
    {
        cout << current->row << " ";
        current = current->next;
    }
    cout << endl;

    current = head;
    cout << "Column positions: ";
    while (current != nullptr)
    {
        cout << current->col << " ";
        current = current->next;
    }
    cout << endl;

    current = head;
    cout << "Values: ";
    while (current != nullptr)
    {
        cout << current->value << " ";
        current = current->next;
    }
}

int main()
{
    int rows, cols;

    cout << "Enter the number of rows and columns in the sparse matrix: ";
    cin >> rows >> cols;

    int inputMatrix[rows][cols];

    cout << "Enter the elements of the sparse matrix:" << endl;
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            cin >> inputMatrix[i][j];
        }
    }

    SparseNode* sparseList = nullptr;
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            if (inputMatrix[i][j] != 0)
            {
                addSparseNode(&sparseList, i, j, inputMatrix[i][j]);
            }
        }
    }

    cout << "Compact representation of the sparse matrix:" << endl;
    printSparseMatrix(sparseList);

    return 0;
}

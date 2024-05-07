#include <iostream>
#include <chrono>
#include <cstdlib>
#include <ctime> 

using std::cin;
using std::cout;
using std::endl;
using std::string;

using std::chrono::high_resolution_clock;
using std::chrono::duration_cast;
using std::chrono::nanoseconds;

typedef struct Node {
    int iPayload;
    Node* ptrNext;
    Node* ptrPrev;
} Node;

Node* createNode(int);
void insertFront(Node**, int);
void insertEnd(Node**, int);
void displayList(Node*);
void deleteAll(Node*&);
void trocaValor(Node*, Node*);
void bubblesort(Node*);
void optimizedBubblesort(Node*);
void selectionSort(Node*);
void optimizedSelectionSort(Node*);
Node* generateRandomList(int);

int main() {
    // Seed para números aleatórios
    srand(time(nullptr));

    // Gerar e exibir uma lista duplamente encadeada aleatória
    Node* largeRandomList = generateRandomList(1000);
    cout << "Lista: ";
    displayList(largeRandomList);

    // Testar bubble sort
    auto timeStart = high_resolution_clock::now();
    bubblesort(largeRandomList);
    auto timeStop = high_resolution_clock::now();
    cout << "Lista ordenada utilizando bubble sort: ";
    displayList(largeRandomList);
    auto timeDuration = duration_cast<nanoseconds>(timeStop - timeStart);
    cout << "Tempo utilizado: " << timeDuration.count() << " nanosegundos" << endl;
    cout << " ========================================== " << endl;

    // Testar bubble sort otimizado
    timeStart = high_resolution_clock::now();
    optimizedBubblesort(largeRandomList);
    timeStop = high_resolution_clock::now();
    cout << "Lista ordenada utilizando bubble sort otimizado: ";
    displayList(largeRandomList);
    timeDuration = duration_cast<nanoseconds>(timeStop - timeStart);
    cout << "Tempo utilizado: " << timeDuration.count() << " nanosegundos" << endl;
    cout << " ========================================== " << endl;

    // Testar selection sort
    timeStart = high_resolution_clock::now();
    selectionSort(largeRandomList);
    timeStop = high_resolution_clock::now();
    cout << "Lista ordenada utilizando selection sort: ";
    displayList(largeRandomList);
    timeDuration = duration_cast<nanoseconds>(timeStop - timeStart);
    cout << "Tempo utilizado: " << timeDuration.count() << " nanosegundos" << endl;
    cout << " ========================================== " << endl;

    // Testar selection sort otimizado
    timeStart = high_resolution_clock::now();
    optimizedSelectionSort(largeRandomList);
    timeStop = high_resolution_clock::now();
    cout << "Lista ordenada utilizando selection sort otimizado: ";
    displayList(largeRandomList);
    timeDuration = duration_cast<nanoseconds>(timeStop - timeStart);
    cout << "Tempo utilizado: " << timeDuration.count() << " nanosegundos" << endl;

    // Limpar a memória
    deleteAll(largeRandomList);

    return 0;
}

Node* createNode(int iPayload) {
    Node* temp = (Node*)malloc(sizeof(Node));
    temp->iPayload = iPayload;
    temp->ptrNext = nullptr;
    temp->ptrPrev = nullptr;
    return temp;
}

void displayList(Node* node) {
    if (node == nullptr) {
        cout << "Lista vazia: não é possível exibir" << endl;
        return;
    }
    if (node->ptrPrev != nullptr) {
        cout << "Meio ou fim da lista: não é possível exibir" << endl;
        return;
    }
    Node* temp = node;
    while (temp != nullptr) {
        cout << temp->iPayload << " ";
        temp = temp->ptrNext;
    }
    cout << endl;
}

void insertFront(Node** head, int iPayload) {
    Node* newNode = createNode(iPayload);
    if (*head != nullptr) {
        newNode->ptrPrev = nullptr;
        (*head)->ptrPrev = newNode;
        newNode->ptrNext = (*head);
        (*head) = newNode;
        return;
    }
    (*head) = newNode;
}

void insertEnd(Node** head, int iPayload) {
    Node* newNode = createNode(iPayload);
    if (*head == nullptr) {
        newNode->ptrPrev = nullptr;
        (*head) = newNode;
        return;
    }
    Node* temp = (*head);
    while (temp->ptrNext != nullptr) temp = temp->ptrNext;
    newNode->ptrPrev = temp;
    temp->ptrNext = newNode;
}

void deleteAll(Node*& head) {
    Node* current = head;
    while (current != nullptr) {
        Node* temp = current->ptrNext;
        free(current);
        current = temp;
    }
    head = nullptr;
}

void trocaValor(Node* node1, Node* node2) {
    int temp = node1->iPayload;
    node1->iPayload = node2->iPayload;
    node2->iPayload = temp;
}

void bubblesort(Node* head) {
    if (head == nullptr || head->ptrNext == nullptr) {
        return;
    }
    Node* lastNode = nullptr;
    Node* firstNode = head;
    while (firstNode->ptrNext != nullptr) {
        Node* current = head;
        while (current->ptrNext != lastNode) {
            if (current->iPayload > current->ptrNext->iPayload) {
                trocaValor(current, current->ptrNext);
            }
            current = current->ptrNext;
        }
        firstNode = firstNode->ptrNext;
        lastNode = current;
    }
}

void optimizedBubblesort(Node* head) {
    if (head == nullptr || head->ptrNext == nullptr) {
        return;
    }
    bool unordered = false;
    Node* lastNode = nullptr;
    do {
        unordered = false;
        Node* current = head;
        while (current->ptrNext != lastNode) {
            if (current->iPayload > current->ptrNext->iPayload) {
                trocaValor(current, current->ptrNext);
                unordered = true;
            }
            current = current->ptrNext;
        }
        lastNode = current;
    } while (unordered);
}

void selectionSort(Node* head) {
    if (head == nullptr || head -> ptrNext == nullptr) {
        // Se a lista estiver vazia ou contiver apenas um nó, não há nada a fazer
        return;
    }

    Node* current = head; // Começamos do nó inicial da lista

    while (current != nullptr) { // Enquanto não chegarmos ao final da lista
        Node* start = current->ptrNext; // Marca o início da iteração atual 

        while (start != nullptr ) { // Enquanto não chegarmos ao final da lista
            if (current->iPayload > start->iPayload) {
                trocaValor(current, start);
            }
            start = start->ptrNext; // Avançar para o próximo nó
        }
        current = current->ptrNext; // Avançar para o próximo nó para a próxima iteração
    }
}

void optimizedSelectionSort(Node* head) {
    if (head == nullptr || head->ptrNext == nullptr) {
        return;
    }
    Node* current = head;
    while (current->ptrNext != nullptr) {
        Node* minNode = current;
        Node* temp = current->ptrNext;
        while (temp != nullptr) {
            if (temp->iPayload < minNode->iPayload) {
                minNode = temp;
            }
            temp = temp->ptrNext;
        }
        trocaValor(current, minNode);
        current = current->ptrNext;
    }
}

Node* generateRandomList(int size) {
    Node* head = nullptr;
    for (int i = 0; i < size; ++i) {
        insertEnd(&head, rand() % 1000); // Inserir números aleatórios entre 0 e 999
    }
    return head;
}
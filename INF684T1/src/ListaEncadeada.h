#include <iostream>
#include "Vertice.h"
using namespace std;

/* Estrutura de dados que representa cada item da lista */
struct list_item {

    struct list_item* prev; // Item antecessor
    Vertice value; // Valor do item atual
    struct list_item* next; // Item sucessor
};


/**
 * Classe que implementa uma lista duplamente encadeada com elementos  não
 * ordenados.
 */
class LinkedList {

    private:
        /* O início da lista é um ponteiro para o primeiro item */
        struct list_item *head;

        /* Tamanho atual da lista */
        int size;

    public:

        /*
         * Construtor da classe de listas encadeadas. Inicializa as variáveis
         */
        LinkedList ()
        {
            head = NULL;
            size = 0;
        }

        /*
         * Destrutor da classe de listas encadeadas. Libera a memória utilizada
         */
        ~LinkedList ()
        {
            while (head != NULL) {
                if(head->next != NULL) {
                    struct list_item *temp = head->next;

                    head->prev = head->next = NULL;
                    free((struct list_item *) head);

                    head = temp;
                } else {
                    head = NULL;
                }
            }
        }

        /*
         * Insere um novo item à lista. As inserções ocorrem no início da lista
         */
        void Insert (Vertice item)
        {
            /* Aloca memória para um struct list_item */
            struct list_item *new_item = (struct list_item *) malloc(
                sizeof(struct list_item)
            );
            new_item->value = item;

            if(isEmpty()) { // Estamos inserindo o primeiro item
                head = new_item;
                new_item->next = NULL;
            } else { // Estamos trocando o primeiro item pelo novo item
                struct list_item *old_head = head;
                head = new_item;
                new_item->next = old_head;
                old_head->prev = new_item;
            }
            new_item->prev = NULL; // Agora o novo item é o início da lista
            size++;
        }

        /*
         * Busca e retorna um item da lista caso encontrado. Caso o item não
         * seja encontrado retorna NULL
         */
        struct list_item* Search (Vertice item)
        {
            struct list_item *iterator = head;

            do {
                if(iterator->value == item) {
                    return iterator;
                }

                iterator = iterator->next;

            } while(iterator != NULL);

            return NULL;
        }

        /*
         * Remove um item da lista caso ele exista
         */
        void Remove (Vertice item)
        {
            struct list_item *item_ptr = Search(item);

            if(item_ptr != NULL) { // Se o item foi encontrado

                if(item_ptr->prev == NULL) { // Início da lista?

                    if(item_ptr->next == NULL) { // E também o final?
                        head = NULL;
                    } else {
                        item_ptr->next->prev = NULL;
                        head = item_ptr->next;
                    }

                } else if (item_ptr->next == NULL) { // Final da lista?
                    item_ptr->prev->next = NULL;

                } else { // Itens do meio da lista. Troca-se os ponteiros
                    item_ptr->prev->next = item_ptr->next;
                    item_ptr->next->prev = item_ptr->prev;
                }

                /* Como utilizamos malloc, vamos desalocar a estrutura */
                free((struct list_item *) item_ptr);
                size--;
            }
        }

        /*
         * Atualiza o valor de um item da lista caso ele exista
         */
        void Update (Vertice item, Vertice new_item)
        {
            struct list_item *iterator = head;

            do {
                if(iterator->value == item) {
                    iterator->value = new_item;
                    break;
                }
                iterator = iterator->next;

            } while (iterator != NULL);
        }

        /*
         * verifica se a lista está vazia
         */
        bool isEmpty ()
        {
            return (size == 0 || head == NULL);
        }

        /*
         * Retorna o tamanho atual da lista
         */
        int Size ()
        {
            return size;
        }

        /*
         * Imprime a lista na saída padrão
         */
        void toString ()
        {
            cout << "Head -> ";
            if(!isEmpty()) {

                struct list_item *current = head;
                cout << "[" << current->value.v << "] -> ";
                while(current->next != NULL) {

                    current = current->next;
                    cout << "[" << current->value.v << "] -> ";
                }
            }

            cout << "NULL" << endl;
        }

        /*
         * Converte a lista para um array dcujo tamanho é o tamanho atual da
         * lista
         */
      
};


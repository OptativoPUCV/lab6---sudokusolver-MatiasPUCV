#include "list.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct {
  int sudo[9][9];
} Node;

Node *createNode() {
  Node *n = (Node *)malloc(sizeof(Node));
  return n;
}

Node *copy(Node *n) {
  Node *new = (Node *)malloc(sizeof(Node));
  *new = *n;
  return new;
}

Node *read_file(char *file_name) {
  Node *n = createNode();
  FILE *file = fopen(file_name, "r");
  int i, j;
  for (i = 0; i < 9; i++) {
    for (j = 0; j < 9; j++) {
      if (!fscanf(file, "%d", &n->sudo[i][j]))
        printf("failed to read data!");
    }
  }

  fclose(file);
  return n;
}

void print_node(Node *n) {
  int i, j;
  for (i = 0; i < 9; i++) {
    for (j = 0; j < 9; j++)
      printf("%d ", n->sudo[i][j]);
    printf("\n");
  }
  printf("\n");
}

int* get_int_arr()
{
  int* temp = malloc(sizeof(int) * 9);

  for (int i = 0; i < 9; i++)
    temp[i] = 0;

  return temp;
}

void valid_arr(int* arr, bool* flag)
{
    bool temp = true;

    for (int i = 0; i < 9; i++)
    {
        if (arr[i] != 0 && arr[i] != 1)
            temp = false;
    }

    if (*flag == true && temp == false)
        *flag = false;

    free(arr);
}

int is_valid(Node *n)
{
    bool result = true;

    for (int i = 0; i < 9; i++)
    {
        int* arr1 = get_int_arr();
        int* arr2 = get_int_arr();
      
        for (int j = 0; j < 9; j++)
        {
            if (n->sudo[i][j] != 0)
                arr1[n->sudo[i][j] - 1] += 1;

            if (n->sudo[j][i] != 0)
                arr2[n->sudo[j][i] - 1] += 1;
        }

        valid_arr(arr1, &result);
        valid_arr(arr2, &result);
    }

    for (int k = 0; k < 9; k++)
    {
      int* arr = get_int_arr();
        for (int p = 0; p < 9; p++)
        {
             int i=3*(k/3) + (p/3);
             int j=3*(k%3) + (p%3);
          
             if (n->sudo[i][j] != 0)
                arr[n->sudo[i][j] - 1] += 1;
        }

        valid_arr(arr, &result);
        printf("\n");
    }
  
    return result;
}

List *get_adj_nodes(Node *n) {
  List *list = createList();

  int i, j;
  for(i = 0; i < 9; i++)
    {
      int flag = 0;
      for (j = 0; j < 9; j++)
        {
          if (n->sudo[i][j] == 0)
          {
            flag = 1;
            break;
          }
        }

      if (flag == 1)
      {
        break;
      }
    }

  for (int index = 1; index < 10; index++)
    {
      Node* node = copy(n);
      n->sudo[i][j] = index;

      if(is_valid(node) == true)
      {
        pushBack(list, node);
        print_node(node);
      }
      else
      {
        free(node);
      }
    }

  return list;
}

int is_final(Node *n) { return 0; }

Node *DFS(Node *initial, int *cont) { return NULL; }

/*
int main( int argc, char *argv[] ){

  Node* initial= read_file("s12a.txt");;

  int cont=0;
  Node* final = DFS(initial, &cont);
  printf("iterations:%d\n",cont);
  print_node(final);

  return 0;
}*/
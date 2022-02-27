#include <stdio.h>
#include <string.h>
#define MAX_SIZE 26
#define true 1
#define false 0

char adjacent[MAX_SIZE][MAX_SIZE];
char visited[MAX_SIZE];
char orderedVertices[MAX_SIZE];
int edgedFounded = -1;

// Para cada novo caso, zeramos o array de adjacencia e os arrays visitados.
void clearVariables()
{
  memset(adjacent, false, sizeof(adjacent));
  memset(visited, false, sizeof(visited));
}

// Procuramos todos os vértices adjancentes a partir um vértice raiz recursivamente.
void dfs(int curr_vertice, int m)
{
  int i;
  visited[curr_vertice] = true;
  orderedVertices[++edgedFounded] = curr_vertice;
  for (i = 0; i < m; ++i)
  {
    if (adjacent[curr_vertice][i])
    {
      if (!visited[i])
      {
        dfs(i, m);
      }
    }
  }
}

// Troca dois elementos de lugares no array
void swap(char *a, char *b)
{
  char temp = *a;
  *a = *b;
  *b = temp;
}

// Ordena utilizando Bubble Sort
void orderArray(char nums[])
{
  int swapped, i;
  char aux;
  while (1)
  {
    swapped = 0;
    for (i = 0; i < edgedFounded; i++)
    {
      if ((i + 1) <= edgedFounded && ((int)nums[i] > (int)nums[i + 1]) > 0)
      {
        swap(&nums[i], &nums[i + 1]);
        swapped = 1;
      }
    }
    if (swapped == 0 && i >= edgedFounded)
    {
      return;
    }
  }
}

void createAdjacence(char verticeA, char verticeB)
{
  adjacent[verticeA - 'a'][verticeB - 'a'] = true;
  adjacent[verticeB - 'a'][verticeA - 'a'] = true;
}

int main()
{
  char verticeA, verticeB;
  int qntTestCase, qntVertice, qntEdges;
  int currCase = 1;
  scanf("%d", &qntTestCase);
  while (qntTestCase--)
  {
    scanf("%d %d%*c", &qntVertice, &qntEdges);
    int index;
    for (index = 0; index < qntEdges; index++)
    {
      scanf("%c %c%*c", &verticeA, &verticeB);
      createAdjacence(verticeA, verticeB);
    }
    printf("Case #%d:\n", currCase++);
    int qntComponents = 0;
    for (index = 0; index < qntVertice; ++index)
    {

      if (!visited[index])
      {
        qntComponents++;
        dfs(index, qntVertice);
        int j;
        orderArray(orderedVertices);
        for (j = 0; j <= edgedFounded; j++)
          printf("%c,", orderedVertices[j] + 'a');

        printf("\n");
      }

      edgedFounded = -1;
    }
    printf("%d connected components\n\n", qntComponents);
    clearVariables();
  }
}
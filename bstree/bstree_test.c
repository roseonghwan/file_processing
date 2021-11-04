#include <stdio.h>

#include "bstree.h"

void print(int key, int value) { printf("%d ", key); }

int main(void)
{
  const int testcases[] = {40, 11, 77, 33, 20, 90, 99, 70, 88, 80, 66, 10, 22, 30, 44, 55, 50, 60, 25, 49};

  struct bs_node *tree = NULL;

  for (const int *it = testcases; it < testcases + sizeof(testcases) / sizeof(int); ++it)
  {
    bs_insert(&tree, *it, 0);
    bs_inorder(tree, print);
    printf("\n");
  }
  for (const int *it = testcases; it < testcases + sizeof(testcases) / sizeof(int); ++it)
  {
    bs_erase(&tree, *it);
    bs_inorder(tree, print);
    printf("\n");
  }
  for (const int *it = testcases; it < testcases + sizeof(testcases) / sizeof(int); ++it)
  {
    bs_insert(&tree, *it, 0);
    bs_inorder(tree, print);
    printf("\n");
  }
  for (const int *it = testcases + sizeof(testcases) / sizeof(int) - 1; testcases <= it; --it)
  {
    bs_erase(&tree, *it);
    bs_inorder(tree, print);
    printf("\n");
  }
}

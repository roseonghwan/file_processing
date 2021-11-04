#ifndef _BSTREE_H
#define _BSTREE_H

#include <stdlib.h>
#include <stdio.h>

struct bs_node
{
  int key;
  int value;
  struct bs_node *left;
  struct bs_node *right;
};

static inline struct bs_node *bs_alloc(void)
{
  struct bs_node *node = malloc(sizeof(struct bs_node));
  node->left = NULL;
  node->right = NULL;
  return node;
}

extern inline void bs_insert(struct bs_node **tree, int key, int value)
{
  struct bs_node *parent = NULL;
  struct bs_node *walk = *tree;
  while (walk != NULL)
  {
    if (key == walk->key)
      return;

    parent = walk;

    if (key > walk->key)
      walk = walk->right;
    else
      walk = walk->left;
  }
  walk = bs_alloc();
  walk->key = key;
  walk->value = value;

  if (parent == NULL)
    *tree = walk;
  else if (key > parent->key)
    parent->right = walk;
  else
    parent->left = walk;
}

extern inline void bs_erase(struct bs_node **tree, int key)
{
  struct bs_node *parent = NULL;
  struct bs_node *walk = *tree;
  while (walk != NULL && walk->key != key)
  {
    parent = walk;
    if (key > walk->key)
      walk = walk->right;
    else
      walk = walk->left;
  }
  if (walk == NULL)
    return;

  if (walk->left != NULL && walk->right != NULL)
  {
    parent = walk;
    struct bs_node *tmp = parent;

    for (walk = walk->left; walk->right != NULL; walk = walk->right)
      tmp = walk;
    printf("parent: %d, tmp: %d, walk: %d\n", parent->key, tmp->key, walk->key);
    parent->key = walk->key;
    parent->value = walk->value;
    parent = tmp;
  }

  if (walk->left == NULL && walk->right == NULL)
  {
    if (parent == NULL)
      *tree = NULL;
    else if (parent->left == walk)
      parent->left = NULL;
    else
      parent->right = NULL;
  }

  else if (walk->left != NULL)
  {
    if (parent == NULL)
      *tree = walk->left;
    else if (parent->left == walk)
      parent->left = walk->left;
    else
      parent->right = walk->left;
  }

  else
  {
    if (parent == NULL)
      *tree = walk->right;
    else if (parent->left == walk)
      parent->left = walk->right;
    else
      parent->right = walk->right;
  }
  free(walk);
}

extern inline void bs_inorder(struct bs_node *tree, void (*func)(int, int))
{
  if (tree != NULL)
  {
    bs_inorder(tree->left, func);
    func(tree->key, tree->value);
    bs_inorder(tree->right, func);
  }
}

#endif

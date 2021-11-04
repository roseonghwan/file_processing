#ifndef _AVLTREE_H
#define _AVLTREE_H

#include <cstdlib>
#include <stack>
#include <iostream>
using namespace std;

struct avl_node
{
    int key;
    int value;
    struct avl_node *left;
    struct avl_node *right;
    size_t height;
};

static inline struct avl_node *avl_alloc()
{
    struct avl_node *node = (struct avl_node *)malloc(sizeof(struct avl_node));
    node->left = nullptr;
    node->right = nullptr;
    node->height = 1;
    return node;
}

static inline size_t max(const size_t a, const size_t b)
{
    if (a > b)
        return a;
    else
        return b;
}

static inline size_t height(const struct avl_node *tree)
{
    if (tree == nullptr)
        return 0;
    else
        return tree->height;
}

static inline void avl_LL(struct avl_node **root, struct avl_node *x, struct avl_node *parent)
{
    struct avl_node *lc = x->left;
    x->left = lc->right;
    lc->right = x;

    if (parent == nullptr)
        *root = lc;
    else if (parent->left == x)
        parent->left = lc;
    else
        parent->right = lc;
}

static inline void avl_RR(struct avl_node **root, struct avl_node *x, struct avl_node *parent)
{
    struct avl_node *rc = x->right;
    x->right = rc->left;
    rc->left = x;

    if (parent == nullptr)
        *root = rc;
    else if (parent->left == x)
        parent->left = rc;
    else
        parent->right = rc;
}

extern inline void avl_insert(struct avl_node **tree, int key, int value)
{
    stack<struct avl_node *> s;
    struct avl_node *parent = nullptr;
    struct avl_node *walk = *tree;
    struct avl_node *x = nullptr;

    while (walk != NULL)
    {
        if (key == walk->key)
            return;

        parent = walk;

        s.push(walk);
        if (key > walk->key)
            walk = walk->right;
        else
            walk = walk->left;
    }

    walk = avl_alloc();
    walk->key = key;
    walk->value = value;

    if (parent == nullptr)
        *tree = walk;
    else if (key > parent->key)
        parent->right = walk;
    else
        parent->left = walk;

    while (!s.empty())
    {
        walk = s.top();
        s.pop();
        walk->height = 1 + max(height(walk->left), height(walk->right));
        if (1 + height(walk->right) < height(walk->left) || 1 + height(walk->left) < height(walk->right))
        {
            x = walk;
            if (s.empty())
                parent = nullptr;
            else
                parent = s.top();
            break;
        }
    }

    if (x == nullptr)
        return;

    // 왼쪽 균형인수가 오른쪽보다 2 큼
    if (1 + height(x->right) < height(x->left))
    {
        // LL case
        if (height(x->left->left) >= height(x->left->right))
        {
            s.push(x->left);
            s.push(x);
            avl_LL(tree, x, parent);
        }

        // LR case
        else
        {
            s.push(x->left->right);
            s.push(x->left);
            s.push(x);
            avl_RR(tree, x->left, x);
            avl_LL(tree, x, parent);
        }
    }

    // 오른쪽 균형인수가 왼쪽보다 2 큼
    else if (1 + height(x->left) < height(x->right))
    {
        // RR case
        if (height(x->right->right) >= height(x->right->left))
        {
            s.push(x->right);
            s.push(x);
            avl_RR(tree, x, parent);
        }

        // RL case
        else
        {
            s.push(x->right->left);
            s.push(x->right);
            s.push(x);
            avl_LL(tree, x->right, x);
            avl_RR(tree, x, parent);
        }
    }

    // 높이 재계산
    while (!s.empty())
    {
        walk = s.top();
        s.pop();
        walk->height = 1 + max(height(walk->left), height(walk->right));
    }
}

extern inline void avl_erase(struct avl_node **tree, int key)
{
    stack<struct avl_node *> s;
    struct avl_node *parent = nullptr;
    struct avl_node *walk = *tree;
    struct avl_node *x = nullptr;

    while (walk != nullptr && key != walk->key)
    {
        parent = walk;
        s.push(walk);

        if (key > walk->key)
            walk = walk->right;
        else
            walk = walk->left;
    }
    if (walk == nullptr)
        return;

    if (walk->left != nullptr && walk->right != nullptr)
    {
        parent = walk;

        struct avl_node *tmp = parent;

        for (walk = walk->left; walk->right != nullptr; walk = walk->right)
            tmp = walk;

        parent->key = walk->key;
        parent->value = walk->value;
        parent = tmp;
    }

    if (walk->left == nullptr && walk->right == nullptr)
    {
        if (parent == nullptr)
            *tree = nullptr;
        else if (parent->left == walk)
            parent->left = nullptr;
        else
            parent->right = nullptr;
    }

    else if (walk->left != nullptr)
    {
        if (parent == nullptr)
            *tree = walk->left;
        else if (parent->left == walk)
            parent->left = walk->left;
        else
            parent->right = walk->left;
    }

    else
    {
        if (parent == nullptr)
            *tree = walk->right;
        else if (parent->left == walk)
            parent->left = walk->right;
        else
            parent->right = walk->right;
    }

    free(walk);

    while (!s.empty())
    {
        walk = s.top();
        s.pop();
        walk->height = 1 + max(height(walk->left), height(walk->right));
        if (1 + height(walk->right) < height(walk->left) || 1 + height(walk->left) < height(walk->right))
        {
            x = walk;
            if (s.empty())
                parent = nullptr;
            else
                parent = s.top();
            break;
        }
    }

    if (x == nullptr)
        return;

    // 왼쪽 균형인수가 오른쪽보다 2 큼
    if (1 + height(x->right) < height(x->left))
    {
        // LL case
        if (height(x->left->left) >= height(x->left->right))
        {
            s.push(x->left);
            s.push(x);
            avl_LL(tree, x, parent);
        }

        // LR case
        else
        {
            s.push(x->left->right);
            s.push(x->left);
            s.push(x);
            avl_RR(tree, x->left, x);
            avl_LL(tree, x, parent);
        }
    }

    // 오른쪽 균형인수가 왼쪽보다 2 큼
    else if (1 + height(x->left) < height(x->right))
    {
        // RR case
        if (height(x->right->right) >= height(x->right->left))
        {
            s.push(x->right);
            s.push(x);
            avl_RR(tree, x, parent);
        }

        // RL case
        else
        {
            s.push(x->right->left);
            s.push(x->right);
            s.push(x);
            avl_LL(tree, x->right, x);
            avl_RR(tree, x, parent);
        }
    }

    // 높이 재계산
    while (!s.empty())
    {
        walk = s.top();
        s.pop();
        walk->height = 1 + max(height(walk->left), height(walk->right));
    }
}

extern inline void avl_inorder(const struct avl_node *tree, void (*func)(const int, int))
{
    if (tree != nullptr)
    {
        avl_inorder(tree->left, func);
        func(tree->key, tree->value);
        avl_inorder(tree->right, func);
    }
}

#endif

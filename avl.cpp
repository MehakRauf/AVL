#include <iostream>
#include <stdlib.h>
using namespace std;

// Tree structure
struct avl
{
    int height;
    int data;
    avl *left;
    avl *right;
};

// to get the height of the node
int getHeight(avl *node)
{
    if (node == NULL)
    {
        return 0;
    }
    return node->height;
}
// shift left function
struct avl *shiftleft(struct avl *node)
{
    // creating a new noode
    avl *Nnode = node->right;
    // left child of the new node
    avl *LC = Nnode->left;
    // assgning the new node as root
    Nnode->left = node;
    // assigning the LC of the Nnode to the node
    node->right = LC;
    // assgning the heights
    node->height = max(getHeight(node->right), getHeight(node->left)) + 1;
    Nnode->height = max(getHeight(Nnode->right), getHeight(Nnode->left)) + 1;

    // return the new node
    return Nnode;
}
// shift right function
struct avl *shiftright(struct avl *node)
{
    avl *Nnode = node->left;
    avl *RC = Nnode->right;
    Nnode->right = node;
    node->left = RC;
    node->height = max(getHeight(node->right), getHeight(node->left)) + 1;
    Nnode->height = max(getHeight(Nnode->right), getHeight(Nnode->left)) + 1;

    return Nnode;
}

// to get the balance factor i.e: left-right
int balance_factor(avl *node)
{
    if (node == NULL)
    {
        return 0;
    }
    return (getHeight(node->left) - getHeight(node->right));
}
// Function to find the node with minimum value in a tree
struct avl *findMinNode(struct avl *node)
{
    struct avl *current = node;
    while (current->left != NULL)
    {
        current = current->left;
    }
    return current;
}

// Function to delete a node from AVL tree
struct avl *deleteNode(struct avl *root, int val)
{
    // Base case
    if (root == NULL)
    {
        return root;
    }
    // If the value to be deleted is smaller than the root value, then it lies in the left subtree
    if (val < root->data)
    {
        root->left = deleteNode(root->left, val);
    }
    // If the value to be deleted is greater than the root value, then it lies in the right subtree
    else if (val > root->data)
    {
        root->right = deleteNode(root->right, val);
    }
    // If the value to be deleted is equal to the root value
    else
    {
        // Node with only one child or no child
        if ((root->left == NULL))
        {
            struct avl *temp = root->right;
            free(root);
            return temp;
        }
        if ((root->right) == NULL)
        {
            struct avl *temp = root->right;
            free(root);
            return temp;
        }
        else
        {
            // Node with two children
            struct avl *temp = findMinNode(root->right);

            // Copy the data to this node
            root->data = temp->data;

            // Delete node
            root->right = deleteNode(root->right, temp->data);
        }
    }

    // If the tree had only one node, then return
    if (root == NULL)
        return root;

    // Update the height of the current node
    root->height = 1 + max(getHeight(root->left), getHeight(root->right));

    // Get the balance factor of this node
    int bf = balance_factor(root);

    //shift right (left left case)
    if (bf > 1 && val < root->left->data)
    {
        return shiftright(root);
    }
    // shift left (right right case)
    if (bf < -1 && val > root->right->data)
    {
        return shiftleft(root);
    }
    // double shift (left right case)
    if (bf > 1 && val > root->left->data)
    {
        root->left = shiftleft(root->left);
        return shiftright(root);
    }
    // double shift (right left case)
    if (bf < -1 && val < root->right->data)
    {
        root->right = shiftright(root->right);
        return shiftleft(root);
    }

    // Return the updated node
    return root;
}

// to insert a node
struct avl *insert(struct avl *node, int val)
{
    // memory allocation
    struct avl *temp = (struct avl *)malloc(sizeof(struct avl));
    temp->data = val;
    temp->left = temp->right = NULL;
    temp->height = 1;
    // if tree is null
    if (node == NULL)
    {
        return temp;
    }
    // if values is smaller than the root node value
    if (val < node->data)
    {
        node->left = insert(node->left, val);
    }
    // if alue is greater
    else
    {
        node->right = insert(node->right, val);
    }
    // calculating the height of the node
    node->height = 1 + max(getHeight(node->left), getHeight(node->right));
    // taking the balance factor
    int bf = balance_factor(node);
    // shift right (left left case)
    if (bf > 1 && val < node->left->data)
    {
        return shiftright(node);
    }
    // shift left (right right case)
    if (bf < -1 && val > node->right->data)
    {
        return shiftleft(node);
    }
    // double shift (left right case)
    if (bf > 1 && val > node->left->data)
    {
        node->left = shiftleft(node->left);
        return shiftright(node);
    }
    // double shift (right left case)
    if (bf < -1 && val < node->right->data)
    {
        node->right = shiftright(node->right);
        return shiftleft(node);
    }
    // returning the node itself if it is already balanced
    return node;
}
// preorder traversal of the tree
void preOrder(avl *node)
{
    if (node == NULL)
    {
        return;
    }
    cout << node->data << " ";
    preOrder(node->left);
    preOrder(node->right);
}
int main()
{
    struct avl *root = NULL;

    // storing the root value every time because of unbalancing
    root = insert(root, 1);
    root = insert(root, 2);
    root = insert(root, 4);
    root = insert(root, 5);
    root = insert(root, 6);
    root = insert(root, 3);
    root = insert(root, 15);
    root = insert(root, 7);
    root = insert(root, 10);
    root = deleteNode(root, 10);

    preOrder(root);
    return 0;
}
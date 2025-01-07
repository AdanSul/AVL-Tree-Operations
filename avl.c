#include "avl.h"
#include <stdio.h>
#include <stdlib.h>


/*Optional utility functions*/
int util_max(int x,int y)
{
    return x>y?x:y;
}
int util_min(int x,int y)
{
    return x<y?x:y;
}
int util_abs(int x)
{
    return (x>0)?x:-x;
}

/*help functions*/
int getHeight(AVLNodePtr node);
int getSize(AVLNodePtr node);
int getSum(AVLNodePtr node);
AVLNodePtr rightRotation(AVLNodePtr node);
AVLNodePtr leftRotation(AVLNodePtr node);
AVLNodePtr Balance_AvlTree_insert(AVLNodePtr root);
void update_height(AVLNodePtr root);
void update_size(AVLNodePtr root);
AVLNodePtr return_Min(AVLNodePtr root);
void update_sum(AVLNodePtr root);
void update_node(AVLNodePtr root);
int check_avlBalance(AVLNodePtr root);
AVLNodePtr buildAVLTree(int* arr, int start, int end);
void mergeArrays(int* A1, int* A2, int* A3, int size1, int size2, int* size3);
void inorderTrav(AVLNodePtr root, int* Array, int* index);
void postOrder(AVLNodePtr root);
int sum_from_x(AVLNodePtr root, int x, int sum1);
int sum_from_y(AVLNodePtr root, int y, int sum2);


/*return the height of an node*/
int getHeight(AVLNodePtr node)
{
    if (node == NULL)
    {
        return -1;
    }
    return node->height;
}


/*return the size of an node*/
int getSize(AVLNodePtr node)
{
    if (node == NULL)
    {
        return 0;
    }
    return node->tree_size;
}

/* retrun the sum of the keys subtree rooted at a particular node.*/
int getSum(AVLNodePtr node)
{
    if (node == NULL)
    {
        return 0;
    }
    return node->tree_sum;
}

AVLNodePtr return_Min(AVLNodePtr root)
{
    AVLNodePtr min = root;
    while (min->child[0] != NULL)
        min = min->child[0];
    return min;
}

AVLNodePtr rightRotation(AVLNodePtr node)
{
    AVLNodePtr lNode = node->child[0];
    AVLNodePtr lRNode = lNode->child[1];

    /*Perform rotation*/
    lNode->child[1] = node;
    node->child[0] = lRNode;

    /*Update heights*/
    node->height = util_max(getHeight(node->child[0]), getHeight(node->child[1])) + 1;
    lNode->height = util_max(getHeight(lNode->child[0]), getHeight(lNode->child[1])) + 1;

    /*update sizes*/
    node->tree_size = getSize(node->child[0]) + getSize(node->child[1]) + 1;
    lNode->tree_size= getSize(lNode->child[0]) + getSize(lNode->child[1]) + 1;

    /*update sums*/
    node->tree_sum = getSum(node->child[0]) + getSum(node->child[1]) + node->key;
    lNode->tree_sum = getSum(lNode->child[0]) + getSum(lNode->child[1]) + lNode->key;

    /*return new root*/
    return lNode;

}

AVLNodePtr leftRotation(AVLNodePtr node)
{
    AVLNodePtr rNode = node->child[1];
    AVLNodePtr rLNode = rNode->child[0];

    /*Perform rotation*/
    rNode->child[0] = node;
    node->child[1] = rLNode;

    /*Update heights*/
    node->height = util_max(getHeight(node->child[0]), getHeight(node->child[1])) + 1;
    rNode->height = util_max(getHeight(rNode->child[0]), getHeight(rNode->child[1])) + 1;

    /*update sizes*/
    node->tree_size = getSize(node->child[0]) + getSize(node->child[1]) + 1;
    rNode->tree_size = getSize(rNode->child[0]) + getSize(rNode->child[1]) + 1;

    /*update sums*/
    node->tree_sum = getSum(node->child[0]) + getSum(node->child[1]) + node->key;
    rNode->tree_sum = getSum(rNode->child[0]) + getSum(rNode->child[1]) + rNode->key;

    /*return new root*/
    return rNode;
}
AVLNodePtr Balance_AvlTree_insert(AVLNodePtr root)
{
    AVLNodePtr subtree;
    /*no need to baLance*/
    if (util_abs((getHeight(root->child[0]) - getHeight(root->child[1]))) <= 1)
        return root;
    /*if the height of the left subtree is greater than right subtree*/
    else if (getHeight(root->child[0]) > getHeight(root->child[1]))
    {
        subtree = root->child[0];
        if (getHeight(subtree->child[0]) < getHeight(subtree->child[1])) /*LR rotaion*/
        {
            leftRotation(subtree);
        }
        return rightRotation(root);    /*L rotation */
    }
    else
    {
        /*if the height of the right subtree is greater than left subtree*/
        subtree = root->child[1];
        if (getHeight(subtree->child[0]) > getHeight(subtree->child[1])) /*RL rotation */
        {
            rightRotation(subtree);
        }
        return leftRotation(root);/* R rotation */
    }
}

AVLNodePtr new_avl_node( int x)
{
    AVLNodePtr newNode;
    /*create a new node to put x in it */
    if ((newNode = (AVLNodePtr)malloc(sizeof(AVLNode))) == NULL)
    {
        return NULL;
    }
    else
    {
        /*update sum/size/height/ values of the node */
        newNode->key = x;
        newNode->child[0] = NULL;
        newNode->child[1] = NULL;
        newNode->height = 0;
        newNode->tree_size = 1;
        newNode->tree_sum = x;
        return (newNode);
    }
}
AVLNodePtr avl_search(AVLNodePtr root,int x)
{
    if (root == NULL)
    {
        return NULL;
    }
    if (root->key < x)
    {
        return avl_search(root->child[1], x);
    }

    else if (root->key > x)
    {
        return avl_search(root->child[0], x);
    }

    else
    {
        return root;
    }
}

AVLNodePtr avl_insert(AVLNodePtr root, int x)
{
    if (root == NULL)
    {
        return new_avl_node(x);
    }
    /* if the root is not null =>search the appropriate place value of x in the root */
    if(!avl_search(root,x))
    {
        if (root->key < x)
        {
            root->child[1] = avl_insert(root->child[1], x);
        }

        else if (root->key > x)
            root->child[0] = avl_insert(root->child[0], x);

        /*update the sum/size/height values */
        root->height = util_max(getHeight(root->child[0]), getHeight(root->child[1]))+1;
        root->tree_size = getSize(root->child[0])+getSize(root->child[1])+1;
        root->tree_sum = getSum(root->child[0])+getSum(root->child[1])+root->key;
        return Balance_AvlTree_insert(root);

    }
    else
        return root;
}
void avl_delete_all (AVLNodePtr root)
{
    if (root == NULL)
        return;

    /*delete the subtrees then delete the root*/
    avl_delete_all(root->child[0]);
    avl_delete_all(root->child[1]);

    free(root);
    return;
}

void update_height(AVLNodePtr root)
{
    int my_child;

    if (root == NULL)
    {
        return;
    }
    if (root->child[0] == NULL && root->child[1] == NULL)
    {
        root->height = 0; /*if its a leaf */
        return;
    }
    if (root->child[0] == NULL || root->child[1] == NULL) /*if its has one child */
    {
        my_child = root->child[0] ? 0 : 1; /*check witch child is not null */
        root->height = root->child[my_child]->height + 1;
        return;
    }
    /*update the height */
    if (root->child[0]->height > root->child[1]->height)
    {
        root->height = root->child[0]->height + 1;
    }
    else
    {
        root->height = root->child[1]->height + 1;
    }
    return;
}


void update_size(AVLNodePtr root)
{

    int my_child;

    if (root == NULL)
    {
        return; /*if its a leaf */
    }
    if (root->child[0] == NULL && root->child[1] == NULL)/*if its a leaf */
    {
        root->tree_size = 1;
        return;
    }
    if (root->child[0] == NULL || root->child[1] == NULL)  /*if its has one child */
    {
        my_child = root->child[0] ? 0 : 1; /*check witch child is not null */
        root->tree_size = root->child[my_child]->tree_size + 1;
        return;
    }
    root->tree_size = root->child[0]->tree_size + root->child[1]->tree_size + 1;
    return;
}

void update_sum(AVLNodePtr root)
{

    int my_child;

    if (root == NULL)
    {
        return;
    }
    if (root->child[0] == NULL && root->child[1] == NULL)/*if its has one child */
    {
        root->tree_sum = root->key;
        return;
    }
    if (root->child[0] == NULL || root->child[1] == NULL) /*if its has one child */
    {
        my_child = root->child[0] ? 0 : 1; /*check witch child is not null */
        root->tree_sum = root->child[my_child]->tree_sum + root->key;
        return;
    }
    root->tree_sum = root->child[0]->tree_sum + root->child[1]->tree_sum + root->key;
    return;
}

void update_node(AVLNodePtr root)
{
    update_height(root);
    update_size(root);
    update_sum(root);
    return;

}

int check_avlBalance(AVLNodePtr root)
{
    if (!root)
        return 0;
    return (getHeight(root->child[0]) - getHeight(root->child[1]));
}


AVLNodePtr avl_delete(AVLNodePtr root, int x)
{
    AVLNodePtr avl_temp;
    int balance;

    if (!root)
    {
        return root;
    }

    if (x > root->key)
    {
        root->child[1] = avl_delete(root->child[1], x);
    }

    else if (x < root->key)
    {
        root->child[0] = avl_delete(root->child[0], x);
    }
    else
    {
        if (!(root->child[0])|| !(root->child[1]))
        {
            root->tree_size--;

            avl_temp = root->child[0] ? root->child[0] : root->child[1];
            if (!avl_temp)
            {
                avl_temp = root;
                root = NULL;
            }
            else
            {
                (*root) = (*avl_temp);
            }

            free(avl_temp);
        }
        else
        {
            root->tree_size -= 1;
            avl_temp = return_Min(root->child[1]);
            root->key = avl_temp->key;
            root->child[1] = avl_delete(root->child[1], avl_temp->key);
        }
    }
    if (!root)
        return root;

    root->height = util_max(getHeight(root->child[0]), getHeight(root->child[1]))+1;
    root->tree_sum = getSum(root->child[0]) + getSum(root->child[1])+ root->key ;
    root->tree_size = getSize(root->child[0]) + getSize(root->child[1]) + 1;

    balance = check_avlBalance(root);

    if (balance < -1 && check_avlBalance(root->child[1]) <= 0)
        return leftRotation(root);

    if (balance < -1 && check_avlBalance(root->child[1]) > 0)
    {
        root->child[1] = rightRotation(root->child[1]);
        return leftRotation(root);
    }
    if (balance > 1 && check_avlBalance(root->child[0]) >= 0)
        return rightRotation(root);

    if (balance > 1 && check_avlBalance(root->child[0]) < 0)
    {
        root->child[0] = leftRotation(root->child[0]);
        return rightRotation(root);
    }

    return root;
}

AVLNodePtr avl_LCA(AVLNodePtr root,int x,int y)
{
    int upVal,downVal ;
    /*calculate the min/max of x and y */
    upVal= util_max(x,y);
    downVal=util_min(x,y);

    if (!root)
        return NULL;

    if (root->key <downVal) /*if the current value is smaller than x*/
        return avl_LCA(root->child[1],x,y);

    else if (root->key >upVal) /*If the current value is grater than y(up limit )*/
        return avl_LCA(root->child[0],x,y);

    return root ;

}


AVLNodePtr buildAVLTree(int* arr, int start, int end)
{
    int mid ;
    AVLNodePtr root;
    if (end < start)
    {
        return NULL;
    }

    mid = (start + end) / 2;   /*the mid val in the array is the root ,because the array is sorted*/
    root = malloc(sizeof(AVLNode));
    root->key = mid;

    root->child[0] = buildAVLTree(arr, start, mid - 1);
    root->child[1] = buildAVLTree(arr, mid + 1, end);

    return root;
}



void mergeArrays(int* A1, int* A2, int* A3, int size1, int size2, int* size3)
{
    int i = 0;
    int j = 0;
    int i3 = 0;
    while (i < size1 && j < size2)
    {
        if (A1[i] < A2[j])
        {
            A3[i3] = A1[i];
            i++;
        }
        else if (A1[i] > A2[j])
        {
            A3[i3] = A2[j];
            j++;
        }
        else   /*to skip the double value*/
        {
            A3[i3] = A2[j];
            i++;
            j++;
            (*size3)--;
        }
        i3++;
    }

    while (i < size1)
    {
        A3[i3] = A1[i];
        i++;
        i3++;
    }
    while (j < size2)
    {
        A3[i3] = A2[j];
        j++;
        i3++;
    }
}
void inorderTrav(AVLNodePtr root, int* Array, int* index)
{
    if (!root)
        return;

    /*The function recursively calls itself on the left child*/
    inorderTrav(root->child[0], Array, index);

    /*store the key of the root node in the array*/
    Array[(*index)++] = root->key;

    /*The function recursively calls itself on the right child*/
    inorderTrav(root->child[1], Array, index);
}

void postOrder(AVLNodePtr root)
{
    if (root == NULL)
        return;

    postOrder(root->child[0]);
    postOrder(root->child[1]);

    update_node(root);

}

AVLNodePtr avl_merge(AVLNodePtr root1,AVLNodePtr root2)
{
    int size1,size2,size3;
    int i1=0,i2=0;
    int* A1;
    int* A2;
    int* A3;
    AVLNodePtr root3;

    /*if one of them is empty return the other tree*/
    if (!root1)
    {
        return root2;
    }
    if (!root2)
    {
        return root1;
    }
    /* Traverse the two trees inOrder , and create tow arrays*/

    size1 = root1->tree_size;
    size2 = root2->tree_size;

    A1= malloc(size1 *(sizeof(int)));
    A2= malloc(size2 *(sizeof(int)));

    /*Traverse the two trees inOrder*/
    inorderTrav(root1, A1, &i1);
    inorderTrav(root2, A2, &i2);

    /* Merge the two arrays into newArray (A3)*/
    size3 = size1 + size2;
    A3 = malloc((size3) * sizeof(int));

    mergeArrays(A1, A2, A3, size1, size2, &size3);

    /*build avl tree from the sorted array*/
    root3 = buildAVLTree(A3, 0, size3 - 1);

    /*travel post order and update thee filed of the nodes*/
    postOrder(root3);

    free(A1);
    free(A2);
    free(A3);

    return root3;
}


int sum_from_x(AVLNodePtr root, int x, int sum1)
{
    sum1 = 0;
    if (!root)
        return 0;

    if (root->key == x)  /*add the root->key and its right subtree ,because they are grater than x and we are in the left ,all the value smaller than y*/
    {
        if (root->child[1] != NULL)
            sum1 += root->child[1]->tree_sum + root->key;

        else
            sum1 += root->key;

    }
    else if (root->key > x) /*should add all the values in the right subtree,because we are in the left: all the val smaller than y and here we check if the key grater than x */
    {
        if (root->child[1] != NULL)
            sum1 += root->child[1]->tree_sum + root->key;

        else
            sum1 += root->key;

        sum1 += sum_from_x(root->child[0], x, sum1);

    }
    else
        sum1 += sum_from_x(root->child[1], x, sum1);

    return sum1;

}

int sum_from_y(AVLNodePtr root, int y, int sum2)
{
    sum2 = 0;
    if (!root)
        return 0;

    if (root->key == y) /*add the sum of the left subtree because their value smaller than y and grater than x because we are in the right part */
    {
        if (root->child[0] != NULL)
            sum2 += root->child[0]->tree_sum + root->key;

        else
            sum2+=root->key;

    }
    else if (root->key < y)  /*root->key smaller than y ,add the sum of the left subtree because their values smaller than root->key that are smaller than y , and grater than x because we are in the right part */
    {
        if (root->child[0] != NULL)
            sum2 += root->child[0]->tree_sum + root->key;

        else
            sum2+=root->key;

        sum2 += sum_from_y(root->child[1], y, sum2);

    }
    else
        sum2 += sum_from_y(root->child[0], y, sum2);

    return sum2;
}


int avl_sum(AVLNodePtr root, int x, int y)
{
    int sum1 = 0, sum2 = 0;
    AVLNodePtr lca_node = avl_LCA(root,x,y);

    return sum_from_x(lca_node->child[0], x, sum1) + sum_from_y(lca_node->child[1],y, sum2) + lca_node->key;
}

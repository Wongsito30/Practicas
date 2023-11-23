#include <stdio.h>
#include <stdlib.h>

struct TreeNode {
    int key;
    struct TreeNode *left, *right;
};

struct TreeNode *newNode(int key) {
    struct TreeNode *newNode = (struct TreeNode *)malloc(sizeof(struct TreeNode));
    newNode->key = key;
    newNode->left = newNode->right = NULL;
    return newNode;
}

struct TreeNode *insert(struct TreeNode *root, int key) {
    if (root != NULL) {
        if (key < root->key) {
            root->left = insert(root->left, key);
        } else {
            root->right = insert(root->right, key);
        }
    } else {
        return newNode(key);
    }
    return root;
}

void deleteTree(struct TreeNode *root) {
    if (root != NULL) {
        deleteTree(root->left);
        deleteTree(root->right);
        free(root);
    }
}

struct TreeNode *deleteNode(struct TreeNode *root, int key) {
    if (root == NULL) {
        printf("EL ARBOL ESTA VACIO.\n");
        return NULL;
    }

    if (key < root->key) {
        root->left = deleteNode(root->left, key);
    } else if (key > root->key) {
        root->right = deleteNode(root->right, key);
    } else {
        if (root->left == NULL) {
            struct TreeNode *temp = root->right;
            free(root);
            return temp;
        } else if (root->right == NULL) {
            struct TreeNode *temp = root->left;
            free(root);
            return temp;
        }

        struct TreeNode *temp = root->right;
        while (temp != NULL && temp->left != NULL) {
            temp = temp->left;
        }

        root->key = temp->key;
        root->right = deleteNode(root->right, temp->key);
    }

    return root;
}

void displayLeft(struct TreeNode *child) {
    printf("LEFT: %d ", child->key);
}

void displayRight(struct TreeNode *child) {
    printf("RIGHT: %d ", child->key);
}

void displayMiddle(struct TreeNode *node) {
    printf("KEY: %d ", node->key);
    if (node->left != NULL) {
        displayLeft(node->left);
    }
    if (node->right != NULL) {
        displayRight(node->right);
    }
    printf("\n");
}

void display(struct TreeNode *root) {
    if (root != NULL) {
        display(root->left);
        displayMiddle(root);
        display(root->right);
    }
}

void inorder(struct TreeNode *root) {
    if (root != NULL) {
        inorder(root->left);
        printf("%d ", root->key);
        inorder(root->right);
    }
}

void preorder(struct TreeNode *root) {
    if (root != NULL) {
        printf("%d ", root->key);
        preorder(root->left);
        preorder(root->right);
    }
}

void postorder(struct TreeNode *root) {
    if (root != NULL) {
        postorder(root->left);
        postorder(root->right);
        printf("%d ", root->key);
    }
}

void search(struct TreeNode *root, int key) {
    if (root == NULL) {
        printf("%d NO EXISTE EN EL ABB\n", key);
        return;
    }

    if (key == root->key) {
        displayMiddle(root);
    } else {
        if (key < root->key) {
            search(root->left, key);
        } else {
            search(root->right, key);
        }
    }
}

int validateBST(struct TreeNode *root) {
    if (root != NULL) {
        struct TreeNode *leftChild = root->left;
        struct TreeNode *rightChild = root->right;

        if (leftChild != NULL) {
            if (leftChild->key == root->key) {
                printf("ESTE NO ES UN ARBOL BINARIO DE BUSQUEDA VALIDO\n");
                return 0;
            }
        }

        if (rightChild != NULL) {
            if (rightChild->key == root->key) {
                printf("ESTE NO ES UN ARBOL BINARIO DE BUSQUEDA VALIDO\n");
                return 0;
            }
        }

        if (validateBST(root->left) == 0) {
            return 0;
        }

        if (validateBST(root->right) == 0) {
            return 0;
        }
    }

    return 1;
}

int main() {
    struct TreeNode *root = newNode(8);

    //--INSERTAR--
    root = insert(root, 10);
    root = insert(root, 8);
    root = insert(root, 7);
    root = insert(root, 6);
    root = insert(root, 12);
    root = insert(root, 13);
    root = insert(root, 14);
    root = insert(root, 16);

    int flag = validateBST(root);

    if (flag == 1) {
        printf("ESTE ES UN ARBOL BINARIO DE BUSQUEDA VALIDO\n");
        printf("--LISTAR--\n");
        display(root);

        printf("--INORDEN--\n");
        inorder(root);

        printf("\n--PREORDEN--\n");
        preorder(root);

        printf("\n--POSORDEN--\n");
        postorder(root);

        printf("\n--ENCONTRAR--\n");
        search(root, 8);
        search(root, 11);
        search(root, 15);

        printf("--LISTAR DESPUES DE BORRAR--\n");
        root = deleteNode(root, 7);
        display(root);
    }

    // Liberar memoria
    deleteTree(root);

    return 0;
}
#include <stdio.h>
#include <stdlib.h>

struct tree_node {
    int value;
    struct tree_node* left;
    struct tree_node* right;
};

int main(void)
{
    struct tree_node node1 = { 5, NULL, NULL };
    struct tree_node node2 = { 16, NULL, NULL };
    struct tree_node node3 = { 10, &node1, &node2 };
    struct tree_node* ptr = node3.left;

    // TODO: access member value of node1 via node1
    printf("node1:%d", node1.value);

    // TODO: access member value of node1 via node3
    printf("node1 via node3:", ptr->value);

    printf("node1 via node3:", node3.left -> value);


        // TODO: access member value of node1 via ptr
        // TODO: alternative syntax?

        return EXIT_SUCCESS;
}
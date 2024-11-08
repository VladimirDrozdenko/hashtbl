#include <memory.h>
#include <stdio.h>
#include <stdlib.h>

#include "map.h"


str2str_node* init_map(const char* pk, const char* pval) {
	str2str_node* root = (str2str_node*)malloc(sizeof(str2str_node));
	root->key = pk;
	root->value = pval;
	return root;
}

void clear_map(str2str_node* proot) {
	if (proot) {
		clear_map(proot->left);
		clear_map(proot->right);
		free(proot);
		proot = 0;
	}
}

void print_map_internal(const str2str_node* proot, int padding) {
	char pad[255];
	for (int i = 0; i < padding; ++i) {
		pad[i] = ' ';
	}
	pad[padding] = 0;

	if (!proot) {
		printf("%s-\n", pad);
		return;
	}

	printf("%s%s (%s)\n", pad, proot->key, proot->value);

	print_map_internal(proot->left, padding+2);
	print_map_internal(proot->right, padding+2);
}

void print_map(const str2str_node* proot) {
	print_map_internal(proot, 0);
}

int add_node(str2str_node** proot, const char* pk, const char* pval) {
	if (!proot) {
		return 0;
	}

	if (!*proot) {
		(*proot) = (str2str_node*)malloc(sizeof(str2str_node));
		(*proot)->key = pk;
		(*proot)->value = pval;
		return 1;
	}

	int cmp = strcmp((*proot)->key, pk);
	if (cmp == 0) {
		return 0; // node with the pk key exists, there is nothing to do
	}
	
	if (cmp > 0) {
		return add_node(&(*proot)->left, pk, pval);
	}

	return add_node(&(*proot)->right, pk, pval);
}

const char* get_map_value(const str2str_node* proot, const char* pk) {
	if (proot) {
		int cmp = strcmp(proot->key, pk);
		if (cmp == 0) {
			return proot->value;
		}
		
		if (cmp > 0) {
			return get_map_value(proot->left, pk);
		}

		return get_map_value(proot->right, pk);
	}

	return 0;
}

// int get_height(const str2str_node* proot) {
// 	if (proot) {
// 		return max(get_height(proot->left), get_height(proot->right)) + 1;
// 	}
// 	return 0;
// }
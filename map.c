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

int __max(int a, int b) {
    return (a > b) ? a : b;
}

int get_height(const str2str_node* proot) {
	if (proot) {
		return __max(get_height(proot->left), get_height(proot->right)) + 1;
	}
	return 0;
}

str2str_node* find_min(str2str_node* proot) {
	if (!proot) {
		return 0;
	}

	if (proot->left) {
		return find_min(proot->left);
	}

	return proot;
}

str2str_node* find_max(str2str_node* proot) {
	if (!proot) {
		return 0;
	}

	if (proot->right) {
		return find_max(proot->right);
	}

	return proot;
}


str2str_node* rotate_left(str2str_node* proot) {
	str2str_node* pr = proot->right;
	if (!pr) {
		return proot; // no rotation
	}

	str2str_node* ptmp = find_min(proot->right);
	if (ptmp == pr) {
		ptmp = 0;
	}

	pr->left = proot;
	proot->right = ptmp;
	proot = pr;
	
	return proot;
}

str2str_node* rotate_right(str2str_node* proot) {
	str2str_node* pl = proot->left;
	if (!pl) {
		return proot; // no rotation
	}

	str2str_node* ptmp = find_max(proot->left);
	if (ptmp == pl) {
		ptmp = 0;
	}

	pl->left = proot;
	proot->left = ptmp;
	proot = pl;
	
	return proot;
}

str2str_node* rebalance(str2str_node* proot) {
	if (!proot) {
		return 0;
	}

	int lh = get_height(proot->left);
	int rh = get_height(proot->right);

	do {
		if (abs(lh-rh) < 2) {
			return proot;
		}

		if (lh < rh) {
			proot = rotate_left(proot);
		} else {
			proot = rotate_right(proot);
		}

		lh = get_height(proot->left);
		rh = get_height(proot->right);
	} while (abs(lh-rh) > 2);

	proot->left = rebalance(proot->left);
	proot->right = rebalance(proot->right);

	return proot;
}

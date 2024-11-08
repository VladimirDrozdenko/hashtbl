#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "map.h"


int main() {
	str2str_node* root = init_map("key3", "value3");

	assert(add_node(&root, "key1", "value1"));
	assert(add_node(&root, "key2", "value2"));

	// the mapping for key1 already exist, the add_node must return false
	assert(!add_node(&root, "key1", "this value will not be stored"));
	
	assert(add_node(&root, "key6", "value6"));
	assert(add_node(&root, "key4", "value4"));

	assert(add_node(&root, "key5", "value5"));

	//assert(get_height(root) == 4);

	print_map(root);

	const char* pval = get_map_value(root, "key1");
	assert(pval && 0==strcmp(pval, "value1"));

	pval = get_map_value(root, "key2");
	assert(pval && 0==strcmp(pval, "value2"));

	pval = get_map_value(root, "key3");
	assert(pval && 0==strcmp(pval, "value3"));

	pval = get_map_value(root, "key6");
	assert(pval && 0==strcmp(pval, "value6"));

	pval = get_map_value(root, "key4");
	assert(pval && 0==strcmp(pval, "value4"));

	pval = get_map_value(root, "key_non_existent");
	assert(!pval);

	clear_map(root);
}
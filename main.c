#include <assert.h>
#include <stdio.h>
#include <string.h>
#include "map.h"


void test_generic() {
	printf("\n---TEST GENERIC---\n");
	str2str_node* root = init_map("key3", "value3");

	assert(add_node(&root, "key1", "value1"));
	assert(add_node(&root, "key2", "value2"));

	// the mapping for key1 already exist, the add_node must return false
	assert(!add_node(&root, "key1", "this value will not be stored"));
	
	assert(add_node(&root, "key6", "value6"));
	assert(add_node(&root, "key4", "value4"));

	assert(add_node(&root, "key5", "value5"));

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

void test_rebalance() {
	printf("\n---TEST REBALANCE---\n");
	str2str_node* root = init_map("key1", "value1");

	add_node(&root, "key2", "value2");
	add_node(&root, "key3", "value3");
	add_node(&root, "key4", "value4");
	add_node(&root, "key5", "value5");
	add_node(&root, "key6", "value6");
	add_node(&root, "key7", "value7");

	print_map(root);

	printf("\nREBALANCING\n");

	root = rebalance(root);

	print_map(root);

	clear_map(root);
}

int main() {
	test_generic();

	test_rebalance();

}
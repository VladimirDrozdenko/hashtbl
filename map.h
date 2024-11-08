#ifndef __MAP_H__
#define __MAP_H__

typedef struct __str2str_node {
	const char* key;
	const char* value;

	struct __str2str_node* left, *right;
} str2str_node;

extern str2str_node* init_map(const char* pk, const char* pval);
extern void clear_map(str2str_node* proot);
extern void print_map(const str2str_node* proot);
extern int add_node(str2str_node** proot, const char* pk, const char* pval);
extern const char* get_map_value(const str2str_node* proot, const char* pk);


#endif //__MAP_H__

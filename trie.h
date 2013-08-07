#ifndef ___TRIE__H__
#define ___TRIE__H__

#include <string.h>
#include <stdlib.h>

#define NOT_EXIST 0x7FFFFFFF

typedef struct tag_trie_node
{
	char value;
	int times;
	struct tag_trie_node *next;			// 下一个兄弟节点
	struct tag_trie_node *children;		// 子节点
}trie_node;

typedef trie_node trie;

// functions
extern trie* create_trie_node(void);
extern void destroy_trie(trie*);
extern int trie_add_record(trie*, const char*, int);
extern int is_trie_member(trie*, const char*);
extern int remove_trie_member(trie*, const char*);


#endif
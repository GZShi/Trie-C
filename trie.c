#include "trie.h"


trie_node* create_trie_node(void)
{
	trie* node = (trie*)malloc(sizeof(trie));
	node->value = '\0';
	node->times = 0;
	node->next = NULL;
	node->children = NULL;
	return node;
}

void destroy_trie(trie* root)
{
	trie* p = NULL;
	trie* t = NULL;
	if(root == NULL)
		return;

	p = root->next;

	// 横向遍历释放兄弟节点
	while(p)
	{
		t = p->next;
		destroy_trie(p);	
		p = t;
	}

	// 垂直遍历释放子孙节点
	t = root->children;
	free(root);
	destroy_trie(t);
}

int trie_add_record(trie* root, const char* str, int times)
{
	trie *p = root->children;

	while(p)
	{
		if(p->value == str[0])
		{
			if(str[0] != '\0')
				return trie_add_record(p, str + 1, times);
			p->times += times;
			return p->times;
		} 
		else if(p->next == NULL)
		{
			if(!(p->next = create_trie_node()))
			{
				return ADD_FAILED;
			}
			p = p->next;
			p->value = str[0];
			if(str[0] != '\0')
				return trie_add_record(p, str + 1, times);
			p->times += times;
			return p->times;
		}
		p = p->next;
	}

	if(!(root->children = create_trie_node()))
	{
		return ADD_FAILED;
	}
	root->children->value = str[0];
	if(str[0] != '\0')
		return trie_add_record(root->children, str + 1, times);
	root->children->times += times;
	return root->children->times;
}

int is_trie_member(trie* root, const char* str)
{
	trie *p = root->children;

	while(p)
	{
		if(p->value == str[0])
		{
			if(str[0] != '\0')
				return is_trie_member(p, str + 1);
			return p->times;
		}
		p = p->next;
	}

	return NOT_EXIST;
}

// 递归删除
int remove(trie* root, const char* str)
{
	trie* p = root->children;
	trie* f = p;
	int retval = NOT_EXIST;

	while(p)
	{
		if(p->value == str[0])
		{
			if(str[0] == '\0')
			{
				retval = p->times;
				return retval;
			}
			retval = remove(p, str + 1);
			
			if(retval != NOT_EXIST)
			{
				if(p->children->value == str[1])	// 第一个子节点就匹配
				{
					f = p->children;
					if(f->children == NULL)
					{
						p->children = p->children->next;
						free(f);
					}
					// return retval;
				}
				else
				{
					f = p = p->children;
					while(p)
					{
						if(p->value == str[1])
						{
							if(p->children == NULL)
							{
								f->next = p->next;
								free(p);
							}
							return retval;
						}
						f = p;
						p = p->next;
					}
				}
			}
			return retval;
		}
		f = p;
		p = p->next;
	}
	return retval;
}

// 清除root的一个记录
int remove_trie_member(trie* root, const char* str)
{
	int retval = remove(root, str);
	if(retval != NOT_EXIST)
	{
		trie* p = root->children;
		trie* f = p;
		if(p->value == str[0] && p->children == NULL)
		{
			root->children = p->next;
			free(p);
			return retval;
		}
		while(p)
		{
			if(p->value == str[0] && p->children == NULL)
			{
				f->next = p->next;
				free(p);
				return retval;
			}
			f = p;
			p = p->next;
		}
	}
}
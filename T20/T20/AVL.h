#ifndef  AVL_H
#define AVL_H
#include<stack>

typedef struct AVLNode
{
	int key;
	int bf;
	AVLNode *left, *right;
}AVLNode, *AVLTree;

void RotateLL(AVLNode *&parent)
{
	AVLNode *subR = parent;
	parent = subR->left;
	subR->left = parent->right;
	parent->right = subR;
	parent->bf = subR->bf = 0;
}

void RotateRR(AVLNode *&parent)
{
	AVLNode *subL = parent;
	parent = subL->right;
	subL->right = parent->left;
	parent->left = subL;
	parent->bf = subL->bf = 0;
}

void RotateLR(AVLNode *&parent)
{
	AVLNode *subR = parent, *subL = subR->left;
	parent = subL->right;
	subL->right = parent->left;
	parent->left = subL;
	subR->left = parent->right;
	parent->right = subR;
	if (parent->bf == 1)
		subL->bf = 0, subR->bf = -1;
	else if (parent->bf == -1)
		subL->bf = 1, subR->bf = 0;
	else
		subL->bf = subR->bf = 0;
	parent->bf = 0;
}

void RotateRL(AVLNode *&parent)
{
	AVLNode *subL = parent, *subR = subL->right;
	parent = subR->left;
	subR->left = parent->right;
	parent->right = subR;
	subL->right = parent->left;
	parent->left = subL;
	if (parent->bf == 1)
		subL->bf = 0, subR->bf = -1;
	else if (parent->bf == -1)
		subL->bf = 1, subR->bf = 0;
	else
		subL->bf = subR->bf = 0;
	parent->bf = 0;
}

bool Insert(AVLTree &ptr, int &key)
{
	if (ptr == NULL)
	{
		ptr = (AVLNode *)malloc(sizeof(AVLNode));
		ptr->key = key;
		ptr->bf = 0;
		ptr->left = ptr->right = NULL;
		return true;
	}
	AVLNode *pr = NULL, *p = ptr, *q;
	std::stack<AVLNode *> S;
	while (p != NULL)
	{
		if (key == p->key)
			return false;
		S.push(p);
		p = (key < p->key) ? p->left : p->right;
	}

	p = (AVLNode *)malloc(sizeof(AVLNode));
	p->key = key; p->bf = 0;
	p->left = p->right = NULL;
	if (!S.size())
		ptr = p;
	else if (key < S.top()->key)
		S.top()->left = p;
	else
		S.top()->right = p;
	while (!S.empty())
	{
		pr = S.top(); S.pop();
		if (p == pr->left)
			++pr->bf;
		else
			--pr->bf;
		if (!pr->bf)
			break;
		if (pr->bf == 1 || pr->bf == -1)
			p = pr;
		else
		{
			int d = (pr->bf < 0) ? -1 : 1;
			if (p->bf == d)
				if (d == 1)
					RotateLL(pr);
				else
					RotateRR(pr);
			else
				if (d == 1)
					RotateLR(pr);
				else
					RotateRL(pr);
			break;
		}
	}
	if (S.empty())
		ptr = pr;
	else //重新链接
	{
		q = S.top();
		if (q->key > pr->key)
			q->left = pr;
		else
			q->right = pr;
	}
	return true;
}

bool Remove(AVLTree &ptr, int &key)
{
	AVLNode *pr = NULL, *p = ptr, *q, *gr = NULL;
	std::stack<AVLNode *> S;
	int d, dd = 0;
	while (p != NULL)
	{
		if (key == p->key)
			break;
		pr = p;
		S.push(pr);
		p = (key < p->key) ? p->left : p->right;
	}
	if (p == NULL)
		return false;
	if (p->left != NULL && p->right != NULL)
	{
		pr = p;
		S.push(pr);
		q = p->left;
		while (q->right != NULL)
		{
			pr = q;
			S.push(pr);
			q = q->right;
		}
		p->key = q->key;
		p = q;
	}
	if (p->left != NULL)
		q = p->left;
	else
		q = p->right;
	if (pr == NULL) //网络上的代码大部分在这个地方有问题好像
	{
		ptr = q;
		return true;
	}
	else
		if (pr->left == p)
			pr->left = q;
		else
			pr->right = q;
	while (!S.empty())
	{
		pr = S.top();
		S.pop();
		if (pr->left == q)
			--pr->bf;
		else
			++pr->bf;
		if (pr->left == NULL && pr->right == NULL)
			pr->bf = 0;
		if (!S.empty())
			gr = S.top(),
			dd = (gr->left == pr) ? 1 : -1;
		else
			dd = 0;
		if (pr->bf == 1 || pr->bf == -1)
			break;
		if (pr->bf != 0)
		{
			if (pr->bf == 2)
			{
				d = 1;
				q = pr->left;
			}
			else
			{
				d = -1;
				q = pr->right;
			}
			if (q->bf == 0)
			{
				if (d == 1)
				{
					RotateLL(pr);
					pr->bf = -1;
					pr->right->bf = 1;
				}
				else
				{
					RotateRR(pr);
					pr->bf = 1;
					pr->left->bf = -1;
				}
				break;
			}
			if (q->bf == d)
			{
				if (d == 1)
					RotateLL(pr);
				else
					RotateRR(pr);
			}
			else
			{
				if (d == 1)
					RotateLR(pr);
				else
					RotateRL(pr);
			}
			if (dd == 1)
				gr->left = pr;
			else if (dd == -1)
				gr->right = pr;
		}
		q = pr;
	}
	if (S.empty())
		ptr = pr;
	free(p);
	return true;
}

bool Find(AVLTree ptr, int &key)
{
	if (!ptr)
		return false;
	AVLNode *p = ptr;
	while (p != NULL)
	{
		if (p->key == key)
			return true;
		p = (key < p->key) ? p->left : p->right;
	}
	return false;
}

void DFS(AVLTree ptr)
{
	if (ptr == NULL)
		return;
	DFS(ptr->left);
	printf("%d ", ptr->key);
	DFS(ptr->right);
}
#endif // ! AVL_H

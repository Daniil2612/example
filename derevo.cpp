#include <iostream>
#include <queue>
 
struct TreeNode {
    int value;
    TreeNode *right;
    TreeNode *left;
};
 
TreeNode *Push(TreeNode *tree, int val) {
    if (!tree) {
        return new TreeNode{val, NULL, NULL};
    }
    if (val < tree->value) {
        tree->left = Push(tree->left, val);
    } else {
        tree->right = Push(tree->right, val);
    }
    return tree;
}
 
 void printTree(TreeNode *root) {
		std::queue<TreeNode *> queue;
    queue.push(root);
    while (!queue.empty()) {
        TreeNode *node = queue.front();
        queue.pop();
        if (node) {
            std::cout << node->value << std::endl;
            queue.push(node->left);
            queue.push(node->right);
        } else {
            std::cout << "nullptr" << std::endl;
        }
    }
    
}

void Delltree(TreeNode *tree) {
    TreeNode  *Now=tree, *Right=NULL, *Left=NULL ;
    Right=Now->right;
    Left=Now->left;
    if( Right!=NULL ) {
        Delltree(Right);
    }
    if( Left!=NULL ) {
        Delltree(Left);
    }
    delete Now;
}

TreeNode* Process(TreeNode* tree, int key) {
    TreeNode  *dang=tree, *buf, *buf1, *buf2,* curr, *last;
    if(tree->value==key) {
        if(tree->right==NULL  && tree->left!=NULL) {
        	buf=dang;
        	dang=dang->left;
            buf->left=NULL;
			delete buf;
          	tree=dang;
            printTree(dang);
        } 
        else {
            if(tree->right!=NULL  && tree->left==NULL) {
            	buf=dang;
            	dang=dang->right;
            	buf->right=NULL;
            	delete buf;
          		tree=dang;
            } 
            else { 
                if(tree->right==NULL  && tree->left==NULL ) {
                    delete dang;
                    dang=NULL;            
                }
                else {
                    dang=tree;
                    buf1=tree->left;
                    buf2=tree->right;
                    curr=tree->right;
                    last=tree;
                    if(curr->left==NULL) {
                    	curr->left=buf1;
                    	dang->left=NULL;
                    	dang->right=NULL;
                    	delete dang;
                    	dang=curr;
                    }
                    else {
                    	while(curr->left!=NULL) {
                    	    last=curr;
                    	    curr=curr->left;
                    	}
                    	last->left=NULL;
                    	curr->left=buf1;
                    	curr->right=buf2;
                    	dang->left=NULL;
                    	dang->right=NULL;
                    	delete dang;
                    	dang=curr;
                    }
                }
            }
        }
		}
	  tree=dang;
    if(tree->right!=NULL) {
	    dang->right=Process(dang->right, key);
	}
	if(dang->left) {
	    dang->left=Process(dang->left, key);
	}
	return dang;
}

int main() {
    TreeNode *tree = NULL;
    int k, value, i, key;
    std::cout << "Введите количество элементов дерева: ";
    std::cin >> k;
    for ( i = 0; i < k; i++) {
        std::cin >> value;
        tree = Push(tree, value);
    }
    std::cout << "Введите значение key ";
    std::cin>>key;
    std::cout<<"дерево до функции process:  ";
    printTree(tree);
    tree=Process(tree, key);
    if(tree!=NULL) {
      std::cout<<"\n";
      std::cout<<"дерево после функции process: ";
      printTree(tree);
   		Delltree(tree);
    }
    return 1;
}



typedef struct BNode* BNode;

struct BNode{
	BNode left;
	BNode right;
	int data;
};

bool AreDuplicatesPresentInBST(BNode root) {
	
	static int n=0;
	static int prev = 0;
	
	if (!root) return false;
	
	if (AreDuplicatesPresentInBST(root->left)) return true;
	
	if ((n>0) && (root->value == prev)) return true;
	
	n++;
	prev = root->value;
	
	return AreDuplicatesPresentInBST(root->right);
}
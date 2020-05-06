
#include<iostream>
#include<string>
#include<queue>
using namespace std;
class node {
public:
	int info;
	node *left;
	node *right;
	int height;
	
	node() {
		left = nullptr;
		right = nullptr;
		info = 0;
		height = 0;
	}
	node(int key) {
		left = nullptr;
		right = nullptr;
		info = key;
		height = 0;
	}
	
};

class AVLTree {
private:
	node *root;
public:
	AVLTree() {
		root = 0;
	}
	bool isEmpty() {
		return (root == 0);
	}
	int max(int x, int y) {
		if (x > y) return x;
		return y;
	}
	int getHeight() {
		return height(root)-1;
	}
	int height(node* root) {
		if (root == 0) return 0;
		if (root->left == 0 && root->right == 0) return 1;
		else return 1 + max(height(root->left),height(root->right));
	}
	node * rightRotation(node *A) {
		node *B = A->left;
		A->left = B->right;
		B->right = A;
		B->height = height(B);
		A->height = height(A);
		return B;
	}
	node *leftRotation(node *A) {
		node *B = A->right;
		A->right = B->left;
		B->left = A;
		B->height = height(B);
		A->height = height(A);
		return B;
	 }
	node* LL(node *root) {
		cout << "LL - right rotation at " << root->info << endl;
		return rightRotation(root);
	}
	node* RR(node *root) {
		cout << "RR - left rotation at "<<root->info << endl;
		return leftRotation(root);
	}
	node *RL(node *root) {
		cout << "RL - right rotation at child " << root->right->info;
		root->right=rightRotation(root->right);
		cout << "- left rotation at parent " << root->info << endl;
		return leftRotation(root);
	}
	node *LR(node *root) {
		cout << "LR - right rotation at child " << root->left->info;
		root->left=leftRotation(root->left);
		cout << "- left rotation at parent " << root->info << endl;
		return rightRotation(root);
	}
	int balanceFactor(node *root) {
		if (root == 0) return 0;
		return (height(root->left) - height(root->right));
	}
	void insert(int key) {
		root=insert(root, key);
	}
	node * balance(node*root) {
		if (balanceFactor(root) == 2) {
			if (balanceFactor(root->left) == 1)
				root=LL(root);
			else
				root=LR(root);
		}
		else if (balanceFactor(root) == -2) {
			if (balanceFactor(root->right) == -1)
				root= RR(root);
			else
				root=RL(root);

		}
		return root;
	}

	node*insert(node* root, int key) {
		if (root == 0) {
			root = new node(key);
		}
		else if (key > root->info) {
			root->right = insert(root->right, key);
			root = balance(root);
		}
		else {
			root->left = insert(root->left, key);
			root = balance(root);
		}
		return root;
	}
	void deletion(int dval) {
		root= deletion(root, dval);
	}
	//Function to delete an element from AVL tree
	node* deletion(node* root, int dval) {//dval=delete value
		node *temp;
		if (root != nullptr) {
			if (dval < root->info) {
				root->left = deletion(root->left, dval);
				if (balanceFactor(root) == -2) {
					if (balanceFactor(root->right) <= 0) {
						//cout << "\n RR rotation \n";
						root = RR(root);//left rotation at parent
					}
					else {
						//cout << "\n RL rotation \n";//right rotation at child, left rotation at parent
						root = RL(root);
					}
				}
			}
			else if (dval > root->info) {
				root->right = deletion(root->right, dval);
				//check balance at root
				if (balanceFactor(root) == 2) {
					if (balanceFactor(root->left) >= 0) {
						//cout << "\n LL rotation \n";
						root = LL(root);
					}
					else {
						//cout << "\n LR rotation \n";
						root = LR(root);
					}
				}
			}
			else {
				if (root->right == nullptr) {// no right tree
					return(root->left);
				}
				else {
					//find the leftmost of right
					temp = root->right;
					while (temp->left != nullptr)
						temp = temp->left;
					cout << "left most node =" << temp->info << endl;
					cout << "copy leftmost->data to root->data" << endl;
					root->info = temp->info;//copy the value of the leftmost of right to the root node
					printOrderLevel(root);
					cout << "delete leftmost node" << endl;
					root->right = deletion(root->right, temp->info);//delete the leftmost node
					if (balanceFactor(root) == 2) {
						cout << "rebalance" << endl;
						if (balanceFactor(root->left) >= 0) 
							root = LL(root);
						else 
							root = LR(root);
					}
				}
			}
		}
		else
			return nullptr;//root=nullptr
			//update height of root node
		root->height = height(root);
		return root;
	}

	void printInOrder() {
		printInOrder(root);
		cout << endl;
	}
	void printInOrder(node* root) {
		if (root == 0)return;
		else {
			printInOrder(root->left);
			cout << root->info << " ";
			printInOrder(root->right);
		}
		
	}
	void printOrderLevel() {
		printOrderLevel(root);
	}
	void printOrderLevel(node *root) {
		if (root == 0) return;
		int h = height(root);
		for (int i = 0;i < h;i++) {
			printALevel(root, i);
			cout << endl;
		}

	}
	void printALevel(int L) {
		printALevel(root, L);
	}
			void printALevel(node *root, int L) {
				if (root == 0) return;
				if (L == 0) cout << root->info  << " ";
				else {
					printALevel(root->left, L - 1);
					printALevel(root->right, L - 1);
				}
			}

};

int main() {
	
	int a[10] = { 8,1,2,6,5,3,4,7,10,9};//change this
	AVLTree tree;
	for (int i = 0; i < 10; i++) {//change size
		cout << "\ninsert " << a[i] << endl;
		tree.insert(a[i]);
		tree.printOrderLevel();
		cout << endl;
	}
	//tree.printInOrder();
	//tree.printALevel(0);
	//tree.printOrderLevel();
	int dval[] = { 1,8,2,5 };//change this
	for (int i = 0; i < 4; i++) {//change size
		cout << "\ndelete " << dval[i] << endl;
		tree.deletion(dval[i]);
		tree.printOrderLevel();
		cout << endl;
	}
	system("PAUSE");
	return 0;
}

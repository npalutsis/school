template <typename T>
T minimum_tree(Node<T> *root) {
	T minimum = root->data;

	if (root->left)
		minimum = min(minimum, minimum_tree(root->left));

	if (root->right)
		minimum = min(minimum, minimum_tree(root->right));

	return minimum;
}
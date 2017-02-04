template <typename T>
size_t height_tree(Node<T> *root) {
	if (root == nullptr) {
		return 0;
	}

	size_t left = height_tree(root->left);
	size_t right = height_tree(root->right);

	return max(left, right) + 1;
}
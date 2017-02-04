template <typename T> 
Node<T> * reverse_node(Node<t> *curr, Node<T> *prev) {
	Node<T> *head = curr;

	if (curr->next != nullptr) {
		reverse_node(curr->next, curr);
	}
	curr->next = prev;

	return head;
}

template <typename T> 
Node<T> * reverse_list(Node<t> *head) {
	return reverse_node(head, static_cast<Node<T> *>(nullptr));
}

template <typename T>
Node<T> * reverse_list_iter(Node<T> *head) {
	Node<T> *next, *prev = nullptr;

	for (auto curr = head; curr != nullptr; curr = next) {
		curr->next = prev;
		next = curr->next;
		prev = curr;
	}

	return prev;
}
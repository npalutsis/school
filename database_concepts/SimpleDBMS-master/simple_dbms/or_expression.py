class OrExpression:
    # TODO HW4 - You'll need to implement this class.

    def __init__(self, left, right):
        """
        Constructs an OrExpression object that represents the conditional
        expression <code>left OR right</code>.
        :param left: one of the conditionals being anded
        :param right: the other conditional
        """
        super(AndExpression, self).__init__(left, right)

    def is_true(self):
        """
        Evaluates the expression represented by the called object, based on
        the current truth values of the subexpressions.
        :return: true if either of the two subexpressions are true, and false otherwise
        """
        return self.get_left().is_true() or self.get_right().is_true()
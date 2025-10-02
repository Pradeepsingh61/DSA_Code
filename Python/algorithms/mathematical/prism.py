"""
Data Structure: PRISM Rule-Based Classifier

Description:
    PRISM is a rule-based machine learning algorithm used for classification. 
    It generates simple if-then rules for each class by analyzing attribute-value pairs.

Use Case:
    Useful in applications requiring interpretable classification rules,
    such as medical diagnosis, decision support systems, or expert systems.

Time Complexity:
    O(N * M * V), where
    - N = number of instances
    - M = number of attributes
    - V = average number of attribute values

Space Complexity:
    O(R), where R = number of generated rules.
"""

from collections import Counter

class PRISM:
    def __init__(self, data, attributes, class_label):
        """
        Initialize the PRISM classifier.
        
        Args:
            data (list of dict): Dataset as list of instances (dict of attribute: value).
            attributes (list): List of attribute names.
            class_label (str): Name of the class attribute.
        """
        self.data = data
        self.attributes = attributes
        self.class_label = class_label
        self.rules = []

    def train(self):
        """Generate rules for each class."""
        classes = set([d[self.class_label] for d in self.data])
        for cls in classes:
            examples = [d for d in self.data if d[self.class_label] == cls]
            while examples:
                rule = self._generate_rule(examples, cls)
                self.rules.append(rule)
                # Remove examples covered by this rule
                examples = [ex for ex in examples if not self._matches_rule(ex, rule)]

    def _generate_rule(self, examples, cls):
        """Generate a single rule for a class."""
        rule = {}
        remaining_attrs = self.attributes.copy()
        while True:
            best_attr, best_value, best_accuracy = None, None, 0
            for attr in remaining_attrs:
                values = set([ex[attr] for ex in examples])
                for val in values:
                    covered = [ex for ex in examples if ex[attr] == val]
                    accuracy = sum(1 for ex in covered if ex[self.class_label] == cls) / len(covered)
                    if accuracy > best_accuracy:
                        best_attr, best_value, best_accuracy = attr, val, accuracy
            if best_attr is None:
                break
            rule[best_attr] = best_value
            remaining_attrs.remove(best_attr)
            # Filter examples covered by this condition
            examples = [ex for ex in examples if ex[best_attr] == best_value]
            if all(ex[self.class_label] == cls for ex in examples):
                break
        rule['class'] = cls
        return rule

    def _matches_rule(self, instance, rule):
        """Check if an instance matches a rule."""
        for attr, val in rule.items():
            if attr == 'class':
                continue
            if instance[attr] != val:
                return False
        return True

    def predict(self, instance):
        """Predict class label for a single instance."""
        for rule in self.rules:
            if self._matches_rule(instance, rule):
                return rule['class']
        return None


def main():
    """Test PRISM implementation."""
    data = [
        {'Outlook':'Sunny', 'Temp':'Hot', 'Humidity':'High', 'Wind':'Weak', 'PlayTennis':'No'},
        {'Outlook':'Sunny', 'Temp':'Hot', 'Humidity':'High', 'Wind':'Strong', 'PlayTennis':'No'},
        {'Outlook':'Overcast', 'Temp':'Hot', 'Humidity':'High', 'Wind':'Weak', 'PlayTennis':'Yes'},
        {'Outlook':'Rain', 'Temp':'Mild', 'Humidity':'High', 'Wind':'Weak', 'PlayTennis':'Yes'}
    ]
    attributes = ['Outlook', 'Temp', 'Humidity', 'Wind']
    prism = PRISM(data, attributes, 'PlayTennis')
    prism.train()
    print("Generated Rules:", prism.rules)
    test_instance = {'Outlook':'Rain', 'Temp':'Mild', 'Humidity':'High', 'Wind':'Weak'}
    print("Prediction:", prism.predict(test_instance))


if __name__ == "__main__":
    main()

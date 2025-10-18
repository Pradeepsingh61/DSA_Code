def prism(data, target):
    rules = []
    classes = set(row[target] for row in data)

    for cls in classes:
        cls_data = [row for row in data if row[target] == cls]
        uncovered = cls_data.copy()

        while uncovered:
            rule = {}
            remaining_features = list(data[0].keys())
            remaining_features.remove(target)

            while True:
                best_feature, best_value, best_coverage = None, None, 0

                for feature in remaining_features:
                    values = set(row[feature] for row in uncovered)
                    for value in values:
                        coverage = [row for row in uncovered if row[feature] == value]
                        if len(coverage) > best_coverage:
                            best_coverage = len(coverage)
                            best_feature = feature
                            best_value = value

                if best_feature is None:
                    break

                rule[best_feature] = best_value
                uncovered = [row for row in uncovered if row[best_feature] == best_value]

                if all(row[target] == cls for row in uncovered):
                    rules.append((rule.copy(), cls))
                    uncovered = [row for row in cls_data if not rule_matches(rule, row)]
                    break

                remaining_features.remove(best_feature)

    return rules

def rule_matches(rule, row):
    for feature, value in rule.items():
        if row[feature] != value:
            return False
    return True

if __name__ == "__main__":
    n = int(input("Enter number of rows: "))
    features = input("Enter feature names separated by space (last one is target): ").split()
    data = []

    for _ in range(n):
        values = input(f"Enter values for {features} separated by space: ").split()
        row = {features[i]: values[i] for i in range(len(features))}
        data.append(row)

    target = features[-1]
    rules = prism(data, target)

    print("\nGenerated Rules:")
    for r, cls in rules:
        print(f"If {r} then {target} = {cls}")

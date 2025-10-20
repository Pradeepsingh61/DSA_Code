"""
K-Nearest Neighbors (KNN) - Simple Implementation from Scratch
-------------------------------------------------------------
This script implements a basic version of the KNN algorithm for classification
using only Python and NumPy (no sklearn).

Concept Summary:
----------------
1. KNN is a supervised learning algorithm used for classification & regression.
2. It finds the K nearest data points to a test point using a distance metric
   (usually Euclidean distance).
3. For classification → predicts the majority label among neighbors.
4. For regression → predicts the average value among neighbors.
5. It is a **lazy learner** (no explicit training phase, prediction happens at query time).

Steps in this code:
-------------------
1. Compute Euclidean distance between the test point and all training points.
2. Sort training points by their distance to the test point.
3. Select top 'k' nearest points.
4. Use majority voting to determine the predicted class.
5. Return the predicted label.

Contributor:
---------------------
💻 Contributed by: **Lakhinana Chaturvedi Kashyap**
"""

import numpy as np
import matplotlib.pyplot as plt  # ✅ Correct import
from collections import Counter

# Function: Euclidean Distance

def euclidean_distance(p1, p2):
    """
    Calculates the Euclidean distance between two points.

    Formula:
    √( (x2 - x1)² + (y2 - y1)² + ... )
    """
    return np.sqrt(np.sum((np.array(p1) - np.array(p2)) ** 2))


# Function: KNN Prediction

def knn_prediction(training_data, training_labels, test_point, k):
    """
    Predicts the class of a test point using the K-Nearest Neighbors algorithm.
    Returns both the predicted label and the k nearest points (for visualization).
    """
    distances = []
    for i in range(len(training_data)):
        dist = euclidean_distance(test_point, training_data[i])
        distances.append((dist, training_labels[i], training_data[i]))  # include point itself

    # Sort by distance (ascending)
    distances.sort(key=lambda x: x[0])

    # Select top k neighbors
    k_neighbors = [label for _, label, _ in distances[:k]]
    nearest_points = [point for _, _, point in distances[:k]]

    # Majority voting
    prediction = Counter(k_neighbors).most_common(1)[0][0]

    return prediction, nearest_points

# Example Usage

# Convert to NumPy arrays for easy slicing
training_data = np.array([
    [1.0, 2.0],
    [2.0, 3.0],
    [3.0, 1.0],
    [6.0, 5.0],
    [7.0, 7.0],
    [8.0, 6.0]
])
training_labels = np.array([0, 0, 0, 1, 1, 1])

# Test data
test_point = np.array([5.0, 5.0])
k = 3

# Predict
prediction, nearest_points = knn_prediction(training_data, training_labels, test_point, k)

print("Predicted label:", prediction)
print("Nearest neighbors:", nearest_points)

# Visualization

plt.figure(figsize=(8, 6))

# Plot class 0 points (blue)
plt.scatter(
    training_data[training_labels == 0][:, 0],
    training_data[training_labels == 0][:, 1],
    color='blue', label='Class 0', s=100
)

# Plot class 1 points (red)
plt.scatter(
    training_data[training_labels == 1][:, 0],
    training_data[training_labels == 1][:, 1],
    color='red', label='Class 1', s=100
)

# Highlight nearest neighbors (yellow)
nearest_points = np.array(nearest_points)
plt.scatter(
    nearest_points[:, 0],
    nearest_points[:, 1],
    edgecolor='black', facecolor='yellow', s=200, label=f'{k} Nearest Neighbors'
)

# Plot test point (green star)
plt.scatter(
    test_point[0], test_point[1],
    color='green', marker='*', s=250, label='Test Point (Predicted)'
)

# Labels and title
plt.title(f"KNN Visualization (k={k}) — Predicted Label: {prediction}")
plt.xlabel("Feature 1")
plt.ylabel("Feature 2")
plt.legend()
plt.grid(True)
plt.show()

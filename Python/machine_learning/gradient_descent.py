"""
Algorithm: Linear Regression using Gradient Descent (Batch & Stochastic)

Description:
This script implements Linear Regression using both Batch Gradient Descent (BGD) 
and Stochastic Gradient Descent (SGD).

Linear Regression fits a straight line to data points (x, y) by minimizing 
the Mean Squared Error (MSE) between the predicted and actual values.

Gradient Descent iteratively adjusts parameters (b0 - intercept, b1 - slope)
in the opposite direction of the gradient of the loss function.

Mathematical Formulation:
    y_pred = b0 + b1 * x
    Loss (MSE) = (1/n) * Σ(y - y_pred)²
    Gradients:
        ∂L/∂b0 = -(2/n) * Σ(y - y_pred)
        ∂L/∂b1 = -(2/n) * Σ(x * (y - y_pred))

Variants:
- Batch Gradient Descent: Uses all samples per iteration (stable but slower)
- Stochastic Gradient Descent: Uses one random sample per iteration (faster but noisier)

Time Complexity:
    - Batch Gradient Descent: O(n * epochs)
    - Stochastic Gradient Descent: O(epochs)
Space Complexity: O(1)
"""

import numpy as np
import matplotlib.pyplot as plt


def gradient_descent(x, y, lr=0.01, epochs=10000, tolerance=1e-6, stochastic=False):
    """
    Performs linear regression using Gradient Descent.
    
    Parameters:
        x (np.ndarray): Feature values
        y (np.ndarray): Target values
        lr (float): Learning rate
        epochs (int): Maximum iterations
        tolerance (float): Convergence threshold
        stochastic (bool): If True, performs Stochastic Gradient Descent
    
    Returns:
        tuple: (b0, b1) - Intercept and Slope
    """
    b0, b1 = 0, 0
    n = len(x)

    for epoch in range(epochs):
        if stochastic:
            # Stochastic Gradient Descent (single random sample)
            i = np.random.randint(0, n)
            xi, yi = x[i], y[i]
            y_pred = b0 + b1 * xi
            b0_grad = -(yi - y_pred)
            b1_grad = -(yi - y_pred) * xi
        else:
            # Batch Gradient Descent (uses full dataset)
            y_pred = b0 + b1 * x
            b0_grad = -np.sum(y - y_pred) / n
            b1_grad = -np.sum((y - y_pred) * x) / n

        # Parameter updates
        b0_new = b0 - lr * b0_grad
        b1_new = b1 - lr * b1_grad

        # Convergence check
        if abs(b0_new - b0) < tolerance and abs(b1_new - b1) < tolerance:
            print(f"✅ Converged after {epoch} epochs")
            break

        b0, b1 = b0_new, b1_new

    return b0, b1


# Example Test Cases
if __name__ == "__main__":
    test_cases = {
        "Case 1: Simple Linear": {
            "x": np.array([0, 1, 2, 3, 4, 5, 6, 7, 8, 9]),
            "y": np.array([1, 3, 2, 5, 7, 8, 8, 9, 10, 12])
        },
        "Case 2: Perfectly Linear": {
            "x": np.arange(0, 10),
            "y": 3 * np.arange(0, 10) + 2  # y = 3x + 2
        },
        "Case 3: Negative Slope": {
            "x": np.arange(0, 10),
            "y": 20 - 2 * np.arange(0, 10)  # y = -2x + 20
        },
        "Case 4: Random Noise Added": {
            "x": np.arange(0, 10),
            "y": 5 * np.arange(0, 10) + np.random.normal(0, 3, 10)  # y = 5x + noise
        }
    }

    for name, data in test_cases.items():
        print(f"\n=== {name} ===")
        x, y = data["x"], data["y"]

        # Batch Gradient Descent
        b0_gd, b1_gd = gradient_descent(x, y, lr=0.01, epochs=10000, stochastic=False)
        y_pred_gd = b0_gd + b1_gd * x

        # Stochastic Gradient Descent
        b0_sgd, b1_sgd = gradient_descent(x, y, lr=0.01, epochs=10000, stochastic=True)
        y_pred_sgd = b0_sgd + b1_sgd * x

        # Metrics
        SST = np.sum((y - np.mean(y))**2)
        SSE_gd = np.sum((y - y_pred_gd)**2)
        SSE_sgd = np.sum((y - y_pred_sgd)**2)
        R2_gd = 1 - (SSE_gd / SST)
        R2_sgd = 1 - (SSE_sgd / SST)

        # Print results
        print(f"Batch GD: Intercept={b0_gd:.4f}, Slope={b1_gd:.4f}, R²={R2_gd:.4f}")
        print(f"SGD:      Intercept={b0_sgd:.4f}, Slope={b1_sgd:.4f}, R²={R2_sgd:.4f}")

        # Visualization
        plt.figure(figsize=(6, 4))
        plt.scatter(x, y, color="blue", label="Data Points")
        plt.plot(x, y_pred_gd, "g--", label="Batch GD")
        plt.plot(x, y_pred_sgd, "m:", label="Stochastic GD")
        plt.xlabel("x")
        plt.ylabel("y")
        plt.legend()
        plt.title(f"{name}")
        plt.show()

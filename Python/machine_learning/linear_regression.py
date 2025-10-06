"""
Algorithm: Linear Regression (Analytical / Closed-form Solution)

Description:
This script implements Linear Regression using the closed-form solution.
It calculates the best-fit line by directly computing the slope (b1) and intercept (b0)
using formulas derived from minimizing the Mean Squared Error (MSE).

Time Complexity: O(n)        # Single pass through data
Space Complexity: O(1)       # Only a few variables stored
"""

import numpy as np
import matplotlib.pyplot as plt

# --- Function for Analytical Linear Regression ---
def linear_regression_analytical(x, y):
    """
    Computes linear regression coefficients using the analytical method.
    
    Parameters:
        x (np.ndarray): Feature values
        y (np.ndarray): Target values
        
    Returns:
        tuple: b0 (intercept), b1 (slope), y_pred (predictions), SSE, R²
    """
    # Compute mean of x and y
    x_mean, y_mean = np.mean(x), np.mean(y)

    # Compute slope (b1) using formula
    b1 = np.sum((x - x_mean) * (y - y_mean)) / np.sum((x - x_mean)**2)

    # Compute intercept (b0) using formula
    b0 = y_mean - b1 * x_mean

    # Compute predicted y values
    y_pred = b0 + b1 * x

    # Compute Sum of Squared Errors (SSE)
    SSE = np.sum((y - y_pred)**2)

    # Compute Total Sum of Squares (SST) for R²
    SST = np.sum((y - y_mean)**2)

    # Compute R² score (coefficient of determination)
    R2 = 1 - (SSE / SST)

    return b0, b1, y_pred, SSE, R2


# --- Test Cases ---
test_cases = {
    "Simple Linear": {
        "x": np.array([0, 1, 2, 3, 4, 5, 6, 7, 8, 9]),
        "y": np.array([1, 3, 2, 5, 7, 8, 8, 9, 10, 12])
    },
    "Perfectly Linear": {
        "x": np.arange(0, 10),
        "y": 3 * np.arange(0, 10) + 2  # y = 3x + 2
    },
    "Negative Slope": {
        "x": np.arange(0, 10),
        "y": 20 - 2 * np.arange(0, 10)  # y = -2x + 20
    },
    "Noisy Data": {
        "x": np.arange(0, 10),
        "y": 5 * np.arange(0, 10) + np.random.normal(0, 3, 10)  # y = 5x + noise
    }
}

# Loop through each test case
for name, data in test_cases.items():
    print(f"\n=== {name} ===")
    x, y = data["x"], data["y"]

    # Compute linear regression using analytical method
    b0, b1, y_pred, SSE, R2 = linear_regression_analytical(x, y)

    # Print coefficients and metrics
    print(f"Intercept (b0): {b0:.4f}, Slope (b1): {b1:.4f}")
    print(f"SSE: {SSE:.4f}, R²: {R2:.4f}")

    # Plot data points and fitted line
    plt.figure(figsize=(6, 4))
    plt.scatter(x, y, color="blue", label="Data Points")           # Original data points
    plt.plot(x, y_pred, "r-", label="Analytical Solution")        # Fitted line
    plt.xlabel("x")                                               # x-axis label
    plt.ylabel("y")                                               # y-axis label
    plt.legend()
    plt.title(f"Linear Regression - {name}")                      # Plot title
    plt.show()

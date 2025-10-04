import numpy as np
import matplotlib.pyplot as plt

# --- Linear Regression using Analytical (Closed-form) Solution ---

# Dataset
x = np.array([0, 1, 2, 3, 4, 5, 6, 7, 8, 9])
y = np.array([1, 3, 2, 5, 7, 8, 8, 9, 10, 12])

# Mean values
x_mean, y_mean = np.mean(x), np.mean(y)

# Compute coefficients (Closed-form)
b1 = np.sum((x - x_mean) * (y - y_mean)) / np.sum((x - x_mean)**2)
b0 = y_mean - b1 * x_mean

# Predictions
y_pred = b0 + b1 * x

# Compute SSE and R²
SSE = np.sum((y - y_pred)**2)
SST = np.sum((y - y_mean)**2)
R2 = 1 - (SSE / SST)

# Print results
print("=== Linear Regression (Analytical Solution) ===")
print(f"Intercept (b0): {b0:.4f}")
print(f"Slope (b1): {b1:.4f}")
print(f"SSE: {SSE:.4f}")
print(f"R²: {R2:.4f}")

# Plot results
plt.scatter(x, y, color="blue", label="Data")
plt.plot(x, y_pred, "r-", label="Analytical Solution")
plt.xlabel("x")
plt.ylabel("y")
plt.legend()
plt.title("Linear Regression - Analytical Solution")
plt.show()

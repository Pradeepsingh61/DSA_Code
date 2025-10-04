import numpy as np
import matplotlib.pyplot as plt

# Linear Regression using Gradient Descent (Full-Batch and SGD) 

# Dataset
x = np.array([0, 1, 2, 3, 4, 5, 6, 7, 8, 9])
y = np.array([1, 3, 2, 5, 7, 8, 8, 9, 10, 12])

# Gradient Descent Function
def gradient_descent(x, y, lr=0.01, epochs=10000, tolerance=1e-6, stochastic=False):
    b0, b1 = 0, 0
    n = len(x)

    for epoch in range(epochs):
        if stochastic:
            # Stochastic (single sample)
            i = np.random.randint(0, n)
            xi, yi = x[i], y[i]
            y_pred = b0 + b1 * xi
            b0_grad = -(yi - y_pred)
            b1_grad = -(yi - y_pred) * xi
        else:
            # Batch Gradient Descent
            y_pred = b0 + b1 * x
            b0_grad = -np.sum(y - y_pred) / n
            b1_grad = -np.sum((y - y_pred) * x) / n

        # Update parameters
        b0_new = b0 - lr * b0_grad
        b1_new = b1 - lr * b1_grad

        # Check convergence
        if abs(b0_new - b0) < tolerance and abs(b1_new - b1) < tolerance:
            break

        b0, b1 = b0_new, b1_new

    return b0, b1


# Full-Batch Gradient Descent
b0_gd, b1_gd = gradient_descent(x, y, lr=0.01, epochs=10000, stochastic=False)
y_pred_gd = b0_gd + b1_gd * x

# Stochastic Gradient Descent 
b0_sgd, b1_sgd = gradient_descent(x, y, lr=0.01, epochs=10000, stochastic=True)
y_pred_sgd = b0_sgd + b1_sgd * x

# Compute metrics
SST = np.sum((y - np.mean(y))**2)
SSE_gd = np.sum((y - y_pred_gd)**2)
SSE_sgd = np.sum((y - y_pred_sgd)**2)
R2_gd = 1 - (SSE_gd / SST)
R2_sgd = 1 - (SSE_sgd / SST)

# Print results
print("=== Gradient Descent (Full-Batch) ===")
print(f"Intercept (b0): {b0_gd:.4f}, Slope (b1): {b1_gd:.4f}")
print(f"SSE: {SSE_gd:.4f}, R²: {R2_gd:.4f}")

print("\n=== Gradient Descent (Stochastic) ===")
print(f"Intercept (b0): {b0_sgd:.4f}, Slope (b1): {b1_sgd:.4f}")
print(f"SSE: {SSE_sgd:.4f}, R²: {R2_sgd:.4f}")

# Plot comparison
plt.scatter(x, y, color="blue", label="Data")
plt.plot(x, y_pred_gd, "g--", label="Batch Gradient Descent")
plt.plot(x, y_pred_sgd, "m:", label="Stochastic GD")
plt.xlabel("x")
plt.ylabel("y")
plt.legend()
plt.title("Linear Regression using Gradient Descent (Batch & Stochastic)")
plt.show()

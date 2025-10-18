/*
 * =====================================================================================
 *
 * Filename:  fractional_knapsack.cpp
 *
 * Description:  Solves the Fractional Knapsack problem using a greedy approach.
 * All logic is contained within the main() function for a single-file
 * demonstration.
 *
 * =====================================================================================
 *
 * Algorithm:  Fractional Knapsack (Single Function Implementation)
 * Language:  C++
 *
 * Description:  Given item weights and values, this algorithm finds the maximum
 * value that can be placed in a knapsack of a given capacity.
 * It allows taking fractions of items.
 *
 * Time Complexity:  O(n log n)
 * Space Complexity:  O(n)
 *
 * =====================================================================================
 *
 * METHODOLOGY
 * -----------
 * The Fractional Knapsack problem is solved using a greedy algorithm. The core
 * idea is to always prioritize the item with the highest "value density" or
 * value-per-unit-of-weight.
 *
 * 1.  Calculate Ratios: First, we compute the value-to-weight ratio for each item.
 * This metric tells us which items are the most valuable for their size.
 *
 * 2.  Sort: We then sort all items in descending order based on this ratio. This
 * ensures that when we fill the knapsack, we are always considering the best
 * possible item at every step.
 *
 * 3.  Fill the Knapsack: We iterate through the sorted list of items. For each
 * item, we take as much as we possibly can. If the whole item fits, we take
 * it. If it doesn't, we take the fraction that will exactly fill the remaining
 * space in the knapsack, and then we stop.
 *
 * =====================================================================================
 *
 * TEST CASE WALKTHROUGH
 * ---------------------
 * Capacity: 50
 * Items:
 * - Item A: {Value: 60, Weight: 10} -> Ratio: 6.0
 * - Item B: {Value: 100, Weight: 20} -> Ratio: 5.0
 * - Item C: {Value: 120, Weight: 30} -> Ratio: 4.0
 *
 * 1.  The items are sorted by ratio (A, B, C).
 * 2.  Take Item A (10kg). Knapsack is at 10/50. Total value is 60.
 * 3.  Take Item B (20kg). Knapsack is at 30/50. Total value is 60 + 100 = 160.
 * 4.  Remaining capacity is 20kg. We can't take all of Item C (30kg).
 * So, we take a fraction: 20kg of Item C.
 * Value from this fraction = 20 * (ratio of C) = 20 * 4.0 = 80.
 * 5.  Final total value = 160 + 80 = 240. Knapsack is full.
 *
 * =====================================================================================
 *
 * COMPLEXITY ANALYSIS
 * -------------------
 * Time Complexity: O(n log n)
 * The runtime is dominated by the sorting step. Calculating ratios is O(n),
 * sorting is O(n log n), and filling the knapsack is O(n). The overall
 * complexity is O(n log n).
 *
 * Space Complexity: O(n)
 * The space required is primarily for storing the vector of 'n' items.
 * The memory usage scales linearly with the number of items.
 *
 * =====================================================================================
 */

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    // A struct to hold item properties, defined locally within main
    struct Item {
        int value;
        int weight;
        double ratio; // value / weight
    };

    // --- Test Case Setup ---
    vector<Item> items = {{60, 10}, {100, 20}, {120, 30}};
    int capacity = 50;

    cout << "--- Fractional Knapsack Problem (All in main) ---\n";
    cout << "Items (Value, Weight): (60,10), (100,20), (120,30)\n";
    cout << "Knapsack Capacity: " << capacity << "\n";

    // --- Core Logic
    // 1. Calculate the value-to-weight ratio for each item
    for (auto& item : items) {
        if (item.weight > 0) {
            item.ratio = static_cast<double>(item.value) / item.weight;
        } else {
            item.ratio = 0; // Handle case of zero weight
        }
    }

    // 2. Sort items based on their ratio in descending order using a lambda function.
    // A lambda is a concise, inline function defined right where it's used.
    sort(items.begin(), items.end(), [](const Item& a, const Item& b) {
        return a.ratio > b.ratio;
    });

    double totalValue = 0.0;
    int currentWeight = 0;

    // 3. Iterate through sorted items and fill the knapsack
    for (const auto& item : items) {
        // If the knapsack is already full, stop
        if (currentWeight == capacity) {
            break;
        }

        // Calculate how much of the current item can be taken
        int weightToTake = min(item.weight, capacity - currentWeight);

        // Add the value of the taken part to the total value
        if (weightToTake > 0) {
            totalValue += weightToTake * item.ratio;
            currentWeight += weightToTake;
        }
    }

    // --- Output the Result ---
    cout << "Maximum value in knapsack: " << totalValue << endl;

    return 0;
}
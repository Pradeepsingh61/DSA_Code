#include <bits/stdc++.h>
using namespace std;

// A simple structure for data points
struct Point
{
    vector<double> features; // coordinates/features
    int label;               // class label (e.g., 0 or 1)
};

// Function to compute Euclidean distance
double euclideanDistance(const vector<double> &a, const vector<double> &b)
{
    double sum = 0.0;
    for (size_t i = 0; i < a.size(); i++)
    {
        sum += (a[i] - b[i]) * (a[i] - b[i]);
    }
    return sqrt(sum);
}

// k-NN classification
int classifyKNN(const vector<Point> &dataset, const vector<double> &query, int k)
{
    // Compute distances from query to all dataset points
    vector<pair<double, int>> distances;
    for (const auto &p : dataset)
    {
        double dist = euclideanDistance(p.features, query);
        distances.push_back({dist, p.label});
    }

    // Sort by distance
    sort(distances.begin(), distances.end());

    // Count labels among k nearest neighbors
    unordered_map<int, int> freq;
    for (int i = 0; i < k; i++)
    {
        freq[distances[i].second]++;
    }

    // Find majority class
    int maxCount = 0, predictedLabel = -1;
    for (auto &entry : freq)
    {
        if (entry.second > maxCount)
        {
            maxCount = entry.second;
            predictedLabel = entry.first;
        }
    }

    return predictedLabel;
}

int main()
{
    // Example dataset: 2D points with labels (0 or 1)
    vector<Point> dataset = {
        {{1.0, 2.0}, 0},
        {{2.0, 3.0}, 0},
        {{3.0, 3.0}, 0},
        {{6.0, 5.0}, 1},
        {{7.0, 7.0}, 1},
        {{8.0, 6.0}, 1}};

    // Query point to classify
    vector<double> query = {5.0, 5.0};

    int k = 3; // Number of neighbors
    int predictedLabel = classifyKNN(dataset, query, k);

    cout << "Query Point: (" << query[0] << ", " << query[1] << ")" << endl;
    cout << "Predicted Class: " << predictedLabel << endl;

    return 0;
}

// This program finds if there are two values in an array that sum to a given
// number
// By: Nick from CoffeeBeforeArch

#include <algorithm>
#include <iostream>
#include <iterator>
#include <unordered_set>
#include <vector>

using std::begin;
using std::binary_search;
using std::cout;
using std::end;
using std::endl;
using std::sort;
using std::unordered_set;
using std::vector;

// Brute force implementation to solve the problem
// Compares all possible pairs of numbers
// Could skip repeated numbers, but this doesn't help worst-case
// O(n^2)
void solveBad(vector<int> &v, int sum) {
  // Check each number...
  for (auto it_1 = begin(v); it_1 < end(v); it_1++) {
    // With all later numbers
    for (auto it_2 = it_1 + 1; it_2 < end(v); it_2++) {
      // Print out the solution if we find one
      if (*it_1 + *it_2 == sum) {
        cout << "FOUND SOLUTION: " << *it_1 << " + " << *it_2 << " = " << sum
             << endl;
        return;
      }
    }
  }

  // Otherwise, exit unsuccesfully
  cout << "NO SOLUTION!" << endl;
}

// Sort the vector ahead of time, then do a binary search
// O(nlog(n)) for both the sorting and searches
void solveBetter1(vector<int> &v, int sum) {
  // Sort the array ahead of time
  sort(begin(v), end(v));

  // Do binary search for the remaining elements
  for (auto i : v) {
    auto b = binary_search(begin(v), end(v), sum - i);
    if (b) {
      cout << "FOUND SOLUTION: " << i << " + " << sum - i << " = " << sum
           << endl;
      return;
    }
  }

  // Otherwise, exit unsuccesfully
  cout << "NO SOLUTION!" << endl;
}

// Sort the vector ahead of time, then walk inwards
// Typically faster than binary search
// O(nlog(n))
void solveBetter2(vector<int> &v, int sum) {
  // Sort the array ahead of time
  sort(begin(v), end(v));

  // Move the left and right sides inwards
  int left = 0;
  int right = v.size() - 1;

  // Move until left and right point to the same spot
  while (left < right) {
    // Test if we've found the solution
    int tmp = v[left] + v[right];
    if (tmp == sum) {
      cout << "FOUND SOLUTION: " << v[left] << " + " << v[right] << " = " << sum
           << endl;
      return;
      // If too small, move the left index over
    } else if (tmp < sum) {
      left++;
      // Otherwise, it's too big, and move the right index over
    } else {
      right--;
    }
  }

  // Otherwise, exit unsuccesfully
  cout << "NO SOLUTION!" << endl;
}

// Insert each element into a hash table, and check if this is a solution
// Requires only one traversal of our vector
// O(n)
void solveBest(vector<int> &v, int sum) {
  // Hash set for storing numbers we've seen
  unordered_set<int> hash;

  // Loop over all elements
  for (auto i : v) {
    // Check for the corresponding number is in the hash set
    if (hash.find(sum - i) != hash.end()) {
      cout << "FOUND SOLUTION: " << i << " + " << sum - i << " = " << sum
           << endl;
      return;
    }

    // Insert the number into the hash set
    hash.insert(i);
  }

  // Otherwise, exit unsuccesfully
  cout << "NO SOLUTION!" << endl;
}

int main() {
  // Input array for the problem
  vector<int> v = {8, 3, 12, 26, 13, 2, 15, 4};

  // Sum to check against
  const int sum = 17;

  // Run our solutions
  solveBad(v, sum);

  solveBetter1(v, sum);
  v = {8, 3, 12, 26, 13, 2, 15, 4};

  solveBetter2(v, sum);
  v = {8, 3, 12, 26, 13, 2, 15, 4};

  solveBest(v, sum);

  return 0;
}

"""
statistics_calculator.py
Basic Statistics Calculator (Object-Oriented Paradigm)

Encapsulates mean, median, and mode in a StatisticsCalculator class.
Uses Python lists and dictionaries to store and manipulate data. Each
statistic is computed by its own method, demonstrating encapsulation.

Author: Murali Krishna Chintha
Course: MSCS-632 Advanced Programming Languages
"""

from collections import Counter


class StatisticsCalculator:
    """Computes basic statistics for a list of integers.

    The dataset is stored as private state and validated on construction,
    so every method operates on known-good data.
    """

    def __init__(self, data):
        if not data:
            raise ValueError("Data list must contain at least one integer.")
        if not all(isinstance(value, int) for value in data):
            raise TypeError("All elements must be integers.")
        # A private copy keeps internal state isolated from the caller's list.
        self._data = list(data)

    @property
    def data(self):
        """Return a copy so external code cannot mutate internal state."""
        return list(self._data)

    def mean(self):
        """Average of all values."""
        return sum(self._data) / len(self._data)

    def median(self):
        """Middle value of the sorted data (average of the two
        central values when the count is even)."""
        ordered = sorted(self._data)
        n = len(ordered)
        mid = n // 2
        if n % 2 == 1:
            return float(ordered[mid])
        return (ordered[mid - 1] + ordered[mid]) / 2.0

    def mode(self):
        """Most frequently occurring value(s).

        A dictionary of value-to-count is built with Counter, then every
        value sharing the maximum count is returned (handles multimodal
        data). The result is sorted for deterministic output.
        """
        counts = Counter(self._data)
        highest = max(counts.values())
        return sorted(value for value, freq in counts.items() if freq == highest)

    def summary(self):
        """Return all three statistics packaged in a dictionary."""
        return {
            "mean": self.mean(),
            "median": self.median(),
            "mode": self.mode(),
        }


def main():
    data = [7, 3, 9, 3, 5, 7, 3, 8, 5, 10, 7, 3]
    calc = StatisticsCalculator(data)

    print("Statistics Calculator (Python, Object-Oriented)")
    print("================================================")
    print(f"Input data ({len(data)} values): " + " ".join(map(str, data)))
    print("Sorted data:           " + " ".join(map(str, sorted(data))))
    print()
    print(f"Mean:   {calc.mean():.2f}")
    print(f"Median: {calc.median():.2f}")
    print("Mode:   " + ", ".join(map(str, calc.mode())))


if __name__ == "__main__":
    main()

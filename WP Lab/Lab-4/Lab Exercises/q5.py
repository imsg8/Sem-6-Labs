class PairFinder:
    def __init__(self, numbers, target):
        self.numbers = numbers
        self.target = target

    def find_pair(self):
        indices = {}

        for i, num in enumerate(self.numbers):
            complement = self.target - num
            if complement in indices:
                return indices[complement] + 1, i + 1
            indices[num] = i

        return None

def main():
    numbers = [10, 20, 10, 40, 50, 60, 70]
    target = int(input("Enter the number to search for: "))
    finder = PairFinder(numbers, target)
    result = finder.find_pair()

    if result:
        print(f"Indices of the pair whose sum equals {target}: {result[0]}, {result[1]}")
    else:
        print(f"No pair found whose sum equals {target}")

if __name__ == "__main__":
    main()
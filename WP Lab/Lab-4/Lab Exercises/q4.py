from itertools import chain, combinations

class SubsetGenerator:
    def __init__(self, input_set):
        self.input_set = input_set

    def get_unique_subsets(self):
        subsets = list(chain.from_iterable(combinations(self.input_set, r) for r in range(len(self.input_set) + 1)))
        return [list(subset) for subset in subsets]

def main():
    input_set = [4, 5, 6]
    generator = SubsetGenerator(input_set)
    unique_subsets = generator.get_unique_subsets()
    print("All unique subsets:", unique_subsets)

if __name__ == "__main__":
    main()

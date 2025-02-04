class StringProcessor:
    def __init__(self):
        self.string = ""

    def get_String(self):
        self.string = input("Enter a string: ")

    def print_String(self):
        print(self.string.upper())

def main():
    processor = StringProcessor()
    processor.get_String()
    processor.print_String()

if __name__ == "__main__":
    main()

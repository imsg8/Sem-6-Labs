def sort_words_alphabetically(input_string):
    words = input_string.split()

    words.sort()

    return words

def main():
    input_string = "apple orange banana mango cherry"
    sorted_words = sort_words_alphabetically(input_string)
    
    print("Original string:", input_string)
    print("Sorted words:", " ".join(sorted_words))

if __name__ == "__main__":
    main()
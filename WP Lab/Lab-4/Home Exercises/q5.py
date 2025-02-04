class StringReverser:
    def reverse_words(self, s: str) -> str:
        words = s.split()
        words.reverse()
        return ' '.join(words)

reverser = StringReverser()
input_string = "Hello World this is Python"
print("Original string:", input_string)
print("Reversed string:", reverser.reverse_words(input_string))

class ParenthesesValidator:
    def __init__(self):
        self.bracket_map = {')': '(', '}': '{', ']': '['}
    
    def is_valid(self, s: str) -> bool:
        stack = []
        for char in s:
            if char in self.bracket_map.values():
                stack.append(char)
            elif char in self.bracket_map:
                if not stack or stack[-1] != self.bracket_map[char]:
                    return False
                stack.pop()
        return len(stack) == 0

validator = ParenthesesValidator()
test_strings = ["()", "()[]{}", "[)", "({[)]", "{{{"]
for s in test_strings:
    print(f"'{s}': {validator.is_valid(s)}")

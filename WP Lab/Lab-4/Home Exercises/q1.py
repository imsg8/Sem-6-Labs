def find_smallest(lst):
    if not lst:
        return None
    smallest = lst[0]
    for num in lst[1:]:
        if num < smallest:
            smallest = num
    return smallest

numbers = [45, 23, 67, 12, 89, 2, 56]
print("The smallest element is:", find_smallest(numbers))

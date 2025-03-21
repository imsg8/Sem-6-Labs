def binary_search_recursive(arr, target, low, high):
    if low > high:
        return -1

    mid = (low + high) // 2

    if arr[mid] == target:
        return mid

    elif target < arr[mid]:
        return binary_search_recursive(arr, target, low, mid - 1)

    else:
        return binary_search_recursive(arr, target, mid + 1, high)

def main():
    arr = [1, 3, 5, 7, 9, 11, 13, 15]
    target = int(input("Enter the number to search for: "))

    result = binary_search_recursive(arr, target, 0, len(arr) - 1)

    if result != -1:
        print(f"Element {target} found at index {result}.")
    else:
        print(f"Element {target} not found in the array.")

if __name__ == "__main__":
    main()

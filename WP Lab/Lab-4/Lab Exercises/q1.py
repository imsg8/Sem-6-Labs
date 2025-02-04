def reverse_file_content(input_file, output_file):
    try:
        with open(input_file, 'r', encoding='utf-8') as file:
            content = file.read()
        
        reversed_content = content[::-1]
        
        with open(output_file, 'w', encoding='utf-8') as file:
            file.write(reversed_content)
        
        print(f"Reversed content has been written to {output_file}")
    except FileNotFoundError:
        print("Error: The input file was not found.")
    except Exception as e:
        print(f"An error occurred: {e}")

input_file = "input.txt"
output_file = "output.txt"
reverse_file_content(input_file, output_file)
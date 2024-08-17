def generate_test_case(filename, n, target):
    with open(filename, 'w') as f:
        f.write(str(target)+'\r\n')
        f.write(str(n)+'\r\n')
        base = 39458793875493875
        for i in range(n):
            number = base - i * target
            f.write(str(number) + '\r\n')  # Write each number to a new line in the file

# Parameters
n = 10  # Number of elements
target = 935863493954678  # 50-digit target difference
filename = 'test_case.txt'  # Output file name

# Generate the test case and write it to the file
generate_test_case(filename, n, target)

print(f"Test case with {n} elements has been written to '{filename}'.")

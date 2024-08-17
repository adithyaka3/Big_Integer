# Modify this file to implement the count_pairs_file function
# using ultra-large integers in C/C++.
import ctypes
def read_file(filename: str) -> tuple[list[int], int]:
    with open(filename) as file:
        # First line is the target
        target = int(file.readline())
        # Second line is the number of integers
        n = int(file.readline())
        # Read the n integers and return them as a list
        return ([int(file.readline()) for _ in range(n)], target)


# def count_pairs(data: list[int], target: int) -> int:
#     """Count the number of pairs of
#     list indices i < j such that
#     data[i] - data[j] = target.
#     Time complexity: Naive O(n^2).
#     """
#     result = 0
#     n = len(data)
#     for i in range(n - 1):
#         for j in range(i + 1, n):
#             if data[i] - data[j] == target:
#                 result += 1
#     return result


def count_pairs(data, target):
    """This is the O(n) approach to solving this problem"""
    result = 0
    freq_map = {}

    # Iterate over the data from right to left to ensure i < j
    for key in data:
        if(freq_map.get(key, 0)!=0):
            result+=freq_map[key]
        freq_map[key-target] = freq_map.get(key-target, 0)+1
    
    return result


def test_count_pairs():
    # Simple correctness tests
    assert count_pairs([1, 2, 3, 4, 5], 1) == 0
    assert count_pairs([5, 4, 3, 2, 1], 1) == 4
    assert count_pairs([1, 2, 3, 4, 5], -3) == 2
    # Test with huge integers
    assert count_pairs([10**20 + 2, 10**20 + 1, 10**20], 1) == 2
    print("count_pairs.py: All tests passed")


def count_pairs_file(filename: str) :

    #preprocessing done in order to call the c function
    func = ctypes.CDLL('./BigInt.so')
    func.readFiles.argtypes = [ctypes.c_char_p]
    func.readFiles.restype = ctypes.c_ulonglong
    filename_c = filename.encode('utf-8')

    result_c = func.readFiles(filename_c)#here result_c stores the returned value from the c program as in integer.
    
    return result_c



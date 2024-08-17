# Modify this file to implement the count_pairs_file function
# using ultra-large integers in C/C++.
import ctypes
import time
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
#Below is the O(n) approach and above is the naive O(n^2) approach
def count_pairs(data, target):
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
    func = ctypes.CDLL('./BigInt.so')
    func.readFiles.argtypes = [ctypes.c_char_p]
    func.readFiles.restype = ctypes.c_ulonglong
    filename_c = filename.encode('utf-8')

    t1 = time.time()
    result_c = func.readFiles(filename_c)#here result stores the returned value from the c program as in integer.
    t2 = time.time()
    
    print("\nC++ implementation :" ,t2-t1)
    # print("Result from C++:", result, '\n\n')

    t3 = time.time()
    data, target = read_file(filename)    
    result_py =  count_pairs(data, target)
    t4 = time.time()
    print("python implementation :" ,t4-t3)
    # print("Result from python:", res, '\n\n')
    assert(result_c==result_py)
    print("T_py/T_c++ : ",(t4-t3)/(t2-t1))
    return result_c



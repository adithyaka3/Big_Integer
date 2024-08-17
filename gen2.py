# Copyrigh 2024 - All Rights Reserved
# Author: Keval Pithadiya (kevalp@iisc.ac.in)
 
from random import randbytes, randrange
 
TARGET_BYTES_MIN, TARGET_BYTES_MAX = 1, 2
ARRAY_SIZE = 1_00_00_000
INTEGER_BYTES_MIN, INTEGER_BYTES_MAX = 3, 4
 
with open("./rand_input.txt", "w") as fh:
  # Generate Target Value
  target_size = randrange(TARGET_BYTES_MIN, TARGET_BYTES_MAX)
  target = int.from_bytes(randbytes(target_size), signed=True, byteorder='little')
  fh.write(str(target) + "\n")
 
  # Write Array Size
  fh.write(str(ARRAY_SIZE) + "\n")
 
  # Generate Array Elements
  for i in range(ARRAY_SIZE):
    integer_size = randrange(INTEGER_BYTES_MIN, INTEGER_BYTES_MAX)
    integer = int.from_bytes(randbytes(integer_size), signed=True, byteorder='little')
    fh.write(str(integer) + "\n")

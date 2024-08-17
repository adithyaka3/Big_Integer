# Variables
CXX = g++
CXXFLAGS = -fPIC -Wall -O3
TARGET = BigInt.so
SRC = BigInt.cpp

# Rule to create the shared object file
$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) -shared -o $(TARGET) $(SRC)

# Clean up the generated files
clean:
	rm -f $(TARGET)

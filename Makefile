CXX = g++
CXXFLAGS = -std=c++17 -Wall

SAMPLES = heap/heap_exploration heap/kth_largest

all: $(SAMPLES)

# Target for sample1
heap_exploration:
	$(CXX) $(CXXFLAGS) heap_exploration.cc -o heap_exploration

	# Target for kth_largest
	kth_largest:
		$(CXX) $(CXXFLAGS) kth_largest.cc -o kth_largest

# Clean build artifacts
clean:
	rm -f $(SAMPLES)

.PHONY: clean
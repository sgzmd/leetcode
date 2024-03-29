CXX = g++
CXXFLAGS = -std=c++17 -Wall

SAMPLES = heap/heap_exploration heap/kth_largest heap/last_stone

all: $(SAMPLES)

# Target for sample1
heap_exploration:
	$(CXX) $(CXXFLAGS) heap_exploration.cc -o heap_exploration

# Target for kth_largest
kth_largest:
	$(CXX) $(CXXFLAGS) kth_largest.cc -o kth_largest

# Target for last_stone
last_stone:
	$(CXX) $(CXXFLAGS) last_stone.cc -o last_stone

# Clean build artifacts
clean:
	rm -f $(SAMPLES)

.PHONY: clean
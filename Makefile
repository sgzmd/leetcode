CXX = g++
CXXFLAGS = -std=c++17 -Wall

SAMPLES = heap/heap_exploration heap/kth_largest heap/last_stone heap/weakest_row \
	heap/kth_smallest_sorted_matrix heap/k_closest_points heap/meeting_rooms_ii \
	heap/sticks

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

# Target for weakest_row
weakest_row:
	$(CXX) $(CXXFLAGS) weakest_row.cc -o weakest_row

# Target for kth_smallest_sorted_matrix
kth_smallest_sorted_matrix:
	$(CXX) $(CXXFLAGS) kth_smallest_sorted_matrix.cc -o kth_smallest_sorted_matrix

# Target for k_closest_points
k_closest_points:
	$(CXX) $(CXXFLAGS) k_closest_points.cc -o k_closest_points

# Target for meeting_room
meeting_room_ii:
	$(CXX) $(CXXFLAGS) meeting_rooms_ii.cc -o meeting_rooms_ii

sticks:
	$(CXX) $(CXXFLAGS) sticks.cc -o sticks

# Clean build artifacts
clean:
	rm -f $(SAMPLES)

.PHONY: clean
#include <iostream>
#include <unordered_map>
using namespace std;

// Define constants
const int PAGE_SIZE = 0x100; // Page size = 256 bytes
const int NUM_PAGES = 0x100; // Total number of pages = 256
const int FRAME_SIZE = 0x100; // Frame size = 256 bytes
const int NUM_FRAMES = 0x100; // Total number of frames = 256

// Page/frame table
unordered_map<int, int> pageFrameTable;

// Function to initialize page/frame table
void initializePageFrameTable() {
    for (int i = 0; i < NUM_PAGES; ++i) {
        // Map logical page number to physical frame number
        pageFrameTable[i] = i % NUM_FRAMES;
    }
}

// Function to translate logical address to physical address
void translateLogicalToPhysical(int logicalAddress) {
    // Calculate page number and offset
    int pageNumber = logicalAddress / PAGE_SIZE; // Calculates the page number from the logical address
    int offset = logicalAddress % PAGE_SIZE; // Calculates the offset within the page from the logical address

    // Check if page number exists in page/frame table
    if (pageFrameTable.find(pageNumber) == pageFrameTable.end()) {
        cout << "Page fault occurred for logical address: 0x" << hex << logicalAddress << endl;
        return;
    }

    // Get corresponding frame number from page/frame table
    int frameNumber = pageFrameTable[pageNumber];

    // Calculate physical address
    int physicalAddress = frameNumber * FRAME_SIZE + offset; // Calculates the physical address by adding offset to the base address of the frame

    // Output results
    cout << "Logical Address: 0x" << hex << logicalAddress << " => Page Number: 0x" << hex << pageNumber << ", Offset: 0x" << hex << offset << endl;
    cout << "Physical Address: 0x" << hex << physicalAddress << endl;
}

int main() {
    // Initialize page/frame table
    initializePageFrameTable();

    // Sample Input
    int logicalAddresses[] = { 0x3A7F, 0xABCD, 0x5678 };

    // Translate logical addresses to physical addresses
    for (int i = 0; i < 3; ++i) {
        translateLogicalToPhysical(logicalAddresses[i]);
    }

    return 0;
}

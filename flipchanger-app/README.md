# FlipChanger App

The main FlipChanger application for Flipper Zero - tracks CD metadata for CD changers (3-200 discs).

## Features Implemented

### ✅ Core Features (v1.0)

- **Main Menu**: Navigation hub with options
- **Slot Browser**: View all slots (1-200) with status
- **Slot Details**: View CD metadata for each slot
- **Navigation**: Full menu system with UP/DOWN/OK/BACK controls
- **Empty Slot Detection**: Shows which slots are empty vs occupied

### 🚧 In Progress / TODO

- **Add/Edit CD**: Data entry interface for CD metadata
- **JSON Storage**: Save/load data to SD card
- **Track Management**: Add/edit track listings
- **Statistics**: Collection statistics (total CDs, by artist, etc.)
- **Settings**: Configure number of slots, etc.

## Building the App

### Prerequisites

- uFBT installed (✅ Done!)
- Flipper Zero device (for testing)

### Build Commands

```bash
cd flipchanger-app

# Build the app
ufbt build APPID=flipchanger

# Build and deploy to device
ufbt launch APPID=flipchanger
```

### Build Output

The app is compiled into a `.fap` file:
- Location: `/Users/gilbertroberts/.ufbt/build/flipchanger.fap`
- Target: 7, API: 87.1

## File Structure

```
flipchanger-app/
├── application.fam      # App manifest (required)
├── flipchanger.h        # Header file with definitions
├── flipchanger.c        # Main application source
└── README.md            # This file
```

## Usage

### Navigation

1. **Main Menu**:
   - UP/DOWN: Navigate menu items
   - OK: Select option
   - BACK: Exit app

2. **Slot List**:
   - UP/DOWN: Scroll through slots
   - OK: View slot details
   - BACK: Return to main menu

3. **Slot Details**:
   - Shows slot number and CD information
   - OK: Edit CD (if occupied) or Add CD (if empty)
   - BACK: Return to slot list

### Current Features

- ✅ View all slots in a scrollable list
- ✅ See which slots are empty vs occupied
- ✅ View basic CD information (artist, album, year, genre, tracks)
- ✅ Navigate between views

### Coming Soon

- ⏳ Add new CDs to empty slots
- ⏳ Edit existing CD metadata
- ⏳ Add track listings
- ⏳ Save data to SD card (JSON format)
- ⏳ Load saved data on startup

## Data Model

### Slot Structure

```c
typedef struct {
    int32_t slot_number;    // 1-200
    bool occupied;          // Is there a CD in this slot?
    CD cd;                  // CD metadata
} Slot;
```

### CD Structure

```c
typedef struct {
    char artist[64];
    char album[64];
    int32_t year;
    char genre[32];
    Track tracks[99];       // Track listings
    int32_t track_count;
    char notes[256];
} CD;
```

### Track Structure

```c
typedef struct {
    int32_t number;         // Track number
    char title[64];         // Track title
    char duration[16];      // Duration (e.g., "3:45")
} Track;
```

## Storage

Data is stored on the SD card at:
- Path: `/ext/apps/Tools/flipchanger_data.json`
- Format: JSON (to be implemented)

## Testing

1. **Build the app**:
   ```bash
   cd flipchanger-app
   ufbt build APPID=flipchanger
   ```

2. **Deploy to device**:
   ```bash
   ufbt launch APPID=flipchanger
   ```

3. **Test navigation**:
   - Main menu → View Slots
   - Browse through slots
   - View slot details
   - Navigate back

## Development Status

| Feature | Status |
|---------|--------|
| App Structure | ✅ Complete |
| Main Menu | ✅ Complete |
| Slot Browser | ✅ Complete |
| Slot Details View | ✅ Complete |
| Navigation | ✅ Complete |
| Add/Edit CD | 🚧 TODO |
| JSON Storage | 🚧 TODO |
| Track Management | 🚧 TODO |
| Statistics | 🚧 TODO |
| Settings | 🚧 TODO |

## Next Steps

1. **Implement Add/Edit Interface**:
   - Text input for artist, album, etc.
   - Track entry system
   - Form validation

2. **Implement JSON Storage**:
   - Save to SD card
   - Load on startup
   - Error handling

3. **Add Track Management**:
   - Add tracks to CDs
   - Edit track information
   - Track count display

4. **Polish & Testing**:
   - Test on actual hardware
   - Error handling
   - UI improvements

## Resources

- [Development Setup Guide](../docs/development_setup.md)
- [Product Vision](../docs/product_vision.md)
- [Flipper Zero Developer Docs](https://developer.flipper.net/)

---

**Status**: ✅ Build successful! Ready for testing on device.

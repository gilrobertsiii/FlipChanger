# FlipChanger

FlipChanger is an open-source application for the Flipper Zero that helps users track physical CDs loaded into a CD changer system (3-200 discs). Store metadata like artist, album, and track listings directly on your Flipper Zero, similar to MP3 ID3 tags.

## Features

- **Slot Management**: Track which CDs are in which slots (1-200)
- **Metadata Storage**: Store artist, album, year, genre, and track listings for each CD
- **View & Browse**: Navigate your collection easily on the Flipper Zero display
- **Add/Edit CDs**: Manage your collection directly from the device
- **Data Persistence**: All data saved to SD card, survives reboots
- **IR Remote Integration** (planned): Control your CD changer using Flipper Zero's infrared capabilities

## Status

🚧 **In Development** - This is a learning project. Contributions welcome!

## Documentation

- [Product Vision Document](docs/product_vision.md)
- [Development Setup Guide](docs/development_setup.md) - Complete research on Flipper Zero app development
- [Quick Start Checklist](docs/quick_start_checklist.md) - Get started checklist

## Application Status

### ✅ FlipChanger App (`flipchanger-app/`) - **MAIN APP**
- Core FlipChanger application
- Slot management (1-200 slots)
- CD metadata tracking
- **Quick start:**
  ```bash
  cd flipchanger-app
  ufbt build APPID=flipchanger    # Build the app
  ufbt launch APPID=flipchanger   # Deploy and run
  ```
- See [flipchanger-app/README.md](flipchanger-app/README.md) for details
- **Status**: ✅ Build successful! Core features working.

### Test Apps

#### 1. C/C++ Hello World (`hello-world-ufbt/`)
- Simple test app to verify uFBT setup
- See [hello-world-ufbt/README.md](hello-world-ufbt/README.md)

#### 2. JavaScript/TypeScript Version (`hello-world-app/`)
- JavaScript SDK test app (requires Node.js)
- See [hello-world-app/README.md](hello-world-app/README.md)

## Installation

> **Coming Soon** - Once published to the Flipper Zero app store, installation instructions will be provided here.

## Development

### Requirements

- Flipper Zero device
- Flipper Zero development environment (see [official docs](https://docs.flipperzero.one/development/firmware))
- SD card for data storage

### Building

> Build instructions coming soon.

## Contributing

Contributions are welcome! This is a learning project, so whether you're a beginner or experienced developer, your input is valuable.

1. Fork the repository
2. Create a feature branch
3. Make your changes
4. Submit a pull request

## License

[MIT License](LICENSE)

## Acknowledgments

- Flipper Zero community
- All contributors and future contributors

---

**Note**: This is an educational project for learning Flipper Zero application development and open-source practices.

# FlipChanger Quick Start Checklist

A practical checklist to get started with FlipChanger development.

## Prerequisites Setup

- [ ] **Node.js Installed**
  ```bash
  node --version  # Should show v18+ or similar
  npm --version   # Should show version number
  ```
  - If not installed: Download from [nodejs.org](https://nodejs.org/)

- [ ] **Flipper Zero Device Available**
  - Firmware updated to latest version
  - USB cable for connection
  - SD card inserted (for data storage)

- [ ] **Development Environment Ready**
  - Code editor (VS Code recommended)
  - Terminal/command line access
  - Git configured

## Initial Project Setup

- [ ] **Create Flipper Zero JS App**
  ```bash
  cd /Users/gilbertroberts/projects/FlipChanger
  npx @flipperdevices/create-fz-app@latest flipchanger-app
  cd flipchanger-app
  ```

- [ ] **Review Generated Structure**
  - Check `src/index.ts` (main app file)
  - Review `package.json` (dependencies)
  - Check `fz-sdk.config.json5` (configuration)

- [ ] **Test Connection**
  ```bash
  npm start  # Should connect to Flipper Zero via USB
  ```

- [ ] **Verify App Runs on Device**
  - Connect Flipper Zero via USB
  - Run `npm start`
  - Check if app appears on device

## Development Tasks (Priority Order)

### Phase 1: Basic Structure ✅ DONE
- [x] Repository created
- [x] Product vision document
- [x] Development setup research

### Phase 2: Project Setup ✅ COMPLETE
- [x] Create Flipper Zero app structure
- [x] Set up build system (uFBT)
- [x] Test basic "Hello World" on device
- [x] Install uFBT and verify setup

### Phase 3: Data Storage
- [ ] Implement JSON file reading
- [ ] Implement JSON file writing
- [ ] Test on SD card
- [ ] Create sample data file

### Phase 4: UI - Navigation ✅ COMPLETE
- [x] Create main menu
- [x] Implement slot list view
- [x] Implement slot detail view
- [x] Add navigation between views
- [x] Memory optimization (SD card caching)

### Phase 5: Core Features
- [ ] Add CD to slot
- [ ] Edit CD metadata
- [ ] View CD metadata
- [ ] Delete/clear slot

### Phase 6: Polish
- [ ] Error handling
- [ ] Input validation
- [ ] UI improvements
- [ ] Testing on device

### Phase 7: IR Integration (Optional)
- [ ] Research IR database API
- [ ] Find CD changer IR codes
- [ ] Implement basic IR control
- [ ] Test with actual CD changer

## Key Commands Reference

```bash
# Development
npm start              # Build and deploy to Flipper Zero
npm run build          # Build without deploying
npm run watch          # Watch for changes and auto-reload

# Testing
# Test on actual Flipper Zero hardware

# Git
git status             # Check repository status
git add .              # Stage all changes
git commit -m "msg"    # Commit changes
git push               # Push to GitHub
```

## Important File Locations

```
FlipChanger/
├── flipchanger-app/          # JS app directory (to be created)
│   ├── src/
│   │   └── index.ts          # Main app code
│   ├── package.json          # Dependencies
│   └── fz-sdk.config.json5   # SDK configuration
├── docs/
│   ├── product_vision.md     # Project vision
│   └── development_setup.md  # This research
└── README.md                 # Project readme
```

## Testing Checklist

Before app store submission:

- [ ] App runs on actual Flipper Zero hardware
- [ ] Data persists after device reboot
- [ ] App works with/without SD card (graceful handling)
- [ ] All features tested (add, edit, view, delete)
- [ ] UI is usable on 128x64 display
- [ ] No crashes during normal use
- [ ] Error messages are clear
- [ ] Code is commented and documented
- [ ] README has build/usage instructions
- [ ] License file included (MIT ✅)

## Useful Resources

- **Full Setup Guide**: `docs/development_setup.md`
- **Product Vision**: `docs/product_vision.md`
- **Official Docs**: https://developer.flipper.net/
- **Flipper Wiki**: https://flipper.wiki/

---

**Current Status**: ✅ Core app structure complete and running on device!  
**Next Step**: Implement JSON storage system, then Add/Edit CD interface.

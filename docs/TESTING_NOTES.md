# FlipChanger Testing Notes

## JSON Storage Testing (January 18, 2024)

### Deployment Status
✅ **App deployed successfully**
- Build: Target 7, API: 87.1
- Size: ~3KB (includes JSON storage)
- Location: `/ext/apps/Tools/flipchanger.fap`
- Device: Connected via USB

### What to Test

1. **Initial Load**:
   - App should start with default 20 slots (all empty)
   - No crash on startup
   - Main menu appears

2. **File Creation**:
   - Navigate through the app
   - Exit the app
   - Check if file exists: `/ext/apps/Tools/flipchanger_data.json`
   - File should contain JSON structure with 20 empty slots

3. **Save Functionality**:
   - When app exits, it should save current cache
   - File should be created/updated
   - JSON format should be valid

4. **Load Functionality**:
   - Start app again
   - App should load data from JSON file (if exists)
   - Cached slots should reflect saved data

### Manual Testing Steps

1. **First Run**:
   ```
   - Launch app
   - Navigate to "View Slots"
   - Should see slots 1-20, all empty
   - Press BACK to exit
   - Check SD card: /ext/apps/Tools/flipchanger_data.json
   ```

2. **Verify JSON File**:
   - File should exist
   - Should contain valid JSON
   - Should have structure:
     ```json
     {
       "version": 1,
       "total_slots": 20,
       "slots": [...]
     }
     ```

3. **Second Run**:
   - Launch app again
   - App should load from JSON file
   - Should show same slots as before

### Known Limitations

1. **Cache Only**: Only cached slots (first 10) are saved/loaded
2. **No Add/Edit Yet**: Can't add CDs yet (interface not implemented)
3. **Simple Parser**: JSON parser is simple - may not handle all edge cases

### Expected Results

✅ App starts without crashes  
✅ JSON file created on exit  
✅ JSON file loads on startup  
✅ Valid JSON format  
✅ Handles missing file gracefully  

---

**Next**: Once verified working, proceed with Add/Edit interface implementation.

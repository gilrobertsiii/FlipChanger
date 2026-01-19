/**
 * FlipChanger - Header File
 * 
 * Main application header with type definitions and function declarations
 */

#pragma once

#include <furi.h>
#include <gui/gui.h>
#include <input/input.h>
#include <storage/storage.h>
#include <notification/notification.h>

#include <stdint.h>
#include <stdbool.h>

// Maximum number of slots (CDs)
#define MAX_SLOTS 200
#define MIN_SLOTS 3

// Maximum string lengths
#define MAX_STRING_LENGTH 64
#define MAX_ARTIST_LENGTH 64
#define MAX_ALBUM_LENGTH 64
#define MAX_GENRE_LENGTH 32
#define MAX_TRACK_TITLE_LENGTH 64
#define MAX_NOTES_LENGTH 256
#define MAX_TRACKS 99

// File path for data storage
#define FLIPCHANGER_DATA_PATH "/ext/apps/Tools/flipchanger_data.json"

// Track information
typedef struct {
    int32_t number;
    char title[MAX_TRACK_TITLE_LENGTH];
    char duration[16];  // Format: "3:45"
} Track;

// CD information
typedef struct {
    char artist[MAX_ARTIST_LENGTH];
    char album[MAX_ALBUM_LENGTH];
    int32_t year;
    char genre[MAX_GENRE_LENGTH];
    Track tracks[MAX_TRACKS];
    int32_t track_count;
    char notes[MAX_NOTES_LENGTH];
} CD;

// Slot information
typedef struct {
    int32_t slot_number;
    bool occupied;
    CD cd;
} Slot;

// Application state
typedef struct {
    Gui* gui;
    ViewPort* view_port;
    NotificationApp* notifications;
    Storage* storage;
    
    // Data
    Slot slots[MAX_SLOTS];
    int32_t total_slots;
    int32_t current_slot_index;  // Currently viewing/editing
    
    // UI State
    enum {
        VIEW_MAIN_MENU,
        VIEW_SLOT_LIST,
        VIEW_SLOT_DETAILS,
        VIEW_ADD_EDIT_CD,
        VIEW_CONFIRM_DELETE,
    } current_view;
    
    int32_t selected_index;      // Selected item in list
    int32_t scroll_offset;        // Scroll position in lists
    bool running;
    bool dirty;                   // Data has been modified, needs save
    
} FlipChangerApp;

// Function declarations
int32_t flipchanger_main(void* p);

// Storage functions
bool flipchanger_load_data(FlipChangerApp* app);
bool flipchanger_save_data(FlipChangerApp* app);

// UI functions
void flipchanger_draw_callback(Canvas* canvas, void* ctx);
void flipchanger_input_callback(InputEvent* input_event, void* ctx);
void flipchanger_draw_main_menu(Canvas* canvas, FlipChangerApp* app);
void flipchanger_draw_slot_list(Canvas* canvas, FlipChangerApp* app);
void flipchanger_draw_slot_details(Canvas* canvas, FlipChangerApp* app);
void flipchanger_draw_add_edit(Canvas* canvas, FlipChangerApp* app);

// Navigation functions
void flipchanger_show_main_menu(FlipChangerApp* app);
void flipchanger_show_slot_list(FlipChangerApp* app);
void flipchanger_show_slot_details(FlipChangerApp* app, int32_t slot_index);
void flipchanger_show_add_edit(FlipChangerApp* app, int32_t slot_index, bool is_new);

// Utility functions
void flipchanger_init_slots(FlipChangerApp* app, int32_t total_slots);
const char* flipchanger_get_slot_status(FlipChangerApp* app, int32_t slot_index);
int32_t flipchanger_count_occupied_slots(FlipChangerApp* app);

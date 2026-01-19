/**
 * FlipChanger - Main Application File
 * 
 * Tracks CD metadata for CD changers (3-200 discs)
 * Similar to MP3 ID3 tags for physical CDs
 */

#include "flipchanger.h"
#include <notification/notification_messages.h>
#include <m-array.h>
#include <stream/stream.h>
#include <stream/buffered_file_stream.h>

// Initialize default slots
void flipchanger_init_slots(FlipChangerApp* app, int32_t total_slots) {
    app->total_slots = (total_slots < MIN_SLOTS) ? MIN_SLOTS : 
                       (total_slots > MAX_SLOTS) ? MAX_SLOTS : total_slots;
    
    for(int32_t i = 0; i < app->total_slots; i++) {
        app->slots[i].slot_number = i + 1;
        app->slots[i].occupied = false;
        memset(&app->slots[i].cd, 0, sizeof(CD));
        app->slots[i].cd.track_count = 0;
    }
    
    app->current_slot_index = 0;
    app->selected_index = 0;
    app->scroll_offset = 0;
}

// Get slot status string
const char* flipchanger_get_slot_status(FlipChangerApp* app, int32_t slot_index) {
    if(slot_index < 0 || slot_index >= app->total_slots) {
        return "Invalid";
    }
    
    if(app->slots[slot_index].occupied) {
        return app->slots[slot_index].cd.album;
    }
    
    return "Empty";
}

// Count occupied slots
int32_t flipchanger_count_occupied_slots(FlipChangerApp* app) {
    int32_t count = 0;
    for(int32_t i = 0; i < app->total_slots; i++) {
        if(app->slots[i].occupied) {
            count++;
        }
    }
    return count;
}

// Load data from JSON file (simplified version - will enhance later)
bool flipchanger_load_data(FlipChangerApp* app) {
    if(!app->storage) {
        return false;
    }
    
    // For now, initialize with default slots
    // TODO: Implement JSON parsing
    flipchanger_init_slots(app, 100);  // Default to 100 slots
    
    // Try to open and read file if it exists
    File* file = storage_file_alloc(app->storage);
    
    if(storage_file_open(file, FLIPCHANGER_DATA_PATH, FSAM_READ, FSOM_OPEN_EXISTING)) {
        // File exists - for now just mark that data file exists
        // TODO: Parse JSON
        storage_file_close(file);
    }
    
    storage_file_free(file);
    
    return true;
}

// Save data to JSON file (simplified version - will enhance later)
bool flipchanger_save_data(FlipChangerApp* app) {
    if(!app->storage) {
        return false;
    }
    
    // TODO: Implement JSON writing
    // For now, just mark that save was attempted
    app->dirty = false;
    
    return true;
}

// Draw main menu
void flipchanger_draw_main_menu(Canvas* canvas, FlipChangerApp* app) {
    canvas_clear(canvas);
    canvas_set_font(canvas, FontPrimary);
    
    // Title
    canvas_draw_str(canvas, 30, 10, "FlipChanger");
    
    // Menu options
    canvas_set_font(canvas, FontSecondary);
    
    int32_t y = 25;
    const char* menu_items[] = {
        "View Slots",
        "Add CD",
        "Statistics",
        "Settings"
    };
    
    int32_t selected = app->selected_index % 4;
    
    for(int32_t i = 0; i < 4; i++) {
        if(i == selected) {
            canvas_draw_box(canvas, 5, y - 8, 118, 10);
            canvas_invert_color(canvas);
        }
        canvas_draw_str(canvas, 10, y, menu_items[i]);
        if(i == selected) {
            canvas_invert_color(canvas);
        }
        y += 12;
    }
    
    // Footer
    canvas_set_font(canvas, FontKeyboard);
    canvas_draw_str(canvas, 5, 60, "UP/DN:Select OK:Go BACK:Exit");
}

// Draw slot list
void flipchanger_draw_slot_list(Canvas* canvas, FlipChangerApp* app) {
    canvas_clear(canvas);
    canvas_set_font(canvas, FontPrimary);
    
    // Header
    char header[32];
    snprintf(header, sizeof(header), "Slots (%ld total)", app->total_slots);
    canvas_draw_str(canvas, 5, 10, header);
    
    // Calculate visible slots (5 per screen)
    int32_t visible_count = 5;
    int32_t start_index = app->scroll_offset;
    int32_t end_index = start_index + visible_count;
    if(end_index > app->total_slots) {
        end_index = app->total_slots;
    }
    
    canvas_set_font(canvas, FontSecondary);
    int32_t y = 20;
    
    for(int32_t i = start_index; i < end_index; i++) {
        char line[64];
        
        if(app->slots[i].occupied) {
            snprintf(line, sizeof(line), "%ld: %s", (long)(i + 1), app->slots[i].cd.artist);
        } else {
            snprintf(line, sizeof(line), "%ld: [Empty]", (long)(i + 1));
        }
        
        if(i == app->selected_index) {
            canvas_draw_box(canvas, 2, y - 8, 124, 9);
            canvas_invert_color(canvas);
        }
        
        canvas_draw_str(canvas, 5, y, line);
        
        if(i == app->selected_index) {
            canvas_invert_color(canvas);
        }
        
        y += 10;
    }
    
    // Footer
    canvas_set_font(canvas, FontKeyboard);
    canvas_draw_str(canvas, 5, 60, "UP/DN:Nav OK:View BACK:Menu");
}

// Draw slot details
void flipchanger_draw_slot_details(Canvas* canvas, FlipChangerApp* app) {
    canvas_clear(canvas);
    
    if(app->current_slot_index < 0 || app->current_slot_index >= app->total_slots) {
        canvas_set_font(canvas, FontPrimary);
        canvas_draw_str(canvas, 5, 30, "Invalid slot");
        return;
    }
    
    Slot* slot = &app->slots[app->current_slot_index];
    
    canvas_set_font(canvas, FontPrimary);
    
    // Slot number
    char slot_str[16];
    snprintf(slot_str, sizeof(slot_str), "Slot %ld", (long)slot->slot_number);
    canvas_draw_str(canvas, 5, 10, slot_str);
    
    if(!slot->occupied) {
        canvas_set_font(canvas, FontSecondary);
        canvas_draw_str(canvas, 5, 30, "[Empty Slot]");
        canvas_set_font(canvas, FontKeyboard);
        canvas_draw_str(canvas, 5, 50, "OK:Add CD BACK:Return");
        return;
    }
    
    // CD information
    canvas_set_font(canvas, FontSecondary);
    int32_t y = 22;
    
    // Artist
    canvas_draw_str(canvas, 5, y, "Artist:");
    if(strlen(slot->cd.artist) > 0) {
        canvas_draw_str(canvas, 35, y, slot->cd.artist);
    }
    y += 10;
    
    // Album
    canvas_draw_str(canvas, 5, y, "Album:");
    if(strlen(slot->cd.album) > 0) {
        canvas_draw_str(canvas, 35, y, slot->cd.album);
    }
    y += 10;
    
    // Year
    if(slot->cd.year > 0) {
        char year_str[24];
        snprintf(year_str, sizeof(year_str), "Year: %ld", (long)slot->cd.year);
        canvas_draw_str(canvas, 5, y, year_str);
        y += 10;
    }
    
    // Genre
    if(strlen(slot->cd.genre) > 0) {
        canvas_draw_str(canvas, 5, y, "Genre:");
        canvas_draw_str(canvas, 35, y, slot->cd.genre);
        y += 10;
    }
    
    // Tracks
    if(slot->cd.track_count > 0) {
        char tracks_str[32];
        snprintf(tracks_str, sizeof(tracks_str), "Tracks: %ld", (long)slot->cd.track_count);
        canvas_draw_str(canvas, 5, y, tracks_str);
    }
    
    // Footer
    canvas_set_font(canvas, FontKeyboard);
    canvas_draw_str(canvas, 5, 60, "OK:Edit BACK:Return");
}

// Draw callback
void flipchanger_draw_callback(Canvas* canvas, void* ctx) {
    FlipChangerApp* app = (FlipChangerApp*)ctx;
    
    switch(app->current_view) {
        case VIEW_MAIN_MENU:
            flipchanger_draw_main_menu(canvas, app);
            break;
        case VIEW_SLOT_LIST:
            flipchanger_draw_slot_list(canvas, app);
            break;
        case VIEW_SLOT_DETAILS:
            flipchanger_draw_slot_details(canvas, app);
            break;
        case VIEW_ADD_EDIT_CD:
            // TODO: Implement add/edit view
            flipchanger_draw_slot_details(canvas, app);
            break;
        default:
            canvas_clear(canvas);
            canvas_set_font(canvas, FontPrimary);
            canvas_draw_str(canvas, 5, 30, "Unknown view");
            break;
    }
}

// Navigation functions
void flipchanger_show_main_menu(FlipChangerApp* app) {
    app->current_view = VIEW_MAIN_MENU;
    app->selected_index = 0;
}

void flipchanger_show_slot_list(FlipChangerApp* app) {
    app->current_view = VIEW_SLOT_LIST;
    app->selected_index = 0;
    app->scroll_offset = 0;
}

void flipchanger_show_slot_details(FlipChangerApp* app, int32_t slot_index) {
    app->current_view = VIEW_SLOT_DETAILS;
    app->current_slot_index = slot_index;
}

void flipchanger_show_add_edit(FlipChangerApp* app, int32_t slot_index, bool is_new) {
    UNUSED(is_new);
    app->current_view = VIEW_ADD_EDIT_CD;
    app->current_slot_index = slot_index;
    // TODO: Implement add/edit functionality
}

// Input callback
void flipchanger_input_callback(InputEvent* input_event, void* ctx) {
    FlipChangerApp* app = (FlipChangerApp*)ctx;
    
    if(input_event->type != InputTypePress) {
        return;
    }
    
    switch(app->current_view) {
        case VIEW_MAIN_MENU:
            if(input_event->key == InputKeyUp) {
                app->selected_index = (app->selected_index + 3) % 4;  // Wrap around
            } else if(input_event->key == InputKeyDown) {
                app->selected_index = (app->selected_index + 1) % 4;
            } else if(input_event->key == InputKeyOk) {
                switch(app->selected_index) {
                    case 0:  // View Slots
                        flipchanger_show_slot_list(app);
                        break;
                    case 1:  // Add CD
                        flipchanger_show_slot_list(app);  // Show slots first to select
                        break;
                    case 2:  // Statistics
                        // TODO: Show statistics
                        break;
                    case 3:  // Settings
                        // TODO: Show settings
                        break;
                }
            } else if(input_event->key == InputKeyBack) {
                app->running = false;
            }
            break;
            
        case VIEW_SLOT_LIST:
            if(input_event->key == InputKeyUp) {
                if(app->selected_index > 0) {
                    app->selected_index--;
                    // Auto-scroll
                    if(app->selected_index < app->scroll_offset) {
                        app->scroll_offset = app->selected_index;
                    }
                }
            } else if(input_event->key == InputKeyDown) {
                if(app->selected_index < app->total_slots - 1) {
                    app->selected_index++;
                    // Auto-scroll
                    if(app->selected_index >= app->scroll_offset + 5) {
                        app->scroll_offset = app->selected_index - 4;
                    }
                }
            } else if(input_event->key == InputKeyOk) {
                flipchanger_show_slot_details(app, app->selected_index);
            } else if(input_event->key == InputKeyBack) {
                flipchanger_show_main_menu(app);
            }
            break;
            
        case VIEW_SLOT_DETAILS:
            if(input_event->key == InputKeyOk) {
                // If empty, go to add. If occupied, go to edit
                if(!app->slots[app->current_slot_index].occupied) {
                    flipchanger_show_add_edit(app, app->current_slot_index, true);
                } else {
                    flipchanger_show_add_edit(app, app->current_slot_index, false);
                }
            } else if(input_event->key == InputKeyBack) {
                flipchanger_show_slot_list(app);
            }
            break;
            
        case VIEW_ADD_EDIT_CD:
            // TODO: Handle add/edit input
            if(input_event->key == InputKeyBack) {
                flipchanger_show_slot_details(app, app->current_slot_index);
            }
            break;
            
        default:
            break;
    }
    
    view_port_update(app->view_port);
}

// Main entry point
int32_t flipchanger_main(void* p) {
    UNUSED(p);
    
    // Allocate app structure
    FlipChangerApp* app = malloc(sizeof(FlipChangerApp));
    memset(app, 0, sizeof(FlipChangerApp));
    
    // Initialize services
    app->gui = furi_record_open(RECORD_GUI);
    app->storage = furi_record_open(RECORD_STORAGE);
    app->notifications = furi_record_open(RECORD_NOTIFICATION);
    app->running = true;
    app->dirty = false;
    
    // Create view port
    app->view_port = view_port_alloc();
    view_port_draw_callback_set(app->view_port, flipchanger_draw_callback, app);
    view_port_input_callback_set(app->view_port, flipchanger_input_callback, app);
    
    // Attach view port to GUI
    gui_add_view_port(app->gui, app->view_port, GuiLayerFullscreen);
    
    // Load data
    flipchanger_load_data(app);
    
    // Send notification that app started
    notification_message(app->notifications, &sequence_blink_green_100);
    
    // Start with main menu
    flipchanger_show_main_menu(app);
    view_port_update(app->view_port);
    
    // Main event loop
    while(app->running) {
        furi_delay_ms(100);
    }
    
    // Save data if dirty
    if(app->dirty) {
        flipchanger_save_data(app);
    }
    
    // Cleanup
    gui_remove_view_port(app->gui, app->view_port);
    view_port_free(app->view_port);
    furi_record_close(RECORD_GUI);
    furi_record_close(RECORD_STORAGE);
    furi_record_close(RECORD_NOTIFICATION);
    free(app);
    
    return 0;
}

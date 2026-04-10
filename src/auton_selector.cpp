// #include "auton_selector.hpp"

// #include <cstdint>

// #include "liblvgl/lvgl.h"

// namespace {
// struct SelectorState {
//   bool initialized = false;
//   int selected_index = 0;
//   lv_obj_t* screen = nullptr;
//   lv_obj_t* count_label = nullptr;
//   lv_obj_t* selected_id_label = nullptr;
//   lv_obj_t* default_label = nullptr;
//   lv_obj_t* detail_title = nullptr;
//   lv_obj_t* detail_body = nullptr;
//   lv_obj_t* footer_label = nullptr;
//   std::vector<lv_obj_t*> buttons;
// };

// SelectorState selector;

// lv_style_t panel_style;
// lv_style_t card_style;
// lv_style_t card_selected_style;
// bool styles_ready = false;

// const AutonEntry& empty_auton() {
//   static const AutonEntry fallback{
//       "No Autonomous",
//       "No autonomous routines are registered yet.",
//       nullptr,
//       false,
//   };
//   return fallback;
// }

// int default_index() {
//   const auto& autons = auton_entries();
//   for (std::size_t i = 0; i < autons.size(); ++i) {
//     if (autons[i].is_default) return static_cast<int>(i);
//   }
//   return 0;
// }

// void ensure_styles() {
//   if (styles_ready) return;

//   lv_style_init(&panel_style);
//   lv_style_set_radius(&panel_style, 20);
//   lv_style_set_bg_opa(&panel_style, LV_OPA_COVER);
//   lv_style_set_bg_color(&panel_style, lv_color_hex(0x111827));
//   lv_style_set_bg_grad_color(&panel_style, lv_color_hex(0x1f2937));
//   lv_style_set_bg_grad_dir(&panel_style, LV_GRAD_DIR_VER);
//   lv_style_set_border_width(&panel_style, 1);
//   lv_style_set_border_color(&panel_style, lv_color_hex(0x334155));
//   lv_style_set_shadow_width(&panel_style, 18);
//   lv_style_set_shadow_color(&panel_style, lv_color_hex(0x020617));
//   lv_style_set_shadow_opa(&panel_style, LV_OPA_40);

//   lv_style_init(&card_style);
//   lv_style_set_radius(&card_style, 16);
//   lv_style_set_bg_opa(&card_style, LV_OPA_COVER);
//   lv_style_set_bg_color(&card_style, lv_color_hex(0x0f172a));
//   lv_style_set_border_width(&card_style, 1);
//   lv_style_set_border_color(&card_style, lv_color_hex(0x273449));
//   lv_style_set_text_color(&card_style, lv_color_hex(0xe2e8f0));
//   lv_style_set_pad_all(&card_style, 12);
//   lv_style_set_shadow_width(&card_style, 0);

//   lv_style_init(&card_selected_style);
//   lv_style_set_bg_opa(&card_selected_style, LV_OPA_COVER);
//   lv_style_set_bg_color(&card_selected_style, lv_color_hex(0x9f1239));
//   lv_style_set_bg_grad_color(&card_selected_style, lv_color_hex(0xea580c));
//   lv_style_set_bg_grad_dir(&card_selected_style, LV_GRAD_DIR_HOR);
//   lv_style_set_border_width(&card_selected_style, 0);
//   lv_style_set_text_color(&card_selected_style, lv_color_hex(0xfff7ed));
//   lv_style_set_shadow_width(&card_selected_style, 16);
//   lv_style_set_shadow_color(&card_selected_style, lv_color_hex(0x7c2d12));
//   lv_style_set_shadow_opa(&card_selected_style, LV_OPA_60);

//   styles_ready = true;
// }

// void update_button_styles() {
//   for (std::size_t i = 0; i < selector.buttons.size(); ++i) {
//     auto* button = selector.buttons[i];
//     lv_obj_remove_style(button, &card_selected_style, LV_PART_MAIN);
//     if (static_cast<int>(i) == selector.selected_index) {
//       lv_obj_add_style(button, &card_selected_style, LV_PART_MAIN);
//       lv_obj_scroll_to_view(button, LV_ANIM_ON);
//     }
//   }
// }

// void update_detail_panel() {
//   const auto& autons = auton_entries();
//   const bool has_autons = !autons.empty();
//   const auto& selected = has_autons ? autons[selector.selected_index] : empty_auton();

//   lv_label_set_text_fmt(selector.count_label,
//                         "%d routines",
//                         static_cast<int>(has_autons ? autons.size() : 0));
//   lv_label_set_text_fmt(selector.selected_id_label,
//                         "AUTO %02d",
//                         selector.selected_index + 1);
//   lv_label_set_text(selector.detail_title, selected.name);
//   lv_label_set_text(selector.detail_body, selected.description);

//   if (selected.is_default) {
//     lv_label_set_text(selector.default_label, "Default selection");
//   } else {
//     lv_label_set_text(selector.default_label, "Tap any card to change");
//   }

//   lv_label_set_text_fmt(selector.footer_label,
//                         "Selected: %s",
//                         selected.name);

//   update_button_styles();
// }

// void select_auton(int index) {
//   const auto& autons = auton_entries();
//   if (!autons.empty()) {
//     if (index < 0 || index >= static_cast<int>(autons.size())) return;
//     selector.selected_index = index;
//   } else {
//     selector.selected_index = 0;
//   }

//   if (selector.initialized) update_detail_panel();
// }

// void handle_select(lv_event_t* event) {
//   const auto index = static_cast<int>(
//       reinterpret_cast<std::uintptr_t>(lv_event_get_user_data(event)));
//   select_auton(index);
// }

// lv_obj_t* make_chip(lv_obj_t* parent, const char* text, lv_color_t bg, lv_color_t fg) {
//   auto* chip = lv_label_create(parent);
//   lv_obj_set_style_radius(chip, LV_RADIUS_CIRCLE, 0);
//   lv_obj_set_style_bg_color(chip, bg, 0);
//   lv_obj_set_style_bg_opa(chip, LV_OPA_COVER, 0);
//   lv_obj_set_style_text_color(chip, fg, 0);
//   lv_obj_set_style_text_font(chip, &lv_font_montserrat_14, 0);
//   lv_obj_set_style_pad_hor(chip, 12, 0);
//   lv_obj_set_style_pad_ver(chip, 6, 0);
//   lv_label_set_text(chip, text);
//   return chip;
// }

// void build_selector_screen() {
//   ensure_styles();

//   selector.screen = lv_obj_create(nullptr);
//   lv_obj_remove_style_all(selector.screen);
//   lv_obj_clear_flag(selector.screen, LV_OBJ_FLAG_SCROLLABLE);
//   lv_obj_set_style_bg_opa(selector.screen, LV_OPA_COVER, 0);
//   lv_obj_set_style_bg_color(selector.screen, lv_color_hex(0x050816), 0);
//   lv_obj_set_style_bg_grad_color(selector.screen, lv_color_hex(0x131a2b), 0);
//   lv_obj_set_style_bg_grad_dir(selector.screen, LV_GRAD_DIR_VER, 0);

//   auto* glow_left = lv_obj_create(selector.screen);
//   lv_obj_remove_style_all(glow_left);
//   lv_obj_set_size(glow_left, 190, 190);
//   lv_obj_set_style_radius(glow_left, LV_RADIUS_CIRCLE, 0);
//   lv_obj_set_style_bg_color(glow_left, lv_color_hex(0xbe123c), 0);
//   lv_obj_set_style_bg_opa(glow_left, LV_OPA_20, 0);
//   lv_obj_align(glow_left, LV_ALIGN_TOP_LEFT, -50, -50);

//   auto* glow_right = lv_obj_create(selector.screen);
//   lv_obj_remove_style_all(glow_right);
//   lv_obj_set_size(glow_right, 220, 220);
//   lv_obj_set_style_radius(glow_right, LV_RADIUS_CIRCLE, 0);
//   lv_obj_set_style_bg_color(glow_right, lv_color_hex(0xfb923c), 0);
//   lv_obj_set_style_bg_opa(glow_right, LV_OPA_20, 0);
//   lv_obj_align(glow_right, LV_ALIGN_BOTTOM_RIGHT, 60, 70);

//   auto* shell = lv_obj_create(selector.screen);
//   lv_obj_add_style(shell, &panel_style, LV_PART_MAIN);
//   lv_obj_clear_flag(shell, LV_OBJ_FLAG_SCROLLABLE);
//   lv_obj_set_size(shell, 458, 218);
//   lv_obj_center(shell);
//   lv_obj_set_style_pad_all(shell, 14, 0);

//   auto* header = lv_obj_create(shell);
//   lv_obj_remove_style_all(header);
//   lv_obj_clear_flag(header, LV_OBJ_FLAG_SCROLLABLE);
//   lv_obj_set_size(header, lv_pct(100), 46);
//   lv_obj_set_flex_flow(header, LV_FLEX_FLOW_ROW);
//   lv_obj_set_flex_align(header, LV_FLEX_ALIGN_SPACE_BETWEEN, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);

//   auto* title_block = lv_obj_create(header);
//   lv_obj_remove_style_all(title_block);
//   lv_obj_clear_flag(title_block, LV_OBJ_FLAG_SCROLLABLE);
//   lv_obj_set_flex_flow(title_block, LV_FLEX_FLOW_COLUMN);

//   auto* title = lv_label_create(title_block);
//   lv_obj_set_style_text_font(title, &lv_font_montserrat_22, 0);
//   lv_obj_set_style_text_color(title, lv_color_hex(0xf8fafc), 0);
//   lv_label_set_text(title, "47510B Autonomous");

//   auto* subtitle = lv_label_create(title_block);
//   lv_obj_set_style_text_font(subtitle, &lv_font_montserrat_12, 0);
//   lv_obj_set_style_text_color(subtitle, lv_color_hex(0x94a3b8), 0);
//   lv_label_set_text(subtitle, "Select a route on the left before the match starts.");

//   auto* chip_row = lv_obj_create(header);
//   lv_obj_remove_style_all(chip_row);
//   lv_obj_clear_flag(chip_row, LV_OBJ_FLAG_SCROLLABLE);
//   lv_obj_set_flex_flow(chip_row, LV_FLEX_FLOW_ROW);
//   lv_obj_set_style_pad_column(chip_row, 8, 0);

//   selector.count_label = make_chip(chip_row,
//                                    "0 routines",
//                                    lv_color_hex(0x172033),
//                                    lv_color_hex(0xcbd5e1));
//   selector.selected_id_label = make_chip(chip_row,
//                                          "AUTO 01",
//                                          lv_color_hex(0x7f1d1d),
//                                          lv_color_hex(0xffedd5));

//   auto* body = lv_obj_create(shell);
//   lv_obj_remove_style_all(body);
//   lv_obj_clear_flag(body, LV_OBJ_FLAG_SCROLLABLE);
//   lv_obj_set_size(body, lv_pct(100), 136);
//   lv_obj_align(body, LV_ALIGN_TOP_LEFT, 0, 54);
//   lv_obj_set_flex_flow(body, LV_FLEX_FLOW_ROW);
//   lv_obj_set_style_pad_column(body, 12, 0);

//   auto* list_panel = lv_obj_create(body);
//   lv_obj_add_style(list_panel, &panel_style, LV_PART_MAIN);
//   lv_obj_set_size(list_panel, 196, lv_pct(100));
//   lv_obj_set_style_pad_all(list_panel, 10, 0);
//   lv_obj_set_style_shadow_width(list_panel, 0, 0);

//   auto* list_header = lv_label_create(list_panel);
//   lv_obj_set_style_text_font(list_header, &lv_font_montserrat_14, 0);
//   lv_obj_set_style_text_color(list_header, lv_color_hex(0xf8fafc), 0);
//   lv_label_set_text(list_header, "ROUTES");

//   auto* list = lv_obj_create(list_panel);
//   lv_obj_remove_style_all(list);
//   lv_obj_set_size(list, lv_pct(100), 96);
//   lv_obj_align(list, LV_ALIGN_BOTTOM_MID, 0, 0);
//   lv_obj_set_flex_flow(list, LV_FLEX_FLOW_COLUMN);
//   lv_obj_set_style_pad_row(list, 8, 0);
//   lv_obj_set_scroll_dir(list, LV_DIR_VER);
//   lv_obj_set_scrollbar_mode(list, LV_SCROLLBAR_MODE_OFF);

//   auto* detail_panel = lv_obj_create(body);
//   lv_obj_add_style(detail_panel, &panel_style, LV_PART_MAIN);
//   lv_obj_set_size(detail_panel, 236, lv_pct(100));
//   lv_obj_set_style_pad_all(detail_panel, 14, 0);
//   lv_obj_set_style_shadow_width(detail_panel, 0, 0);

//   selector.default_label = make_chip(detail_panel,
//                                      "Tap any card to change",
//                                      lv_color_hex(0x172033),
//                                      lv_color_hex(0xcbd5e1));
//   lv_obj_align(selector.default_label, LV_ALIGN_TOP_LEFT, 0, 0);

//   selector.detail_title = lv_label_create(detail_panel);
//   lv_obj_set_width(selector.detail_title, lv_pct(100));
//   lv_obj_set_style_text_font(selector.detail_title, &lv_font_montserrat_18, 0);
//   lv_obj_set_style_text_color(selector.detail_title, lv_color_hex(0xf8fafc), 0);
//   lv_label_set_long_mode(selector.detail_title, LV_LABEL_LONG_WRAP);
//   lv_obj_align(selector.detail_title, LV_ALIGN_TOP_LEFT, 0, 34);

//   selector.detail_body = lv_label_create(detail_panel);
//   lv_obj_set_width(selector.detail_body, lv_pct(100));
//   lv_obj_set_style_text_font(selector.detail_body, &lv_font_montserrat_14, 0);
//   lv_obj_set_style_text_color(selector.detail_body, lv_color_hex(0xcbd5e1), 0);
//   lv_label_set_long_mode(selector.detail_body, LV_LABEL_LONG_WRAP);
//   lv_obj_align(selector.detail_body, LV_ALIGN_TOP_LEFT, 0, 72);

//   auto* footer = lv_obj_create(shell);
//   lv_obj_remove_style_all(footer);
//   lv_obj_clear_flag(footer, LV_OBJ_FLAG_SCROLLABLE);
//   lv_obj_set_size(footer, lv_pct(100), 20);
//   lv_obj_align(footer, LV_ALIGN_BOTTOM_LEFT, 0, 0);

//   selector.footer_label = lv_label_create(footer);
//   lv_obj_set_style_text_font(selector.footer_label, &lv_font_montserrat_12, 0);
//   lv_obj_set_style_text_color(selector.footer_label, lv_color_hex(0x94a3b8), 0);
//   lv_label_set_text(selector.footer_label, "Selected: ");

//   selector.buttons.clear();
//   const auto& autons = auton_entries();
//   if (autons.empty()) {
//     auto* empty = lv_obj_create(list);
//     lv_obj_add_style(empty, &card_style, LV_PART_MAIN);
//     lv_obj_clear_flag(empty, LV_OBJ_FLAG_SCROLLABLE);
//     lv_obj_set_width(empty, lv_pct(100));

//     auto* empty_label = lv_label_create(empty);
//     lv_obj_set_width(empty_label, lv_pct(100));
//     lv_label_set_long_mode(empty_label, LV_LABEL_LONG_WRAP);
//     lv_label_set_text(empty_label, "Add entries in autons.cpp to populate the selector.");
//   } else {
//     for (std::size_t i = 0; i < autons.size(); ++i) {
//       auto* button = lv_btn_create(list);
//       lv_obj_add_style(button, &card_style, LV_PART_MAIN);
//       lv_obj_clear_flag(button, LV_OBJ_FLAG_SCROLLABLE);
//       lv_obj_set_width(button, lv_pct(100));
//       lv_obj_set_style_pad_all(button, 10, 0);
//       lv_obj_add_event_cb(button,
//                           handle_select,
//                           LV_EVENT_CLICKED,
//                           reinterpret_cast<void*>(static_cast<std::uintptr_t>(i)));

//       auto* row = lv_obj_create(button);
//       lv_obj_remove_style_all(row);
//       lv_obj_clear_flag(row, LV_OBJ_FLAG_SCROLLABLE);
//       lv_obj_set_width(row, lv_pct(100));
//       lv_obj_set_flex_flow(row, LV_FLEX_FLOW_ROW);
//       lv_obj_set_flex_align(row, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);
//       lv_obj_set_style_pad_column(row, 10, 0);

//       auto* number = lv_label_create(row);
//       lv_obj_set_style_text_font(number, &lv_font_montserrat_14, 0);
//       lv_obj_set_style_text_color(number, lv_color_hex(0xfda4af), 0);
//       lv_label_set_text_fmt(number, "%02d", static_cast<int>(i + 1));

//       auto* name = lv_label_create(row);
//       lv_obj_set_width(name, 130);
//       lv_obj_set_style_text_font(name, &lv_font_montserrat_14, 0);
//       lv_label_set_long_mode(name, LV_LABEL_LONG_WRAP);
//       lv_label_set_text(name, autons[i].name);

//       selector.buttons.push_back(button);
//     }
//   }

//   selector.initialized = true;
//   selector.selected_index = default_index();
//   update_detail_panel();
// }
// }  // namespace

// void auton_selector_initialize() {
//   if (!selector.initialized) build_selector_screen();
//   auton_selector_show();
// }

// void auton_selector_show() {
//   if (!selector.initialized) build_selector_screen();

//   update_detail_panel();
//   if (lv_scr_act() != selector.screen) {
//     lv_scr_load_anim(selector.screen, LV_SCR_LOAD_ANIM_FADE_ON, 250, 0, false);
//   }
// }

// void auton_selector_run_selected() {
//   const auto& autons = auton_entries();
//   if (autons.empty()) return;

//   const auto& selected = autons[selector.selected_index];
//   if (selector.initialized) {
//     lv_label_set_text_fmt(selector.footer_label, "Running: %s", selected.name);
//   }

//   if (selected.routine != nullptr) selected.routine();
// }

// const AutonEntry& auton_selector_selected() {
//   const auto& autons = auton_entries();
//   if (autons.empty()) return empty_auton();
//   return autons[selector.selected_index];
// }

// bool auton_selector_is_active() {
//   return selector.initialized;
// }

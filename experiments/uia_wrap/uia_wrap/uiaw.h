#pragma once
#include <optional>

namespace uia {

//
// Enumerations
//
enum class tree_scope {
	none = 0x0,
	element = 0x1,
	children = 0x2,
	descendants = 0x4,
	parent = 0x8,
	ancestors = 0x10,
	subtree = 0x7,
};

enum class pattern_id {
	invoke_pattern = 10000,
	selection_pattern = 10001,
	value_pattern = 10002,
	range_value_pattern = 10003,
	scroll_pattern = 10004,
	expand_collapse_pattern = 10005,
	grid_pattern = 10006,
	grid_item_pattern = 10007,
	multiple_view_pattern = 10008,
	window_pattern = 10009,
	selection_item_pattern = 10010,
	dock_pattern = 10011,
	table_pattern = 10012,
	table_item_pattern = 10013,
	text_pattern = 10014,
	toggle_pattern = 10015,
	transform_pattern = 10016,
	scroll_item_pattern = 10017,
	legacy_i_accessible_pattern = 10018,
	item_container_pattern = 10019,
	virtualized_item_pattern = 10020,
	synchronized_input_pattern = 10021,
	object_model_pattern = 10022,
	annotation_pattern = 10023,
	text_pattern2 = 10024,
	styles_pattern = 10025,
	spreadsheet_pattern = 10026,
	spreadsheet_item_pattern = 10027,
	transform_pattern2 = 10028,
	text_child_pattern = 10029,
	drag_pattern = 10030,
	drop_target_pattern = 10031,
	text_edit_pattern = 10032,
	custom_navigation_pattern = 10033,
	selection_pattern2 = 10034
};

enum class property_id {
	runtime_id_property_id = 30000,
	bounding_rectangle_property_id = 30001,
	process_id_property_id = 30002,
	control_type_property_id = 30003,
	localized_control_type_property_id = 30004,
	name_property_id = 30005,
	accelerator_key_property_id = 30006,
	access_key_property_id = 30007,
	has_keyboard_focus_property_id = 30008,
	is_keyboard_focusable_property_id = 30009,
	is_enabled_property_id = 30010,
	automation_id_property_id = 30011,
	class_name_property_id = 30012,
	help_text_property_id = 30013,
	clickable_point_property_id = 30014,
	culture_property_id = 30015,
	is_control_element_property_id = 30016,
	is_content_element_property_id = 30017,
	labeled_by_property_id = 30018,
	is_password_property_id = 30019,
	native_window_handle_property_id = 30020,
	item_type_property_id = 30021,
	is_offscreen_property_id = 30022,
	orientation_property_id = 30023,
	framework_id_property_id = 30024,
	is_required_for_form_property_id = 30025,
	item_status_property_id = 30026,
	is_dock_pattern_available_property_id = 30027,
	is_expand_collapse_pattern_available_property_id= 30028,
	is_grid_item_pattern_available_property_id = 30029,
	is_grid_pattern_available_property_id = 30030,
	is_invoke_pattern_available_property_id = 30031,
	is_multiple_view_pattern_available_property_id = 30032,
	is_range_value_pattern_available_property_id = 30033,
	is_scroll_pattern_available_property_id = 30034,
	is_scroll_item_pattern_available_property_id = 30035,
	is_selection_item_pattern_available_property_id = 30036,
	is_selection_pattern_available_property_id = 30037,
	is_table_pattern_available_property_id = 30038,
	is_table_item_pattern_available_property_id = 30039,
	is_text_pattern_available_property_id = 30040,
	is_toggle_pattern_available_property_id = 30041,
	is_transform_pattern_available_property_id = 30042,
	is_value_pattern_available_property_id = 30043,
	is_window_pattern_available_property_id = 30044,
	value_value_property_id = 30045,
	value_is_read_only_property_id = 30046,
	range_value_value_property_id = 30047,
	range_value_is_read_only_property_id = 30048,
	range_value_minimum_property_id = 30049,
	range_value_maximum_property_id = 30050,
	range_value_large_change_property_id = 30051,
	range_value_small_change_property_id = 30052,
	scroll_horizontal_scroll_percent_property_id = 30053,
	scroll_horizontal_view_size_property_id = 30054,
	scroll_vertical_scroll_percent_property_id = 30055,
	scroll_vertical_view_size_property_id = 30056,
	scroll_horizontally_scrollable_property_id = 30057,
	scroll_vertically_scrollable_property_id = 30058,
	selection_selection_property_id = 30059,
	selection_can_select_multiple_property_id = 30060,
	selection_is_selection_required_property_id = 30061,
	grid_row_count_property_id = 30062,
	grid_column_count_property_id = 30063,
	grid_item_row_property_id = 30064,
	grid_item_column_property_id = 30065,
	grid_item_row_span_property_id = 30066,
	grid_item_column_span_property_id = 30067,
	grid_item_containing_grid_property_id = 30068,
	dock_dock_position_property_id = 30069,
	expand_collapse_expand_collapse_state_property_id=30070,
	multiple_view_current_view_property_id = 30071,
	multiple_view_supported_views_property_id = 30072,
	window_can_maximize_property_id = 30073,
	window_can_minimize_property_id = 30074,
	window_window_visual_state_property_id = 30075,
	window_window_interaction_state_property_id = 30076,
	window_is_modal_property_id = 30077,
	window_is_topmost_property_id = 30078,
	selection_item_is_selected_property_id = 30079,
	selection_item_selection_container_property_id = 30080,
	table_row_headers_property_id = 30081,
	table_column_headers_property_id = 30082,
	table_row_or_column_major_property_id = 30083,
	table_item_row_header_items_property_id = 30084,
	table_item_column_header_items_property_id = 30085,
	toggle_toggle_state_property_id = 30086,
	transform_can_move_property_id = 30087,
	transform_can_resize_property_id = 30088,
	transform_can_rotate_property_id = 30089,
	is_legacy_i_accessible_pattern_available_property_id=30090,
	legacy_i_accessible_child_id_property_id = 30091,
	legacy_i_accessible_name_property_id = 30092,
	legacy_i_accessible_value_property_id = 30093,
	legacy_i_accessible_description_property_id = 30094,
	legacy_i_accessible_role_property_id = 30095,
	legacy_i_accessible_state_property_id = 30096,
	legacy_i_accessible_help_property_id = 30097,
	legacy_i_accessible_keyboard_shortcut_property_id=30098,
	legacy_i_accessible_selection_property_id = 30099,
	legacy_i_accessible_default_action_property_id = 30100,
	aria_role_property_id = 30101,
	aria_properties_property_id = 30102,
	is_data_valid_for_form_property_id = 30103,
	controller_for_property_id = 30104,
	described_by_property_id = 30105,
	flows_to_property_id = 30106,
	provider_description_property_id = 30107,
	is_item_container_pattern_available_property_id = 30108,
	is_virtualized_item_pattern_available_property_id=30109,
	is_synchronized_input_pattern_available_property_id=30110,
	optimize_for_visual_content_property_id = 30111,
	is_object_model_pattern_available_property_id = 30112,
	annotation_annotation_type_id_property_id = 30113,
	annotation_annotation_type_name_property_id = 30114,
	annotation_author_property_id = 30115,
	annotation_date_time_property_id = 30116,
	annotation_target_property_id = 30117,
	is_annotation_pattern_available_property_id = 30118,
	is_text_pattern2_available_property_id = 30119,
	styles_style_id_property_id = 30120,
	styles_style_name_property_id = 30121,
	styles_fill_color_property_id = 30122,
	styles_fill_pattern_style_property_id = 30123,
	styles_shape_property_id = 30124,
	styles_fill_pattern_color_property_id = 30125,
	styles_extended_properties_property_id = 30126,
	is_styles_pattern_available_property_id = 30127,
	is_spreadsheet_pattern_available_property_id = 30128,
	spreadsheet_item_formula_property_id = 30129,
	spreadsheet_item_annotation_objects_property_id = 30130,
	spreadsheet_item_annotation_types_property_id = 30131,
	is_spreadsheet_item_pattern_available_property_id=30132,
	transform2_can_zoom_property_id = 30133,
	is_transform_pattern2_available_property_id = 30134,
	live_setting_property_id = 30135,
	is_text_child_pattern_available_property_id = 30136,
	is_drag_pattern_available_property_id = 30137,
	drag_is_grabbed_property_id = 30138,
	drag_drop_effect_property_id = 30139,
	drag_drop_effects_property_id = 30140,
	is_drop_target_pattern_available_property_id = 30141,
	drop_target_drop_target_effect_property_id = 30142,
	drop_target_drop_target_effects_property_id = 30143,
	drag_grabbed_items_property_id = 30144,
	transform2_zoom_level_property_id = 30145,
	transform2_zoom_minimum_property_id = 30146,
	transform2_zoom_maximum_property_id = 30147,
	flows_from_property_id = 30148,
	is_text_edit_pattern_available_property_id = 30149,
	is_peripheral_property_id = 30150,
	is_custom_navigation_pattern_available_property_id=30151,
	position_in_set_property_id = 30152,
	size_of_set_property_id = 30153,
	level_property_id = 30154,
	annotation_types_property_id = 30155,
	annotation_objects_property_id = 30156,
	landmark_type_property_id = 30157,
	localized_landmark_type_property_id = 30158,
	full_description_property_id = 30159,
	fill_color_property_id = 30160,
	outline_color_property_id = 30161,
	fill_type_property_id = 30162,
	visual_effects_property_id = 30163,
	outline_thickness_property_id = 30164,
	center_point_property_id = 30165,
	rotation_property_id = 30166,
	size_property_id = 30167,
	is_selection_pattern2_available_property_id = 30168,
	selection2_first_selected_item_property_id = 30169,
	selection2_last_selected_item_property_id = 30170,
	selection2_current_selected_item_property_id = 30171,
	selection2_item_count_property_id = 30172,
	heading_level_property_id = 30173,
	is_dialog_property_id = 30174
};


enum class automation_element_mode {
	none = 0,
	full = 1
};



class uiautomation_element;
class uiautomation;

//
//
//
class condition {};


//
//
//
class uiautomation_element {
	void* p_ {};  // An IUIAutomationElement object
	
	explicit uiautomation_element(void*);
public:
	~uiautomation_element();

	friend class uiautomation;
};

//
// Exposes properties and methods of a cache request. Client applications use this interface to specify the
// properties and control patterns to be cached when a Microsoft UI Automation element is obtained.
//
class cache_request {
	void* p_ {};  // IUIAutomationCacheRequest
	explicit cache_request(void*);
public:
	~cache_request();

	bool add_pattern(pattern_id);
	bool add_property(property_id);
	std::optional<cache_request> clone();
	std::optional<automation_element_mode> get_automation_element_mode();
	std::optional<condition> get_tree_filter();

	friend class uiautomation;
};


//
// The CUIAutomation object (IUIAUtomation*)
//
class uiautomation {
	void* p_ {};  // The CUIAutomation object (IUIAUtomation*)

	explicit uiautomation(void*);
public:
	static uiautomation create();

	std::optional<uiautomation_element> get_root_element();
	std::optional<uiautomation_element> get_focused_element();

	//bool add_structure_changed_event_handler(uiautomation_element, , tree_scope, cache_request, structure_changed_event_handler);

	std::optional<cache_request> create_cache_request();

	~uiautomation();
};














}  // namespace uia

#include "uiaw.h"
#include <UIAutomation.h>
#include <UIAutomationClient.h>
#include <cstdint>


//
// Enumerations
//

TreeScope get_native(uia::tree_scope ts) {
	static_assert(static_cast<uint64_t>(uia::tree_scope::none) == static_cast<uint64_t>(TreeScope::TreeScope_None));
	static_assert(static_cast<uint64_t>(uia::tree_scope::element) == static_cast<uint64_t>(TreeScope::TreeScope_Element));
	static_assert(static_cast<uint64_t>(uia::tree_scope::children) == static_cast<uint64_t>(TreeScope::TreeScope_Children));
	static_assert(static_cast<uint64_t>(uia::tree_scope::descendants) == static_cast<uint64_t>(TreeScope::TreeScope_Descendants));
	static_assert(static_cast<uint64_t>(uia::tree_scope::parent) == static_cast<uint64_t>(TreeScope::TreeScope_Parent));
	static_assert(static_cast<uint64_t>(uia::tree_scope::ancestors) == static_cast<uint64_t>(TreeScope::TreeScope_Ancestors));
	static_assert(static_cast<uint64_t>(uia::tree_scope::subtree) == static_cast<uint64_t>(TreeScope::TreeScope_Subtree));

	return static_cast<TreeScope>(ts);
}

PATTERNID get_native(uia::pattern_id pid) {
	static_assert(static_cast<uint64_t>(uia::pattern_id::invoke_pattern) == UIA_InvokePatternId);
	static_assert(static_cast<uint64_t>(uia::pattern_id::selection_pattern) == UIA_SelectionPatternId);
	static_assert(static_cast<uint64_t>(uia::pattern_id::value_pattern) == UIA_ValuePatternId);
	static_assert(static_cast<uint64_t>(uia::pattern_id::range_value_pattern) == UIA_RangeValuePatternId);
	static_assert(static_cast<uint64_t>(uia::pattern_id::scroll_pattern) == UIA_ScrollPatternId);
	static_assert(static_cast<uint64_t>(uia::pattern_id::expand_collapse_pattern) == UIA_ExpandCollapsePatternId);
	static_assert(static_cast<uint64_t>(uia::pattern_id::grid_pattern) == UIA_GridPatternId);
	static_assert(static_cast<uint64_t>(uia::pattern_id::grid_item_pattern) == UIA_GridItemPatternId);
	static_assert(static_cast<uint64_t>(uia::pattern_id::multiple_view_pattern) == UIA_MultipleViewPatternId);
	static_assert(static_cast<uint64_t>(uia::pattern_id::window_pattern) == UIA_WindowPatternId);
	static_assert(static_cast<uint64_t>(uia::pattern_id::selection_item_pattern) == UIA_SelectionItemPatternId);
	static_assert(static_cast<uint64_t>(uia::pattern_id::dock_pattern) == UIA_DockPatternId);
	static_assert(static_cast<uint64_t>(uia::pattern_id::table_pattern) == UIA_TablePatternId);
	static_assert(static_cast<uint64_t>(uia::pattern_id::table_item_pattern) == UIA_TableItemPatternId);
	static_assert(static_cast<uint64_t>(uia::pattern_id::text_pattern) == UIA_TextPatternId);
	static_assert(static_cast<uint64_t>(uia::pattern_id::toggle_pattern) == UIA_TogglePatternId);
	static_assert(static_cast<uint64_t>(uia::pattern_id::transform_pattern) == UIA_TransformPatternId);
	static_assert(static_cast<uint64_t>(uia::pattern_id::scroll_item_pattern) == UIA_ScrollItemPatternId);
	static_assert(static_cast<uint64_t>(uia::pattern_id::legacy_i_accessible_pattern) == UIA_LegacyIAccessiblePatternId);
	static_assert(static_cast<uint64_t>(uia::pattern_id::item_container_pattern) == UIA_ItemContainerPatternId);
	static_assert(static_cast<uint64_t>(uia::pattern_id::virtualized_item_pattern) == UIA_VirtualizedItemPatternId);
	static_assert(static_cast<uint64_t>(uia::pattern_id::synchronized_input_pattern) == UIA_SynchronizedInputPatternId);
	static_assert(static_cast<uint64_t>(uia::pattern_id::object_model_pattern) == UIA_ObjectModelPatternId);
	static_assert(static_cast<uint64_t>(uia::pattern_id::annotation_pattern) == UIA_AnnotationPatternId);
	static_assert(static_cast<uint64_t>(uia::pattern_id::text_pattern2) == UIA_TextPattern2Id);
	static_assert(static_cast<uint64_t>(uia::pattern_id::styles_pattern) == UIA_StylesPatternId);
	static_assert(static_cast<uint64_t>(uia::pattern_id::spreadsheet_pattern) == UIA_SpreadsheetPatternId);
	static_assert(static_cast<uint64_t>(uia::pattern_id::spreadsheet_item_pattern) == UIA_SpreadsheetItemPatternId);
	static_assert(static_cast<uint64_t>(uia::pattern_id::transform_pattern2) == UIA_TransformPattern2Id);
	static_assert(static_cast<uint64_t>(uia::pattern_id::text_child_pattern) == UIA_TextChildPatternId);
	static_assert(static_cast<uint64_t>(uia::pattern_id::drag_pattern) == UIA_DragPatternId);
	static_assert(static_cast<uint64_t>(uia::pattern_id::drop_target_pattern) == UIA_DropTargetPatternId);
	static_assert(static_cast<uint64_t>(uia::pattern_id::text_edit_pattern) == UIA_TextEditPatternId);
	static_assert(static_cast<uint64_t>(uia::pattern_id::custom_navigation_pattern) == UIA_CustomNavigationPatternId);
	static_assert(static_cast<uint64_t>(uia::pattern_id::selection_pattern2) == UIA_SelectionPattern2Id);

	return static_cast<PATTERNID>(pid);
}

PROPERTYID get_native(uia::property_id pid) {
	static_assert(static_cast<uint64_t>(uia::property_id::runtime_id_property_id) == UIA_RuntimeIdPropertyId);
	static_assert(static_cast<uint64_t>(uia::property_id::bounding_rectangle_property_id) == UIA_BoundingRectanglePropertyId);
	static_assert(static_cast<uint64_t>(uia::property_id::process_id_property_id) == UIA_ProcessIdPropertyId);
	static_assert(static_cast<uint64_t>(uia::property_id::control_type_property_id) == UIA_ControlTypePropertyId);
	static_assert(static_cast<uint64_t>(uia::property_id::localized_control_type_property_id) == UIA_LocalizedControlTypePropertyId);
	static_assert(static_cast<uint64_t>(uia::property_id::name_property_id) == UIA_NamePropertyId);
	static_assert(static_cast<uint64_t>(uia::property_id::accelerator_key_property_id) == UIA_AcceleratorKeyPropertyId);
	static_assert(static_cast<uint64_t>(uia::property_id::access_key_property_id) == UIA_AccessKeyPropertyId);
	static_assert(static_cast<uint64_t>(uia::property_id::has_keyboard_focus_property_id) == UIA_HasKeyboardFocusPropertyId);
	static_assert(static_cast<uint64_t>(uia::property_id::is_keyboard_focusable_property_id) == UIA_IsKeyboardFocusablePropertyId);
	static_assert(static_cast<uint64_t>(uia::property_id::is_enabled_property_id) == UIA_IsEnabledPropertyId);
	static_assert(static_cast<uint64_t>(uia::property_id::automation_id_property_id) == UIA_AutomationIdPropertyId);
	static_assert(static_cast<uint64_t>(uia::property_id::class_name_property_id) == UIA_ClassNamePropertyId);
	static_assert(static_cast<uint64_t>(uia::property_id::help_text_property_id) == UIA_HelpTextPropertyId);
	static_assert(static_cast<uint64_t>(uia::property_id::clickable_point_property_id) == UIA_ClickablePointPropertyId);
	static_assert(static_cast<uint64_t>(uia::property_id::culture_property_id) == UIA_CulturePropertyId);
	static_assert(static_cast<uint64_t>(uia::property_id::is_control_element_property_id) == UIA_IsControlElementPropertyId);
	static_assert(static_cast<uint64_t>(uia::property_id::is_content_element_property_id) == UIA_IsContentElementPropertyId);
	static_assert(static_cast<uint64_t>(uia::property_id::labeled_by_property_id) == UIA_LabeledByPropertyId);
	static_assert(static_cast<uint64_t>(uia::property_id::is_password_property_id) == UIA_IsPasswordPropertyId);
	static_assert(static_cast<uint64_t>(uia::property_id::native_window_handle_property_id) == UIA_NativeWindowHandlePropertyId);
	static_assert(static_cast<uint64_t>(uia::property_id::item_type_property_id) == UIA_ItemTypePropertyId);
	static_assert(static_cast<uint64_t>(uia::property_id::is_offscreen_property_id) == UIA_IsOffscreenPropertyId);
	static_assert(static_cast<uint64_t>(uia::property_id::orientation_property_id) == UIA_OrientationPropertyId);
	static_assert(static_cast<uint64_t>(uia::property_id::framework_id_property_id) == UIA_FrameworkIdPropertyId);
	static_assert(static_cast<uint64_t>(uia::property_id::is_required_for_form_property_id) == UIA_IsRequiredForFormPropertyId);
	static_assert(static_cast<uint64_t>(uia::property_id::item_status_property_id) == UIA_ItemStatusPropertyId);
	static_assert(static_cast<uint64_t>(uia::property_id::is_dock_pattern_available_property_id) == UIA_IsDockPatternAvailablePropertyId);
	static_assert(static_cast<uint64_t>(uia::property_id::is_expand_collapse_pattern_available_property_id) == UIA_IsExpandCollapsePatternAvailablePropertyId);
	static_assert(static_cast<uint64_t>(uia::property_id::is_grid_item_pattern_available_property_id) == UIA_IsGridItemPatternAvailablePropertyId);
	static_assert(static_cast<uint64_t>(uia::property_id::is_grid_pattern_available_property_id) == UIA_IsGridPatternAvailablePropertyId);
	static_assert(static_cast<uint64_t>(uia::property_id::is_invoke_pattern_available_property_id) == UIA_IsInvokePatternAvailablePropertyId);
	static_assert(static_cast<uint64_t>(uia::property_id::is_multiple_view_pattern_available_property_id) == UIA_IsMultipleViewPatternAvailablePropertyId);
	static_assert(static_cast<uint64_t>(uia::property_id::is_range_value_pattern_available_property_id) == UIA_IsRangeValuePatternAvailablePropertyId);
	static_assert(static_cast<uint64_t>(uia::property_id::is_scroll_pattern_available_property_id) == UIA_IsScrollPatternAvailablePropertyId);
	static_assert(static_cast<uint64_t>(uia::property_id::is_scroll_item_pattern_available_property_id) == UIA_IsScrollItemPatternAvailablePropertyId);
	static_assert(static_cast<uint64_t>(uia::property_id::is_selection_item_pattern_available_property_id) == UIA_IsSelectionItemPatternAvailablePropertyId);
	static_assert(static_cast<uint64_t>(uia::property_id::is_selection_pattern_available_property_id) == UIA_IsSelectionPatternAvailablePropertyId);
	static_assert(static_cast<uint64_t>(uia::property_id::is_table_pattern_available_property_id) == UIA_IsTablePatternAvailablePropertyId);
	static_assert(static_cast<uint64_t>(uia::property_id::is_table_item_pattern_available_property_id) == UIA_IsTableItemPatternAvailablePropertyId);
	static_assert(static_cast<uint64_t>(uia::property_id::is_text_pattern_available_property_id) == UIA_IsTextPatternAvailablePropertyId);
	static_assert(static_cast<uint64_t>(uia::property_id::is_toggle_pattern_available_property_id) == UIA_IsTogglePatternAvailablePropertyId);
	static_assert(static_cast<uint64_t>(uia::property_id::is_transform_pattern_available_property_id) == UIA_IsTransformPatternAvailablePropertyId);
	static_assert(static_cast<uint64_t>(uia::property_id::is_value_pattern_available_property_id) == UIA_IsValuePatternAvailablePropertyId);
	static_assert(static_cast<uint64_t>(uia::property_id::is_window_pattern_available_property_id) == UIA_IsWindowPatternAvailablePropertyId);
	static_assert(static_cast<uint64_t>(uia::property_id::value_value_property_id) == UIA_ValueValuePropertyId);
	static_assert(static_cast<uint64_t>(uia::property_id::value_is_read_only_property_id) == UIA_ValueIsReadOnlyPropertyId);
	static_assert(static_cast<uint64_t>(uia::property_id::range_value_value_property_id) == UIA_RangeValueValuePropertyId);
	static_assert(static_cast<uint64_t>(uia::property_id::range_value_is_read_only_property_id) == UIA_RangeValueIsReadOnlyPropertyId);
	static_assert(static_cast<uint64_t>(uia::property_id::range_value_minimum_property_id) == UIA_RangeValueMinimumPropertyId);
	static_assert(static_cast<uint64_t>(uia::property_id::range_value_maximum_property_id) == UIA_RangeValueMaximumPropertyId);
	static_assert(static_cast<uint64_t>(uia::property_id::range_value_large_change_property_id) == UIA_RangeValueLargeChangePropertyId);
	static_assert(static_cast<uint64_t>(uia::property_id::range_value_small_change_property_id) == UIA_RangeValueSmallChangePropertyId);
	static_assert(static_cast<uint64_t>(uia::property_id::scroll_horizontal_scroll_percent_property_id) == UIA_ScrollHorizontalScrollPercentPropertyId);
	static_assert(static_cast<uint64_t>(uia::property_id::scroll_horizontal_view_size_property_id) == UIA_ScrollHorizontalViewSizePropertyId);
	static_assert(static_cast<uint64_t>(uia::property_id::scroll_vertical_scroll_percent_property_id) == UIA_ScrollVerticalScrollPercentPropertyId);
	static_assert(static_cast<uint64_t>(uia::property_id::scroll_vertical_view_size_property_id) == UIA_ScrollVerticalViewSizePropertyId);
	static_assert(static_cast<uint64_t>(uia::property_id::scroll_horizontally_scrollable_property_id) == UIA_ScrollHorizontallyScrollablePropertyId);
	static_assert(static_cast<uint64_t>(uia::property_id::scroll_vertically_scrollable_property_id) == UIA_ScrollVerticallyScrollablePropertyId);
	static_assert(static_cast<uint64_t>(uia::property_id::selection_selection_property_id) == UIA_SelectionSelectionPropertyId);
	static_assert(static_cast<uint64_t>(uia::property_id::selection_can_select_multiple_property_id) == UIA_SelectionCanSelectMultiplePropertyId);
	static_assert(static_cast<uint64_t>(uia::property_id::selection_is_selection_required_property_id) == UIA_SelectionIsSelectionRequiredPropertyId);
	static_assert(static_cast<uint64_t>(uia::property_id::grid_row_count_property_id) == UIA_GridRowCountPropertyId);
	static_assert(static_cast<uint64_t>(uia::property_id::grid_column_count_property_id) == UIA_GridColumnCountPropertyId);
	static_assert(static_cast<uint64_t>(uia::property_id::grid_item_row_property_id) == UIA_GridItemRowPropertyId);
	static_assert(static_cast<uint64_t>(uia::property_id::grid_item_column_property_id) == UIA_GridItemColumnPropertyId);
	static_assert(static_cast<uint64_t>(uia::property_id::grid_item_row_span_property_id) == UIA_GridItemRowSpanPropertyId);
	static_assert(static_cast<uint64_t>(uia::property_id::grid_item_column_span_property_id) == UIA_GridItemColumnSpanPropertyId);
	static_assert(static_cast<uint64_t>(uia::property_id::grid_item_containing_grid_property_id) == UIA_GridItemContainingGridPropertyId);
	static_assert(static_cast<uint64_t>(uia::property_id::dock_dock_position_property_id) == UIA_DockDockPositionPropertyId);
	static_assert(static_cast<uint64_t>(uia::property_id::expand_collapse_expand_collapse_state_property_id) == UIA_ExpandCollapseExpandCollapseStatePropertyId);
	static_assert(static_cast<uint64_t>(uia::property_id::multiple_view_current_view_property_id) == UIA_MultipleViewCurrentViewPropertyId);
	static_assert(static_cast<uint64_t>(uia::property_id::multiple_view_supported_views_property_id) == UIA_MultipleViewSupportedViewsPropertyId);
	static_assert(static_cast<uint64_t>(uia::property_id::window_can_maximize_property_id) == UIA_WindowCanMaximizePropertyId);
	static_assert(static_cast<uint64_t>(uia::property_id::window_can_minimize_property_id) == UIA_WindowCanMinimizePropertyId);
	static_assert(static_cast<uint64_t>(uia::property_id::window_window_visual_state_property_id) == UIA_WindowWindowVisualStatePropertyId);
	static_assert(static_cast<uint64_t>(uia::property_id::window_window_interaction_state_property_id) == UIA_WindowWindowInteractionStatePropertyId);
	static_assert(static_cast<uint64_t>(uia::property_id::window_is_modal_property_id) == UIA_WindowIsModalPropertyId);
	static_assert(static_cast<uint64_t>(uia::property_id::window_is_topmost_property_id) == UIA_WindowIsTopmostPropertyId);
	static_assert(static_cast<uint64_t>(uia::property_id::selection_item_is_selected_property_id) == UIA_SelectionItemIsSelectedPropertyId);
	static_assert(static_cast<uint64_t>(uia::property_id::selection_item_selection_container_property_id) == UIA_SelectionItemSelectionContainerPropertyId);
	static_assert(static_cast<uint64_t>(uia::property_id::table_row_headers_property_id) == UIA_TableRowHeadersPropertyId);
	static_assert(static_cast<uint64_t>(uia::property_id::table_column_headers_property_id) == UIA_TableColumnHeadersPropertyId);
	static_assert(static_cast<uint64_t>(uia::property_id::table_row_or_column_major_property_id) == UIA_TableRowOrColumnMajorPropertyId);
	static_assert(static_cast<uint64_t>(uia::property_id::table_item_row_header_items_property_id) == UIA_TableItemRowHeaderItemsPropertyId);
	static_assert(static_cast<uint64_t>(uia::property_id::table_item_column_header_items_property_id) == UIA_TableItemColumnHeaderItemsPropertyId);
	static_assert(static_cast<uint64_t>(uia::property_id::toggle_toggle_state_property_id) == UIA_ToggleToggleStatePropertyId);
	static_assert(static_cast<uint64_t>(uia::property_id::transform_can_move_property_id) == UIA_TransformCanMovePropertyId);
	static_assert(static_cast<uint64_t>(uia::property_id::transform_can_resize_property_id) == UIA_TransformCanResizePropertyId);
	static_assert(static_cast<uint64_t>(uia::property_id::transform_can_rotate_property_id) == UIA_TransformCanRotatePropertyId);
	static_assert(static_cast<uint64_t>(uia::property_id::is_legacy_i_accessible_pattern_available_property_id) == UIA_IsLegacyIAccessiblePatternAvailablePropertyId);
	static_assert(static_cast<uint64_t>(uia::property_id::legacy_i_accessible_child_id_property_id) == UIA_LegacyIAccessibleChildIdPropertyId);
	static_assert(static_cast<uint64_t>(uia::property_id::legacy_i_accessible_name_property_id) == UIA_LegacyIAccessibleNamePropertyId);
	static_assert(static_cast<uint64_t>(uia::property_id::legacy_i_accessible_value_property_id) == UIA_LegacyIAccessibleValuePropertyId);
	static_assert(static_cast<uint64_t>(uia::property_id::legacy_i_accessible_description_property_id) == UIA_LegacyIAccessibleDescriptionPropertyId);
	static_assert(static_cast<uint64_t>(uia::property_id::legacy_i_accessible_role_property_id) == UIA_LegacyIAccessibleRolePropertyId);
	static_assert(static_cast<uint64_t>(uia::property_id::legacy_i_accessible_state_property_id) == UIA_LegacyIAccessibleStatePropertyId);
	static_assert(static_cast<uint64_t>(uia::property_id::legacy_i_accessible_help_property_id) == UIA_LegacyIAccessibleHelpPropertyId);
	static_assert(static_cast<uint64_t>(uia::property_id::legacy_i_accessible_keyboard_shortcut_property_id) == UIA_LegacyIAccessibleKeyboardShortcutPropertyId);
	static_assert(static_cast<uint64_t>(uia::property_id::legacy_i_accessible_selection_property_id) == UIA_LegacyIAccessibleSelectionPropertyId);
	static_assert(static_cast<uint64_t>(uia::property_id::legacy_i_accessible_default_action_property_id) == UIA_LegacyIAccessibleDefaultActionPropertyId);
	static_assert(static_cast<uint64_t>(uia::property_id::aria_role_property_id) == UIA_AriaRolePropertyId);
	static_assert(static_cast<uint64_t>(uia::property_id::aria_properties_property_id) == UIA_AriaPropertiesPropertyId);
	static_assert(static_cast<uint64_t>(uia::property_id::is_data_valid_for_form_property_id) == UIA_IsDataValidForFormPropertyId);
	static_assert(static_cast<uint64_t>(uia::property_id::controller_for_property_id) == UIA_ControllerForPropertyId);
	static_assert(static_cast<uint64_t>(uia::property_id::described_by_property_id) == UIA_DescribedByPropertyId);
	static_assert(static_cast<uint64_t>(uia::property_id::flows_to_property_id) == UIA_FlowsToPropertyId);
	static_assert(static_cast<uint64_t>(uia::property_id::provider_description_property_id) == UIA_ProviderDescriptionPropertyId);
	static_assert(static_cast<uint64_t>(uia::property_id::is_item_container_pattern_available_property_id) == UIA_IsItemContainerPatternAvailablePropertyId);
	static_assert(static_cast<uint64_t>(uia::property_id::is_virtualized_item_pattern_available_property_id) == UIA_IsVirtualizedItemPatternAvailablePropertyId);
	static_assert(static_cast<uint64_t>(uia::property_id::is_synchronized_input_pattern_available_property_id) == UIA_IsSynchronizedInputPatternAvailablePropertyId);
	static_assert(static_cast<uint64_t>(uia::property_id::optimize_for_visual_content_property_id) == UIA_OptimizeForVisualContentPropertyId);
	static_assert(static_cast<uint64_t>(uia::property_id::is_object_model_pattern_available_property_id) == UIA_IsObjectModelPatternAvailablePropertyId);
	static_assert(static_cast<uint64_t>(uia::property_id::annotation_annotation_type_id_property_id) == UIA_AnnotationAnnotationTypeIdPropertyId);
	static_assert(static_cast<uint64_t>(uia::property_id::annotation_annotation_type_name_property_id) == UIA_AnnotationAnnotationTypeNamePropertyId);
	static_assert(static_cast<uint64_t>(uia::property_id::annotation_author_property_id) == UIA_AnnotationAuthorPropertyId);
	static_assert(static_cast<uint64_t>(uia::property_id::annotation_date_time_property_id) == UIA_AnnotationDateTimePropertyId);
	static_assert(static_cast<uint64_t>(uia::property_id::annotation_target_property_id) == UIA_AnnotationTargetPropertyId);
	static_assert(static_cast<uint64_t>(uia::property_id::is_annotation_pattern_available_property_id) == UIA_IsAnnotationPatternAvailablePropertyId);
	static_assert(static_cast<uint64_t>(uia::property_id::is_text_pattern2_available_property_id) == UIA_IsTextPattern2AvailablePropertyId);
	static_assert(static_cast<uint64_t>(uia::property_id::styles_style_id_property_id) == UIA_StylesStyleIdPropertyId);
	static_assert(static_cast<uint64_t>(uia::property_id::styles_style_name_property_id) == UIA_StylesStyleNamePropertyId);
	static_assert(static_cast<uint64_t>(uia::property_id::styles_fill_color_property_id) == UIA_StylesFillColorPropertyId);
	static_assert(static_cast<uint64_t>(uia::property_id::styles_fill_pattern_style_property_id) == UIA_StylesFillPatternStylePropertyId);
	static_assert(static_cast<uint64_t>(uia::property_id::styles_shape_property_id) == UIA_StylesShapePropertyId);
	static_assert(static_cast<uint64_t>(uia::property_id::styles_fill_pattern_color_property_id) == UIA_StylesFillPatternColorPropertyId);
	static_assert(static_cast<uint64_t>(uia::property_id::styles_extended_properties_property_id) == UIA_StylesExtendedPropertiesPropertyId);
	static_assert(static_cast<uint64_t>(uia::property_id::is_styles_pattern_available_property_id) == UIA_IsStylesPatternAvailablePropertyId);
	static_assert(static_cast<uint64_t>(uia::property_id::is_spreadsheet_pattern_available_property_id) == UIA_IsSpreadsheetPatternAvailablePropertyId);
	static_assert(static_cast<uint64_t>(uia::property_id::spreadsheet_item_formula_property_id) == UIA_SpreadsheetItemFormulaPropertyId);
	static_assert(static_cast<uint64_t>(uia::property_id::spreadsheet_item_annotation_objects_property_id) == UIA_SpreadsheetItemAnnotationObjectsPropertyId);
	static_assert(static_cast<uint64_t>(uia::property_id::spreadsheet_item_annotation_types_property_id) == UIA_SpreadsheetItemAnnotationTypesPropertyId);
	static_assert(static_cast<uint64_t>(uia::property_id::is_spreadsheet_item_pattern_available_property_id) == UIA_IsSpreadsheetItemPatternAvailablePropertyId);
	static_assert(static_cast<uint64_t>(uia::property_id::transform2_can_zoom_property_id) == UIA_Transform2CanZoomPropertyId);
	static_assert(static_cast<uint64_t>(uia::property_id::is_transform_pattern2_available_property_id) == UIA_IsTransformPattern2AvailablePropertyId);
	static_assert(static_cast<uint64_t>(uia::property_id::live_setting_property_id) == UIA_LiveSettingPropertyId);
	static_assert(static_cast<uint64_t>(uia::property_id::is_text_child_pattern_available_property_id) == UIA_IsTextChildPatternAvailablePropertyId);
	static_assert(static_cast<uint64_t>(uia::property_id::is_drag_pattern_available_property_id) == UIA_IsDragPatternAvailablePropertyId);
	static_assert(static_cast<uint64_t>(uia::property_id::drag_is_grabbed_property_id) == UIA_DragIsGrabbedPropertyId);
	static_assert(static_cast<uint64_t>(uia::property_id::drag_drop_effect_property_id) == UIA_DragDropEffectPropertyId);
	static_assert(static_cast<uint64_t>(uia::property_id::drag_drop_effects_property_id) == UIA_DragDropEffectsPropertyId);
	static_assert(static_cast<uint64_t>(uia::property_id::is_drop_target_pattern_available_property_id) == UIA_IsDropTargetPatternAvailablePropertyId);
	static_assert(static_cast<uint64_t>(uia::property_id::drop_target_drop_target_effect_property_id) == UIA_DropTargetDropTargetEffectPropertyId);
	static_assert(static_cast<uint64_t>(uia::property_id::drop_target_drop_target_effects_property_id) == UIA_DropTargetDropTargetEffectsPropertyId);
	static_assert(static_cast<uint64_t>(uia::property_id::drag_grabbed_items_property_id) == UIA_DragGrabbedItemsPropertyId);
	static_assert(static_cast<uint64_t>(uia::property_id::transform2_zoom_level_property_id) == UIA_Transform2ZoomLevelPropertyId);
	static_assert(static_cast<uint64_t>(uia::property_id::transform2_zoom_minimum_property_id) == UIA_Transform2ZoomMinimumPropertyId);
	static_assert(static_cast<uint64_t>(uia::property_id::transform2_zoom_maximum_property_id) == UIA_Transform2ZoomMaximumPropertyId);
	static_assert(static_cast<uint64_t>(uia::property_id::flows_from_property_id) == UIA_FlowsFromPropertyId);
	static_assert(static_cast<uint64_t>(uia::property_id::is_text_edit_pattern_available_property_id) == UIA_IsTextEditPatternAvailablePropertyId);
	static_assert(static_cast<uint64_t>(uia::property_id::is_peripheral_property_id) == UIA_IsPeripheralPropertyId);
	static_assert(static_cast<uint64_t>(uia::property_id::is_custom_navigation_pattern_available_property_id) == UIA_IsCustomNavigationPatternAvailablePropertyId);
	static_assert(static_cast<uint64_t>(uia::property_id::position_in_set_property_id) == UIA_PositionInSetPropertyId);
	static_assert(static_cast<uint64_t>(uia::property_id::size_of_set_property_id) == UIA_SizeOfSetPropertyId);
	static_assert(static_cast<uint64_t>(uia::property_id::level_property_id) == UIA_LevelPropertyId);
	static_assert(static_cast<uint64_t>(uia::property_id::annotation_types_property_id) == UIA_AnnotationTypesPropertyId);
	static_assert(static_cast<uint64_t>(uia::property_id::annotation_objects_property_id) == UIA_AnnotationObjectsPropertyId);
	static_assert(static_cast<uint64_t>(uia::property_id::landmark_type_property_id) == UIA_LandmarkTypePropertyId);
	static_assert(static_cast<uint64_t>(uia::property_id::localized_landmark_type_property_id) == UIA_LocalizedLandmarkTypePropertyId);
	static_assert(static_cast<uint64_t>(uia::property_id::full_description_property_id) == UIA_FullDescriptionPropertyId);
	static_assert(static_cast<uint64_t>(uia::property_id::fill_color_property_id) == UIA_FillColorPropertyId);
	static_assert(static_cast<uint64_t>(uia::property_id::outline_color_property_id) == UIA_OutlineColorPropertyId);
	static_assert(static_cast<uint64_t>(uia::property_id::fill_type_property_id) == UIA_FillTypePropertyId);
	static_assert(static_cast<uint64_t>(uia::property_id::visual_effects_property_id) == UIA_VisualEffectsPropertyId);
	static_assert(static_cast<uint64_t>(uia::property_id::outline_thickness_property_id) == UIA_OutlineThicknessPropertyId);
	static_assert(static_cast<uint64_t>(uia::property_id::center_point_property_id) == UIA_CenterPointPropertyId);
	static_assert(static_cast<uint64_t>(uia::property_id::rotation_property_id) == UIA_RotationPropertyId);
	static_assert(static_cast<uint64_t>(uia::property_id::size_property_id) == UIA_SizePropertyId);
	static_assert(static_cast<uint64_t>(uia::property_id::is_selection_pattern2_available_property_id) == UIA_IsSelectionPattern2AvailablePropertyId);
	static_assert(static_cast<uint64_t>(uia::property_id::selection2_first_selected_item_property_id) == UIA_Selection2FirstSelectedItemPropertyId);
	static_assert(static_cast<uint64_t>(uia::property_id::selection2_last_selected_item_property_id) == UIA_Selection2LastSelectedItemPropertyId);
	static_assert(static_cast<uint64_t>(uia::property_id::selection2_current_selected_item_property_id) == UIA_Selection2CurrentSelectedItemPropertyId);
	static_assert(static_cast<uint64_t>(uia::property_id::selection2_item_count_property_id) == UIA_Selection2ItemCountPropertyId);
	static_assert(static_cast<uint64_t>(uia::property_id::heading_level_property_id) == UIA_HeadingLevelPropertyId);
	static_assert(static_cast<uint64_t>(uia::property_id::is_dialog_property_id) == UIA_IsDialogPropertyId);

	return static_cast<PATTERNID>(pid);
}

AutomationElementMode get_native(uia::automation_element_mode m) {
	static_assert(static_cast<AutomationElementMode>(uia::automation_element_mode::none) == AutomationElementMode::AutomationElementMode_None);
	static_assert(static_cast<AutomationElementMode>(uia::automation_element_mode::full) == AutomationElementMode::AutomationElementMode_Full);
	
	return static_cast<AutomationElementMode>(m);
}

uia::automation_element_mode get_uia(AutomationElementMode aem) {
	return static_cast<uia::automation_element_mode>(aem);
}










//
// uiautomation_element (IUIAutomationElement)
//
uia::uiautomation_element::uiautomation_element(void* p) {
	p_ = p;
}
uia::uiautomation_element::~uiautomation_element() {
	IUIAutomationElement* p = reinterpret_cast<IUIAutomationElement*>(p_);
	p->Release();
}


//
// cache_request
//
uia::cache_request::cache_request(void* p) {
	p_ = p;
}

bool uia::cache_request::add_pattern(uia::pattern_id pid) {
	IUIAutomationCacheRequest* p = reinterpret_cast<IUIAutomationCacheRequest*>(p_);
	HRESULT hr = p->AddPattern(get_native(pid));
	if (FAILED(hr)) {
		return false;
	}
	return true;
}

bool uia::cache_request::add_property(property_id pid) {
	IUIAutomationCacheRequest* p = reinterpret_cast<IUIAutomationCacheRequest*>(p_);
	HRESULT hr = p->AddProperty(get_native(pid));
	if (FAILED(hr)) {
		return false;
	}
	return true;
}

std::optional<uia::cache_request> uia::cache_request::clone() {
	IUIAutomationCacheRequest* p = reinterpret_cast<IUIAutomationCacheRequest*>(p_);
	IUIAutomationCacheRequest* cloned {nullptr};
	HRESULT hr = p->Clone(&cloned);
	if (FAILED(hr)) {
		return {};
	}
	return uia::cache_request(cloned);
}

std::optional<uia::automation_element_mode> uia::cache_request::get_automation_element_mode() {
	IUIAutomationCacheRequest* p = reinterpret_cast<IUIAutomationCacheRequest*>(p_);
	AutomationElementMode mode {};
	HRESULT hr = p->get_AutomationElementMode(&mode);
	if (FAILED(hr)) {
		return {};
	}
	return get_uia(mode);
}

uia::cache_request::~cache_request() {
	IUIAutomationCacheRequest* p = reinterpret_cast<IUIAutomationCacheRequest*>(p_);
	p->Release();
}


//
// uiautomation (CUIAutomation/IUIAutomation*)
//
uia::uiautomation uia::uiautomation::create() {
	IUIAutomation* p {nullptr};
	HRESULT hr = CoCreateInstance(CLSID_CUIAutomation, nullptr, CLSCTX_INPROC_SERVER, IID_IUIAutomation, 
        reinterpret_cast<void**>(&p));

	return uia::uiautomation(p);
}

uia::uiautomation::uiautomation(void* p) {
	p_ = p;
}

std::optional<uia::uiautomation_element> uia::uiautomation::get_root_element() {
	IUIAutomation* p = reinterpret_cast<IUIAutomation*>(p_);
	IUIAutomationElement* elem {nullptr};
	HRESULT hr = p->GetRootElement(&elem);
	if (FAILED(hr)) {
		return {};
	}

	return uia::uiautomation_element(elem);
}

std::optional<uia::uiautomation_element> uia::uiautomation::get_focused_element() {
	IUIAutomation* p = reinterpret_cast<IUIAutomation*>(p_);
	IUIAutomationElement* elem {nullptr};
	HRESULT hr = p->GetFocusedElement(&elem);
	if (FAILED(hr)) {
		return {};
	}

	return uia::uiautomation_element(elem);
}

std::optional<uia::cache_request> uia::uiautomation::create_cache_request() {
	IUIAutomation* p = reinterpret_cast<IUIAutomation*>(p_);
	IUIAutomationCacheRequest* rq {nullptr};
	HRESULT hr = p->CreateCacheRequest(&rq);
	if (FAILED(hr)) {
		return {};
	}

	return uia::cache_request(rq);
}

uia::uiautomation::~uiautomation() {
	IUIAutomation* p = reinterpret_cast<IUIAutomation*>(p_);
	p->Release();
}








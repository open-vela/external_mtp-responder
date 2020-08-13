/*
 * Copyright (c) 2012, 2013 Samsung Electronics Co., Ltd.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef _MTP_CMD_HANDLER_UTIL_H_
#define	_MTP_CMD_HANDLER_UTIL_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "mtp_entity_device.h"

typedef struct {
	mtp_uint32 store_id;
	mtp_uint64 obj_size;
	mtp_obj_t *obj;
} obj_data_t;

mtp_err_t _hutil_get_storage_entry(mtp_uint32 store_id, store_info_t *info);
mtp_err_t _hutil_get_storage_ids(ptp_array_t *store_ids);
mtp_err_t _hutil_get_device_property(mtp_uint32 prop_id,
		device_prop_desc_t* dev_prop);
mtp_err_t _hutil_set_device_property(mtp_uint32 prop_id, void *data,
		mtp_uint32 data_sz);
mtp_err_t _hutil_reset_device_entry(mtp_uint32 prop_id);
mtp_err_t _hutil_add_object_entry(obj_info_t *obj_info, mtp_char *file_name,
		mtp_obj_t **new_obj);
mtp_err_t _hutil_remove_object_entry(mtp_uint32 obj_handle, mtp_uint32 format);
mtp_err_t _hutil_get_object_entry(mtp_uint32 obj_handle, mtp_obj_t **obj_ptr);
mtp_err_t _hutil_copy_object_entries(mtp_uint32 dst_store_id,
		mtp_uint32 src_store_id, mtp_uint32 h_parent, mtp_uint32 obj_handle,
		mtp_uint32 *new_hobj, mtp_bool keep_handle);
mtp_err_t _hutil_move_object_entry(mtp_uint32 dst_store_id, mtp_uint32 h_parent,
		mtp_uint32 obj_handle);
mtp_err_t _hutil_duplicate_object_entry(mtp_uint32 dst_store_id,
		mtp_uint32 h_parent, mtp_uint32 obj_handle, mtp_uint32 *new_handle);
mtp_err_t _hutil_read_file_data_from_offset(mtp_uint32 obj_handle, off_t offset,
		void *data, mtp_uint32 *data_sz);
mtp_err_t _hutil_write_file_data(mtp_uint32 store_id, mtp_obj_t *obj,
		mtp_char *fpath);
mtp_err_t _hutil_get_object_entry_size(mtp_uint32 obj_handle, mtp_uint64 *obj_sz);
mtp_err_t _hutil_set_protection(mtp_uint32 obj_handle, mtp_uint16 prot_status);
mtp_err_t _hutil_get_num_objects(mtp_uint32 store_id, mtp_uint32 h_parent,
		mtp_uint32 format, mtp_uint32 *num_obj);
mtp_err_t _hutil_get_object_handles(mtp_uint32 store_id, mtp_uint32 format,
		mtp_uint32 h_parent, ptp_array_t *handle_arr);
mtp_err_t _hutil_construct_object_entry(mtp_uint32 store_id, mtp_uint32 h_parent,
		obj_data_t *objdata, mtp_obj_t **obj, void *data, mtp_uint32 data_sz);
mtp_err_t _hutil_construct_object_entry_prop_list(
		mtp_uint32 store_id,
		mtp_uint32 h_parent,
		mtp_uint16 format,
		mtp_uint64 obj_sz,
		obj_data_t *obj_data,
		mtp_obj_t **obj_ptr,
		void *data,
		mtp_int32 data_sz,
		mtp_uint32 *err_idx);
mtp_err_t _hutil_get_object_prop_value(mtp_uint32 obj_handle, mtp_uint32 prop_code,
		obj_prop_val_t  *prop_val, mtp_obj_t **obj);
mtp_err_t _hutil_update_object_property(
		mtp_uint32 obj_handle,
		mtp_uint32 prop_code,
		mtp_uint16 *data_type,
		void *buf,
		mtp_uint32 buf_sz,
		mtp_uint32 *prop_sz);
mtp_err_t _hutil_get_prop_desc(mtp_uint32 format, mtp_uint32 prop_code, void *data);
mtp_err_t _hutil_get_object_prop_supported(mtp_uint32 format,
		ptp_array_t *prop_arr);

#ifdef MTP_USE_RUNTIME_GETOBJECTPROPVALUE
mtp_err_t _hutil_get_object_prop_list(mtp_uint32 obj_handle,
		mtp_uint32 format,
		mtp_uint32 prop_code,
		mtp_uint32 group_code,
		mtp_uint32 depth,
		obj_proplist_t *prop_list,
		ptp_array_t *obj_arr);
#else /* MTP_USE_RUNTIME_GETOBJECTPROPVALUE */
mtp_err_t _hutil_get_object_prop_list(
		mtp_uint32 obj_handle,
		mtp_uint32 format,
		mtp_uint32 prop_code,
		mtp_uint32 group_code,
		mtp_uint32 depth,
		obj_proplist_t *prop_list);
#endif /* MTP_USE_RUNTIME_GETOBJECTPROPVALUE */

mtp_err_t _hutil_add_object_references_enhanced(mtp_uint32 obj_handle,
		mtp_uchar *buffer, mtp_uint32 buf_sz);
mtp_err_t _hutil_remove_object_reference(mtp_uint32 obj_handle,
		mtp_uint32 ref_handle);
mtp_err_t _hutil_get_object_references(mtp_uint32 obj_handle,
		ptp_array_t *parray, mtp_uint32 *num_ele);
mtp_err_t _hutil_get_number_of_objects(mtp_uint32 store_id,
		mtp_uint32 *num_obj);
mtp_err_t _hutil_get_interdep_prop_config_list_size(mtp_uint32 *list_sz,
		mtp_uint32 format);
mtp_err_t _hutil_get_interdep_prop_config_list_data(void *data,
		mtp_uint32 list_sz, mtp_uint32 format);
mtp_err_t _hutil_get_playback_skip(mtp_int32 skip_param);
mtp_err_t _hutil_format_storage(mtp_uint32 store_id, mtp_uint32 fs_format);
mtp_uint32 _hutil_get_storage_info_size(store_info_t *store_info);

#ifdef __cplusplus
}
#endif

#endif /* _MTP_CMD_HANDLER_UTIL_H_ */

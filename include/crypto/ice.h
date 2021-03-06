/* Copyright (c) 2014-2015, The Linux Foundation. All rights reserved.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 and
 * only version 2 as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 */

#ifndef _QCOM_INLINE_CRYPTO_ENGINE_H_
#define _QCOM_INLINE_CRYPTO_ENGINE_H_

#include <linux/platform_device.h>

struct request;

enum ice_cryto_algo_mode {
	ICE_CRYPTO_ALGO_MODE_AES_ECB = 0x0,
	ICE_CRYPTO_ALGO_MODE_AES_XTS = 0x3,
};

enum ice_crpto_key_size {
	ICE_CRYPTO_KEY_SIZE_128 = 0x0,
	ICE_CRYPTO_KEY_SIZE_256 = 0x2,
};

enum ice_crpto_key_mode {
	ICE_CRYPTO_USE_KEY0_HW_KEY = 0x0,
	ICE_CRYPTO_USE_KEY1_HW_KEY = 0x1,
	ICE_CRYPTO_USE_LUT_SW_KEY0 = 0x2,
	ICE_CRYPTO_USE_LUT_SW_KEY  = 0x3
};

struct ice_crypto_setting {
	enum ice_crpto_key_size		key_size;
	enum ice_cryto_algo_mode	algo_mode;
	enum ice_crpto_key_mode		key_mode;
	unsigned short			key_index;

};

struct ice_data_setting {
	struct ice_crypto_setting	crypto_data;
	bool				sw_forced_context_switch;
	bool				decr_bypass;
	bool				encr_bypass;
};

enum ice_event_completion {
	ICE_INIT_COMPLETION,
	ICE_RESUME_COMPLETION,
	ICE_RESET_COMPLETION,
};

enum ice_error_code {
	ICE_ERROR_UNEXPECTED_ICE_DEVICE,
	ICE_ERROR_PARTITIAL_KEY_LOAD,
	ICE_ERROR_IMPROPER_INITIALIZATION,
	ICE_ERROR_INVALID_ARGUMENTS,
	ICE_ERROR_HW_DISABLE_FUSE_BLOWN,
	ICE_ERROR_ICE_KEY_RESTORE_FAILED,
	ICE_ERROR_ICE_TZ_INIT_FAILED,
	ICE_ERROR_STREAM1_PREMATURE_LBA_CHANGE,
	ICE_ERROR_STREAM2_PREMATURE_LBA_CHANGE,
	ICE_ERROR_STREAM1_UNEXPECTED_LBA,
	ICE_ERROR_STREAM2_UNEXPECTED_LBA,
	ICE_ERROR_STREAM1_NOT_EXPECTED_DUN,
	ICE_ERROR_STREAM2_NOT_EXPECTED_DUN,
	ICE_ERROR_STREAM1_NOT_EXPECTED_DUS,
	ICE_ERROR_STREAM2_NOT_EXPECTED_DUS,
	ICE_ERROR_STREAM1_NOT_EXPECTED_DBO,
	ICE_ERROR_STREAM2_NOT_EXPECTED_DBO,
	ICE_ERROR_STREAM1_NOT_EXPECTED_ENC_SEL,
	ICE_ERROR_STREAM2_NOT_EXPECTED_ENC_SEL,
	ICE_ERROR_STREAM1_NOT_EXPECTED_CONF_IDX,
	ICE_ERROR_STREAM2_NOT_EXPECTED_CONF_IDX,
	ICE_ERROR_STREAM1_NOT_EXPECTED_NEW_TRNS,
	ICE_ERROR_STREAM2_NOT_EXPECTED_NEW_TRNS
};

typedef void (*ice_success_cb)(void *, enum ice_event_completion);
typedef void (*ice_error_cb)(void *, enum ice_error_code);

struct qcom_ice_variant_ops *qcom_ice_get_variant_ops(struct device_node *node);
struct platform_device *qcom_ice_get_pdevice(struct device_node *node);

#ifdef CONFIG_CRYPTO_DEV_QCOM_ICE
int qcom_ice_setup_ice_hw(const char *, int);
#else
static inline int qcom_ice_setup_ice_hw(const char *storage_type, int enable)
{
	return 0;
}
#endif

struct qcom_ice_variant_ops {
	const char *name;
	int	(*init)(struct platform_device *, void *,
				ice_success_cb, ice_error_cb);
	int	(*reset)(struct platform_device *);
	int	(*resume)(struct platform_device *);
	int	(*suspend)(struct platform_device *);
	int	(*config)(struct platform_device *, struct request* ,
				struct ice_data_setting*);
	int	(*status)(struct platform_device *);
	void	(*debug)(struct platform_device *);
};

#endif /* _QCOM_INLINE_CRYPTO_ENGINE_H_ */

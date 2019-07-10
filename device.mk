#
# Copyright (C) 2017 The LineageOS Project
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#      http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
#

$(call inherit-product, $(SRC_TARGET_DIR)/product/languages_full.mk)

# Get non-open-source specific aspects
$(call inherit-product-if-exists, vendor/samsung/trlteduos/trlteduos-vendor.mk)

# Overlays
DEVICE_PACKAGE_OVERLAYS += device/samsung/trlteduos/overlay

# Keylayouts
PRODUCT_COPY_FILES += \
    device/samsung/trlteduos/keylayout/sec_touchkey.kl:$(TARGET_COPY_OUT_SYSTEM)/usr/keylayout/sec_touchkey.kl \
    device/samsung/trlteduos/keylayout/gpio-keys.kl:$(TARGET_COPY_OUT_SYSTEM)/usr/keylayout/gpio-keys.kl \
    device/samsung/trlteduos/keylayout/synaptics_rmi4_i2c.kl:$(TARGET_COPY_OUT_SYSTEM)/usr/keylayout/synaptics_rmi4_i2c.kl \
    device/samsung/trlteduos/keylayout/Vendor_04e8_Product_7021.kl:$(TARGET_COPY_OUT_SYSTEM)/usr/keylayout/Vendor_04e8_Product_7021.kl \
    device/samsung/trlteduos/idc/Synaptics_HID_TouchPad.idc:$(TARGET_COPY_OUT_SYSTEM)/usr/idc/Synaptics_HID_TouchPad.idc \
    device/samsung/trlteduos/idc/sec_e-pen.idc:$(TARGET_COPY_OUT_SYSTEM)/usr/idc/sec_e-pen.idc \
    device/samsung/trlteduos/idc/sec_touchscreen.idc:$(TARGET_COPY_OUT_SYSTEM)/usr/idc/sec_touchscreen.idc

# Radio/RIL
$(call inherit-product, device/samsung/trlte-common/radio/dual/product.mk)

# common trlte
$(call inherit-product, device/samsung/trlte-common/trlte.mk)

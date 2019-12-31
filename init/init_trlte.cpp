/*
   Copyright (c) 2020, The LineageOS Project. All rights reserved.

   Redistribution and use in source and binary forms, with or without
   modification, are permitted provided that the following conditions are
   met:
    * Redistributions of source code must retain the above copyright
      notice, this list of conditions and the following disclaimer.
    * Redistributions in binary form must reproduce the above
      copyright notice, this list of conditions and the following
      disclaimer in the documentation and/or other materials provided
      with the distribution.
    * Neither the name of The Linux Foundation nor the names of its
      contributors may be used to endorse or promote products derived
      from this software without specific prior written permission.

   THIS SOFTWARE IS PROVIDED "AS IS" AND ANY EXPRESS OR IMPLIED
   WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
   MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT
   ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS
   BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
   CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
   SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR
   BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
   WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
   OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN
   IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */


#include <stdlib.h>

#include <android-base/file.h>
#include <android-base/logging.h>
#include <android-base/properties.h>
#include <android-base/strings.h>

#include "property_service.h"
#include "vendor_init.h"

#define _REALLY_INCLUDE_SYS__SYSTEM_PROPERTIES_H_
#include <sys/_system_properties.h>

using android::base::GetProperty;
using android::base::ReadFileToString;
using android::base::Trim;
using android::init::property_set;

#define SERIAL_NUMBER_FILE "/efs/FactoryApp/serial_no"

// copied from build/tools/releasetools/ota_from_target_files.py
// but with "." at the end and empty entry
std::vector<std::string> ro_product_props_default_source_order = {
    "",
    "product.",
    "product_services.",
    "odm.",
    "vendor.",
    "system.",
};

void property_override(char const prop[], char const value[], bool add = true)
{
    auto pi = (prop_info *) __system_property_find(prop);

    if (pi != nullptr) {
        __system_property_update(pi, value, strlen(value));
    } else if (add) {
        __system_property_add(prop, strlen(prop), value, strlen(value));
    }
}

void vendor_load_properties()
{
    const std::string bootloader = GetProperty("ro.bootloader", "");

    char const *serial_number_file = SERIAL_NUMBER_FILE;
    std::string serial_number;

    if (ReadFileToString(serial_number_file, &serial_number)) {
        serial_number = Trim(serial_number);
        property_override("ro.serialno", serial_number.c_str());
    }

    const auto set_ro_product_prop = [](const std::string &source,
            const std::string &prop, const std::string &value) {
        auto prop_name = "ro.product." + source + prop;
        property_override(prop_name.c_str(), value.c_str(), false);
    };

    if (bootloader.find("N9100ZC") == 0) {
        /* trlteduoszc */
        for (const auto &source : ro_product_props_default_source_order) {
            set_ro_product_prop(source, "fingerprint", "samsung/trlteduoszc/trltechn:6.0.1/MMB29M/N9100ZCS1DQH1:user/release-keys");
            set_ro_product_prop(source, "device", "trlteduoszc");
            set_ro_product_prop(source, "model", "SM-N9100");
            set_ro_product_prop(source, "name", "trltechn");
        }
        property_override("ro.build.description", "trlteduoszc-user 6.0.1 MMB29M N9100ZCS1DQH1 release-keys");
        property_override("ro.build.product", "trlteduoszc");
    } else if (bootloader.find("N9100ZH") == 0) {
        /* trlteduoszh */
        for (const auto &source : ro_product_props_default_source_order) {
            set_ro_product_prop(source, "fingerprint", "samsung/trlteduoszh/trltechnzh:6.0.1/MMB29M/N9100ZHU1DQG1:user/release-keys");
            set_ro_product_prop(source, "device", "trltechnzh");
            set_ro_product_prop(source, "model", "SM-N9100");
            set_ro_product_prop(source, "name", "trlteduoszh");
        }
        property_override("ro.build.description", "trlteduoszh-user 6.0.1 MMB29M N9100ZHU1DQG1 release-keys");
        property_override("ro.build.product", "trltechnzh");
    } else if (bootloader.find("N9106W") == 0) {
        /* trlteduoszn */
        for (const auto &source : ro_product_props_default_source_order) {
            set_ro_product_prop(source, "fingerprint", "samsung/trlteduoszn/trltechn:6.0.1/MMB29M/N9106WZNU1DQB1:user/release-keys");
            set_ro_product_prop(source, "device", "trltechn");
            set_ro_product_prop(source, "model", "SM-N9106W");
            set_ro_product_prop(source, "name", "trlteduoszn");
        }
        property_override("ro.build.description", "trlteduoszn-user 6.0.1 MMB29M N9106WZNU1DQB1 release-keys");
        property_override("ro.build.product", "trltechn");
    } else if (bootloader.find("N9109W") == 0) {
        /* trlteduosctc */
        for (const auto &source : ro_product_props_default_source_order) {
            set_ro_product_prop(source, "fingerprint", "samsung/trlteduosctc/trltechn:6.0.1/MMB29M/N9109WKEU1DQD1:user/release-keys");
            set_ro_product_prop(source, "device", "trltechn");
            set_ro_product_prop(source, "model", "SM-N9109W");
            set_ro_product_prop(source, "name", "trlteduosctc");
        }
        property_override("ro.build.description", "trlteduosctc-user 6.0.1 MMB29M N9109WKEU1DQD1 release-keys");
        property_override("ro.build.product", "trltechn");
    }

    const std::string device = GetProperty("ro.product.device", "");
    LOG(INFO) << "Found bootloader " << bootloader << ". " << "Setting build properties for " << device << ".\n";
}

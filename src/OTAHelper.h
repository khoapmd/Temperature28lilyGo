#pragma once

#ifndef OTA_HELPER_H
#define OTA_HELPER_H

#include <WiFi.h>

String OTACheck(boolean forceUpdate);
void OTAUpdate();

#endif 
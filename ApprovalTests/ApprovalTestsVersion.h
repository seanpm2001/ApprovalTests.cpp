#pragma once

#include "ApprovalTests/ApprovalsMacroDefaults.h"

#define APPROVAL_TESTS_VERSION_MAJOR 8
#define APPROVAL_TESTS_VERSION_MINOR 7
#define APPROVAL_TESTS_VERSION_PATCH 1
#define APPROVAL_TESTS_VERSION_STR "8.7.1"

#define APPROVAL_TESTS_VERSION                                                           \
    (APPROVAL_TESTS_VERSION_MAJOR * 10000 + APPROVAL_TESTS_VERSION_MINOR * 100 +         \
     APPROVAL_TESTS_VERSION_PATCH)

#if !APPROVAL_TESTS_HIDE_DEPRECATED_CODE
// clang-format off
// Deprecated, for regression only:
#define APPROVALTESTS_VERSION       APPROVAL_TESTS_VERSION
#define APPROVALTESTS_VERSION_MAJOR APPROVAL_TESTS_VERSION_MAJOR
#define APPROVALTESTS_VERSION_MINOR APPROVAL_TESTS_VERSION_MINOR
#define APPROVALTESTS_VERSION_PATCH APPROVAL_TESTS_VERSION_PATCH
#define APPROVALTESTS_VERSION_STR   APPROVAL_TESTS_VERSION_STR
// clang-format on
#endif

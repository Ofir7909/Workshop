#pragma once

#include <cassert>
#include <fstream>
#include <functional>
#include <iostream>
#include <map>
#include <memory>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

#include <assert.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>

#include "Log.h"

#define clean_errno() (errno == 0 ? "None" : strerror(errno))
#define log_error(M, ...) \
	fprintf(stderr, "[ERROR] (%s:%d: errno: %s) " M "\n", __FILE__, __LINE__, clean_errno(), ##__VA_ARGS__)
#define assertf(A, M, ...)           \
	if (!(A)) {                      \
		log_error(M, ##__VA_ARGS__); \
		assert(A);                   \
	}
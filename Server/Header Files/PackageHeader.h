#pragma once

#include "PackageType.h"

struct PackageHeader
{
	PackageType type;
	size_t size;
};
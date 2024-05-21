#pragma once

#include <library/cpp/yt/memory/ref_counted.h>
#include <library/cpp/yt/memory/intrusive_ptr.h>

#include <library/cpp/yt/misc/strong_typedef.h>

namespace NYT::NPhoenix2 {

////////////////////////////////////////////////////////////////////////////////

using TConstructor = void* (*)();

////////////////////////////////////////////////////////////////////////////////

class TFieldDescriptor;
class TTypeDescriptor;
class TUniverseDescriptor;

////////////////////////////////////////////////////////////////////////////////

DECLARE_REFCOUNTED_STRUCT(TFieldSchema);
DECLARE_REFCOUNTED_STRUCT(TTypeSchema);
DECLARE_REFCOUNTED_STRUCT(TUniverseSchema);

////////////////////////////////////////////////////////////////////////////////

YT_DEFINE_STRONG_TYPEDEF(TTypeTag, ui32);
YT_DEFINE_STRONG_TYPEDEF(TFieldTag, ui32);

////////////////////////////////////////////////////////////////////////////////

} // namespace NYT::NPhoenix2


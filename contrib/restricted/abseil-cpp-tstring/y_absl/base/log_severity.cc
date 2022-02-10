// Copyright 2017 The Abseil Authors.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//      https://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include "y_absl/base/log_severity.h" 

#include <ostream>

namespace y_absl { 
ABSL_NAMESPACE_BEGIN

std::ostream& operator<<(std::ostream& os, y_absl::LogSeverity s) { 
  if (s == y_absl::NormalizeLogSeverity(s)) return os << y_absl::LogSeverityName(s); 
  return os << "y_absl::LogSeverity(" << static_cast<int>(s) << ")"; 
}
ABSL_NAMESPACE_END
}  // namespace y_absl 

// Copyright (c) 2023, Adam Simpkins
#pragma once

#define ASEL_CONCAT_IMPL(s1, s2) s1##s2
#define ASEL_CONCAT(s1, s2) ASEL_CONCAT_IMPL(s1, s2)
#define ASEL_CONCAT3(s1, s2, s3) ASEL_CONCAT(ASEL_CONCAT(s1, s2), s3)
#define ASEL_CONCAT4(s1, s2, s3, s4)                                           \
  ASEL_CONCAT(ASEL_CONCAT(ASEL_CONCAT(s1, s2), s3), s4)

#define ASEL_STRINGIFY(s) #s

#define ASEL_UNIQUE_NAME(str)                                                  \
  ASEL_CONCAT(ASEL_CONCAT(ASEL_CONCAT(str, __COUNTER__), _), __LINE__)

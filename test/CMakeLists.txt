set(
    asel_test_srcs
    ArrayTest.cpp
    LogTest.cpp
    RangeTest.cpp
    RatioTest.cpp
)

set(
    esp_test_srcs
    EspErrorTest.cpp
)

if(ESP_PLATFORM)
    idf_component_register(
        SRCS ${asel_test_srcs} ${esp_test_srcs}
        REQUIRES "asel"
        WHOLE_ARCHIVE
    )
else()
    add_library(
        asel_test_cases
        OBJECT
        "${asel_test_srcs}"
    )
    target_link_libraries(asel_test_cases PUBLIC asel)
endif()

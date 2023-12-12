set(
    asel_test_srcs
    error_test.cpp
)

if(ESP_PLATFORM)
    idf_component_register(
        SRCS ${asel_test_srcs}
        REQUIRES "asel"
        WHOLE_ARCHIVE
    )
else()
    add_library(
        test_cases
        OBJECT
        "${asel_test_srcs}"
    )
    target_link_libraries(test_cases PUBLIC asel)
endif()

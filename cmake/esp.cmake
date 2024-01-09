set(
    esp_srcs
    "asel/esp/EspError.cpp"
)

idf_component_register(
    SRCS ${srcs} ${esp_srcs}
    INCLUDE_DIRS ".."
    REQUIRES esp_timer
)
target_compile_definitions(
    ${COMPONENT_LIB}
    PUBLIC
    "ESP_TARGET=${target}"
    ASEL_HAVE_STDLIB=1
)
target_compile_options(${COMPONENT_LIB} PRIVATE -Werror)

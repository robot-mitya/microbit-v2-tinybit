#cmake_policy(SET CMP0175 NEW)
add_custom_command(
    TARGET ${device.device}
    POST_BUILD
    COMMAND "${ARM_NONE_EABI_SIZE}" "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${device.device}"
#    DEPENDS  ${device.device}
    COMMENT "Print total size info:"
)

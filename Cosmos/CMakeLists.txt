cmake_minimum_required(VERSION 3.16)
project(CosmosEngine CXX)

# Quét tất cả file .cpp nằm trực tiếp trong thư mục Cosmos
file(GLOB COSMOS_SOURCES "*.cpp")

# Đóng gói thành thư viện tĩnh libCosmos.a
add_library(Cosmos STATIC ${COSMOS_SOURCES})

# Cấu hình vị trí xuất file libCosmos.a ra thư mục vendors/lib chung của dự án
set_target_properties(Cosmos PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/vendors/lib"
)

# Nếu code của Cosmos gọi trực tiếp các hàm của SDL3 hoặc spdlog thì liên kết tại đây
target_link_libraries(Cosmos
    ${SDL3_LIB}
    ${SDL3_IMAGE_LIB}
    ${SDL3_MIXER_LIB}
    ${SPDLOG_LIB}
)

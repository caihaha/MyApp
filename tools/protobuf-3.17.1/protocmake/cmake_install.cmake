# Install script for directory: E:/Project/myproject/MyApp/tools/protobuf-3.17.1/cmake

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "C:/Program Files (x86)/protobuf")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "Release")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xlibprotobuf-litex" OR NOT CMAKE_INSTALL_COMPONENT)
  if("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "E:/Project/myproject/MyApp/tools/protobuf-3.17.1/protocmake/Debug/libprotobuf-lited.lib")
  elseif("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "E:/Project/myproject/MyApp/tools/protobuf-3.17.1/protocmake/Release/libprotobuf-lite.lib")
  elseif("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Mm][Ii][Nn][Ss][Ii][Zz][Ee][Rr][Ee][Ll])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "E:/Project/myproject/MyApp/tools/protobuf-3.17.1/protocmake/MinSizeRel/libprotobuf-lite.lib")
  elseif("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Rr][Ee][Ll][Ww][Ii][Tt][Hh][Dd][Ee][Bb][Ii][Nn][Ff][Oo])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "E:/Project/myproject/MyApp/tools/protobuf-3.17.1/protocmake/RelWithDebInfo/libprotobuf-lite.lib")
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xlibprotobufx" OR NOT CMAKE_INSTALL_COMPONENT)
  if("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "E:/Project/myproject/MyApp/tools/protobuf-3.17.1/protocmake/Debug/libprotobufd.lib")
  elseif("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "E:/Project/myproject/MyApp/tools/protobuf-3.17.1/protocmake/Release/libprotobuf.lib")
  elseif("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Mm][Ii][Nn][Ss][Ii][Zz][Ee][Rr][Ee][Ll])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "E:/Project/myproject/MyApp/tools/protobuf-3.17.1/protocmake/MinSizeRel/libprotobuf.lib")
  elseif("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Rr][Ee][Ll][Ww][Ii][Tt][Hh][Dd][Ee][Bb][Ii][Nn][Ff][Oo])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "E:/Project/myproject/MyApp/tools/protobuf-3.17.1/protocmake/RelWithDebInfo/libprotobuf.lib")
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xlibprotocx" OR NOT CMAKE_INSTALL_COMPONENT)
  if("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "E:/Project/myproject/MyApp/tools/protobuf-3.17.1/protocmake/Debug/libprotocd.lib")
  elseif("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "E:/Project/myproject/MyApp/tools/protobuf-3.17.1/protocmake/Release/libprotoc.lib")
  elseif("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Mm][Ii][Nn][Ss][Ii][Zz][Ee][Rr][Ee][Ll])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "E:/Project/myproject/MyApp/tools/protobuf-3.17.1/protocmake/MinSizeRel/libprotoc.lib")
  elseif("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Rr][Ee][Ll][Ww][Ii][Tt][Hh][Dd][Ee][Bb][Ii][Nn][Ff][Oo])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "E:/Project/myproject/MyApp/tools/protobuf-3.17.1/protocmake/RelWithDebInfo/libprotoc.lib")
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  if("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE EXECUTABLE FILES "E:/Project/myproject/MyApp/tools/protobuf-3.17.1/protocmake/Debug/protoc.exe")
  elseif("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE EXECUTABLE FILES "E:/Project/myproject/MyApp/tools/protobuf-3.17.1/protocmake/Release/protoc.exe")
  elseif("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Mm][Ii][Nn][Ss][Ii][Zz][Ee][Rr][Ee][Ll])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE EXECUTABLE FILES "E:/Project/myproject/MyApp/tools/protobuf-3.17.1/protocmake/MinSizeRel/protoc.exe")
  elseif("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Rr][Ee][Ll][Ww][Ii][Tt][Hh][Dd][Ee][Bb][Ii][Nn][Ff][Oo])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE EXECUTABLE FILES "E:/Project/myproject/MyApp/tools/protobuf-3.17.1/protocmake/RelWithDebInfo/protoc.exe")
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/pkgconfig" TYPE FILE FILES
    "E:/Project/myproject/MyApp/tools/protobuf-3.17.1/protocmake/protobuf.pc"
    "E:/Project/myproject/MyApp/tools/protobuf-3.17.1/protocmake/protobuf-lite.pc"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xprotobuf-headersx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/google/protobuf" TYPE FILE RENAME "any.h" FILES "E:/Project/myproject/MyApp/tools/protobuf-3.17.1/src/google/protobuf/any.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xprotobuf-headersx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/google/protobuf" TYPE FILE RENAME "any.pb.h" FILES "E:/Project/myproject/MyApp/tools/protobuf-3.17.1/src/google/protobuf/any.pb.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xprotobuf-headersx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/google/protobuf" TYPE FILE RENAME "api.pb.h" FILES "E:/Project/myproject/MyApp/tools/protobuf-3.17.1/src/google/protobuf/api.pb.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xprotobuf-headersx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/google/protobuf" TYPE FILE RENAME "arena.h" FILES "E:/Project/myproject/MyApp/tools/protobuf-3.17.1/src/google/protobuf/arena.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xprotobuf-headersx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/google/protobuf" TYPE FILE RENAME "arena_impl.h" FILES "E:/Project/myproject/MyApp/tools/protobuf-3.17.1/src/google/protobuf/arena_impl.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xprotobuf-headersx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/google/protobuf" TYPE FILE RENAME "arenastring.h" FILES "E:/Project/myproject/MyApp/tools/protobuf-3.17.1/src/google/protobuf/arenastring.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xprotobuf-headersx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/google/protobuf/compiler" TYPE FILE RENAME "code_generator.h" FILES "E:/Project/myproject/MyApp/tools/protobuf-3.17.1/src/google/protobuf/compiler/code_generator.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xprotobuf-headersx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/google/protobuf/compiler" TYPE FILE RENAME "command_line_interface.h" FILES "E:/Project/myproject/MyApp/tools/protobuf-3.17.1/src/google/protobuf/compiler/command_line_interface.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xprotobuf-headersx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/google/protobuf/compiler/cpp" TYPE FILE RENAME "cpp_generator.h" FILES "E:/Project/myproject/MyApp/tools/protobuf-3.17.1/src/google/protobuf/compiler/cpp/cpp_generator.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xprotobuf-headersx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/google/protobuf/compiler/csharp" TYPE FILE RENAME "csharp_generator.h" FILES "E:/Project/myproject/MyApp/tools/protobuf-3.17.1/src/google/protobuf/compiler/csharp/csharp_generator.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xprotobuf-headersx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/google/protobuf/compiler/csharp" TYPE FILE RENAME "csharp_names.h" FILES "E:/Project/myproject/MyApp/tools/protobuf-3.17.1/src/google/protobuf/compiler/csharp/csharp_names.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xprotobuf-headersx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/google/protobuf/compiler" TYPE FILE RENAME "importer.h" FILES "E:/Project/myproject/MyApp/tools/protobuf-3.17.1/src/google/protobuf/compiler/importer.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xprotobuf-headersx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/google/protobuf/compiler/java" TYPE FILE RENAME "java_generator.h" FILES "E:/Project/myproject/MyApp/tools/protobuf-3.17.1/src/google/protobuf/compiler/java/java_generator.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xprotobuf-headersx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/google/protobuf/compiler/java" TYPE FILE RENAME "java_kotlin_generator.h" FILES "E:/Project/myproject/MyApp/tools/protobuf-3.17.1/src/google/protobuf/compiler/java/java_kotlin_generator.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xprotobuf-headersx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/google/protobuf/compiler/java" TYPE FILE RENAME "java_names.h" FILES "E:/Project/myproject/MyApp/tools/protobuf-3.17.1/src/google/protobuf/compiler/java/java_names.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xprotobuf-headersx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/google/protobuf/compiler/js" TYPE FILE RENAME "js_generator.h" FILES "E:/Project/myproject/MyApp/tools/protobuf-3.17.1/src/google/protobuf/compiler/js/js_generator.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xprotobuf-headersx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/google/protobuf/compiler/js" TYPE FILE RENAME "well_known_types_embed.h" FILES "E:/Project/myproject/MyApp/tools/protobuf-3.17.1/src/google/protobuf/compiler/js/well_known_types_embed.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xprotobuf-headersx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/google/protobuf/compiler/objectivec" TYPE FILE RENAME "objectivec_generator.h" FILES "E:/Project/myproject/MyApp/tools/protobuf-3.17.1/src/google/protobuf/compiler/objectivec/objectivec_generator.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xprotobuf-headersx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/google/protobuf/compiler/objectivec" TYPE FILE RENAME "objectivec_helpers.h" FILES "E:/Project/myproject/MyApp/tools/protobuf-3.17.1/src/google/protobuf/compiler/objectivec/objectivec_helpers.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xprotobuf-headersx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/google/protobuf/compiler" TYPE FILE RENAME "parser.h" FILES "E:/Project/myproject/MyApp/tools/protobuf-3.17.1/src/google/protobuf/compiler/parser.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xprotobuf-headersx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/google/protobuf/compiler/php" TYPE FILE RENAME "php_generator.h" FILES "E:/Project/myproject/MyApp/tools/protobuf-3.17.1/src/google/protobuf/compiler/php/php_generator.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xprotobuf-headersx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/google/protobuf/compiler" TYPE FILE RENAME "plugin.h" FILES "E:/Project/myproject/MyApp/tools/protobuf-3.17.1/src/google/protobuf/compiler/plugin.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xprotobuf-headersx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/google/protobuf/compiler" TYPE FILE RENAME "plugin.pb.h" FILES "E:/Project/myproject/MyApp/tools/protobuf-3.17.1/src/google/protobuf/compiler/plugin.pb.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xprotobuf-headersx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/google/protobuf/compiler/python" TYPE FILE RENAME "python_generator.h" FILES "E:/Project/myproject/MyApp/tools/protobuf-3.17.1/src/google/protobuf/compiler/python/python_generator.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xprotobuf-headersx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/google/protobuf/compiler/ruby" TYPE FILE RENAME "ruby_generator.h" FILES "E:/Project/myproject/MyApp/tools/protobuf-3.17.1/src/google/protobuf/compiler/ruby/ruby_generator.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xprotobuf-headersx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/google/protobuf" TYPE FILE RENAME "descriptor.h" FILES "E:/Project/myproject/MyApp/tools/protobuf-3.17.1/src/google/protobuf/descriptor.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xprotobuf-headersx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/google/protobuf" TYPE FILE RENAME "descriptor.pb.h" FILES "E:/Project/myproject/MyApp/tools/protobuf-3.17.1/src/google/protobuf/descriptor.pb.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xprotobuf-headersx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/google/protobuf" TYPE FILE RENAME "descriptor_database.h" FILES "E:/Project/myproject/MyApp/tools/protobuf-3.17.1/src/google/protobuf/descriptor_database.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xprotobuf-headersx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/google/protobuf" TYPE FILE RENAME "duration.pb.h" FILES "E:/Project/myproject/MyApp/tools/protobuf-3.17.1/src/google/protobuf/duration.pb.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xprotobuf-headersx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/google/protobuf" TYPE FILE RENAME "dynamic_message.h" FILES "E:/Project/myproject/MyApp/tools/protobuf-3.17.1/src/google/protobuf/dynamic_message.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xprotobuf-headersx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/google/protobuf" TYPE FILE RENAME "empty.pb.h" FILES "E:/Project/myproject/MyApp/tools/protobuf-3.17.1/src/google/protobuf/empty.pb.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xprotobuf-headersx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/google/protobuf" TYPE FILE RENAME "extension_set.h" FILES "E:/Project/myproject/MyApp/tools/protobuf-3.17.1/src/google/protobuf/extension_set.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xprotobuf-headersx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/google/protobuf" TYPE FILE RENAME "extension_set_inl.h" FILES "E:/Project/myproject/MyApp/tools/protobuf-3.17.1/src/google/protobuf/extension_set_inl.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xprotobuf-headersx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/google/protobuf" TYPE FILE RENAME "field_mask.pb.h" FILES "E:/Project/myproject/MyApp/tools/protobuf-3.17.1/src/google/protobuf/field_mask.pb.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xprotobuf-headersx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/google/protobuf" TYPE FILE RENAME "generated_enum_reflection.h" FILES "E:/Project/myproject/MyApp/tools/protobuf-3.17.1/src/google/protobuf/generated_enum_reflection.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xprotobuf-headersx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/google/protobuf" TYPE FILE RENAME "generated_enum_util.h" FILES "E:/Project/myproject/MyApp/tools/protobuf-3.17.1/src/google/protobuf/generated_enum_util.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xprotobuf-headersx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/google/protobuf" TYPE FILE RENAME "generated_message_reflection.h" FILES "E:/Project/myproject/MyApp/tools/protobuf-3.17.1/src/google/protobuf/generated_message_reflection.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xprotobuf-headersx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/google/protobuf" TYPE FILE RENAME "generated_message_table_driven.h" FILES "E:/Project/myproject/MyApp/tools/protobuf-3.17.1/src/google/protobuf/generated_message_table_driven.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xprotobuf-headersx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/google/protobuf" TYPE FILE RENAME "generated_message_util.h" FILES "E:/Project/myproject/MyApp/tools/protobuf-3.17.1/src/google/protobuf/generated_message_util.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xprotobuf-headersx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/google/protobuf" TYPE FILE RENAME "has_bits.h" FILES "E:/Project/myproject/MyApp/tools/protobuf-3.17.1/src/google/protobuf/has_bits.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xprotobuf-headersx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/google/protobuf" TYPE FILE RENAME "implicit_weak_message.h" FILES "E:/Project/myproject/MyApp/tools/protobuf-3.17.1/src/google/protobuf/implicit_weak_message.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xprotobuf-headersx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/google/protobuf/io" TYPE FILE RENAME "coded_stream.h" FILES "E:/Project/myproject/MyApp/tools/protobuf-3.17.1/src/google/protobuf/io/coded_stream.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xprotobuf-headersx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/google/protobuf/io" TYPE FILE RENAME "gzip_stream.h" FILES "E:/Project/myproject/MyApp/tools/protobuf-3.17.1/src/google/protobuf/io/gzip_stream.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xprotobuf-headersx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/google/protobuf/io" TYPE FILE RENAME "io_win32.h" FILES "E:/Project/myproject/MyApp/tools/protobuf-3.17.1/src/google/protobuf/io/io_win32.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xprotobuf-headersx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/google/protobuf/io" TYPE FILE RENAME "printer.h" FILES "E:/Project/myproject/MyApp/tools/protobuf-3.17.1/src/google/protobuf/io/printer.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xprotobuf-headersx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/google/protobuf/io" TYPE FILE RENAME "strtod.h" FILES "E:/Project/myproject/MyApp/tools/protobuf-3.17.1/src/google/protobuf/io/strtod.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xprotobuf-headersx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/google/protobuf/io" TYPE FILE RENAME "tokenizer.h" FILES "E:/Project/myproject/MyApp/tools/protobuf-3.17.1/src/google/protobuf/io/tokenizer.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xprotobuf-headersx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/google/protobuf/io" TYPE FILE RENAME "zero_copy_stream.h" FILES "E:/Project/myproject/MyApp/tools/protobuf-3.17.1/src/google/protobuf/io/zero_copy_stream.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xprotobuf-headersx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/google/protobuf/io" TYPE FILE RENAME "zero_copy_stream_impl.h" FILES "E:/Project/myproject/MyApp/tools/protobuf-3.17.1/src/google/protobuf/io/zero_copy_stream_impl.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xprotobuf-headersx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/google/protobuf/io" TYPE FILE RENAME "zero_copy_stream_impl_lite.h" FILES "E:/Project/myproject/MyApp/tools/protobuf-3.17.1/src/google/protobuf/io/zero_copy_stream_impl_lite.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xprotobuf-headersx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/google/protobuf" TYPE FILE RENAME "map.h" FILES "E:/Project/myproject/MyApp/tools/protobuf-3.17.1/src/google/protobuf/map.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xprotobuf-headersx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/google/protobuf" TYPE FILE RENAME "map_entry.h" FILES "E:/Project/myproject/MyApp/tools/protobuf-3.17.1/src/google/protobuf/map_entry.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xprotobuf-headersx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/google/protobuf" TYPE FILE RENAME "map_entry_lite.h" FILES "E:/Project/myproject/MyApp/tools/protobuf-3.17.1/src/google/protobuf/map_entry_lite.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xprotobuf-headersx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/google/protobuf" TYPE FILE RENAME "map_field.h" FILES "E:/Project/myproject/MyApp/tools/protobuf-3.17.1/src/google/protobuf/map_field.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xprotobuf-headersx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/google/protobuf" TYPE FILE RENAME "map_field_inl.h" FILES "E:/Project/myproject/MyApp/tools/protobuf-3.17.1/src/google/protobuf/map_field_inl.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xprotobuf-headersx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/google/protobuf" TYPE FILE RENAME "map_field_lite.h" FILES "E:/Project/myproject/MyApp/tools/protobuf-3.17.1/src/google/protobuf/map_field_lite.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xprotobuf-headersx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/google/protobuf" TYPE FILE RENAME "map_type_handler.h" FILES "E:/Project/myproject/MyApp/tools/protobuf-3.17.1/src/google/protobuf/map_type_handler.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xprotobuf-headersx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/google/protobuf" TYPE FILE RENAME "message.h" FILES "E:/Project/myproject/MyApp/tools/protobuf-3.17.1/src/google/protobuf/message.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xprotobuf-headersx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/google/protobuf" TYPE FILE RENAME "message_lite.h" FILES "E:/Project/myproject/MyApp/tools/protobuf-3.17.1/src/google/protobuf/message_lite.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xprotobuf-headersx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/google/protobuf" TYPE FILE RENAME "metadata.h" FILES "E:/Project/myproject/MyApp/tools/protobuf-3.17.1/src/google/protobuf/metadata.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xprotobuf-headersx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/google/protobuf" TYPE FILE RENAME "metadata_lite.h" FILES "E:/Project/myproject/MyApp/tools/protobuf-3.17.1/src/google/protobuf/metadata_lite.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xprotobuf-headersx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/google/protobuf" TYPE FILE RENAME "parse_context.h" FILES "E:/Project/myproject/MyApp/tools/protobuf-3.17.1/src/google/protobuf/parse_context.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xprotobuf-headersx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/google/protobuf" TYPE FILE RENAME "port.h" FILES "E:/Project/myproject/MyApp/tools/protobuf-3.17.1/src/google/protobuf/port.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xprotobuf-headersx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/google/protobuf" TYPE FILE RENAME "port_def.inc" FILES "E:/Project/myproject/MyApp/tools/protobuf-3.17.1/src/google/protobuf/port_def.inc")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xprotobuf-headersx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/google/protobuf" TYPE FILE RENAME "port_undef.inc" FILES "E:/Project/myproject/MyApp/tools/protobuf-3.17.1/src/google/protobuf/port_undef.inc")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xprotobuf-headersx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/google/protobuf" TYPE FILE RENAME "reflection.h" FILES "E:/Project/myproject/MyApp/tools/protobuf-3.17.1/src/google/protobuf/reflection.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xprotobuf-headersx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/google/protobuf" TYPE FILE RENAME "reflection_ops.h" FILES "E:/Project/myproject/MyApp/tools/protobuf-3.17.1/src/google/protobuf/reflection_ops.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xprotobuf-headersx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/google/protobuf" TYPE FILE RENAME "repeated_field.h" FILES "E:/Project/myproject/MyApp/tools/protobuf-3.17.1/src/google/protobuf/repeated_field.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xprotobuf-headersx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/google/protobuf" TYPE FILE RENAME "service.h" FILES "E:/Project/myproject/MyApp/tools/protobuf-3.17.1/src/google/protobuf/service.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xprotobuf-headersx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/google/protobuf" TYPE FILE RENAME "source_context.pb.h" FILES "E:/Project/myproject/MyApp/tools/protobuf-3.17.1/src/google/protobuf/source_context.pb.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xprotobuf-headersx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/google/protobuf" TYPE FILE RENAME "struct.pb.h" FILES "E:/Project/myproject/MyApp/tools/protobuf-3.17.1/src/google/protobuf/struct.pb.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xprotobuf-headersx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/google/protobuf/stubs" TYPE FILE RENAME "bytestream.h" FILES "E:/Project/myproject/MyApp/tools/protobuf-3.17.1/src/google/protobuf/stubs/bytestream.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xprotobuf-headersx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/google/protobuf/stubs" TYPE FILE RENAME "callback.h" FILES "E:/Project/myproject/MyApp/tools/protobuf-3.17.1/src/google/protobuf/stubs/callback.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xprotobuf-headersx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/google/protobuf/stubs" TYPE FILE RENAME "casts.h" FILES "E:/Project/myproject/MyApp/tools/protobuf-3.17.1/src/google/protobuf/stubs/casts.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xprotobuf-headersx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/google/protobuf/stubs" TYPE FILE RENAME "common.h" FILES "E:/Project/myproject/MyApp/tools/protobuf-3.17.1/src/google/protobuf/stubs/common.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xprotobuf-headersx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/google/protobuf/stubs" TYPE FILE RENAME "hash.h" FILES "E:/Project/myproject/MyApp/tools/protobuf-3.17.1/src/google/protobuf/stubs/hash.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xprotobuf-headersx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/google/protobuf/stubs" TYPE FILE RENAME "logging.h" FILES "E:/Project/myproject/MyApp/tools/protobuf-3.17.1/src/google/protobuf/stubs/logging.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xprotobuf-headersx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/google/protobuf/stubs" TYPE FILE RENAME "macros.h" FILES "E:/Project/myproject/MyApp/tools/protobuf-3.17.1/src/google/protobuf/stubs/macros.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xprotobuf-headersx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/google/protobuf/stubs" TYPE FILE RENAME "map_util.h" FILES "E:/Project/myproject/MyApp/tools/protobuf-3.17.1/src/google/protobuf/stubs/map_util.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xprotobuf-headersx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/google/protobuf/stubs" TYPE FILE RENAME "mutex.h" FILES "E:/Project/myproject/MyApp/tools/protobuf-3.17.1/src/google/protobuf/stubs/mutex.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xprotobuf-headersx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/google/protobuf/stubs" TYPE FILE RENAME "once.h" FILES "E:/Project/myproject/MyApp/tools/protobuf-3.17.1/src/google/protobuf/stubs/once.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xprotobuf-headersx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/google/protobuf/stubs" TYPE FILE RENAME "platform_macros.h" FILES "E:/Project/myproject/MyApp/tools/protobuf-3.17.1/src/google/protobuf/stubs/platform_macros.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xprotobuf-headersx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/google/protobuf/stubs" TYPE FILE RENAME "port.h" FILES "E:/Project/myproject/MyApp/tools/protobuf-3.17.1/src/google/protobuf/stubs/port.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xprotobuf-headersx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/google/protobuf/stubs" TYPE FILE RENAME "status.h" FILES "E:/Project/myproject/MyApp/tools/protobuf-3.17.1/src/google/protobuf/stubs/status.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xprotobuf-headersx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/google/protobuf/stubs" TYPE FILE RENAME "stl_util.h" FILES "E:/Project/myproject/MyApp/tools/protobuf-3.17.1/src/google/protobuf/stubs/stl_util.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xprotobuf-headersx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/google/protobuf/stubs" TYPE FILE RENAME "stringpiece.h" FILES "E:/Project/myproject/MyApp/tools/protobuf-3.17.1/src/google/protobuf/stubs/stringpiece.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xprotobuf-headersx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/google/protobuf/stubs" TYPE FILE RENAME "strutil.h" FILES "E:/Project/myproject/MyApp/tools/protobuf-3.17.1/src/google/protobuf/stubs/strutil.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xprotobuf-headersx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/google/protobuf/stubs" TYPE FILE RENAME "template_util.h" FILES "E:/Project/myproject/MyApp/tools/protobuf-3.17.1/src/google/protobuf/stubs/template_util.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xprotobuf-headersx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/google/protobuf" TYPE FILE RENAME "text_format.h" FILES "E:/Project/myproject/MyApp/tools/protobuf-3.17.1/src/google/protobuf/text_format.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xprotobuf-headersx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/google/protobuf" TYPE FILE RENAME "timestamp.pb.h" FILES "E:/Project/myproject/MyApp/tools/protobuf-3.17.1/src/google/protobuf/timestamp.pb.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xprotobuf-headersx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/google/protobuf" TYPE FILE RENAME "type.pb.h" FILES "E:/Project/myproject/MyApp/tools/protobuf-3.17.1/src/google/protobuf/type.pb.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xprotobuf-headersx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/google/protobuf" TYPE FILE RENAME "unknown_field_set.h" FILES "E:/Project/myproject/MyApp/tools/protobuf-3.17.1/src/google/protobuf/unknown_field_set.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xprotobuf-headersx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/google/protobuf/util" TYPE FILE RENAME "delimited_message_util.h" FILES "E:/Project/myproject/MyApp/tools/protobuf-3.17.1/src/google/protobuf/util/delimited_message_util.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xprotobuf-headersx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/google/protobuf/util" TYPE FILE RENAME "field_comparator.h" FILES "E:/Project/myproject/MyApp/tools/protobuf-3.17.1/src/google/protobuf/util/field_comparator.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xprotobuf-headersx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/google/protobuf/util" TYPE FILE RENAME "field_mask_util.h" FILES "E:/Project/myproject/MyApp/tools/protobuf-3.17.1/src/google/protobuf/util/field_mask_util.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xprotobuf-headersx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/google/protobuf/util" TYPE FILE RENAME "json_util.h" FILES "E:/Project/myproject/MyApp/tools/protobuf-3.17.1/src/google/protobuf/util/json_util.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xprotobuf-headersx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/google/protobuf/util" TYPE FILE RENAME "message_differencer.h" FILES "E:/Project/myproject/MyApp/tools/protobuf-3.17.1/src/google/protobuf/util/message_differencer.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xprotobuf-headersx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/google/protobuf/util" TYPE FILE RENAME "time_util.h" FILES "E:/Project/myproject/MyApp/tools/protobuf-3.17.1/src/google/protobuf/util/time_util.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xprotobuf-headersx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/google/protobuf/util" TYPE FILE RENAME "type_resolver.h" FILES "E:/Project/myproject/MyApp/tools/protobuf-3.17.1/src/google/protobuf/util/type_resolver.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xprotobuf-headersx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/google/protobuf/util" TYPE FILE RENAME "type_resolver_util.h" FILES "E:/Project/myproject/MyApp/tools/protobuf-3.17.1/src/google/protobuf/util/type_resolver_util.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xprotobuf-headersx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/google/protobuf" TYPE FILE RENAME "wire_format.h" FILES "E:/Project/myproject/MyApp/tools/protobuf-3.17.1/src/google/protobuf/wire_format.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xprotobuf-headersx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/google/protobuf" TYPE FILE RENAME "wire_format_lite.h" FILES "E:/Project/myproject/MyApp/tools/protobuf-3.17.1/src/google/protobuf/wire_format_lite.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xprotobuf-headersx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/google/protobuf" TYPE FILE RENAME "wrappers.pb.h" FILES "E:/Project/myproject/MyApp/tools/protobuf-3.17.1/src/google/protobuf/wrappers.pb.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xprotobuf-headersx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/google/protobuf" TYPE FILE RENAME "any.proto" FILES "E:/Project/myproject/MyApp/tools/protobuf-3.17.1/src/google/protobuf/any.proto")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xprotobuf-headersx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/google/protobuf" TYPE FILE RENAME "api.proto" FILES "E:/Project/myproject/MyApp/tools/protobuf-3.17.1/src/google/protobuf/api.proto")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xprotobuf-headersx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/google/protobuf/compiler" TYPE FILE RENAME "plugin.proto" FILES "E:/Project/myproject/MyApp/tools/protobuf-3.17.1/src/google/protobuf/compiler/plugin.proto")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xprotobuf-headersx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/google/protobuf" TYPE FILE RENAME "descriptor.proto" FILES "E:/Project/myproject/MyApp/tools/protobuf-3.17.1/src/google/protobuf/descriptor.proto")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xprotobuf-headersx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/google/protobuf" TYPE FILE RENAME "duration.proto" FILES "E:/Project/myproject/MyApp/tools/protobuf-3.17.1/src/google/protobuf/duration.proto")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xprotobuf-headersx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/google/protobuf" TYPE FILE RENAME "empty.proto" FILES "E:/Project/myproject/MyApp/tools/protobuf-3.17.1/src/google/protobuf/empty.proto")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xprotobuf-headersx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/google/protobuf" TYPE FILE RENAME "field_mask.proto" FILES "E:/Project/myproject/MyApp/tools/protobuf-3.17.1/src/google/protobuf/field_mask.proto")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xprotobuf-headersx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/google/protobuf" TYPE FILE RENAME "source_context.proto" FILES "E:/Project/myproject/MyApp/tools/protobuf-3.17.1/src/google/protobuf/source_context.proto")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xprotobuf-headersx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/google/protobuf" TYPE FILE RENAME "struct.proto" FILES "E:/Project/myproject/MyApp/tools/protobuf-3.17.1/src/google/protobuf/struct.proto")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xprotobuf-headersx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/google/protobuf" TYPE FILE RENAME "timestamp.proto" FILES "E:/Project/myproject/MyApp/tools/protobuf-3.17.1/src/google/protobuf/timestamp.proto")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xprotobuf-headersx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/google/protobuf" TYPE FILE RENAME "type.proto" FILES "E:/Project/myproject/MyApp/tools/protobuf-3.17.1/src/google/protobuf/type.proto")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xprotobuf-headersx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/google/protobuf" TYPE FILE RENAME "wrappers.proto" FILES "E:/Project/myproject/MyApp/tools/protobuf-3.17.1/src/google/protobuf/wrappers.proto")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xprotobuf-protosx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/google/protobuf" TYPE FILE RENAME "descriptor.proto" FILES "E:/Project/myproject/MyApp/tools/protobuf-3.17.1/src/google/protobuf/descriptor.proto")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xprotobuf-protosx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/google/protobuf" TYPE FILE RENAME "any.proto" FILES "E:/Project/myproject/MyApp/tools/protobuf-3.17.1/src/google/protobuf/any.proto")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xprotobuf-protosx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/google/protobuf" TYPE FILE RENAME "api.proto" FILES "E:/Project/myproject/MyApp/tools/protobuf-3.17.1/src/google/protobuf/api.proto")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xprotobuf-protosx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/google/protobuf" TYPE FILE RENAME "duration.proto" FILES "E:/Project/myproject/MyApp/tools/protobuf-3.17.1/src/google/protobuf/duration.proto")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xprotobuf-protosx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/google/protobuf" TYPE FILE RENAME "empty.proto" FILES "E:/Project/myproject/MyApp/tools/protobuf-3.17.1/src/google/protobuf/empty.proto")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xprotobuf-protosx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/google/protobuf" TYPE FILE RENAME "field_mask.proto" FILES "E:/Project/myproject/MyApp/tools/protobuf-3.17.1/src/google/protobuf/field_mask.proto")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xprotobuf-protosx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/google/protobuf" TYPE FILE RENAME "source_context.proto" FILES "E:/Project/myproject/MyApp/tools/protobuf-3.17.1/src/google/protobuf/source_context.proto")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xprotobuf-protosx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/google/protobuf" TYPE FILE RENAME "struct.proto" FILES "E:/Project/myproject/MyApp/tools/protobuf-3.17.1/src/google/protobuf/struct.proto")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xprotobuf-protosx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/google/protobuf" TYPE FILE RENAME "timestamp.proto" FILES "E:/Project/myproject/MyApp/tools/protobuf-3.17.1/src/google/protobuf/timestamp.proto")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xprotobuf-protosx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/google/protobuf" TYPE FILE RENAME "type.proto" FILES "E:/Project/myproject/MyApp/tools/protobuf-3.17.1/src/google/protobuf/type.proto")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xprotobuf-protosx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/google/protobuf" TYPE FILE RENAME "wrappers.proto" FILES "E:/Project/myproject/MyApp/tools/protobuf-3.17.1/src/google/protobuf/wrappers.proto")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xprotobuf-protosx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/google/protobuf/compiler" TYPE FILE RENAME "plugin.proto" FILES "E:/Project/myproject/MyApp/tools/protobuf-3.17.1/src/google/protobuf/compiler/plugin.proto")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xprotobuf-exportx" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/cmake/protobuf-targets.cmake")
    file(DIFFERENT EXPORT_FILE_CHANGED FILES
         "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/cmake/protobuf-targets.cmake"
         "E:/Project/myproject/MyApp/tools/protobuf-3.17.1/protocmake/CMakeFiles/Export/cmake/protobuf-targets.cmake")
    if(EXPORT_FILE_CHANGED)
      file(GLOB OLD_CONFIG_FILES "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/cmake/protobuf-targets-*.cmake")
      if(OLD_CONFIG_FILES)
        message(STATUS "Old export file \"$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/cmake/protobuf-targets.cmake\" will be replaced.  Removing files [${OLD_CONFIG_FILES}].")
        file(REMOVE ${OLD_CONFIG_FILES})
      endif()
    endif()
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/cmake" TYPE FILE FILES "E:/Project/myproject/MyApp/tools/protobuf-3.17.1/protocmake/CMakeFiles/Export/cmake/protobuf-targets.cmake")
  if("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/cmake" TYPE FILE FILES "E:/Project/myproject/MyApp/tools/protobuf-3.17.1/protocmake/CMakeFiles/Export/cmake/protobuf-targets-debug.cmake")
  endif()
  if("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Mm][Ii][Nn][Ss][Ii][Zz][Ee][Rr][Ee][Ll])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/cmake" TYPE FILE FILES "E:/Project/myproject/MyApp/tools/protobuf-3.17.1/protocmake/CMakeFiles/Export/cmake/protobuf-targets-minsizerel.cmake")
  endif()
  if("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Rr][Ee][Ll][Ww][Ii][Tt][Hh][Dd][Ee][Bb][Ii][Nn][Ff][Oo])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/cmake" TYPE FILE FILES "E:/Project/myproject/MyApp/tools/protobuf-3.17.1/protocmake/CMakeFiles/Export/cmake/protobuf-targets-relwithdebinfo.cmake")
  endif()
  if("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/cmake" TYPE FILE FILES "E:/Project/myproject/MyApp/tools/protobuf-3.17.1/protocmake/CMakeFiles/Export/cmake/protobuf-targets-release.cmake")
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xprotobuf-exportx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/cmake" TYPE DIRECTORY FILES "E:/Project/myproject/MyApp/tools/protobuf-3.17.1/protocmake/cmake/" REGEX "/protobuf\\-targets\\.cmake$" EXCLUDE)
endif()

if(CMAKE_INSTALL_COMPONENT)
  set(CMAKE_INSTALL_MANIFEST "install_manifest_${CMAKE_INSTALL_COMPONENT}.txt")
else()
  set(CMAKE_INSTALL_MANIFEST "install_manifest.txt")
endif()

string(REPLACE ";" "\n" CMAKE_INSTALL_MANIFEST_CONTENT
       "${CMAKE_INSTALL_MANIFEST_FILES}")
file(WRITE "E:/Project/myproject/MyApp/tools/protobuf-3.17.1/protocmake/${CMAKE_INSTALL_MANIFEST}"
     "${CMAKE_INSTALL_MANIFEST_CONTENT}")

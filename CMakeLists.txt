cmake_minimum_required( VERSION 3.7 )
project( the-forge )

# Compiler configurations
set(CXX_STANDARD 14)
set(CXX_STANDARD_REQUIRED ON)
set(CXX_EXTENSIONS OFF)

# configure the renderer
option( FORGE_RENDERER_DX11   "[FORGE] Renderer: Use DirectX 11" )
option( FORGE_RENDERER_DX12   "[FORGE] Renderer: Use DirectX 12" )
option( FORGE_RENDERER_METAL  "[FORGE] Renderer: Use Metal"      )
option( FORGE_RENDERER_VULKAN "[FORGE] Renderer: Use Vulkan"     )

# configure other features
option( FORGE_ENABLE_MATH_CHECKS        "[FORGE] Feature: Enable Math Checks"           )
option( FORGE_ENABLE_SCRIPTING          "[FORGE] Feature: Enable Lua Scripting"         )
option( FORGE_ENABLE_RELOAD_SHADER      "[FORGE] Feature: Enable Reload-Shader Server"  )
option( FORGE_ENABLE_UI                 "[FORGE] Feature: Enable UI"                    )
option( FORGE_ENABLE_FONTS              "[FORGE] Feature: Enable Fonts"                 )
option( FORGE_ENABLE_INPUT              "[FORGE] Feature: Enable Input"                 )
option( FORGE_ENABLE_MATERIALS          "[FORGE] Feature: Enable Materials"             )
option( FORGE_ENABLE_ZIP_FILESYSTEM     "[FORGE] Feature: Enable ZIP File System"       )
option( FORGE_ENABLE_ENABLE_SCREENSHOT  "[FORGE] Feature: Enable Screenshot"            )
option( FORGE_ENABLE_PROFILER           "[FORGE] Feature: Enable Profiler"              )
option( FORGE_ENABLE_MESHOPTIMIZER      "[FORGE] Feature: Enable Mesh Optimizer"        )

# configure debug features
option( FORGE_ENABLE_ANIMATION_DEBUG          "[FORGE] Debug: Enable Animation Debugging"               )
option( FORGE_ENABLE_GPU_ANIMATION_DEBUG      "[FORGE] Debug: Enable GPU Animation Debugging"           )
option( FORGE_ENABLE_THREAD_PERFORMANCE_STATS "[FORGE] Debug: Enable Thread Performance Stats"          )
option( FORGE_ENABLE_VMA_LOG                  "[FORGE] Debug: Enable Vulkan Memory Allocation Logging"  )

# setup helper directories
set( FORGE_DIR                            "${CMAKE_CURRENT_SOURCE_DIR}/Common_3"  )
set( FORGE_APP_DIR                        "${FORGE_DIR}/Application"              )
set( FORGE_FONT_DIR                       "${FORGE_APP_DIR}/Fonts"                )
set( FORGE_PROFILER_DIR                   "${FORGE_APP_DIR}/Profiler"             )
set( FORGE_GAME_DIR                       "${FORGE_DIR}/GAME"                     )
set( FORGE_SCRIPTING_DIR                  "${FORGE_GAME_DIR}/Scripting"           )
set( FORGE_GRAPHICS_DIR                   "${FORGE_DIR}/Graphics"                 )
set( FORGE_OS_DIR                         "${FORGE_DIR}/OS"                       )
set( FORGE_UI_DIR                         "${FORGE_APP_DIR}/UI"                   )
set( FORGE_RESOURCES_DIR                  "${FORGE_DIR}/Resources"                )
set( FORGE_RESOURCE_LOADER_DIR            "${FORGE_RESOURCES_DIR}/ResourceLoader" )
set( FORGE_TOOLS_DIR                      "${FORGE_DIR}/Tools"                    )
set( FORGE_UTILITIES_DIR                  "${FORGE_DIR}/Utilities"                )
set( FORGE_UTILITIES_FILE_SYSTEM_DIR      "${FORGE_UTILITIES_DIR}/FileSystem"     )
set( FORGE_UTILITIES_LOG_DIR              "${FORGE_UTILITIES_DIR}/Log"            )
set( FORGE_UTILITIES_MATH_DIR             "${FORGE_UTILITIES_DIR}/Math"           )
set( FORGE_UTILITIES_MEMORY_TRACKING_DIR  "${FORGE_UTILITIES_DIR}/MemoryTracking" )
set( FORGE_UTILITIES_THREADING_DIR        "${FORGE_UTILITIES_DIR}/Threading"      )

# setup third-party directories
set( FORGE_BSTRLIB_DIR            "${FORGE_UTILITIES_DIR}/ThirdParty/OpenSource/bstrlib"                )
set( FORGE_CPU_FEATURES_DIR       "${FORGE_OS_DIR}/ThirdParty/OpenSource/cpu_features/src"              )
set( FORGE_FONT_STASH_DIR         "${FORGE_APP_DIR}/ThirdParty/OpenSource/Fontstash/src"                )
set( FORGE_IMGUI_DIR              "${FORGE_APP_DIR}/ThirdParty/OpenSource/imgui"                        )
set( FORGE_LUA_DIR                "${FORGE_GAME_DIR}/ThirdParty/OpenSource/lua-5.3.5/src"               )
set( FORGE_LZ4_DIR                "${FORGE_UTILITIES_DIR}/ThirdParty/OpenSource/lz4"                    )
set( FORGE_SPIRV_DIR              "${FORGE_GRAPHICS_DIR}/ThirdParty/OpenSource/SPIRV_Cross"             )
set( FORGE_TINY_DDS_DIR           "${FORGE_RESOURCE_LOADER_DIR}/ThirdParty/OpenSource/tinydds"          )
set( FORGE_TINY_IMAGE_FORMAT_DIR  "${FORGE_RESOURCE_LOADER_DIR}/ThirdParty/OpenSource/tinyimageformat"  )
set( FORGE_TINY_KTX_DIR           "${FORGE_RESOURCE_LOADER_DIR}/ThirdParty/OpenSource/tinyktx"          )
set( FORGE_ZSTD_DIR               "${FORGE_UTILITIES_DIR}/ThirdParty/OpenSource/zstd"                   )

# determine running OS
# > WIN32 for Windows
# > APPLE for MacOS
# > LINUX for Linux operating system (this could be other unix based OS's too, but taking a guess that it's linux )
set( LINUX OFF )
if( UNIX AND NOT APPLE )
  set( LINUX ON )
endif()

# add custom config file instead of the default one found in "Application/Config.h"
include_directories( ${CMAKE_CURRENT_SOURCE_DIR} )
# add_compile_definitions( EXTERNAL_CONFIG_FILEPATH="../../Configs/CustomConfig.h" )

#glob the config files
file( GLOB FORGE_CONFIG_FILES "${CMAKE_CURRENT_SOURCE_DIR}/*.h" "${CMAKE_CURRENT_SOURCE_DIR}/Application/Config.h" )

# os specific files
if( WIN32 )
  file( GLOB FORGE_OS_FILES "${FORGE_OS_DIR}/Windows/*.h" "${FORGE_OS_DIR}/Windows/*.c" "${FORGE_OS_DIR}/Windows/*.cpp" )
endif()
if( LINUX )
  # not tested
  file( GLOB FORGE_OS_FILES "${FORGE_OS_DIR}/Linux/*.c" "${FORGE_OS_DIR}/Linux/*.cpp" "${FORGE_UTILITIES_FILE_SYSTEM_DIR}/UnixFileSystem.c" )
endif()

# renderer specific files
if( FORGE_RENDERER_DX11 )
  file( GLOB FORGE_GRAPHICS_RENDERER_FILES "${FORGE_GRAPHICS_DIR}/Direct3D11/*.*" )
endif()
if( FORGE_RENDERER_DX12 )
  file( GLOB FORGE_GRAPHICS_RENDERER_FILES "${FORGE_GRAPHICS_DIR}/Direct3D12/*.*" )
endif()
if( FORGE_RENDERER_METAL )
  file( GLOB FORGE_GRAPHICS_RENDERER_FILES "${FORGE_GRAPHICS_DIR}/Metal/*.*")
endif()
if( FORGE_RENDERER_VULKAN )
  file( GLOB FORGE_GRAPHICS_RENDERER_FILES "${FORGE_GRAPHICS_DIR}/Vulkan/*.*")
endif()

# set the feature/debug defines based on the options
if( FORGE_ENABLE_MATH_CHECKS )
  add_compile_definitions( ENABLE_MATH_CHECKS )
endif()
if( FORGE_ENABLE_SCRIPTING )
  add_compile_definitions( ENABLE_FORGE_SCRIPTING )
endif()
if( FORGE_ENABLE_RELOAD_SHADER )
  add_compile_definitions( ENABLE_FORGE_RELOAD_SHADER )
endif()
if( FORGE_ENABLE_UI )
  add_compile_definitions( ENABLE_FORGE_UI )
endif()
if( FORGE_ENABLE_FONTS )
  add_compile_definitions( ENABLE_FORGE_FONTS )
endif()
if( FORGE_ENABLE_INPUT )
  add_compile_definitions( ENABLE_FORGE_INPUT )
endif()
if( FORGE_ENABLE_MATERIALS )
  add_compile_definitions( ENABLE_FORGE_MATERIALS )
endif()
if( FORGE_ENABLE_ZIP_FILESYSTEM )
  add_compile_definitions( ENABLE_ZIP_FILESYSTEM )
endif()
if( FORGE_ENABLE_ENABLE_SCREENSHOT )
  add_compile_definitions( ENABLE_SCREENSHOT )
endif()
if( FORGE_ENABLE_PROFILER )
  add_compile_definitions( ENABLE_PROFILER )
endif()
if( FORGE_ENABLE_MESHOPTIMIZER )
  add_compile_definitions( ENABLE_MESHOPTIMIZER )
endif()
if( FORGE_ENABLE_ANIMATION_DEBUG )
  add_compile_definitions( ENABLE_FORGE_ANIMATION_DEBUG )
endif()
if( FORGE_ENABLE_GPU_ANIMATION_DEBUG )
  add_compile_definitions( ENABLE_FORGE_GPU_ANIMATION_DEBUG )
endif()
if( FORGE_ENABLE_THREAD_PERFORMANCE_STATS )
  add_compile_definitions( ENABLE_THREAD_PERFORMANCE_STATS )
endif()
if( FORGE_ENABLE_VMA_LOG )
  add_compile_definitions( ENABLE_VMA_LOG )
endif()

add_library( the-forge
    ${FORGE_CONFIG_FILES}
    ${FORGE_OS_FILES}
    ${FORGE_GRAPHICS_RENDERER_FILES}
    "${FORGE_APP_DIR}/CameraController.cpp"
    "${FORGE_APP_DIR}/InputSystem.cpp"
    "${FORGE_APP_DIR}/RemoteControl.cpp"
    "${FORGE_APP_DIR}/Screenshot.cpp"
    "${FORGE_FONT_DIR}/FontSystem.cpp"
    "${FORGE_FONT_DIR}/stbtt.cpp"
    "${FORGE_PROFILER_DIR}/GpuProfiler.cpp"
    "${FORGE_PROFILER_DIR}/ProfilerBase.cpp"
    "${FORGE_IMGUI_DIR}/imgui_demo.cpp"
    "${FORGE_IMGUI_DIR}/imgui_draw.cpp"
    "${FORGE_IMGUI_DIR}/imgui_tables.cpp"
    "${FORGE_IMGUI_DIR}/imgui_widgets.cpp"
    "${FORGE_IMGUI_DIR}/imgui.cpp"
    "${FORGE_UI_DIR}/UI.cpp"
    "${FORGE_SCRIPTING_DIR}/LuaManager.cpp"
    "${FORGE_SCRIPTING_DIR}/LuaManagerImpl.cpp"
    "${FORGE_SCRIPTING_DIR}/LuaSystem.cpp"
    "${FORGE_LUA_DIR}/lapi.c"
    "${FORGE_LUA_DIR}/lauxlib.c"
    "${FORGE_LUA_DIR}/lbaselib.c"
    "${FORGE_LUA_DIR}/lbitlib.c"
    "${FORGE_LUA_DIR}/lcode.c"
    "${FORGE_LUA_DIR}/lcorolib.c"
    "${FORGE_LUA_DIR}/lctype.c"
    "${FORGE_LUA_DIR}/ldblib.c"
    "${FORGE_LUA_DIR}/ldebug.c"
    "${FORGE_LUA_DIR}/ldo.c"
    "${FORGE_LUA_DIR}/ldump.c"
    "${FORGE_LUA_DIR}/lfunc.c"
    "${FORGE_LUA_DIR}/lgc.c"
    "${FORGE_LUA_DIR}/linit.c"
    "${FORGE_LUA_DIR}/liolib.c"
    "${FORGE_LUA_DIR}/llex.c"
    "${FORGE_LUA_DIR}/lmathlib.c"
    "${FORGE_LUA_DIR}/lmem.c"
    "${FORGE_LUA_DIR}/loadlib.c"
    "${FORGE_LUA_DIR}/lobject.c"
    "${FORGE_LUA_DIR}/lopcodes.c"
    "${FORGE_LUA_DIR}/loslib.c"
    "${FORGE_LUA_DIR}/lparser.c"
    "${FORGE_LUA_DIR}/lstate.c"
    "${FORGE_LUA_DIR}/lstring.c"
    "${FORGE_LUA_DIR}/lstrlib.c"
    "${FORGE_LUA_DIR}/ltable.c"
    "${FORGE_LUA_DIR}/ltablib.c"
    "${FORGE_LUA_DIR}/ltm.c"
    "${FORGE_LUA_DIR}/lundump.c"
    "${FORGE_LUA_DIR}/lutf8lib.c"
    "${FORGE_LUA_DIR}/lvm.c"
    "${FORGE_LUA_DIR}/lzio.c"
    "${FORGE_GRAPHICS_DIR}/CommonShaderReflection.cpp"
    "${FORGE_GRAPHICS_DIR}/GraphicsConfig.cpp"
    "${FORGE_GRAPHICS_DIR}/PickRenderingAPI.cpp"
    "${FORGE_SPIRV_DIR}/spirv_cfg.cpp"
    "${FORGE_SPIRV_DIR}/spirv_cpp.cpp"
    "${FORGE_SPIRV_DIR}/spirv_cross_parsed_ir.cpp"
    "${FORGE_SPIRV_DIR}/spirv_cross_util.cpp"
    "${FORGE_SPIRV_DIR}/spirv_cross.cpp"
    "${FORGE_SPIRV_DIR}/spirv_glsl.cpp"
    "${FORGE_SPIRV_DIR}/spirv_hlsl.cpp"
    "${FORGE_SPIRV_DIR}/spirv_msl.cpp"
    "${FORGE_SPIRV_DIR}/spirv_parser.cpp"
    "${FORGE_SPIRV_DIR}/spirv_reflect.cpp"
    "${FORGE_SPIRV_DIR}/SpirvTools.cpp"
    "${FORGE_OS_DIR}/CPUConfig.cpp"
    "${FORGE_OS_DIR}/WindowSystem/WindowSystem.cpp"
    "${FORGE_RESOURCE_LOADER_DIR}/ResourceLoader.cpp"
    "${FORGE_TOOLS_DIR}/Network/Network.c"
    "${FORGE_TOOLS_DIR}/ReloadServer/ReloadClient.cpp"
    "${FORGE_UTILITIES_DIR}/Timer.c"
    "${FORGE_UTILITIES_FILE_SYSTEM_DIR}/FileSystem.c"
    "${FORGE_UTILITIES_FILE_SYSTEM_DIR}/SystemRun.c"
    "${FORGE_UTILITIES_LOG_DIR}/Log.c"
    "${FORGE_UTILITIES_MATH_DIR}/Algorithms.c"
    "${FORGE_UTILITIES_MATH_DIR}/StbDs.c"
    "${FORGE_UTILITIES_MEMORY_TRACKING_DIR}/MemoryTracking.c"
    "${FORGE_BSTRLIB_DIR}/bstrlib.c"
    "${FORGE_LZ4_DIR}/lz4.c"
    "${FORGE_LZ4_DIR}/lz4.h"
    "${FORGE_LZ4_DIR}/lz4hc.c"
    "${FORGE_LZ4_DIR}/lz4hc.h"
    "${FORGE_ZSTD_DIR}/common/bits.h"
    "${FORGE_ZSTD_DIR}/common/bitstream.h"
    "${FORGE_ZSTD_DIR}/common/compiler.h"
    "${FORGE_ZSTD_DIR}/common/cpu.h"
    "${FORGE_ZSTD_DIR}/common/debug.c"
    "${FORGE_ZSTD_DIR}/common/debug.h"
    "${FORGE_ZSTD_DIR}/common/entropy_common.c"
    "${FORGE_ZSTD_DIR}/common/error_private.c"
    "${FORGE_ZSTD_DIR}/common/error_private.h"
    "${FORGE_ZSTD_DIR}/common/fse_decompress.c"
    "${FORGE_ZSTD_DIR}/common/fse.h"
    "${FORGE_ZSTD_DIR}/common/huf.h"
    "${FORGE_ZSTD_DIR}/common/mem.h"
    "${FORGE_ZSTD_DIR}/common/pool.c"
    "${FORGE_ZSTD_DIR}/common/pool.h"
    "${FORGE_ZSTD_DIR}/common/portability_macros.h"
    "${FORGE_ZSTD_DIR}/common/threading.c"
    "${FORGE_ZSTD_DIR}/common/threading.h"
    "${FORGE_ZSTD_DIR}/common/xxhash.c"
    "${FORGE_ZSTD_DIR}/common/xxhash.h"
    "${FORGE_ZSTD_DIR}/common/zstd_common.c"
    "${FORGE_ZSTD_DIR}/common/zstd_deps.h"
    "${FORGE_ZSTD_DIR}/common/zstd_internal.h"
    "${FORGE_ZSTD_DIR}/common/zstd_trace.h"
    "${FORGE_ZSTD_DIR}/decompress/huf_decompress_amd64.S"
    "${FORGE_ZSTD_DIR}/decompress/huf_decompress.c"
    "${FORGE_ZSTD_DIR}/decompress/zstd_ddict.c"
    "${FORGE_ZSTD_DIR}/decompress/zstd_ddict.h"
    "${FORGE_ZSTD_DIR}/decompress/zstd_decompress_block.c"
    "${FORGE_ZSTD_DIR}/decompress/zstd_decompress_block.h"
    "${FORGE_ZSTD_DIR}/decompress/zstd_decompress_internal.h"
    "${FORGE_ZSTD_DIR}/decompress/zstd_decompress.c"
)

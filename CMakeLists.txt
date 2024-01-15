# CMakeのバージョン指定
cmake_minimum_required(VERSION 3.5)

#プロジェクトの指定と言語の指定
project(fdtd1d_main LANGUAGES C)

# Ninjaでdebugする
set(CMAKE_BUILD_TYPE,"Debug")

# Debugの設定
set(CMAKE_C_FLAGS_DEBUG "-g")

# 変数 excitation_mode を設定
# set(excitation_mode "gaussian" CACHE STRING "Excitation mode: gaussian or sin")
set(excitation_mode "sin" CACHE STRING "Excitation mode: gaussian or sin")

# excitation_mode に応じてサブディレクトリと実行ファイルを追加
if(excitation_mode STREQUAL "gaussian")
    add_subdirectory(./fdtd1d_gaussian)
    add_executable(main main_1d_gaussian.c)
    target_link_libraries(main fdtd1d_lib_gaussian)

elseif(excitation_mode STREQUAL "sin")
    add_subdirectory(./fdtd1d_sinwave)
    add_executable(main main_1d_sinwave.c)
    target_link_libraries(main fdtd1d_lib_sinwave)
    set(angular_frequency_num "759")

else()
    message("Invalid excitation_mode specified. Use 'gaussian' or 'sin'.")
endif()

# # sub directoryの指定
# add_subdirectory(./fdtd1d_gaussian)
# # targer名をmainに指定する。
# add_executable(main main_1d_gaussian.c)

# sub directoryのprojectをtarget projectに付加

# コンパイルオプションの指定
target_compile_options(main PRIVATE -Wall -Wextra)
target_compile_options(main PRIVATE -O2)
target_compile_options(main PRIVATE -std=gnu99)

# ビルドの高速化
target_compile_options(main PRIVATE -pipe)

# 自動的にそのアーキテクチャにそったオプションをつける
target_compile_options(main PRIVATE -march=native)

# ループの展開を行う。
target_compile_options(main PRIVATE -funroll-loops)

# 計算をメモリ上ではなくCPUのレジスタにコピーして行うようにする
target_compile_options(main PRIVATE -fforce-addr)

# CPUの拡張命令セットを使うようにする
target_compile_options(main PRIVATE -msse -msse2 -msse3)
target_compile_options(main PRIVATE -m3dnow)
target_compile_options(main PRIVATE -mfpmath=sse)

# open mp用
target_compile_options(main PRIVATE -fopenmp)

# math.hを使用するためのライブラリのリンク
target_link_libraries(main m)

message("angular_frequency_num=" ${angular_frequency_num})

# カスタムターゲットの定義
add_custom_target(run_main
    COMMAND $<TARGET_FILE:main> ${angular_frequency_num}
    DEPENDS main
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
)

# エイリアスの定義,make runで実行できる
add_custom_target(run ALL DEPENDS run_main)

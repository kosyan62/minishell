cmake_minimum_required(VERSION 3.28)
project(. C)

set(CMAKE_C_STANDARD 11)

add_custom_target(libft
    COMMAND make -C includes/libft/libft
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    COMMENT "Building libft"
)

include_directories(
        includes/libft/libft/includes
        includes
)

link_libraries(includes/libft/libft.a)

add_executable(minishell
        includes/mshheader.h
        src/command.c
        src/env_commands.c
        src/env_extra_funct.c
        src/env_funct.c
        src/env_tmp_funct.c
        src/errors.c
        src/extension.c
        src/general_bultins.c
        src/main.c
        src/minishell.c
        src/readline.c)

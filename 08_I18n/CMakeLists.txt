cmake_minimum_required(VERSION 3.10)
project(guess_number)

# Настройка каталогов для локализации
set(LOCALE_PATH "${CMAKE_SOURCE_DIR}/locales")

# Добавление пути к локализации
add_definitions(-DLOCALE_PATH=\"${LOCALE_PATH}\")

# Добавление основного исполняемого файла
add_executable(guess_number src/main.c)

# Подключение gettext для перевода
find_package(Gettext REQUIRED)
add_custom_command(TARGET guess_number POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E make_directory ${LOCALE_PATH}/ru/LC_MESSAGES
    COMMAND msgfmt -o ${LOCALE_PATH}/ru/LC_MESSAGES/guess_number.mo ${LOCALE_PATH}/ru/LC_MESSAGES/guess_number.po
    COMMENT "Compiling translations"
)
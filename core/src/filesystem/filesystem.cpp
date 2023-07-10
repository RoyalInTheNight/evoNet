//
// Created by MikoG on 07.07.2023.
//
#include "../../include/filesystem/filesystem.h"

core_types::size_t Filesystem::filesystem::file_size(const fs::path &path) {
    std::ifstream file(path, std::ios_base::binary);

    if (file.fail()) {
        last_fs_errno = core_fs::fs_errno::fs_file_open_errno;
        call_filesystem_exception(last_fs_errno);
    }

    std::streampos size = file.tellg();
    file.seekg(0, std::ios_base::end);

    size = file.tellg() - size;

    file.close();

    last_fs_errno = core_fs::fs_errno::fs_file_ok;

    return size;
}

core_pointer::string_t Filesystem::filesystem::read_file(const fs::path &path) {
    core_types::size_t size = file_size(path);

    std::ifstream file(path, std::ios_base::binary);

    if (file.fail()) {
        last_fs_errno = core_fs::fs_errno::fs_file_open_errno;
        call_filesystem_exception(last_fs_errno);
    }

    core_pointer::string_t data = new core_types::int8_t[size];

    file.read(data, size);
    file.close();

    last_fs_errno = core_fs::fs_errno::fs_file_ok;

    return data;
}

core_types::void_t Filesystem::filesystem::write_file(const fs::path &path, core_pointer::string_t data) {
    std::ofstream file(path, std::ios_base::binary);

    if (file.is_open()) {
        std::string data_buffer = data;

        file.write(data_buffer.c_str(), data_buffer.size());
        file.close();

        last_fs_errno = core_fs::fs_errno::fs_file_ok;
    }

    else {
        last_fs_errno = core_fs::fs_errno::fs_file_open_errno;
        call_filesystem_exception(last_fs_errno);
    }
}

core_types::void_t Filesystem::filesystem::create_dir(const fs::path &path) {
    core_types::bit result = fs::create_directory(path);

    if (!result) {
        last_fs_errno = core_fs::fs_errno::fs_create_dir_errno;
        call_filesystem_exception(last_fs_errno);
    }

    last_fs_errno = core_fs::fs_errno::fs_file_ok;
}

core_types::void_t Filesystem::filesystem::remove_dir(const fs::path &path) {
    core_types::bit result = fs::remove(path);

    if (!result) {
        last_fs_errno = core_fs::fs_errno::fs_remove_dir_errno;
        call_filesystem_exception(last_fs_errno);
    }

    last_fs_errno = core_fs::fs_errno::fs_file_ok;
}

core_types::void_t Filesystem::filesystem::remove_file(const fs::path &path) {
    remove_dir(path);
}

core_types::void_t Filesystem::filesystem::copy_file(const fs::path &path_from,
                                                     const fs::path &path_to) {
    core_types::bit result = fs::copy_file(path_from, path_to);

    if (!result) {
        last_fs_errno = core_fs::fs_errno::fs_copy_file_errno;
        call_filesystem_exception(last_fs_errno);
    }

    last_fs_errno = core_fs::fs_errno::fs_file_ok;
}

core_types::void_t Filesystem::filesystem::move_file(const fs::path &path_from, const fs::path &path_to) {
    copy_file(path_from, path_to);

    remove_file(path_from);
}

core_types::void_t Filesystem::filesystem::call_filesystem_exception(core_types::u_int32_t last_errno) {
    switch (last_errno) {
        default:
            throw std::runtime_error("debug");
    }
}
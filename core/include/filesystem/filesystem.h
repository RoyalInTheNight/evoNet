//
// Created by MikoG on 07.07.2023.
//

#ifndef EVO_FILESYSTEM_H
#define EVO_FILESYSTEM_H

#include <filesystem>
#include <stdexcept>
#include <fstream>
#include <string>
#include "../core.h"

namespace fs           = std::filesystem;
namespace core_types   = core;
namespace core_pointer = core::pointer_types;
namespace core_fs      = core::filesystem;
//using json = nlohmann::json;

namespace Filesystem {
    class filesystem {
    private:
        core_types::u_int32_t last_fs_errno;

    public:
        core_types::size_t file_size(const fs::path &);
        core_types::void_t write_file(const fs::path &, core_pointer::string_t);
        core_pointer::string_t read_file(const fs::path &);
        // static json read_json(const fs::path&);
        // static json write_json(const fs::path&, json&);

        core_types::void_t create_dir(const fs::path &);
        core_types::void_t remove_dir(const fs::path &);
        core_types::void_t remove_file(const fs::path &);
        core_types::void_t copy_file(const fs::path &, const fs::path &);
        core_types::void_t move_file(const fs::path &, const fs::path &);
        core_types::void_t call_filesystem_exception(core_types::u_int32_t);
    };
}

#endif //EVO_FILESYSTEM_H

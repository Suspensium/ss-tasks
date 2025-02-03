#pragma once

#include <filesystem>
#include <forward_list>
#include <set>
#include <thread>

namespace fs = std::filesystem;

class CodeReader {
public:
    CodeReader() {
        fileType = fs::file_type::directory;
        path = PROJECT_ROOT_DIR;

        read();
    }

    explicit CodeReader(const fs::path &inPath, const fs::file_type type, const bool bAbsolutePath = false) {
        fileType = type;

        switch (fileType) {
            case fs::file_type::regular:
                if (!bAbsolutePath) {
                    path = PROJECT_ROOT_DIR;
                    path += "/";
                }
                path += inPath;
                if (!fs::exists(path) || !fs::is_regular_file(path)) {
                    throw std::runtime_error("File is not valid");
                }
                break;
            case fs::file_type::directory:
                if (!bAbsolutePath) {
                    path = PROJECT_ROOT_DIR;
                    path += "/";
                }
                path += inPath;
                if (!fs::exists(path) || !fs::is_directory(path)) {
                    throw std::runtime_error("Directory is not valid");
                }
                break;
            default:
                throw std::invalid_argument("File type not supported");
        }

        read();
    }

    void read();

    void joinThreads() {
        for (std::jthread &thread: threads) {
            thread.join();
        }
    }

    uint64_t outputInfo(std::ostream &os) const;

private:
    bool readFile(fs::path filePath);

    struct {
        std::atomic<size_t> totalProcessedFiles{};
        std::atomic<size_t> blankLines{};
        std::atomic<size_t> commentLines{};
        std::atomic<size_t> codeLines{};
        uint64_t totalTime{};
    } results;

    fs::path path;

    inline static std::set<fs::path> codeFileExtensions{".h", ".hpp", ".c", ".cpp"};

    std::forward_list<std::jthread> threads;

    fs::file_type fileType;
};

void run_task3();

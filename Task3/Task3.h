#pragma once

#include <cassert>
#include <filesystem>
#include <queue>
#include <set>
#include <thread>

namespace fs = std::filesystem;

class CodeReader {
public:
    CodeReader() {
        fileType = fs::file_type::directory;
        directoryPath = PROJECT_ROOT_DIR;

        read();
    }

    explicit CodeReader(const fs::path &inPath, const fs::file_type type, const bool bAbsolutePath = false) {
        fileType = type;

        switch (fileType) {
            case fs::file_type::regular:
                if (!bAbsolutePath) {
                    filePath = PROJECT_ROOT_DIR;
                    filePath += "/";
                }
                filePath += inPath;
                if (!fs::exists(filePath) || !fs::is_regular_file(filePath)) {
                    throw std::runtime_error("File is not valid");
                }
                break;
            case fs::file_type::directory:
                if (!bAbsolutePath) {
                    directoryPath = PROJECT_ROOT_DIR;
                    directoryPath += "/";
                }
                directoryPath += inPath;
                if (!fs::exists(directoryPath) || !fs::is_directory(directoryPath)) {
                    throw std::runtime_error("Directory is not valid");
                }
                break;
            default:
                throw std::invalid_argument("File type not supported");
        }

        read();
    }

    ~CodeReader() {
        switch (fileType) {
            case fs::file_type::directory:
                directoryPath.~path();
                break;
            case fs::file_type::regular:
                filePath.~path();
                break;
            default:
                break;
        }
    }

    void read();

    void joinThreads() {
        for (std::jthread &thread: threads) {
            thread.join();
        }
    }

    uint64_t outputInfo(std::ostream &os) const;

private:
    void readFile(fs::path filePath);

    struct {
        std::atomic<size_t> totalProcessedFiles{};
        std::atomic<size_t> blankLines{};
        std::atomic<size_t> commentLines{};
        std::atomic<size_t> codeLines{};
        uint64_t totalTime{};
    } results;

    union {
        fs::path directoryPath{};
        fs::path filePath;
    };

    inline static std::set<fs::path> codeFileExtensions{".h", ".hpp", ".c", ".cpp"};

    std::deque<std::jthread> threads;

    fs::file_type fileType;
};

void run_task3();

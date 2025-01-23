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
        directoryPath = fs::current_path().parent_path();

        read();
    }

    explicit CodeReader(const fs::path &inPath, const fs::file_type type) {
        fileType = type;

        switch (fileType) {
            case fs::file_type::regular:
                filePath = inPath;
                break;
            case fs::file_type::directory:
                directoryPath = inPath;
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

    std::forward_list<std::jthread> threads;

    fs::file_type fileType;
};

void run_task3();

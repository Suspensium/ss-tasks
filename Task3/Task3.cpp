#include "Task3.h"

#include <iostream>
#include <fstream>

// Remove whitespaces from the start of the string
void trimWhitespaces(std::string &line) {
    if (line.empty()) return;

    line.erase(
        line.begin(),
        std::ranges::find_if(line, [](unsigned char c) { return !std::isspace(c); })
    );
}

void CodeReader::readFile(const fs::path filePath) {
    std::ifstream file{filePath, std::ios::in};

    if (!file.is_open()) {
        std::cerr << "Error opening file " << filePath << std::endl;
        return;
    }

    // For multi-lined comments
    bool bInComment = false;
    std::string line;
    while (std::getline(file, line, '\n')) {
        trimWhitespaces(line);

        if (line.empty()) {
            bInComment ? ++results.commentLines : ++results.blankLines;
            continue;
        }

        if (line.starts_with("//")) {
            ++results.commentLines;
        } else if (line.starts_with("/*")) {
            ++results.commentLines;
            bInComment = true;
        } else if (line.ends_with("*/")) {
            ++results.commentLines;
            bInComment = false;
        } else {
            bInComment ? ++results.commentLines : ++results.codeLines;
        }
    }

    file.close();

    ++results.totalProcessedFiles;
}

void CodeReader::read() {
    using rdir_iter = fs::recursive_directory_iterator;

    const auto start = std::chrono::high_resolution_clock::now();

    if (fileType == fs::file_type::directory) {
        for (auto it = rdir_iter{directoryPath}; it != rdir_iter{}; ++it) {
            const fs::directory_entry &entry = *it;

            if (!entry.is_regular_file()) continue;

            if (codeFileExtensions.contains(entry.path().extension())) {
                threads.emplace_front(&CodeReader::readFile, this, entry.path());
            }
        }
    } else {
        if (exists(filePath)) {
            threads.emplace_front(&CodeReader::readFile, this, filePath);
        }
    }

    joinThreads();

    const auto end = std::chrono::high_resolution_clock::now();
    const auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

    results.totalTime += duration.count();
}

uint64_t CodeReader::outputInfo(std::ostream &os) const {
    os <<
            "Total processed files: " << results.totalProcessedFiles.load() << '\n' <<
            "Blank lines: " << results.blankLines.load() << '\n' <<
            "Comment lines: " << results.commentLines.load() << '\n' <<
            "Code lines: " << results.codeLines.load() << '\n' <<
            "Total time taken: " << results.totalTime << " ms.\n";

    return results.totalTime;
}

void run_task3() {
    constexpr size_t iterations = 1;

    std::ofstream ofstream;
    uint64_t resultSum{};

    for (size_t i = 0; i < iterations; ++i) {
        std::cout << "Iteration: " << i + 1 << "\n\n";

        CodeReader reader{};
        reader.outputInfo(std::cout);
        ofstream.open("Output.txt", std::ios::out);
        resultSum += reader.outputInfo(ofstream);
        ofstream.close();

        std::cout << "\n" << std::endl;
    }

    std::cout << "Medium time result: " << resultSum / iterations << " ms." << std::endl;

    ofstream.open("Output.txt", std::ios::app);
    ofstream << '\n' << "Medium time result: " << resultSum / iterations << " ms.";
    ofstream.close();
}

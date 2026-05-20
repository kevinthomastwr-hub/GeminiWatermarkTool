/**
 * @file    image_io.hpp
 * @brief   Image encoder helpers with Unicode-safe file writing.
 * @author  AllenK (Kwyshell)
 * @license MIT
 */

#pragma once

#include <opencv2/core.hpp>
#include <cstddef>
#include <filesystem>
#include <vector>

namespace gwt {

/**
 * Encode a BGR cv::Mat to PNG bytes using OpenCV's encoder.
 */
std::vector<unsigned char> encode_png(
    const cv::Mat& image,
    int compression_level = 3
);

/**
 * Encode and write a PNG file. Uses std::ofstream with the
 * std::filesystem::path overload, which goes through the wide-char
 * Win32 file APIs on Windows -- so non-ASCII paths work on every
 * Windows version, independent of the active code page or any
 * UTF-8 ACP manifest setting. cv::imwrite() would route the path
 * through the system ACP and fail on non-ASCII characters on older
 * Windows.
 */
bool write_png(
    const std::filesystem::path& path,
    const cv::Mat& image,
    int compression_level = 3
);

}  // namespace gwt

/**
 * @file    image_io.cpp
 * @brief   Image encoding helpers.
 * @author  AllenK (Kwyshell)
 * @license MIT
 */

#include "image_io.hpp"

#include <opencv2/imgcodecs.hpp>

#include <fstream>

namespace gwt {

std::vector<unsigned char> encode_png(
    const cv::Mat& image,
    int compression_level)
{
    std::vector<unsigned char> png;
    const std::vector<int> params = { cv::IMWRITE_PNG_COMPRESSION, compression_level };
    if (!cv::imencode(".png", image, png, params)) {
        return {};
    }
    return png;
}

bool write_png(
    const std::filesystem::path& path,
    const cv::Mat& image,
    int compression_level)
{
    std::vector<unsigned char> bytes = encode_png(image, compression_level);
    if (bytes.empty()) return false;

    std::ofstream out(path, std::ios::binary | std::ios::trunc);
    if (!out) return false;
    out.write(reinterpret_cast<const char*>(bytes.data()),
              static_cast<std::streamsize>(bytes.size()));
    return out.good();
}

}  // namespace gwt

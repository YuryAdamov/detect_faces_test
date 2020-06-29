#ifndef DETECTOR_H_
#define DETECTOR_H_

#include <memory>
#include <vector>
#include <utility>
#include <string>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/objdetect.hpp>
#include <opencv2/imgproc.hpp>

enum DetectError {
    DETECT_FACE_ERR_NONE = 0,
    DETECT_FACE_NO_CASCADE=1,
    DETECT_FACE_BAD_IMAGE=2,
    DETECT_FACE_NO_FACES=3,
    DETECT_FACE_SECOND_READ_ERR=4
};


std::pair<DetectError,std::vector<cv::Rect>> detect_faces(std::string file_path);

#endif

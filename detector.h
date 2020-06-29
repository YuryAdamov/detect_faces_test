#ifndef DETECTOR_H_
#define DETECTOR_H_

#include <memory>
#include <vector>
#include <utility>
#include <string>
#include <sstream>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/objdetect.hpp>
#include <opencv2/imgproc.hpp>

enum DetectError 
{
    DETECT_FACE_ERR_NONE = 0,
    DETECT_FACE_NO_CASCADE=1,
    DETECT_FACE_BAD_IMAGE=2,
    DETECT_FACE_NO_FACES=3,
    DETECT_FACE_SECOND_READ_ERR=4,
    DETECT_FACE_NOT_INITIALIZED=255
};

struct DetectorResult
{
    DetectorResult():errorCode(DETECT_FACE_NOT_INITIALIZED),fileName(),faces(){}
    DetectorResult(DetectError error, std::vector<cv::Rect> faces, std::string file): errorCode(error),fileName(file),faces(faces){}
    DetectorResult(DetectError error, std::vector<cv::Rect> faces): errorCode(error),fileName(),faces(faces){}
    DetectorResult(DetectError error): errorCode(error),fileName(),faces(){}

    DetectError errorCode;
    std::string fileName;
    std::vector<cv::Rect> faces;
    std::string toJson(void);
};


DetectorResult detect_faces(std::string file_path);

#endif

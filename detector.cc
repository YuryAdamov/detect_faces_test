#include "detector.h"

std::unique_ptr<cv::CascadeClassifier> cascade_;

const double scaleFactor=2.0;

std::pair<DetectError,std::vector<cv::Rect>> detect_faces(std::string file_path)
{
    cv::Mat image,processed_image,processed_image2;
    std::vector<cv::Rect> result;
    image = cv::imread(file_path,cv::IMREAD_GRAYSCALE);
    if(image.empty())
    {
        return std::make_pair(DETECT_FACE_BAD_IMAGE,result);
    }
    if(cascade_ == NULL)
    {
        cascade_ = std::make_unique<cv::CascadeClassifier>();
        if(!cascade_->load("haarcascade_frontalface_alt.xml"))
        {
            cascade_ = NULL;
            return std::make_pair(DETECT_FACE_NO_CASCADE,result);
        }
    }
    cascade_->detectMultiScale(image,result,1.1,2,cv::CASCADE_SCALE_IMAGE,cv::Size(30,30));

    image = cv::imread(file_path,cv::IMREAD_COLOR);

    if(image.empty())
    {
        return std::make_pair(DETECT_FACE_SECOND_READ_ERR,result);
    }

    cv::resize(image,processed_image,cv::Size(),1/scaleFactor,1/scaleFactor,cv::INTER_LINEAR);
    for(auto &rect: result)
    {
        cv::Rect new_rect;
        new_rect.x=rect.x/scaleFactor;
        new_rect.y=rect.y/scaleFactor;
        new_rect.height = rect.height/scaleFactor;
        new_rect.width=rect.width/scaleFactor;
       
        cv::blur(processed_image(new_rect),processed_image(new_rect),cv::Size(new_rect.height/10,new_rect.height/10));
    }

    cv::imwrite(file_path+"_processed.jpg",processed_image);

    return std::make_pair(DETECT_FACE_ERR_NONE,result);
}


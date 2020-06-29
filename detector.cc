#include "detector.h"
#include <boost/algorithm/string/join.hpp>

std::unique_ptr<cv::CascadeClassifier> cascade_;

const double scaleFactor=2.0;

DetectError initialize_haar_cascade(void)
{
    return initialize_haar_cascade("haarcascade_frontalface_alt.xml");
}

DetectError initialize_haar_cascade(const std::string &cascadePath)
{
    if(cascade_ == NULL)
    {
        cascade_ = std::make_unique<cv::CascadeClassifier>();
        if(!cascade_->load(cascadePath))
        {
            cascade_ = NULL;
            return DETECT_FACE_NO_CASCADE;
        }
    }
    return DETECT_FACE_ERR_NONE;
}

DetectorResult detect_faces(const std::string &file_path)
{
    cv::Mat image,processed_image;
    std::vector<cv::Rect> faces;

    image = cv::imread(file_path,cv::IMREAD_GRAYSCALE);
    if(image.empty())
    {
        return DetectorResult(DETECT_FACE_BAD_IMAGE);
    }

    initialize_haar_cascade();

    cascade_->detectMultiScale(image,faces,1.1,2,cv::CASCADE_SCALE_IMAGE,cv::Size(30,30));

    image = cv::imread(file_path,cv::IMREAD_COLOR);

    if(image.empty())
    {
        return DetectorResult(DETECT_FACE_SECOND_READ_ERR,faces);
    }

    cv::resize(image,processed_image,cv::Size(),1/scaleFactor,1/scaleFactor,cv::INTER_LINEAR);
    for(auto &rect: faces)
    {
        cv::Rect new_rect;
        new_rect.x=rect.x/scaleFactor;
        new_rect.y=rect.y/scaleFactor;
        new_rect.height = rect.height/scaleFactor;
        new_rect.width=rect.width/scaleFactor;
       
        cv::blur(processed_image(new_rect),processed_image(new_rect),cv::Size(new_rect.height/10,new_rect.height/10));
    }

    std::string newFilePath;
    newFilePath = file_path + "_processed.jpg";
    cv::imwrite(newFilePath,processed_image);

    return DetectorResult(DETECT_FACE_ERR_NONE,faces,newFilePath);
}

std::string jsonQuote(std::string s)
{
    std::ostringstream res;
    res<<'"';
    for (auto c=s.cbegin(); c != s.cend(); c++)
    {
        switch(*c)
        {
          case '"' : 
              res<<'\\'<<'"';
              break;
          case '\\' : 
              res << "\\\\";
              break;
          default:
              res<<*c;
        }
    }
    res<<'"';
    return res.str();

}

std::string DetectorResult::toJson(void)
{
    std::ostringstream resStr;
    if(errorCode == DETECT_FACE_ERR_NONE)
    {
        resStr<<"{"<<"filename:"<<jsonQuote(fileName)<<","<<"faces: [";
        std::vector<std::string> faces_strings;
        faces_strings.reserve(faces.size());
        for(auto &face : faces)
        {
            std::ostringstream givenFace;
            givenFace<<"{ tl_x:"<<face.x
                <<",tl_y:"<<face.y
                <<",width:"<<face.width
                <<",height:"<<face.height<<"}";
            faces_strings.push_back(givenFace.str());
        }
        resStr<<boost::join(faces_strings,", ");
        resStr<<"]}";
    }
    else
    {
        resStr<<"{"<<"error:"<<errorCode<<"}";
    }
    return resStr.str();


}

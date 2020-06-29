#include "gtest/gtest.h"
#include "detector.h"
#include "testconf.h"


TEST(Minimal_Test,test_detect_one_face)
{
    std::pair<DetectError,std::vector<cv::Rect>> faces;
    faces=detect_faces("../test_images/images-000.png"); 
    ASSERT_EQ(faces.first,DETECT_FACE_ERR_NONE);
    EXPECT_EQ(faces.second.size(),9);
}


int main(int argc, char *argv[])
{
    ::testing::InitGoogleTest(&argc,argv);
    return RUN_ALL_TESTS();
}

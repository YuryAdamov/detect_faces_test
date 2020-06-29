#include "gtest/gtest.h"
#include "detector.h"
#include "testconf.h"


TEST(Minimal_Test,test_detect_multiple_face)
{
    DetectorResult faces;
    faces=detect_faces("../test_images/images-000.png"); 
    ASSERT_EQ(faces.errorCode,DETECT_FACE_ERR_NONE);
    EXPECT_EQ(faces.faces.size(),9);
}


int main(int argc, char *argv[])
{
    ::testing::InitGoogleTest(&argc,argv);
    return RUN_ALL_TESTS();
}

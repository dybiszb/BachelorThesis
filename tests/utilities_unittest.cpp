#include "gtest/gtest.h"

class UtilitiesTest : public ::testing::Test {
protected:
//    Settings settings = utils::readFromINI("../config.ini");
//    CGLFWRenderer* renderer;

    UtilitiesTest() {
//        renderer = new CGLFWRenderer(settings);
    }

    virtual ~UtilitiesTest() {
//        delete renderer;
    }

    virtual void SetUp() {
    }

    virtual void TearDown() {
    }


};

// Test case must be called the class above
// Also note: use TEST_F instead of TEST to access the test fixture (from google test primer)
TEST_F(UtilitiesTest, MethodBarDoesAbc) {
    int i = 1;
    EXPECT_EQ(1, i);
}
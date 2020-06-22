#include <gtest/gtest.h>
#include "iNOBEngine.h"

TEST(FileUtilsTest, GetFileToStringGetsFile) {
	std::string text = 
		R"(ひらがなと漢字
English Text as Well
Ænd Nårwegian)";
	FileUtils::WriteStringToFile("THIS_IS_A_TEST_TEXT_FILE", text);
	std::string retText = FileUtils::GetFileToString("THIS_IS_A_TEST_TEXT_FILE");
	ASSERT_EQ(text, retText);
}
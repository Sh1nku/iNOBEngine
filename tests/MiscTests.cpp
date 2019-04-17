#include <gtest/gtest.h>
#include "iNOBEngine.h"

TEST(MiscTests, FailLoadTexture) {
	std::string file = "THIS_FILE_SHOULD_NOT_EXIST.png";
	Texture* tex = Texture::LoadTexture( file );
	ASSERT_EQ(tex->GetWidth(), 2);
}
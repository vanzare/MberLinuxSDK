#include "gtest/gtest.h"
#include "mber.h"

#include <vector>

TEST(Base64Test, HandlesNullInput)
{
	ASSERT_EQ(0, Base64Encode(NULL, 4, NULL, 8));
}

TEST(Base64Test, CorrectlyEncodesInput)
{
	const char* const input = "Base64 text to encode.";
	const int inputLength = (int)strlen(input);
	// Twice the input length is enough space for Base64 encoding.
	// Defaults to question marks since those aren't valid Base64 characters.
	std::vector<char> output(inputLength * 2, '?');
	Base64Encode(input, inputLength, output.data(), (int)output.size());
	ASSERT_STREQ("QmFzZTY0IHRleHQgdG8gZW5jb2RlLg==", output.data());
}

TEST(Base64Test, NullTerminatesOutput)
{
	const char* const input = "Base64 text to encode.";
	const int inputLength = (int)strlen(input);
	// Twice the input length is enough space for Base64 encoding.
	// Defaults to question marks since those aren't valid Base64 characters.
	std::vector<char> output(inputLength * 2, '?');
	const int result = Base64Encode(input, inputLength, output.data(), (int)output.size());
	ASSERT_EQ(result, strlen(output.data()));
}

TEST(Base64Test, DoesntChunkData)
{
	const char* const input = "This is a really, really long string that should get chunked with newlines and carriage returns inserted into the middle of it, which is a bad thing.";
	const int inputLength = (int)strlen(input);
	// Twice the input length is enough space for Base64 encoding.
	// Defaults to question marks since those aren't valid Base64 characters.
	std::vector<char> output(inputLength * 2, '?');
	Base64Encode(input, inputLength, output.data(), (int)output.size());
	ASSERT_STREQ("VGhpcyBpcyBhIHJlYWxseSwgcmVhbGx5IGxvbmcgc3RyaW5nIHRoYXQgc2hvdWxkIGdldCBjaHVua2VkIHdpdGggbmV3bGluZXMgYW5kIGNhcnJpYWdlIHJldHVybnMgaW5zZXJ0ZWQgaW50byB0aGUgbWlkZGxlIG9mIGl0LCB3aGljaCBpcyBhIGJhZCB0aGluZy4=", output.data());
}

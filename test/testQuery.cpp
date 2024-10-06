#include <gtest/gtest.h>
#include <iostream>
#include "src/query/queryProcessor.h"

TEST(QueryProcessorTest, TitleQueries) {
    const char* input = "title[love]"; 
    std::string expected = "SELECT * FROM rolas r WHERE (r.title LIKE '%love%');";
    std::string resultado = processQuery(input);
    EXPECT_EQ(expected, resultado);  

    input = "title[love|happy]";
    expected = "SELECT * FROM rolas r WHERE (r.title LIKE '%love%' OR r.title LIKE '%happy%');";
    resultado = processQuery(input);
    EXPECT_EQ(expected, resultado);

    input = "title[love&happy]";
    expected = "SELECT * FROM rolas r WHERE (r.title LIKE '%love%' AND r.title LIKE '%happy%');";
    resultado = processQuery(input);
    EXPECT_EQ(expected, resultado);
}

TEST(QueryProcessorTest, AlbumQueries) {
    const char* input = "album[a]"; 
    std::string expected = "SELECT * FROM rolas r JOIN albums a ON r.id_album = a.id_album WHERE (a.name LIKE '%a%');";
    std::string resultado = processQuery(input);
    EXPECT_EQ(expected, resultado);  

    input = "album[a|b]";
    expected = "SELECT * FROM rolas r JOIN albums a ON r.id_album = a.id_album WHERE (a.name LIKE '%a%' OR a.name LIKE '%b%');";
    resultado = processQuery(input);
    EXPECT_EQ(expected, resultado);

    input = "album[a&b]";
    expected = "SELECT * FROM rolas r JOIN albums a ON r.id_album = a.id_album WHERE (a.name LIKE '%a%' AND a.name LIKE '%b%');";
    resultado = processQuery(input);
    EXPECT_EQ(expected, resultado);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

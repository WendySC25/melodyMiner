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

TEST(QueryProcessorTest, PerformerQueries) {
    const char* input = "performer[John Doe]"; 
    std::string expected = "SELECT * FROM rolas r JOIN performers p ON r.id_performer = p.id_performer WHERE (p.name LIKE '%John Doe%');";
    std::string resultado = processQuery(input);
    EXPECT_EQ(expected, resultado);  

    input = "performer[fire|Jane Doe]";
    expected = "SELECT * FROM rolas r JOIN performers p ON r.id_performer = p.id_performer WHERE (p.name LIKE '%fire%' OR p.name LIKE '%Jane Doe%');";
    resultado = processQuery(input);
    EXPECT_EQ(expected, resultado);

    input = "performer[fire&Jane Doe]";
    expected = "SELECT * FROM rolas r JOIN performers p ON r.id_performer = p.id_performer WHERE (p.name LIKE '%fire%' AND p.name LIKE '%Jane Doe%');";
    resultado = processQuery(input);
    EXPECT_EQ(expected, resultado);
}

TEST(QueryProcessorTest, YearQueries) {
    const char* input = "year[2024]"; 
    std::string expected = "SELECT * FROM rolas r WHERE (r.year = 2024);";
    std::string resultado = processQuery(input);
    EXPECT_EQ(expected, resultado); 
}

TEST(QueryProcessorTest, CombinedQueries) {
    const char* input = "title[love], album[a], performer[John Doe], year[2022], genre[pop], track[1]"; 
    std::string expected = "SELECT * FROM rolas r JOIN albums a ON r.id_album = a.id_album "
                           "JOIN performers p ON r.id_performer = p.id_performer "
                           "WHERE (r.title LIKE '%love%') AND (a.name LIKE '%a%') AND "
                           "(p.name LIKE '%John Doe%') AND (r.year = 2022) AND "
                           "(r.genre LIKE '%pop%') AND (r.track = 1);";
    std::string resultado = processQuery(input);
    EXPECT_EQ(expected, resultado);  

    input = "title[love|happy], album[a|b], performer[John Doe|Jane Doe], year[2020|2021], genre[rock|pop], track[2&3]";
    expected = "SELECT * FROM rolas r JOIN albums a ON r.id_album = a.id_album "
               "JOIN performers p ON r.id_performer = p.id_performer "
               "WHERE (r.title LIKE '%love%' OR r.title LIKE '%happy%') AND "
               "(a.name LIKE '%a%' OR a.name LIKE '%b%') AND "
               "(p.name LIKE '%John Doe%' OR p.name LIKE '%Jane Doe%') AND "
               "(r.year = 2020 OR r.year = 2021) AND "
               "(r.genre LIKE '%rock%' OR r.genre LIKE '%pop%') AND "
               "(r.track = 2 AND r.track = 3);";
    resultado = processQuery(input);
    EXPECT_EQ(expected, resultado);

    input = "title[love&happy], album[a], performer[John Doe], year[2021], genre[pop]";
    expected = "SELECT * FROM rolas r JOIN albums a ON r.id_album = a.id_album "
               "JOIN performers p ON r.id_performer = p.id_performer "
               "WHERE (r.title LIKE '%love%' AND r.title LIKE '%happy%') AND "
               "(a.name LIKE '%a%') AND "
               "(p.name LIKE '%John Doe%') AND (r.year = 2021) AND "
               "(r.genre LIKE '%pop%');";
    resultado = processQuery(input);
    EXPECT_EQ(expected, resultado);
}



int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

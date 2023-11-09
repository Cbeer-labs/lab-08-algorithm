// Copyright 2023 Your Name <your_email>

#include <gtest/gtest.h>
#include "lab-08.hpp"
#include <vector>
#include <chrono>
#include <cstdint>

bool operator==(const Student& a, const Student& b)
{
    return a.Name == b.Name &&
        a.GroupId == b.GroupId &&
        a.Subjects == b.Subjects &&
        a.Ratings == b.Ratings;
}

bool operator==(const Group& a, const Group& b)
{
    return a.Id == b.Id &&
        a.Students == b.Students;
}

bool operator==(const UserRepr& lhs, const UserRepr& rhs) {
    return lhs.id == rhs.id &&
        lhs.name_encoded == rhs.name_encoded &&
        lhs.surname_encoded == rhs.surname_encoded &&
        lhs.date_of_birth == rhs.date_of_birth &&
        lhs.last_seen == rhs.last_seen;
}

bool operator==(const GroupUserRepr& lhs, const GroupUserRepr& rhs) {
    return lhs.name == rhs.name && lhs.members == rhs.members;
}

bool operator==(const StudentRepr& lhs, const StudentRepr& rhs) {
    return lhs.name == rhs.name && lhs.ratings ==rhs.ratings;
}

bool operator==(const Rating& lhs, const Rating& rhs) {
    return lhs.subject == rhs.subject && lhs.rating == rhs.rating;
}

class TestFirstPart : public ::testing::Test {
protected:
    void SetUp() {
    // TODO add empty ratings
        Ratings1 = { 3, 5, 4, 5, 5, 4 };
        Ratings2 = { 5, 5, 5, 5, 5, 5 };
        Ratings3 = { 3, 3, 3, 4, 3, 3 };
        Ratings4 = { 4, 4, 5, 4, 4, 4 };
        Ratings5 = { 4, 4, 5, 5, 5, 4 };
        Ratings6 = { 5, 5, 5, 5, 5, 5 };
        Ratings7 = { 3, 5, 3, 3, 5, 4 };
        Ratings8 = { 5, 4, 5, 4, 5, 4 };
        Ratings9 = { 5, 2, 5, 4, 5, 4 };
        Ratings10 = { 2, 2, 5, 4, 5, 4 };
        Subjects1 =
        { "Math", "Physics", "IT", "English", "Ecology", "Literature" };
        Subjects2 =
        { "Physics", "Russian", "Politology", "Biology", "History" };
        Subjects3 =
        { "IT", "English", "Math", "PE", "Electronic", "IT" };
        student1 = { "Asya", "iu8-34", Ratings2, Subjects1 }; // 30
        student2 = { "Romka", "iu8-34", Ratings6, Subjects1 }; // 30
        student3 = { "Petya", "iu9-54", Ratings1, Subjects3 }; // 26
        student4 = { "Vasya", "iu9-54", Ratings7, Subjects3 }; // 23
        student5 = { "Alice", "iu9-54", Ratings8, Subjects3 }; // 27
        student6 = { "Anton", "ibm3-12", Ratings3, Subjects2 }; // 19
        student7 = { "Robert", "ibm3-12", Ratings4, Subjects2 }; // 25
        student8 = { "Vanya", "ibm3-12", Ratings5, Subjects2 }; // 27
        student9 = { "Uma", "ibm3-12", Ratings9, Subjects2 }; // 25
        student10 = { "Inga", "ibm3-12", Ratings10, Subjects2 }; // 22
    }

public:
    std::vector<uint8_t> Ratings1;
    std::vector<uint8_t> Ratings2;
    std::vector<uint8_t> Ratings3;
    std::vector<uint8_t> Ratings4;
    std::vector<uint8_t> Ratings5;
    std::vector<uint8_t> Ratings6;
    std::vector<uint8_t> Ratings7;
    std::vector<uint8_t> Ratings8;
    std::vector<uint8_t> Ratings9;
    std::vector<uint8_t> Ratings10;
    std::vector<std::string> Subjects1;
    std::vector<std::string> Subjects2;
    std::vector<std::string> Subjects3;
    Student student1;
    Student student2;
    Student student3;
    Student student4;
    Student student5;
    Student student6;
    Student student7;
    Student student8;
    Student student9;
    Student student10;
};

class TestSecondPart : public ::testing::Test {
protected:
    void SetUp() {
        row1 = DatabaseRepr {
            0,
            "Asya\n\n",
            "Pipkin;",
            1100003267,
            1696544867,
            {{0, 1, 2, 3}},
        };
        row2 = DatabaseRepr {
            1,
            "Ro.mka",
            "Kilki31-n",
            1052144327,
            1672329647,
            {{3, 2, 2, 1}},
        };
        row3 = DatabaseRepr {
            2,
            "Pe\\t=ya",
            "Pu\389021pkin",
            1104984047,
            1672329647,
            {{3, 1, 2, 1}},
        };
        row4 = DatabaseRepr {
            3,
            "Vasya\n\n\n\n\n\t\n\1\2",
            "Vasilyev\1\2\3",
            1103273891,
            1672321233,
            {{3, 5, 2, 9}},
        };
        row5 = DatabaseRepr {
            4,
            "Alice\\",
            "Sh",
            1103254324,
            1673349021,
            {{0, 2, 0, 1}},
        };
        row6 = DatabaseRepr {
            5,
            "A,./,./nton",
            "Bul-=``kin",
            1104327911,
            1672980423,
            {{34, 2, 23, 1}},
        };
        row7 = DatabaseRepr {
            6,
            "Rob\\.\7\6\4\3ert",
            "Tr12345678ebor",
            1104290138,
            1672490812,
            {{59, 23, 1}},
        };
        row8 = DatabaseRepr {
            7,
            "Van\n\r\n,,,ya",
            "Iv-=`-`anov",
            1104738911,
            1672329647,
            {{3, 2}},
        };
        row9 = DatabaseRepr {
            8,
            "Uma",
            "Umkin",
            1104984047,
            1672329647,
            {{3, 2, 2, 1}},
        };
        row10 = DatabaseRepr {
            9,
            "Inga",
            "Ignatova",
            1104289301,
            1672279136,
            {},
        };
        result1 = UserRepr {
            0,
            "Asya",
            "Pipkin",
            timepoint_t(std::chrono::seconds(1100003267)),
            timepoint_t(std::chrono::seconds(1696544867)),
        };
        result2 = UserRepr {
            1,
            "Romka",
            "Kilkin",
            timepoint_t(std::chrono::seconds(1052144327)),
            timepoint_t(std::chrono::seconds(1672329647)),
        };
        result3 = UserRepr {
            2,
            "Petya",
            "Pupkin",
            timepoint_t(std::chrono::seconds(1104984047)),
            timepoint_t(std::chrono::seconds(1672329647)),
        };
        result4 = UserRepr {
            3,
            "Vasya",
            "Vasilyev",
            timepoint_t(std::chrono::seconds(1103273891)),
            timepoint_t(std::chrono::seconds(1672321233)),
        };
        result5 = UserRepr {
            4,
            "Alice",
            "Sh",
            timepoint_t(std::chrono::seconds(1103254324)),
            timepoint_t(std::chrono::seconds(1673349021)),
        };
        result6 = UserRepr {
            5,
            "Anton",
            "Bulkin",
            timepoint_t(std::chrono::seconds(1104327911)),
            timepoint_t(std::chrono::seconds(1672980423)),
        };
        result7 = UserRepr {
            6,
            "Robert",
            "Trebor",
            timepoint_t(std::chrono::seconds(1104290138)),
            timepoint_t(std::chrono::seconds(1672490812)),
        };
        result8 = UserRepr {
            7,
            "Vanya",
            "Ivanov",
            timepoint_t(std::chrono::seconds(1104738911)),
            timepoint_t(std::chrono::seconds(1672329647)),
        };
        result9 = UserRepr {
            8,
            "Uma",
            "Umkin",
            timepoint_t(std::chrono::seconds(1104984047)),
            timepoint_t(std::chrono::seconds(1672329647)),
        };
        result10 = UserRepr {
            9,
            "Inga",
            "Ignatova",
            timepoint_t(std::chrono::seconds(1104289301)),
            timepoint_t(std::chrono::seconds(1672279136)),
        };
    }
public:
    DatabaseRepr row1;
    DatabaseRepr row2;
    DatabaseRepr row3;
    DatabaseRepr row4;
    DatabaseRepr row5;
    DatabaseRepr row6;
    DatabaseRepr row7;
    DatabaseRepr row8;
    DatabaseRepr row9;
    DatabaseRepr row10;
    UserRepr result1;
    UserRepr result2;
    UserRepr result3;
    UserRepr result4;
    UserRepr result5;
    UserRepr result6;
    UserRepr result7;
    UserRepr result8;
    UserRepr result9;
    UserRepr result10;
};

class TestThirdPart : public ::testing::Test {
protected:
    void SetUp() {
        db_stud1 = { 0, "Asya" };
        db_stud2 = { 1, "Romka" };
        db_stud3 = { 2, "Petya" };
        db_stud4 = { 3, "Vasya" };
        db_rate1 = { 0, 0, "Math", 5 };
        db_rate2 = { 1, 1, "Math", 4 };
        db_rate3 = { 2, 2, "Math", 3 };
        db_rate4 = { 3, 3, "Math", 4 };
        db_rate5 = { 4, 2, "Philosophy", 2 };
        db_rate6 = { 5, 1, "Programming", 5 };
        db_group1 = { 0, "iu8-13" };
        db_group2 = { 1, "iu8-14" };
        db_group_stud1 = { 0, 0 };
        db_group_stud2 = { 1, 1 };
        db_group_stud3 = { 2, 0 };
        db_group_stud4 = { 3, 1 };
        db_group_stud5 = { 4, 0 };
    }
public:
    StudentDatabaseRepr db_stud1;
    StudentDatabaseRepr db_stud2;
    StudentDatabaseRepr db_stud3;
    StudentDatabaseRepr db_stud4;
    StudentRatingsDatabaseRepr db_rate1;
    StudentRatingsDatabaseRepr db_rate2;
    StudentRatingsDatabaseRepr db_rate3;
    StudentRatingsDatabaseRepr db_rate4;
    StudentRatingsDatabaseRepr db_rate5;
    StudentRatingsDatabaseRepr db_rate6;
    GroupsDatabaseRepr db_group1;
    GroupsDatabaseRepr db_group2;
    GroupsStudentsBinding db_group_stud1;
    GroupsStudentsBinding db_group_stud2;
    GroupsStudentsBinding db_group_stud3;
    GroupsStudentsBinding db_group_stud4;
    GroupsStudentsBinding db_group_stud5;
};

// Сортировка студентов по именам
TEST_F(TestFirstPart, SortByName) {
    // базовый сценарий
    std::vector<Student> students =
    { student1, student2, student3, student4,
    student5, student6, student7, student8 };
    std::vector<Student> result =
    { student5, student6, student1, student3, 
    student7, student2, student8, student4, };
    SortByName(students);
    EXPECT_EQ(students, result);
    // пустой вектор
    students = { };
    result = { };
    SortByName(students);
    EXPECT_EQ(students, result);
    // вектор, состоящий из имен, начинающихся на одну букву
    students = { student1, student6, student5 };
    result = { student5, student6, student1 };
    SortByName(students);
    EXPECT_EQ(students, result);
    // вектор из одного элемента
    students = { student4 };
    result = { student4 };
    SortByName(students);
    EXPECT_EQ(students, result);
}

// Сортировка всех студентов по средней оценке
TEST_F(TestFirstPart, SortByRating) {
    // базовый сценарий
    std::vector<Student> students =
    { student1, student2, student3, student4, student5,
    student6, student7, student8 };
    std::vector<Student> result =
    { student1, student2, student5, student8,
    student3, student7, student4, student6 };
    SortByRating(students);
    EXPECT_EQ(students, result);
    // вектор, состоящий из ребят с одинаковым рейтингом
    students = { student8, student5 };
    result = { student8, student5 };
    SortByRating(students);
    EXPECT_EQ(students, result);
    // вектор из одного элемента
    students = { student4 };
    result = { student4 };
    SortByRating(students);
    EXPECT_EQ(students, result);
    // пустой вектор
    students = { };
    result = { };
    SortByRating(students);
    EXPECT_EQ(students, result);
}

// Возвращаем двоечников
TEST_F(TestFirstPart, FilterTwoness) {
    // базовый сценарий
    std::vector<Student> students =
    { student1, student2, student3, student4, student5,
    student6, student7, student8, student9, student10 };
    auto filtered = FilterTwoness(students);
    std::vector<Student> expected = { student9, student10 };
    EXPECT_EQ(filtered, expected);
    // без двоечников
    students =
    { student1, student2, student3, student4,
    student5, student6, student7, student8 };
    filtered = FilterTwoness(students);
    expected = {};
    EXPECT_EQ(filtered, expected);
    // вектор с одним элементом
    students = { student9 };
    filtered = FilterTwoness(students);
    expected = { student9 };
    EXPECT_EQ(filtered, expected);
    // пустой вектор
    students = { };
    filtered = FilterTwoness(students);
    expected = {};
    EXPECT_EQ(filtered, expected);
}

// Количество отличников
TEST_F(TestFirstPart, FilterExcellent) {
    // базовый сценарий
    std::vector<Student> students =
    { student1, student2, student3, student4, student5,
    student6, student7, student8, student9, student10 };
    auto filtered = FilterExcellent(students);
    std::vector<Student> expected = { student1, student2 };
    EXPECT_EQ(filtered, expected);
    // без отличников
    students =
    { student9, student10, student3, student4,
    student5, student6, student7, student8 };
    filtered = FilterExcellent(students);
    expected = {};
    EXPECT_EQ(filtered, expected);
    // вектор с одним элементом
    students = { student1 };
    filtered = FilterExcellent(students);
    expected = { student1 };
    EXPECT_EQ(filtered, expected);
    // пустой вектор
    students = { };
    filtered = FilterExcellent(students);
    expected = {};
    EXPECT_EQ(filtered, expected);
}

// массив структур Group
TEST_F(TestFirstPart, Groups) {
    // базовый сценарий
    std::vector<Student> students =
    { student1, student2, student3, student4, student5,
    student6, student7, student8, student9, student10 };
    std::vector<Student> students1group = { student1, student2 };
    std::vector<Student> students2group = { student3, student4, student5 };
    std::vector<Student> students3group = { student6, student7, student8,
    student9, student10 };
    Group group1 = { "iu8-34", students1group };
    Group group2 = { "iu9-54", students2group };
    Group group3 = { "ibm3-12", students3group };
    std::vector<Group> expected = { group1, group2, group3 };
    auto result = Groups(students);
    EXPECT_EQ(result, expected);
    // все из одной группы
    students = { student3, student4, student5 };
    students2group = { student3, student4, student5 };
    group2 = { "iu9-54", students2group };
    expected = { group2 };
    result = Groups(students);
    EXPECT_EQ(result, expected);
    // вектор с одним элементом
    students = { student1 };
    students1group = { student1 };
    group1 = { "iu8-34", students1group };
    expected = { group1 };
    result = Groups(students);
    EXPECT_EQ(result, expected);
    // пустой вектор
    students = { };
    expected = { };
    result = Groups(students);
    EXPECT_EQ(result, expected);
}

TEST_F(TestSecondPart, MapStructs) {
    // general case
    std::vector<DatabaseRepr> usersInDatabase = {
        row1, row2, row3, row4, row5, row6, row7, row8, row9, row10
    };
    std::vector<UserRepr> expected = {
        result1, result2, result3, result4, result5, result6, result7,
        result8, result9, result10
    };
    std::vector<UserRepr> result = userRepresent(usersInDatabase.cbegin(),
                                                    usersInDatabase.cend());
    EXPECT_EQ(expected, result);
    // empty
    usersInDatabase = {};
    expected = {};
    result = userRepresent(usersInDatabase.cbegin(), usersInDatabase.cend());
    EXPECT_EQ(expected, result);
}

TEST_F(TestThirdPart, ArrangeRange) {
    std::vector<GroupUserRepr> result = GroupsRequestAssemble(
        { db_stud1, db_stud2, db_stud3, db_stud4 },
        { db_rate1, db_rate2, db_rate3, db_rate4, db_rate5, db_rate6 },
        { db_group1, db_group2 },
        { db_group_stud1, db_group_stud2, db_group_stud3, db_group_stud4 }
        );
    std::vector<GroupUserRepr> expected = {
      {
        "iu8-13",
        {
          {
            "Asya",
            {{"Math", 5}}
          },
          {
            "Petya",
            {{"Math", 3}, {"Philosophy", 2}}
          }
        }
      },
      {
        "iu8-14",
        {
          {
            "Romka",
            {{"Math", 4}, {"Programming", 5}}
          },
          {
            "Vasya",
            {{"Math", 4}}
          }
        }
      }
    };
    EXPECT_EQ(expected, result);
}

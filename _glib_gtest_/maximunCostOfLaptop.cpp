#include <bits/stdc++.h>
#include <glib-2.0/glib.h>
#include <glib-2.0/glib/gvariant.h>
#include <gtest/gtest.h>

using namespace std;
int maxCost(vector<int> cost, vector<string> labels, int dailyCount) {
    int len = cost.size();
    int max_cost {0};
    int count = 0;
    int temp_cost {0};
    for (int idx = 0; idx < len;) {
        temp_cost += cost[idx];
        if (labels[idx] == "legal") {
            count++;
        }
        
        if (count == dailyCount) {
            if (max_cost < temp_cost) {
                max_cost = temp_cost;
                std::cout << "max_cost: " << max_cost << std::endl;
            }
            count = 0;
            temp_cost = 0;
        }
        
        idx++;
    }
    
    return max_cost;
}

TEST(BASIC_MOCK_TEST, MAXIMUNCOST) {
    EXPECT_EQ(
        maxCost({5,2,1,3,0,1}, {"illegal", "legal", "legal","legal","legal","legal"}, 2),
        8
    );

    EXPECT_EQ(
        maxCost({2,1,1,5,6,1}, {"illegal", "legal", "legal","legal","legal","legal"}, 2),
        11
    );
}


int number_of_string(const std::string& text) {
    int ret = 0;
    for(int i = 0; i < text.size(); i++) {
        ret += static_cast<int>(text[i]);
    }
    return ret;
}

int compare_string(const std::string& text, const std::string& cmptext) {
    auto len = text.length();
    if (len != cmptext.length()) {
        return len > cmptext.length() ? 1 : -1;
    }

    auto i = 0;
    while (i < len) {
        if (text[i] != cmptext[i]) {
            return (int)text[i] > (int)cmptext[i] ? 1 : -1;
        }
        ++i;
    }
    return 0;
}


TEST(GLIB_TEST, STRING_COMPERATION) {
    EXPECT_EQ(
        compare_string("value", "lavue"), 
        1
    );
    EXPECT_EQ(
        compare_string("value", "value"), 
        0
    );
    EXPECT_EQ(
        compare_string("lalue", "value"), 
        -1
    );
}

int main() {
    testing::InitGoogleTest();
    return RUN_ALL_TESTS();
}
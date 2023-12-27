#include "Logger.h"
#include "SQLManagement.h"

// class Module {
//     public:
//         void trace() {
//             WLOG_INF("Hello World!");
//         }

//     private:
//         WLOG_DEF("Module");  
// };

#define FILE_DB "./tpn.db"

int main(int argc, char** argv) {
    // Module module_;
    // module_.trace();
    BackendLib::SQLAccessor *accessor = BackendLib::SQLAccessor::getInstance(FILE_DB);

    accessor->create_table("CREATE TABLE IF NOT EXISTS DemoTable("
        "NameId INTEGER PRIMARY KEY AUTOINCREMENT,"
        "NAME VARCHAR(255) NOT NULL"
    ");");
    accessor->execute_sql_commands("INSERT INTO DemoTable(NAME) VALUES (\"John\");");
    accessor->execute_sql_commands("INSERT INTO DemoTable(NAME) VALUES (\"Lyna\");");
    accessor->execute_sql_commands("INSERT INTO DemoTable(NAME) VALUES (\"Hanny\");");
    
    accessor->execute_sql_commands("SELECT * FROM DemoTable LIMIT 1", true);
    accessor->execute_sql_commands("SELECT * FROM DemoTable");

    if (accessor) {
        accessor = nullptr;
    }
    return 0;
}
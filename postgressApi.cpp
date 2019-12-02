#include <iostream>
#include <pqxx/pqxx>
#include <thread>
#include <chrono>

//g++ -std=c++17 postgressApi.cpp libpqxx.a -lpq
int main(int, char *argv[])
{
    //pqxx::connection c("postgres://localhost?host=localhost&port=5432&user=felipe&password=felipe/PETGYN");
    pqxx::connection c("postgres://felipe:felipe@localhost:5432/petgyn");
    
    try{
        pqxx::work txn(c);

    // Query the DB using txn.exec().
    // Here, we expect exactly one result row, so we use
    // exec1() instead.  It returns a row instead of a full
    // result.
    // If we don't get exactly one row, it will throw an
    // exception.
    /*pqxx::row r = txn.exec1(
        "SELECT id "
        "FROM Employee "
        "WHERE name =" +
        txn.quote(argv[1]));
    */
        
        pqxx::result r = txn.exec(
            "SELECT id,equation,description "
            " FROM \"TimeFunctions\" "
        );

        for (const auto &row : r){
            for (const auto &field : row){
                std::cout << field.c_str() << '\t';
            }
            std::cout << std::endl;
        }
    }
    catch (const std::exception &e)
    {
        std::cout << e.what() <<std::endl;
    }
    
    pqxx::work txn(c);

    std::cout << c.is_open() << std::endl;
    txn.exec0(
        "UPDATE \"TimeFunctions\" "
        "SET description = 'Fabricio' "
        "WHERE id = 2"
    );

    txn.commit();
  
    /*std::this_thread::sleep_for(std::chrono::milliseconds(200));
    pqxx::work txn3(c);

    r = txn3.exec(
        "SELECT id,equation,description "
        " FROM \"TimeFunctions\" "
        );

    
    for (const auto &row : r)
    {
        for (const auto &field : row)
            std::cout << field.c_str() << '\t';
        std::cout << std::endl;
    }
    */
    // We can address the first field in the row as r[0].
    // The column's name would also work, but be less
    // efficient: r["id"].
    // The field's as<type>() method converts the field's
    // string value to a type of our choice.
    //int employee_id = r[0].as<int>();

    //std::cout << "Updating employee #" << r[0] << std::endl;

    // Update the employee's salary.
    // Here we use exec0() to say that we expect an empty
    // result.  If the result does contain data, it will
    // throw an exception.
    /*txn.exec0(
        "UPDATE EMPLOYEE "
        "SET salary = salary + 1 "
        "WHERE id = " +
        txn.quote(employee_id));
    */
    // Make our change definite.
    //txn.commit();

    //std::cout<<c.is_open()<<std::endl;

}
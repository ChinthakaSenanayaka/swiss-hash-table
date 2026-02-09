using System;

namespace cs
{
    class Program
    {
        static void Main(string[] args)
        {
           TestInsert testInsert = new TestInsert();
           testInsert.testStart();

           TestSearch testSearch = new TestSearch();
           testSearch.testStart();

           TestDelete testDelete = new TestDelete();
           testDelete.testStart();
        }
    }
}
